## zadanie 3 lista 1
## Borys Adamiak

import decimal
def vat_faktura(lista: list):
    suma = sum(lista)
    return 0.23 * suma


def vat_paragon(lista: list):
    lista_vat = []
    for i in lista:
        lista_vat.append(0.23 * i)
    return sum(lista_vat)

def turn_to_decimal(lista: list):
    lista_dec = []
    for i in lista:
        lista_dec.append(decimal.Decimal(i))
    return lista_dec

def vat_faktura_dec(lista: list):
    lista = turn_to_decimal(lista)
    suma = sum(lista)
    return decimal.Decimal(0.23) * suma


def vat_paragon_dec(lista: list):
    lista_vat = []
    for i in lista:
        lista_vat.append(decimal.Decimal(0.23) * decimal.Decimal(i))
    return sum(lista_vat)



l1 = [1, 2, 3, 4, 5]
l2 = [2.2, 2.9999999, 0.11111111, 2.3]
print(vat_faktura(l1) == vat_paragon(l1))
print(vat_faktura(l2) == vat_paragon(l2))


print(vat_faktura_dec(l1) == vat_paragon_dec(l1))
print(vat_faktura_dec(l2) == vat_paragon_dec(l2))