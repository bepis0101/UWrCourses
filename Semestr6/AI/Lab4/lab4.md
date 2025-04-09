# zad 1
```
h(s) = max(
  mindystansczarnegokróladonarożnika,
  mindystansbiałegokróladonarożnika-1
)
```
```
H(s) = max(h(bialego_króla), h(czarnego_króla))
```
# zad 2
dla król + goniec + skoczek vs król <br>
mat bedzie wysteopowal tylko w przypadku gdy czarny król bedzie w rogu planszy koloru gońca <br>
```
h(s) = max(
  min(dystans_czarnego_króla_do_właściwego_narożnika),
  ⌈manhattan(biały_król, czarny_król) / 2⌉,
  ⌈manhattan(goniec, czarny_król) / 3⌉,
  ⌈manhattan(skoczek, czarny_król) / 3⌉
)
```
# zad 3
założenia: <br>
$h(goal) = 0$ <br>
$cost(a, b) + h(b) >= h(a)$ <br>
teza: $h(a) <= cost(a)$ <br>
załóżmy że $h(s_n) <= cost(s_n)$ <br>
ze spójności $h(s_{n+1}) <= cost(s_n, s_{n+1}) + h(s_n) <= cost(s_n, s_{n+1}) + cost(s_n) = cost(s_{n+1})$ therefore $h(s_{n+1}) <= cost(s_{n+1})$ <br>

optymistyczna ale nie spójna byłaby heurystyka z samymi wartościami ujemnymi

# zad 4
$h <= cost, f = h+dist$ <br>
weźmy 2 stany końcowe $s_1$ i $s_2$ i załóżmy że $cost(s_1) < cost(s_2)$ <br>
załóżmy że $s_2$ zostało odwiedzone przed $s_1$ więc
$f(s_2) < f(s_1)$ <br>
heurystyka jest optymistyczna więc $h(s_2) = h(s_1) = 0$
$f(s_2) = dist(s_2) = cost(s_2)$ i to samo dla $s_1$ <br>
$cost(s_2) < cost(s_1)$ nie zgadza sie z założeniem <br>

# zad 5
preproccessing może polegać na obliczeniu odległości z każdego miasta do celu i z każdego miasta do każdego miasta ze stacją benzynową
mozemy dzieki temu przechodzic do miasta najblizej celu jesli mamy na to paliwo i jesli nie to do najblizszej stacji benzynowej <br>

# zad 6
Maks każdego pola ilość kroków do pola docelowego <br>
Dla sokobana heurystyka może być maks odległości od pudła do celu <br>

# zad 7
Liczymy odległość pola do celu i pola blokującego do pustego pola bierzemy maksa

# zad 8

Bierzemy po kolei więzy i zmniejszamy ich arność zachowując założenia

$X_1 = 2A+4B$

$X_2 = 7C$

$X_3 = D^2$

$X_4 = EF$

$X_5 = G^3$

$X_6 = X_3 + X_2$

$X_7 = X_4 + X_5$

$X_8 = X_6 + X_7$

$X_1 > X_8$

Zamienić arność z 3 na 2 możemy w bardzo prosty spoób

$X = A + B + C$

$Y = A + B$

$X = Y + C$

# zad 9

# zad 10

$h(n) = max_{L \in Landmarks}(C^*(n, L) - C^*(L, goal))$, 0 for negatives

$C(n, L) - C(L, goal) \leq C(n, goal)$

z nierówności trójkąta mamy
$C(n, goal) + C(L, goal) \geq C(n, L)$ 
więc $C(n, L) - C(L, goal) \leq C(n, goal)$ <br>

dobrą heurą mogłoby być wyznaczenie najdalszego punktu od jakiegos losowego punktu i nastepnie wyznaczanie najdalszych punktow od istniejacych punktow



