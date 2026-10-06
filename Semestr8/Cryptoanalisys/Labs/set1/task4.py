from collections import Counter

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def move_by_n(text, n):
    result = ""
    for char in text:
        c = chr((ord(char) - ord('A') + n ) % 26 + ord('a'))
        result += c
    return result

text = "FDGEFYQUMYMODKBFASDMBTQD"
print("SOLVE CEASAR CIPHER")
for n in range(1, 26):
    print(f"{n}: {move_by_n(text, n)}")

print("------------------------------------")
print("SOLVE VIGENERE")

text2 = 'XHQPMFTFSJBHAMEHGIGHISHLPHLJAECWRVSRJWXNQECBSIQSCQSRHERWTWSVLVMRVLJAECWRVSRJWXNQECBSIFIHCPKS'
english = {
    'A': .082, 'B': .015, 'C': .028, 'D': .043, 'E': .127, 'F': .022,
    'G': .020, 'H': .061, 'I': .070, 'J': .002, 'K': .008, 'L': .040,
    'M': .024, 'N': .067, 'O': .075, 'P': .019, 'Q': .001, 'R': .060,
    'S': .063, 'T': .091, 'U': .028, 'V': .010, 'W': .024, 'X': .002,
    'Y': .020, 'Z': .001
}

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

occ = kasiski_method(text2)
for substring, positions in occ.items():
    if len(positions) > 1:
        for i in range(len(positions) - 1, 0, -1):
            distance = positions[i] - positions[i - 1]
            print(f"{substring}: {distance}")

# 39 = 3 * 13 two candidates for key length
columns = [text2[i::3] for i in range(3)]
print([ic(segment) for segment in columns])

def best_shift(col, freq):
    def chi(shift):
        dec = [chr((ord(c) - ord('A') - shift) % len(alphabet) + ord('A')) for c in col]
        cnt = Counter(dec)
        return sum((cnt[l] - len(col) * p) ** 2 / (len(col) * p) for l, p in freq.items())
    return min(range(26), key=chi)

results = []

for col in columns:
    shift = best_shift(col, english)
    decoded_col = ''.join(chr((ord(c) - ord('A') - shift) % len(alphabet) + ord('A')) for c in col)
    results.append(decoded_col)

plaintext = [''] * len(text2)
for i, decoded_col in enumerate(results):
    plaintext[i::3] = decoded_col
print(''.join(plaintext))