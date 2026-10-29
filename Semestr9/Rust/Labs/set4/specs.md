Kurs języka Rust 2026 (Łukasz Piwowar)

Lista 4 (Projekt I)

#### **terminy:**

- 9.XI.2026 12:00 (grupa poniedziałkowa)
- 5.XI.2026 12:00 (grupa czwartkowa)
- 5.XI.2026 14:00 (grupa czwartkowa)

**Zadanie 1** [30]

Całość kodu należy przygotować samodzielnie (w tym zadaniu nie wolno używać zewnetrznych bibliotek poza wbudowanymi).

**10 punktów**

Przygotuj klasę Image przechowującą obrazek 24 bitowy, umożliwiającą ustalanie kolorów pixeli oraz zapis do pliku w formacie tekstowym ppm (lub binarnym bmp dla chętnych).

**10 punktów**

Przygotuj klasę Complex umożliwiającą operację na liczbach zespolonych.

**10 punktów**

Używając zaimplementowanych klas, napisz program generujący wybrany fraktal i zapisujący go w formie obrazka do pliku. Przygotuj kilka testów generujących różne fragmenty fraktala w różnych rozdzielczościach.

Pamiętaj o parametrze:

cargo run --release

i

cargo test --release

Linki:

- http://netpbm.sourceforge.net/doc/ppm.html
- http://www.fractal-explorer.com/complexnumbers.html (tu jest błąd w mnożeniu)
- https://pl.wikipedia.org/wiki/Liczby_zespolone#Mnożenie (tu nie ma błędu)
- http://www.fractal-explorer.com/mandelbrotset.html
- https://doc.rust-lang.org/std/ops/index.html