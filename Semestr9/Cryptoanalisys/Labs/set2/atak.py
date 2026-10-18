#!/usr/bin/env python3
"""AES-128: CTR z powtórzonym IV (atak jak na two-time pad), plastyczność CTR, ECB vs CBC.

Wejście:  obraz1.rgba, obraz2.rgba (256x256, RGBA, bez metadanych)
Wyjście:  *.rgba (szyfrogramy itd.), *.png (podglądy), plansza.png
"""
import os
from Crypto.Cipher import AES
from Crypto.Util import Counter
from PIL import Image, ImageDraw, ImageFont

W = H = 256
N = W * H * 4

P1 = open("obraz1.rgba", "rb").read()
P2 = open("obraz2.rgba", "rb").read()
assert len(P1) == len(P2) == N

KEY = os.urandom(16)     # klucz znany tylko "nadawcy"
IV = os.urandom(16)      # ten sam initial vector


def xor(a, b):
    return bytes(x ^ y for x, y in zip(a, b))


def ctr(data, key=KEY, iv=IV):
    c = Counter.new(128, initial_value=int.from_bytes(iv, "big"))
    return AES.new(key, AES.MODE_CTR, counter=c).encrypt(data)


def ecb(data):
    return AES.new(KEY, AES.MODE_ECB).encrypt(data)


def cbc(data):
    return AES.new(KEY, AES.MODE_CBC, iv=IV).encrypt(data)


def podglad(raw, nazwa, nieprzezroczysty=True):
    """Zapisuje surowe bajty + PNG. Kanał A nadpisujemy na 255, inaczej:
    - w szyfrogramach A jest losowe -> obraz częściowo przezroczysty,
    - w XOR-ze A1^A2 = 255^255 = 0 -> obraz CAŁKOWICIE przezroczysty (niewidoczny)."""
    open(nazwa + ".rgba", "wb").write(raw)
    im = Image.frombytes("RGBA", (W, H), raw)
    if nieprzezroczysty:
        im.putalpha(255)
    im.save(nazwa + ".png")
    return im


# --- 1. CTR z tym samym IV ---------------------------------------------------
C1, C2 = ctr(P1), ctr(P2)
im_c1 = podglad(C1, "ctr_obraz1")
im_c2 = podglad(C2, "ctr_obraz2")

# --- 2. two-time pad: C1 ^ C2 = (P1 ^ K) ^ (P2 ^ K) = P1 ^ P2 ------------------
X = xor(C1, C2)
assert X == xor(P1, P2)
alfa = set(X[3::4])
print("unikalne wartości bajtu A w C1^C2:", alfa, "(0 = przezroczysty!)")
podglad(X, "xor_bez_poprawki_A", nieprzezroczysty=False)
im_x = podglad(X, "xor_ctr")

# znając P1, odzyskujemy P2 bez klucza
assert xor(X, P1) == P2
print("P2 = C1 ^ C2 ^ P1  ->  OK (bez znajomości klucza)")

# --- 3. plastyczność CTR: wstawiamy "I hate you!" -----------------------------
cel = Image.frombytes("RGBA", (W, H), P2)
d = ImageDraw.Draw(cel)
try:
    font = ImageFont.truetype("DejaVuSans-Bold.ttf", 30)
except OSError:
    font = ImageFont.load_default(size=30)
tekst = "I hate you!"
tw = d.textlength(tekst, font=font)
d.rectangle([0, 8, W - 1, 52], fill=(0, 0, 0, 255))
d.text(((W - tw) / 2, 12), tekst, font=font, fill=(255, 40, 40, 255))
P2_nowy = cel.tobytes()

# atakujący zna C2 i P2, NIE zna klucza:  C2' = C2 ^ P2 ^ P2'
C2_zmod = xor(C2, xor(P2, P2_nowy))
open("ctr_obraz2_zmodyfikowany.rgba", "wb").write(C2_zmod)

# odbiorca odszyfrowuje prawdziwym kluczem
D = ctr(C2_zmod)
assert D == P2_nowy
im_d = podglad(D, "odszyfrowany_zmodyfikowany")
print("odszyfrowany zmodyfikowany szyfrogram == obraz z 'I hate you!'  ->  OK")

# --- 4. ECB i CBC --------------------------------------------------------------
im_e1, im_e2 = podglad(ecb(P1), "ecb_obraz1"), podglad(ecb(P2), "ecb_obraz2")
im_b1, im_b2 = podglad(cbc(P1), "cbc_obraz1"), podglad(cbc(P2), "cbc_obraz2")

# --- plansza -------------------------------------------------------------------
im_p1 = Image.frombytes("RGBA", (W, H), P1)
im_p2 = Image.frombytes("RGBA", (W, H), P2)
wiersze = [
    [("obraz1", im_p1), ("CTR(obraz1)", im_c1), ("ECB(obraz1)", im_e1), ("CBC(obraz1)", im_b1)],
    [("obraz2", im_p2), ("CTR(obraz2)", im_c2), ("ECB(obraz2)", im_e2), ("CBC(obraz2)", im_b2)],
    [("C1 xor C2 (A=255)", im_x), ("Dec(C2 ^ P2 ^ P2')", im_d)],
]
M, T = 10, 22
pl = Image.new("RGBA", (4 * W + 5 * M, 3 * (W + T) + 4 * M), (255, 255, 255, 255))
dp = ImageDraw.Draw(pl)
try:
    f2 = ImageFont.truetype("DejaVuSans.ttf", 15)
except OSError:
    f2 = ImageFont.load_default()
for r, wiersz in enumerate(wiersze):
    for c, (tytul, im) in enumerate(wiersz):
        x, y = M + c * (W + M), M + r * (W + T + M)
        dp.text((x, y), tytul, font=f2, fill=(0, 0, 0, 255))
        pl.paste(im, (x, y + T))
pl.save("plansza.png")
print("gotowe")