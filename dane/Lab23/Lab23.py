import pandas as pd
import numpy as np

# Manipulowanie danymi:
# Zapoznaj się z obiektem ’pandas.DataFrame’ i utwórz:
# Tabelę złożoną z liczb losowych przedziału normalnego złożoną z trzech kolumn z nagłówkiem (A,B,C)
# i pięciu wierszy z indeksem o nazwie ”data” złożonym z dat w przedziale od 2020-03-01 do 2020-03-05

daty = pd.date_range(
    start="2020-03-01",
    end="2020-03-05",
    freq="D",
    name="data"
)

tabela = pd.DataFrame(
    np.random.randn(5, 3),
    columns=["A", "B", "C"],
    index=daty
)

# print(tabela)

# Wygeneruj tabelę złożoną z liczb losowych i indeksie ”id” w formacie ’integer’ złożoną z 20 wierszy i trzech kolumn (’A’,’B’,’C’).

tabela = pd.DataFrame(
    np.random.randn(20, 3),
    columns=['A', 'B', 'C'],
    index=pd.Index(range(20), name='id')
)

# wybierz trzy pierwsze wiersze z tabeli
print(tabela.head(3))

# wybierz trzy ostatnie wiersze z tabeli
print(tabela.tail(3))

# wyświetl nazwę indeksu tabeli
print(tabela.index.name)

# wyświetl nazwy kolumn
print(tabela.columns)

# wyświetl tylko dane bez indeksów i nagłówków kolumn
print(tabela.to_numpy())
print(tabela.values.tolist())

# wybierz pięć losowo wybranych wierszy
print(tabela.sample(n=5))

# wybierz wartości kolumny ’A’ a następnie ’A’ i ’B’
print(tabela['A'])
print(tabela[['A', 'B']])

# zapoznaj się z funkcją ’iloc’ i wyświetl:
# trzy pierwsze wiersze i kolumny ’A’ i ’B’
print(tabela.iloc[:3, :3])

# wiersz piąty
print(tabela.iloc[4])

# wiersze 0,5,6,7 i kolumny 1 i 2
print(tabela.iloc[[0, 5, 6, 7], [1, 2]])

# Zapoznaj się z funkcją ’describe’ i wyświetl podstawowe statystyki tabeli:
print(tabela.describe())

# sprawdź które dane są są większe od 0
print(tabela > 0)

# wyświetl tylko dane większe od 0
print(tabela[tabela > 0])

# wybierz kolumny A tylko dane większe od 0
print(tabela.loc[tabela['A'] > 0, 'A'])

# policz średnią w kolumnach
print(tabela.mean())

# policz średnią w wierszach
print(tabela.mean(axis=1))

# Zapoznaj się z funkcją ’concat’. Utwórz dwie dowlone tabele i połącz je ze sobą. 
tabela1 = pd.DataFrame({
    'A': [1, 2, 3],
    'B': [4, 5, 6]
})

tabela2 = pd.DataFrame({
    'A': [7, 8, 9],
    'B': [10, 11, 12]
})
tabela3 = pd.concat([tabela1, tabela2])
print(tabela3)

# Dokonaj transpozycji nowej tabeli.
print(tabela3.T)

# Sortowanie: W tabelach DataFrame mogą być umieszczone różne typy danych
df = pd.DataFrame(
    {"x": [1, 2, 3, 4, 5],
    "y": ['a', 'b', 'a', 'b', 'b']},
    index=np.arange(5)
    )
df.index.name='id'
print(df)

# Posortuj dane po ’id’ rosnąco
print(df.sort_values(by='id', ascending=True))

# Posortuj dane po kolumnie ’y’ malejąco
print(df.sort_values(by='y', ascending=False))

# Grupowanie danych (prześledź działania):
slownik = {
    'Day': ['Mon', 'Tue', 'Mon', 'Tue', 'Mon'],
    'Fruit': ['Apple', 'Apple', 'Banana', 'Banana', 'Apple'],
    'Pound': [10, 15, 50, 40, 5],
    'Profit': [20, 30, 25, 20, 10]
}
df3 = pd.DataFrame(slownik)
print(df3)
print(df3.groupby('Day').sum())
print(df3.groupby(['Day','Fruit']).sum())

# Wypełnianie danych:
df=pd.DataFrame(np.random.randn(20, 3), index=np.arange(20), columns=['A','B','C'])
df.index.name='id'
print(df)

# Wykonaj i opisz jak działają poniższe komendy:
df['B']=1
print(df)

df.iloc[1,2]=10
print(df)

df[df>0]=-df
print(df)

# Uzupełnianie danych. Wykonaj i opisz działanie poniższych komend:
df.iloc[[0, 3], 1] = np.nan
print(df)

df.fillna(0, inplace=True)
print(df)

df.iloc[[0, 3], 1] = np.nan
df=df.replace(to_replace=np.nan,value=-9999)
print(df)

df.iloc[[0, 3], 1] = np.nan
print(pd.isnull(df))