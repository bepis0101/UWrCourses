# zad 1
### Losowość
Znajdujemy ukryte zależności pomiędzy testami, testy powinny być niezależne od siebie, być może testy wykonują się poprawnie tylko w ustalonej kolejności i tasowanie pomaga znaleźć takie błędy.

plugin: pytest-random-order
### Minimum jeden sukces
W przypadkach gdy test jest podatny na czynniki losowe takie jak opóźnienia sieciowe.

plugin: pytest-rerunfailures
### 100% sukces
Gdy musimy mieć pewność że test jest stabilny i deterministyczny. Możemy odkryć problem wyścigów, równoległości i zależności od stanu środowiska.

plugin: pytest-repeat

# zad 2
1. Czy są trackowane dane zużycia?
2. Czy użycie jest sezonowe?
3. Czy jest planowane dodanie nowego produktu?
4. Czy planowane są kampanie marketingowe które mogą zwiększyć ruch?
5. Jakie było zużycie CPU, RAM, pamięci i sieci w ciągu ostatniego roku (średnie, minimalne i maksymalne)?
6. Przewidywana liczba aktywnych użytkowników

# zad 3
Przede wszytkim YAML używa wcięć jak w Pythonie ale spacjami nie tabami, więc występują takie problemy jak w Pythonie. 

Klucz: wartość

Listy
```
owoce:
  -jabłko
  -banan
  -pomarańcza
```
komentarze pythonowe, brak typowania, 

# zad 4
```jinja2``` to silnik do templatowania w pythonie

Używa się go do generowania HTMLa, plików konfiguracyjnych, ale także dowolnych plików tekstowych które będą podobne 

# zad 5
Zdawałoby się że to dużo ale jeśli codziennie co najmniej jeden pracownik ma problem to już inaczej.

# zad 6
(row_key, column_key, timestamp) -> value

kolumny są grupowane w rodziny kolumn

wiersze posortowane leksykograficxnie po kluczu 

każda komórka może mieć różne wersje rozróżniane timestampem

przechowywanie jest rozproszone po "tabletach" (zakresach wierszy)

# zad 7
- Jaki problem biznesowy ma rozwiązać ta funkcjonalność?
- Kto będzie użytkownikiem końcowym tej funkcjonalności?
- Jakie mają potrzeby i ograniczenia?
- Główne przypadki użycia?
- Edgecasy
- Z jakimi innymi modułami lub usługami ma się integrować?
- Czy wymaga nowych API lub modyfikacji istniejących?
- Jaki jest termin wdrożenia (czy to „must-have” czy „nice-to-have”)?

# zad 8

# zad 9
1. Tworzy repozytorium Git (lub inne) w katalogu /etc.

2. Po instalacji pakietów (np. przez apt/dnf) automatycznie dodaje commit ze zmianami, które pakiet wprowadził do /etc.

3. Pozwala przeglądać historię zmian, porównywać różne wersje plików, przywracać stare wersje.

4. Obsługuje hooki i może automatycznie podpisywać commity.

###  Dlaczego warto używać etckeeper?

Śledzenie zmian w konfiguracji

Możesz sprawdzić, kiedy i kto zmienił dany plik.

Łatwo znaleźć przyczynę problemów po aktualizacji lub ręcznej edycji.

Bezpieczne przywracanie

W razie błędów konfiguracji możesz wrócić do działającej wersji systemu.

Audyt i compliance

Firmy mogą wymagać historii zmian w konfiguracji dla audytu.

Integracja z automatyzacją i CI/CD

Można zintegrować /etc z repozytorium Git i narzędziami do automatyzacji konfiguracji.

Minimalny wysiłek

Po instalacji większość pracy wykonuje się automatycznie (commity po instalacji pakietów).