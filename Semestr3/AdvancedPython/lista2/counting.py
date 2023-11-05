import os
os.chdir('Python/lista2')
# print(os.getcwd())
file = open('Potop.txt', 'r', encoding='utf-8')

def compression(text: str):
    res = []
    for c in text:
        if not res:
            res.append((c, 1))
        else:
            if res[-1][0] == c:
                temp = (c, res[-1][1] + 1)
                res.pop()
                res.append(temp)
            else:
                res.append((c, 1))
    return res

def decompression(lst: list):
    res = ''
    for c, n in lst:
        res += c * n
    return res

lst = compression('anna maaa krówkeeeeee')

print(lst)
print(decompression(lst))

lstPotop = compression(file.read())
print(lstPotop)
print(decompression(lstPotop))