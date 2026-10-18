from collections import Counter
from functools import reduce
from math import gcd

alphabet = "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŻŹ"
char2num = {c: i for i, c in enumerate(alphabet)}

text = (
    'ŃABQYĆVLHĄOHQKĆNVODGQVŹŁFIXDWUJOZQNXŃNMRHZŹVSUJDFCWUFKRYĘSUÓLIWZEĆFHĄZNŚĘRKN'
    'YRZXCSIKQKĘVZZSHAMĆULNBSHJTÓHINQDOWŹKŁGSDATFŹCJDNMYAABCWXQOŻKĘYXTCXŹGZQMĆBZI'
    'ĘZEXSŃLĄFŹPDVNYNVŹZCIOFSQŻZKGAPXÓŁRUŃŃIQRUÓŁNZSYHQPBLIMŻAOPĄWLNBCEŚXSZĄÓOCUA'
    'ZXTXCUJUĆIHĄNAGGIUNMBCBDXRQLOBIQOBYPIPZXXĘZĘONOTŹQIULUXHRNAKSHBŹĘTFXWZSĘĘÓBV'
    'IBJRAÓĘWWQŹZEĆDTNŹNŚ'
)
crib = 'KULTURY'

polish = {
    'A': .0891, 'Ą': .0099, 'B': .0147, 'C': .0396, 'Ć': .0040, 'D': .0325,
    'E': .0766, 'Ę': .0111, 'F': .0030, 'G': .0142, 'H': .0108, 'I': .0821,
    'J': .0228, 'K': .0351, 'L': .0210, 'Ł': .0182, 'M': .0280, 'N': .0552,
    'Ń': .0020, 'O': .0775, 'Ó': .0085, 'P': .0313, 'Q': .0001, 'R': .0469,
    'S': .0432, 'Ś': .0066, 'T': .0398, 'U': .0250, 'V': .0001, 'W': .0465,
    'X': .0001, 'Y': .0376, 'Z': .0564, 'Ż': .0083, 'Ź': .0006
}

def shift_back(s, shift):
    return ''.join(alphabet[(char2num[c] - shift) % len(alphabet)] for c in s)

def kasiski_method(text):
    occurances = {}
    length = 3
    for start in range(len(text) - length + 1):
        substring = text[start:start + length]
        if substring in occurances:
            occurances[substring].append(start)
        else:
            occurances[substring] = [start]
    return occurances

def ic(s):
    n = len(s)
    freqs = [s.count(c) for c in alphabet]
    ic_value = sum(f * (f - 1) for f in freqs) / (n * (n - 1)) if n > 1 else 0
    return ic_value

print("KASISKI")
occ = kasiski_method(text)
distances = []
for substring, positions in occ.items():
    if len(positions) > 1:
        for i in range(len(positions) - 1, 0, -1):
            distance = positions[i] - positions[i - 1]
            distances.append(distance)
            print(f"{substring}: {distance}")
print("gcd:", reduce(gcd, distances))

print("------------------------------------")
print("IC")
for key_len in range(1, 21):
    cols = [text[i::key_len] for i in range(key_len)]
    print(f"{key_len}: {sum(ic(c) for c in cols) / key_len:.4f}")

def best_shift(col, freq):
    def chi(shift):
        cnt = Counter(shift_back(col, shift))
        return sum((cnt[l] - len(col) * p) ** 2 / (len(col) * p) for l, p in freq.items())
    return min(range(len(alphabet)), key=chi)

def solve(key_len):
    columns = [text[i::key_len] for i in range(key_len)]
    shifts = [best_shift(col, polish) for col in columns]
    plaintext = [''] * len(text)
    for i, (col, shift) in enumerate(zip(columns, shifts)):
        plaintext[i::key_len] = shift_back(col, shift)
    return ''.join(alphabet[s] for s in shifts), ''.join(plaintext)

print("------------------------------------")
print("SOLVE VIGENERE")
for key_len in range(1, 21):
    key, plaintext = solve(key_len)
    print(f"{key_len}: {key} {'<-- contains ' + crib if crib in plaintext else ''}")
    if crib in plaintext:
        print(plaintext)
