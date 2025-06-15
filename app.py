from flask import Flask, render_template, jsonify, request
import serial
import tensorflow as tf
import numpy as np
from collections import deque

app = Flask(__name__)

model = tf.keras.models.load_model("sepsis_lstm_model.keras")
history = deque(maxlen=20)

user_data = {
    "age": 30,
    "gender": "Mężczyzna",
    "spo2": 0.0,
    "hr": 0.0,
    "temp": 0.0,
    "gsr": 0.0,
    "probability": 0.0,
    "status": "Oczekiwanie na dane...",
    "samples": 0,
}

# Licznik błędnych pomiarów SpO₂
spo2_fail_count = 0
MAX_SPO2_FAILS = 5  # po tylu błędach podstawiamy 90

def collect_data():
    global spo2_fail_count
    data = {}
    lines = []

    try:
        with serial.Serial("COM7", 9600, timeout=4) as ser:
            for _ in range(10):
                line = ser.readline().decode().strip()
                if line:
                    lines.append(line)
    except Exception as e:
        print(f"Serial error: {e}")
        return None

    for line in lines:
        try:
            if "SpO2:" in line:
                spo2_val = float(line.split("SpO2:")[1].split("%")[0].strip())
                hr_val = float(line.split("HR:")[1].split("bpm")[0].strip())
                temp_val = float(line.split("Temp:")[1].split("°C")[0].strip())

                # ----------- filtr błędnych wartości SpO2 --------------
                if spo2_val == -1:
                    spo2_fail_count += 1
                    print(f"Błędny odczyt SpO2 ({spo2_fail_count}/5)")
                    if spo2_fail_count < MAX_SPO2_FAILS:
                        continue  # pomijamy odczyt
                    else:
                        # przy 5-tym razie: podstawiamy 90
                        spo2_val = 90.0
                        print("Podstawiamy wartość 90 dla SpO2")
                else:
                    spo2_fail_count = 0  # reset przy poprawnym odczycie
                

                data["spo2"] = spo2_val
                data["hr"] = hr_val
                data["temp"] = temp_val

            elif "GSR" in line:
                data["gsr"] = float(line.split(":")[1].strip())
        except Exception as e:
            print(f"Błąd parsowania: {e}")
            continue

    return data if "spo2" in data and "gsr" in data else None



@app.route('/')
def index():
    return render_template('index.html', data=user_data)

def generate_alerts(data, history):
    alerts = []

    if len(history) < 5:
        return alerts  

    # Bierzemy ostatnie 5 próbek
    recent = list(history)[-5:]
    recent = np.array(recent)

    # Indeksy:
    # 0: SpO2, 1: HR, 2: Temp, 3: GSR, 4: age, 5: gender
    temps = recent[:, 2]
    spo2s = recent[:, 0]
    hrs = recent[:, 1]
    gsrs = recent[:, 3]

    # Temperatura
    if np.all(temps > 38.0):
        alerts.append("Utrzymująca się gorączka")
    elif np.all(temps > 37.1):
        alerts.append("Wystąpił stan podgorączkowy")

    # SpO2
    if np.mean(spo2s) < 90:
        alerts.append("Bardzo niska wartość natlenienia - zalecane skontaktowanie się z lekarzem!")
    elif np.any(spo2s < 94):
        alerts.append("Możliwe niedotlenienie")

    # HR
    if np.all(hrs > 100):
        alerts.append("Wystąpiło podwyższone tętno")
    elif np.all(hrs < 60):
        alerts.append("Bradykardia – tętno poniżej 60 bpm")

    # GSR 
    if np.mean(gsrs) > 600:  
        alerts.append("Wysoka aktywność skóry – możliwe pobudzenie lub stres organizmu")
        
        
    #tarczyca    
    if np.mean(hrs) < 60 and np.mean(temps) < 36 and np.mean(gsrs) > 1000:
        alerts.append("Podejrzenie niedoczynności tarczycy")

    #covid
    if np.mean(temps) > 38 and np.mean(spo2s) < 85:
        alerts.append("Podejrzenie choroby - covid")
    return alerts


@app.route('/update', methods=['GET'])
def update():
    global history
    age = request.args.get("age", type=int, default=user_data["age"])
    gender = request.args.get("gender", default=user_data["gender"])
    user_data["age"] = age
    user_data["gender"] = gender

    data = collect_data()
    if data:
        user_data.update(data)
        sample = [
            user_data["spo2"], user_data["hr"], user_data["temp"], user_data["gsr"],
            user_data["age"], 1 if user_data["gender"] == "Mężczyzna" else 0
        ]
        history.append(sample)
        user_data["samples"] = len(history)
        user_data["status"] = "Dane pobrane."
        user_data["alerts"] = generate_alerts(user_data, history)

    else:
        user_data["status"] = "❌ Nie udało się pobrać danych."
        user_data["alerts"] = []

    return jsonify(user_data)




@app.route('/predict', methods=['GET'])
def predict():
    if len(history) == 20:
        X = np.array([list(history)], dtype=np.float32)
        probability = float(model.predict(X)[0][0]) * 100
        user_data["probability"] = round(probability, 2)
        user_data["status"] = "✅ Predykcja wykonana!"
    else:
        user_data["status"] = f"⚠️ Za mało danych ({len(history)}/20)"
    return jsonify(user_data)


if __name__ == "__main__":
    app.run(debug=True)
