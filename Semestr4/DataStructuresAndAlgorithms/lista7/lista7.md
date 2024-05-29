# zad 1
Mamy pogrupowane operacje. Załóżmy BSO, że operacji union jest $U$ a operacji find jest $F$. <br>
$U+F=\sigma$<br>
Koszt wykonania jednej operacji union bedzie $O(1)$ wiec wykonanie wszystkich operacji union bedzie w czasie $O(U)$ <br>
Jedna operacja Find przejdziemy maksymalnie po wszystkich zlaczonych wierzcholkach a wiec $U-1$ razy
Koszt $F$ za operacje Find bo zawsze dojdziemy do korzenia reszte wywolujemy na synach korzenia czyli tez maks F
$$O(U) + O(F) + 2O(F) = O(U+F) = O(|\sigma|)$$

# zad 2
# zad 3
# zad 4
## Rozdawanie żetonów z wykładu 
### Operacja FIND dostaje żeton jeśli:
- wierzchołek $v$ jest korzeniem 
- ojciec wierzchołka $v$ jest korzeniem 
- ojciec wierzchołka $v$ jest w innej grupie niż $v$

wpp
- żeton dostaje wierzchołek $v$

W dowodzie z wykładu pokazaliśmy, że koszt na jeden wierzchołek wynosi $F(k) - F(k-1)$, bo rząd ojca wierzchołka $v$ może rosnąć w najgorszym przypadku o co najmniej 1.

Tylko wtedy po takim jednym przejściu FIND'em wszystkie wierzchołki, które były na ścieżce następnie były podpięte pod korzeń.

Teraz po przejściu takim FIND'em  wierzchołki nie będą podpięte pod korzeń tylko pod swoich dziadków. 
Więc aby dojść do takiego stanu jak wyżej, musimy wykonać więcej pracy

## Analiza zamortyzowana 
W dowodzie z wykładu musieliśmy udowodnić
1. Każdy **FIND** $F_i$ dostał $O(\log^* n)$ żetonów
2. Suma żetonów w wierzchołkach wynosi $O(n \log^* n)$

### D.1 
Tu się nic nie zmienia, bo przejdziemy przez wierzchołki jak zwykłym **FIND**'dzie, więc **FIND** $F_i$ dostanie $O(\log^* n)$ żetonów
### D.2
Rozpatrujemy najgorszy przypadek kiedy będziemy się wywoływali **FIND**'ami na wierzchołku $v$

Przed pierwszym **FIND**'em koszt od wierzchołka $v$ wynosił $F(k)-F(k-1)$, po kolejnych będzie wynosił $\frac{F(k)-F(k-1)}{2}, \frac{F(k)-F(k-1)}{4}, ...$ 

Czyli taki suma tych operacji $\rho_1 = F(k)-F(k-1)+ \frac{F(k)-F(k-1)}{2} + \frac{F(k)-F(k-1)}{4} + ... \le 2 \cdot \bigg(F(k)-F(k-1) \bigg)$ 

W pierwotnej wersji wszystkie wierzchołki, które wystąpiły na ścieżce były podłączane bezpośrednio do korzenia. Teraz z jednej ścieżki powstaną nam dwie nowe, o połowę krótsze niż ta z przed operacji **FIND**. 

Widzmy, że jeśli wywołamy się **FIND**'em na nowo powstałych ścieżkach to znowu będziemy mieć 2 razy więcej krótszych ścieżek. 


#### Możemy ropisać jak będą wyglądały koszty wszystkich podzielonych ścieżek


#### Obliczamy ile wierzchołków jest w 1 grupie (To było na wykładzie)
$$\sum^{F(k)}_{i = F(k-1)+1}   \frac{n}{2^{i-1}}(\text{Też było}) = \frac{n}{2^{F(k-1)+1}} \cdot \bigg(1+ \frac{1}{2}+\frac{1}{4} + ... \bigg) \le \frac{n}{2^{F(k-1)}} = \frac{n}{F(k)} \text{(tyle mamy w 1 grupie)}$$




#### Więc koszt na 1 grupę będzie wynosił
$$\frac{n}{F(k)} \cdot 4\bigg(F(k) -F(k-1)\bigg) \le 2n$$

Grup jest $\log^*n$
#### To nam daje 
$$O(4n \log^* n) = O(n \log^* n)$$

# zad 5

Ile najwiecej ostatnich krawedzi jestesmy w stanie dodac żeby ścieżka dalej nie istniała?
W każdym ruchu Unionujemy krawedz do zbioru
Sprawdzamy dla wszystkich wierzcholkow czy cos nam sie zmienilo
$$if(find(u) \neq find(v))$$