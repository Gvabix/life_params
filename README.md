# Inteligentne systemy sensoryczne - System pomiaru parametrów życiowych pacjenta.

## Autorzy:
- Gabriela Bułat
- Emilia Myrta
- Gabriela Chmielecka

## Opis projektu
Celem projektu było stworzenie systemu do wczesnego wykrywania sepsy na podstawie danych  pobieranych z czujników. System łączy platformę sprzętową (Arduino) z aplikacją desktopową opartą na Pythonie oraz modelem sztucznej inteligencji (LSTM).

## Część sprzętowa (Arduino)

- **Pulsoksymetr** - `MAX30102` – mierzący poziom tętna (HR), temperaturę oraz saturację krwi (SpO₂).

- **Czujnik impedancji skóry** - `Grove GSR` – pomiar przewodnictwa skóry.

Dane są wysyłane przez port szeregowy do komputera w celu dalszego przetwarzania.

## Część programowa (Python + GUI)

Interfejs użytkownika aplikacji został zrealizowany z wykorzystaniem systemu szablonów **Jinja2** dostępnego w ramach frameworka **Flask**, a także technologii **HTML**, **CSS** oraz **JavaScript**.

Strona główna prezentuje następujące informacje:
- bieżące dane pochodzące z czujników: saturacja krwi (SpO₂), tętno (HR), temperatura ciała oraz przewodność skóry (GSR),
- dane użytkownika: wiek i płeć,
- liczbę zebranych próbek,
- status działania systemu (np. oczekiwanie na dane, błąd odczytu, dane pobrane),
- komunikaty ostrzegawcze (alerty) na podstawie analizy ostatnich wartości,
- wynik predykcji ryzyka wystąpienia sepsy (wyrażony w procentach).

Aplikacja dynamicznie odświeża dane, co umożliwia płynną aktualizację informacji bez potrzeby przeładowywania strony.

Dodatkowo, w interfejsie zaimplementowano możliwość przełączania pomiędzy **trybem jasnym i ciemnym**, co zwiększa komfort użytkowania w różnych warunkach oświetleniowych.

## Model AI

Model operuje na sekwencyjnych danych czasowych zebranych w 20-godzinnym oknie przesuwanym po czasie hospitalizacji pacjenta. Każda próbka danych ma postać macierzy o wymiarach 20 x 6, gdzie 20 to liczba kolejnych godzin, a 6 to liczba wybranych cech fizjologicznych:

- **HR** – tętno (Heart Rate),
- **O2Sat** – saturacja krwi tlenem,
- **Temp** – temperatura ciała,
- **GSR** - impedancja skóry,
