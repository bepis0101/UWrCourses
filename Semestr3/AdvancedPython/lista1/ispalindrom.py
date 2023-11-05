## zadanie 2 lista 1
## Borys Adamiak


import re

def isPalindrom(s: str):
    s = s.lower()
    s = re.sub(r'[^a-zA-Z]', '', s)
    return s == s[::-1]

print(isPalindrom("Kobyła ma mały bok"))
print(isPalindrom("Eine güldne, gute Tugend: Lüge nie!"))