# zad 1
## a) 
local beam search dla k=1 to hill climbing

## b) 
local beam search dla jednego stanu początkowego i $\infty$ stanów zapisanych to BFS

## c) 
simultaed annealing z T = 0 przez cały czas działania
to będzie po prostu hill climbing (nie akceptujemy gorszych stanów)

## d) 
sim annealing z T = $\infty$ przez cały czas działania
to będzie random search (wszystkie stany są akceptowane)

## e) 
algotrytm genetyczny z populacją 1 to bedzie hill climbing (bo mamy tylko jednego osobnika i go mutujemy)

# zad 2

## a) evolution + hill climbing
podczas mutacji osobnika, jeżeli jego ocena jest lepsza od rodzica to go przyjmujemy, jeżeli nie to go odrzucamy
## b) $A^*$ + local beam search
trzymamy tylko k najlepszych stanów przez co zyskujemy czas (ale tracimy optymalność)
## c) SA + evolution
z czasem zmniejeszamy temperaturę przez co zmniejszamy prawdopodobieństwo akceptacji gorszego stanu
## d) taboo search + evolution
uciekamy z plaskich lokalnych maksimow

# zad 3

Ant colony i jego zastosowanie do problemu komiwojażera

Ant colony to algorytm inspirowany zachowaniem mrówek, które szukają najkrótszej drogi do źródła pokarmu. W przypadku problemu komiwojażera, algorytm ten polega na symulacji ruchu mrówek po grafie reprezentującym miasta i drogi między nimi. Mrówki zostawiają feromony na krawędziach, co wpływa na prawdopodobieństwo wyboru danej krawędzi przez inne mrówki. W miarę upływu czasu, feromony parują, co pozwala na eksplorację nowych tras. 

# zad 4

nasze zmienne to bloki B_idx_dlugosc, a domeny wszystkie mozliwe polozenia blokow, nasze ograniczenia to nie nakladanie sie blokow nie wykraczanie poza plansze oraz brak scian

# zad 5

battleships to łamigówka podobna do obrazków logicznych
chodzi o to ze mamy okreslona liczbe statkow o okreslonej dlugosci i musimy je usatwic na pplanszy tak zeby sie nie stykaly i spelnialy ilosc pol zamalowanych w wierszach i kolumnach

dla kazdego statku patrzymy na jego pozycje startowa rozwazamy ulozenie poziome i pionowe i sumujemy ilosc pol zajetych we wsztsrkich wierszach i kolumnach nie moze byc sasiadajacych 

# zad 6

# zad 7



# zad 8 
potencjalna heura dla pentago - patrzymy na wolne pole jesli daje nam odpowiednio linie dlugosci 1-5 to dajemy tyle punktow z wylaczeniem 5 bo tam dajemy $\infty$ i ujemne dla przeciwnika

# zad 9 
dla każdego pionka liczymy czy jest ile ma mozliwych ruchów i ile możliwych bić (bicie x 10)

# zad 10

jeśli nasz agent jest pierwszy zaczynamy zajęciem środka.
w pierwszej kolejnosci jesli mamy szanse na wygrana to wykonujemy ten ruch w drugiej kolejnosci jesli przeciwnik ma szanse na wygrana to blokujemy ten ruch w trzeciej kolejnosci wybieramy narozniki.
jesli nasz agent jest drugi to to samo tylko nie koniecznie zajmiemy srodek

# zad 11

## a) 
  - Alpha-Beta
    - reużuywamy zbudowane drzewo do przeszukiwania
  - MCTS
    - używać wcześnie zgromadzonych statystyk 
    - reużyć części policzonego drzewa (tree reuse)
## b) 
  - Alpha Beta
    - równoległe przeszukiwanie dzieci drzewa
  - MCTS
    - wykonujemy kilka symulacji w tym samym czasie