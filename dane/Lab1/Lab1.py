import numpy as np

# Zadania wprowadzające
a=np.array([1,2,3,4,5,6,7])
b=np.array([[1,2,3,4,5], [6,7,8,9,10]])

# Tablice
# Wykonaj transpozycję tablicy ’b’ za pomocą funkcji transpose.
print(np.transpose(b))

# Utwórz i wyświetl tablicę składającą się ze 100 elementów za pomocą funkcji arange.
print(np.arange(100))

# Utwórz i wyświetl tablicę składającą się z 10 liczb w zakresie od 0 do 10
print(np.arange(0,10))

# Liczby losowe
# Za pomocą arange utwórz tablicę pomiędzy wartościami od 0 do 100 i skoku wartości co 5
print(np.arange(0, 101, 5))

# Za pomocą funkcji random utwórz tablicę z 20 liczb losowych rozkładu normalnego, zaokrąglonych do dwu miejsc po przecinku.
print(np.round(np.random.randn(20), 2))

# Wygeneruj losowo 100 liczb całkowitych w zakresie od 1 do 1000.
print(np.random.randint(1, 1001, size=100))

# Za pomocą funkcji ’zeros’ i ’ones’ wygeneruj dwie macierze o rozmiarze 3x2.
print(np.zeros((3, 2)))
print(np.ones((3, 2)))

# Utwórz macierz losową złożoną z liczb całkowitych o rozmiarze 5x5 i nadaj jej typ 32bit.
print(np.random.randint(1, 101, size=(5, 5), dtype=np.int32))

# Wygeneruj tablicę złożoną z losowo wybranych liczb dziesiętnych od 0-10
a = np.random.uniform(0, 10, size=10)
# Zamień wartości na ’integer’ i wstaw w nową tablicę
b = a.astype(int)
print(b)
# Znajdź funkcję ’numpy’, która zaokrągli tablicę (a) do liczb całkowitych. Zamień je następnie na typ ’integer’
c = np.round(a)
c = c.astype(int)
print(c)

# Selekcja danych
b = np.array([[1,2,3,4,5], [6,7,8,9,10]], dtype=np.int32)
print(b.ndim)
print(b.size)

# Wybierz wartości 2 i 4 z tablicy b.
print(b[0, 1])
print(b[0, 3])

# Wybierz wszystkie wiersze z kolumny 1.
print(b[:, 0])

# Wygeneruj macierz losową o rozmiarze 20x7, złożoną liczb całkowitych w przedziale 0-100.
# Wyświetl wszystkie wiersze dla czterech pierwszych kolumn.
a = np.random.randint(0, 101, size=(20, 7))
print(a[:, :4])

# Operacje matematyczne i logiczne
# Stwórz dwie macierze w przedziale 0-10 o rozmiarach 3x3 (a i b). Dodaj, pomnóż, podziel, spotęguj je przez siebie.
a = np.random.randint(0, 11, size=(3, 3))
b = np.random.randint(0, 11, size=(3, 3))
print("A:")
print(a)
print("B:")
print(b)

print("Dodawanie")
print(a + b)
print("Mnozenie")
print(a * b)
print("Dzielenie")
print(a / b)
print("Potegowanie")
print(a ** b)

# Sprawdź czy wartość macierzy a jest większa lub równa 4.
print(a >= 4)

# Sprawdź czy wartość macierzy a 1¿= ¡=4. (??)

# Znajdź funkcję w numpy do obliczenia sumy głównej przekątnej macierzy b.
print(np.trace(b))

# Dane statystyczne
# Oblicz sumę, wartość minimum, maksimum, odchylenie standardowe w macierzy b.
print(np.sum(b))

print(np.min(b))
print(np.max(b))

print(np.std(b))

# Oblicz średnią dla wierszy w macierzy b. Oblicz średnią dla kolumn macierzy b.
print(np.mean(b, axis=1))
print(np.mean(b, axis=0))

# Rzutowanie wymiarów za pomocą shape lub resize:
# Utwórz tablicę składającą się z 50 liczb.
a = np.arange(50)

# Za pomocą funkcji ’reshape’ utwórz macierz 10x5. To samo za pomocą resize.
b = a.reshape(10,5)
print(b)
a.resize(10, 5)
print(a)

# Sprawdź do czego służy komenda ravel.
print(np.ravel(a))

# Stwórz dwie tablice o rozmiarach 5 i 4 i dodaj je do siebie. Sprawdź do czego służy funkcja ’NEWAXIS’ i wykorzystaj ją.
a = np.arange(5)
b = np.arange(4)

a = a[:, np.newaxis]
print(a + b)

# Sortowanie danych:
# Sprawdź składnię funkcji sort i argsort.
a = np.random.randn(5,5)
print(np.sort(a))
print(np.argsort(a))

# Posortuj wiersze rosnąco. Posortuj kolumny malejąco.
print(np.sort(a, axis=1))
print(np.sort(a, axis=0)[::-1])

b = np.array([(1,'M','mazowieckie'), (2,'ZP','zachodniopomorskie'), (3,'ML','małopolskie')])
# Zadanie: Na podstawie powyższej tablicy zrób macierz 3x3. Posortuj dane rosnąco po kolumnie 2.
print(b[np.argsort(b[:, 2])])
# Wyświetl nazwę województwa zachodniopomorskiego.
print(b[1][2])

