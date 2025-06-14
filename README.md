# Inteligentne systemy sensoryczne - System pomiaru parametrów życiowych pacjenta.

## Autorzy:
- Gabriela Bułat
- Emilia Myrta
- Gabriela Chmielecka

## Opis projektu
Celem projektu było stworzenie systemu do wczesnego wykrywania sepsy na podstawie danych  pobieranych z czujników. System łączy platformę sprzętową (Arduino) z aplikacją desktopową opartą na Pythonie oraz modelem sztucznej inteligencji (LSTM).

## Część sprzętowa (Arduino)

- **Czujnik temperatury** - `MLX90614` – umożliwiający bezkontaktowy pomiar temperatury ciała.

- **Pulsoksymetr** - `MAX30102` – mierzący poziom tętna (HR) oraz saturacji krwi (SpO₂).

- **Czujnik impedancji skóry** - `Grove GSR` – pomiar przewodnictwa skóry.

Dane są wysyłane przez port szeregowy do komputera w celu dalszego przetwarzania.

## Część programowa (Python + GUI)

Aplikacja desktopowa została stworzona z użyciem biblioteki **Taipy GUI**. Jej funkcje obejmują:

- Interfejs graficzny do wyświetlania aktualnych danych z sensorów
- Gromadzenie serii 20 próbek pomiarowych
- Wczytywanie modelu `sepsis_lstm_model.keras` (LSTM)
- Predykcja prawdopodobieństwa sepsy
- Wizualizacja historii pomiarów na wykresie

## Działanie systemu

1. Użytkownik uruchamia aplikację i wybiera dane demograficzne (wiek, płeć).
2. System zbiera dane z sensorów i zapisuje je jako kolejne próbki.
3. Po zebraniu 20 pomiarów możliwe jest wykonanie predykcji.
4. Model LSTM analizuje dane i zwraca **prawdopodobieństwo sepsy**.
5. Wynik i dane historyczne są wyświetlane w aplikacji.

## Przykładowe dane zbierane przez system

- **SpO₂**: poziom natlenienia krwi (%)
- **HR**: tętno (uderzeń na minutę)
- **Temperatura**: °C
- **GSR**: przewodność skóry (wartość analogowa)

## Model AI

Model `sepsis_lstm_model.keras` został wytrenowany do analizy sekwencji danych biologicznych i przewidywania prawdopodobieństwa wystąpienia sepsy. Wymaga on dokładnie **20 próbek wejściowych** w określonym formacie.
