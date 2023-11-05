import random, os
def simplifyText(text: str, lengthOfWord: int, numOfWords: int) -> str:
    res = ''
    res = filter(lambda s: len(s) <= lengthOfWord, text.split())
    res = list(res)
    while len(res) > numOfWords:
        res.pop(random.randint(0, len(res) - 1))
    res = ' '.join(res)
    return res


print(simplifyText('ala ma kota a kot ma aleeeee', 3, 5))
os.chdir('Python/lista2')
file = open('Potop.txt', 'r', encoding='utf-8')
print(simplifyText(file.read().replace('—', ''), 5, 100))