import pandas as pd

# Wczytaj dane
df = pd.read_csv("dataset/2/Dataset.csv")  # Zmień na swoją ścieżkę

# Grupowanie po pacjencie i sprawdzenie, czy którykolwiek miał SepsisLabel==1
grouped = df.groupby("Patient_ID")["SepsisLabel"].max()

# max() da 1 jeśli pacjent miał sepsę w którymkolwiek momencie
num_with_sepsis = (grouped == 1).sum()
num_total_patients = grouped.shape[0]

print(f"Liczba pacjentów z sepsą: {num_with_sepsis}")
print(f"Łączna liczba pacjentów: {num_total_patients}")
print(f"Odsetek pacjentów z sepsą: {100 * num_with_sepsis / num_total_patients:.2f}%")
