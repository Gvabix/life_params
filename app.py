from flask import Flask, render_template, jsonify, request
import serial
import tensorflow as tf
import numpy as np
from collections import deque
import pandas as pd

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
    "ecg": 0.0,
    "probability": 0.0,
    "status": "Oczekiwanie na dane...",
    "samples": 0,
}


def collect_data():
    data = {}
    lines = []
    try:
        with serial.Serial("/dev/cu.usbmodem14101", 9600, timeout=4) as ser:
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
                data["spo2"] = float(line.split("SpO2:")[1].split("%")[0].strip())
                data["hr"] = float(line.split("HR:")[1].split("bpm")[0].strip())
                data["temp"] = float(line.split("Temp:")[1].split("°C")[0].strip())
            elif "GSR" in line:
                data["gsr"] = float(line.split(":")[1].strip())
            elif "ECG SPI Raw" in line:
                data["ecg"] = float(line.split(":")[1].strip())
        except Exception as e:
            print(f"Błąd parsowania: {e}")
            continue

    return data if "spo2" in data and "gsr" in data else None


@app.route('/')
def index():
    return render_template('index.html', data=user_data)


@app.route('/update', methods=['GET'])
def update():
    global history
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
    else:
        user_data["status"] = "❌ Nie udało się pobrać danych."

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