# Zadania podsumowujące

# 1) Utwórz macierz składającą się z pięciu kolumn i 10 wierszy losowo wybranych
# liczb całkowitych i policz sumę głównej przekątnej macierzy, używając funkcji ’trace’
# a następnie wyświetl wartości używając funkcji ’diag’.

a = np.random.randint(0, 101, size=(10, 5))
print(a)
trace = np.trace(a)
przekatna = np.diag(a)
print("Przekątna: ", przekatna, " Suma glównej przekątnej: ", trace)

# 2) Utwórz dwie tablice z losowo wybranych liczb dziesiętnych z rozkładu normalnego i przemnóż je przez siebie.

a = np.random.randn(20)
b = np.random.randn(20)
print(a * b)

# 3) Utwórz dwie tablice z losowo wybranych liczb całkowitych w zakresie od 1-100.
# Stwórz z nich macierze o 5 kolumnach i dodaj je do siebie.

a = np.random.randint(1, 101, size=(4, 5))
b = np.random.randint(1, 101, size=(4, 5))
print(a + b)

# 4) Stwórz macierz o 5 kolumnach i 4 wierszach oraz 4 kolumnach i 5 wierszach i dodaj je do siebie używając transformacji wymiarów.

a = np.random.randint(1, 101, size=(4, 5))
b = np.random.randint(1, 101, size=(5, 4))

wynik = a[:, :, np.newaxis] + b[np.newaxis, :, :]

print("Wynik: ")
print(wynik)

# 5) Pomnóż kolumny 3 i 4, stworzonych przez siebie macierzy.

a = np.random.randint(1, 101, size=(4, 5))
b = np.random.randint(1, 101, size=(4, 5))

print("Wynik mnozenia kolumny trzeciej i czwartej:")
print(a[:, 2] * a[:, 3])
print(b[:, 2] * b[:, 3])

# 6) Wygeneruj dwie macierze o rozkładzie normalnym (np.random.normal) i jednostajnym (np.random.uniform).
# Policz wartość średnią, odchylenie standardowa, wariancję itp. Porównaj wyniki z obu zbiorów danych.

a = np.random.normal(size=(100))
b = np.random.uniform(size=(100))

sredniaA = np.mean(a)
odchylenieA = np.std(a)
wariancjaA = np.var(a)

sredniaB = np.mean(b)
odchylenieB = np.std(b)
wariancjaB = np.var(b)

text1 = "Średnia w rozkladzie normalnym jest większa niz w jednostajnym"
text2 = "Średnia w rozkladzie jednostajnym jest większa niz w normalnym"
print(text1) if sredniaA > sredniaB else print(text2)

text1 = "Odchylenie standardowe w rozkladzie normalnym jest większe niz w jednostajnym"
text2 = "Odchylenie standardowe w rozkladzie jednostajnym jest większe niz w normalnym"
print(text1) if odchylenieA > odchylenieB else print(text2)

text1 = "Wariancja w rozkladzie normalnym jest większa niz w jednostajnym"
text2 = "Wariancja w rozkladzie jednostajnym jest większa niz w normalnym"
print(text1) if wariancjaA > wariancjaB else print(text2)

# 7) Wygeneruj dwie macierze kwadratowe a i b, pomnóż je przez siebie używając (a*b) oraz funkcji dot.
# Jaka jest różnica? Napisz kiedy warto wykorzystać funkcję dot?

a = np.random.randint(1, 101, size=(5, 5))
b = np.random.randint(1, 101, size=(5, 5))

wynik1 = a * b
wynik2 = np.dot(a, b)

print("a * b powoduj mnozenie parami, dot jest monozeniem macierzowym")

# 8) Sprawdź funkcję strides oraz as strided. Zastosuj je do wyboru danych z macierzy np. 5 kolumn z trzech pierwszych wierszy.

a = np.random.randint(1, 101, size=(10, 10))
stride = a.strides
print(np.lib.stride_tricks.as_strided(a, shape=(3, 5), strides=(stride[0], stride[1])))

# 9) Wygeneruj dwie tablice a i b. Połącz je z użyciem funkcji vstack i hstack.
# Czym one się różnią? Zastanów się i napisz, w jakich przypadkach warto je zastosować?

a = np.random.randint(1, 101, size=(5, 5))
b = np.random.randint(1, 101, size=(5, 5))

v = np.vstack((a, b))
h = np.hstack((a, b))

print("vstack lączy macierze w pionie, hstack lączy macierze w poziomie - przydatne gdy chcemy polączyc dane z kilku źródel w jedną macierz")

# 10) Użyj funkcji strides i as strided do obliczenia wartości maksymalnej bloków danych z macierzy (rysunek)

a = np.arange(24)
a = a.reshape(4, 6)
stride = a.strides

temp = np.lib.stride_tricks.as_strided(a, shape=(2, 2, 2, 3), strides=(2 * stride[0], 3* stride[1], stride[0], stride[1]))
temp = temp.reshape(4,2,3)
wynik = np.max(temp, axis=(1,2))

print("Max z 4 podmacierzy:")
print(wynik)