from taipy.gui import Gui, State
import serial
import tensorflow as tf
import numpy as np
from collections import deque
import pandas as pd


# Wczytaj model
model = tf.keras.models.load_model("sepsis_lstm_model.keras")
history = deque(maxlen=20)

# Zmienne GUI
age = 30
gender = "Mężczyzna"
spo2 = hr = temp = gsr = probability = 0.0
status = "Oczekiwanie na dane..."
samples = 0
chart_data = []


# Funkcja odczytu danych z portu COM
def collect_data():
    data = {}
    lines = []
    try:
        with serial.Serial("COM3", 9600, timeout=4) as ser:
            for _ in range(10):
                line = ser.readline().decode().strip()
                if line:
                    lines.append(line)
                    print(f"Odebrana linia: {line}")
    except Exception as e:
        print(f"Serial error: {e}")
        return None

    for line in lines:
        if "SpO2:" in line:
            try:
                data["spo2"] = float(line.split("SpO2:")[1].split("%")[0].strip())
                data["hr"] = float(line.split("HR:")[1].split("bpm")[0].strip())
                data["temp"] = float(line.split("Temp:")[1].split("°C")[0].strip())
            except Exception as e:
                print(f"Błąd parsowania SpO2/HR/Temp: {e}")
        elif "GSR" in line:
            try:
                data["gsr"] = float(line.split(":")[1].strip())
            except Exception as e:
                print(f"Błąd parsowania GSR: {e}")
    return data if "spo2" in data and "gsr" in data else None

# Obsługa przycisku "Pobierz dane"
def update_data(state: State):
    global history
    data = collect_data()
    if data:
        state.spo2 = data["spo2"]
        state.hr = data["hr"]
        state.temp = data["temp"]
        state.gsr = data["gsr"]
        state.status = "Dane pobrane."

        sample = [
            state.spo2, state.hr, state.temp, state.gsr,
            state.age, 1 if state.gender == "Mężczyzna" else 0
        ]
        history.append(sample)
        state.chart_data = pd.DataFrame(
            [{"nr": i+1, "SpO2": h[0], "HR": h[1], "Temp": h[2], "GSR": h[3]} for i, h in enumerate(history)]
        )


        state.samples = len(history)
        print(f"Dodano próbkę #{len(history)}")
    else:
        state.status = "❌ Nie udało się pobrać danych."

# Obsługa przycisku "Przewiduj sepsę"
def predict_sepsis(state: State):
    if len(history) == 20:
        X = np.array([list(history)], dtype=np.float32)
        state.probability = float(model.predict(X)[0][0]) * 100
        state.status = f"✅ Predykcja wykonana!"
        print(f"Predykcja: {state.probability:.2f}%")
    else:
        state.status = f"⚠️ Za mało danych ({len(history)}/20)"

    state.chart_data = pd.DataFrame(
        [{"nr": i+1, "SpO2": h[0], "HR": h[1], "Temp": h[2], "GSR": h[3]} for i, h in enumerate(history)]
    )


# GUI layout
page = """
# Sepsis Monitor

Wiek: <|{age}|number|>
Płeć: <|{gender}|selector|lov=Mężczyzna;Kobieta|>

<|Pobierz dane z Arduino|button|on_action=update_data|>
<|Przewiduj sepsę|button|on_action=predict_sepsis|>

**Status:** {status}

### Dane czujników:
- SpO2: **<|{spo2}|>**
- HR: **<|{hr}|>**
- Temp: **<|{temp}|>**
- GSR: **<|{gsr}|>**
- Zebrane próbki: **<|{samples}|text|>/20**

### Wynik:
Prawdopodobieństwo sepsy: **<|{probability:.2f}|>%**

### Historia pomiarów

<|{chart_data}|chart|type=line|x=nr|y[1]=SpO2|y[2]=HR|y[3]=Temp|y[4]=GSR|title=Historia parametrów|>

"""

def on_init(state: State):
    state.chart_data = []
    state.samples = len(history)
    state.status = "Gotowe do pomiaru"

def on_update(state: State):
    state.samples = len(history)

gui = Gui(page=page)
gui.on_init = on_init
gui.on_update = on_update
gui.run()
