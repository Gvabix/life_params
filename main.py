import streamlit as st
import serial
import time
import tensorflow as tf
import numpy as np


model = tf.keras.models.load_model("sepsis_lstm_model.keras")


# pobieranie danych z Arduino
def get_serial_data(port="COM3", baudrate=9600):
    try:
        with serial.Serial(port, baudrate, timeout=2) as ser:
            line = ser.readline().decode().strip()
            return line
    except:
        return None


st.title("Monitor parametrów życiowych")

# dane wejściowe
age = st.number_input("Wiek", min_value=0, max_value=120, value=30)
gender = st.selectbox("Płeć", ["Mężczyzna", "Kobieta"])

# przycisk do aktualizacji danych
if st.button("Odczytaj dane i przewiduj sepsę"):
    raw_data = get_serial_data()

    if raw_data:
        st.text(f"Dane: {raw_data}")

        # parsowanie danych z czujników (trzeba jeszcze dopasowac format)
        try:
            spo2 = float(raw_data.split("SpO2: ")[1].split("%")[0])
            hr = float(raw_data.split("HR: ")[1].split("bpm")[0])
            temp = float(raw_data.split("Temp: ")[1].split("°C")[0])
            gsr = float(raw_data.split("GSR : ")[1].split("|")[0])
            ecg = float(raw_data.split("ECG SPI Raw: ")[1])
        except:
            st.error("Nie udało się sparsować danych.")
            spo2, hr, temp, gsr, ecg = 0, 0, 0, 0, 0

        sex = 1 if gender == "Mężczyzna" else 0

        # dane wejściowe do modelu (do dostosowania do formatu modelu)
        X = np.array([[age, sex, spo2, hr, temp, gsr, ecg]])
        y_pred = model.predict(X)
        st.success(f"Prawdopodobieństwo sepsy: {y_pred[0][0] * 100:.2f}%")
    else:
        st.warning("Brak danych z Arduino.")
