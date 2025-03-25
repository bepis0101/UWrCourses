# zad 5
Interfejs IUserStore<TUser> z przestrzeni nazw Microsoft.AspNetCore.Identity jest podstawowym interfejsem do zarządzania użytkownikami w ASP.NET Core Identity. Definiuje wiele metod związanych z operacjami na użytkownikach, takimi jak:

Tworzenie i usuwanie użytkowników.

Zarządzanie hasłami.

Zarządzanie rolami.

Zarządzanie tokenami.

Zarządzanie danymi osobowymi.

Problem: Implementacja pełnego interfejsu IUserStore<TUser> może być obciążająca, zwłaszcza gdy aplikacja nie wymaga wszystkich funkcji. Na przykład, jeśli aplikacja nie korzysta z ról, metody związane z rolami stają się zbędne, co prowadzi do implementacji metod, które nigdy nie będą używane

Aby dostosować się do zasady ISP, interfejs IUserStore<TUser> można podzielić na bardziej wyspecjalizowane interfejsy, z których każdy odpowiada za konkretną funkcjonalność. ASP.NET Core Identity już częściowo realizuje tę koncepcję poprzez interfejsy takie jak:
```
IUserPasswordStore<TUser> – zarządzanie hasłami.

IUserRoleStore<TUser> – zarządzanie rolami.

IUserEmailStore<TUser> – zarządzanie adresami e-mail.

IUserPhoneNumberStore<TUser> – zarządzanie numerami telefonów.

IUserTwoFactorStore<TUser> – zarządzanie uwierzytelnianiem dwuskładnikowym.
```
Zalecenie: Zamiast implementować pełny interfejs IUserStore<TUser>, zaleca się implementację tylko tych interfejsów, które są niezbędne dla danej aplikacji. Na przykład, jeśli aplikacja wymaga jedynie zarządzania hasłami i adresami e-mail użytkowników, wystarczy zaimplementować IUserPasswordStore<TUser> oraz IUserEmailStore<TUser>.

# zad 6
SRP – koncentruje się na odpowiedzialności klas.
ISP – koncentruje się na odpowiedzialności interfejsów.
SRP = „Jaka jest odpowiedzialność klasy?”
ISP = „Czy klient implementuje tylko potrzebne metody?”