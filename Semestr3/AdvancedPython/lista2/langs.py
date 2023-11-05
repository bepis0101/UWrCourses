from urllib import request
import re

def calcLang(url, lang: dict = {}) -> dict:
    s = request.urlopen(url).read().decode('utf-8')
    s = s.lower()
    s = re.sub(r'[^a-zA-Z]', '', s)
    for c in s:
        if c in lang:
            lang[c] += 1
        else:
            lang[c] = 1
    for k, v in lang.items():
        lang[k] = v / len(s)
    return lang


def guessLang(langs, url):
    calculations = calcLang(url)
    mini = 1
    lang = ''
    for name, d, _ in langs:
        if len(d) == 0: 
            continue

        stat = 0
        for k, v in d.items():
            if k in calculations: 
                stat += abs(v - calculations[k])
            else: 
                stat += v
        stat /= len(d)

        if stat < mini:
            mini = stat
            lang = name

    return lang

polish = {}
italian = {}
german = {}

polishUrls = [
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_I',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_II',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_III',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_IV',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_VI',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_VII',
]

italianUrls = [
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/I',
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/II',
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/III',
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/IV',
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/V',
    'https://it.wikisource.org/wiki/Viaggio_al_centro_della_Terra/VI',
]

germanUrls = [
    'https://de.wikisource.org/wiki/Der_Fahrgast',
    'https://de.wikisource.org/wiki/Der_Kaufmann_(Kafka)',
    'https://de.wikisource.org/wiki/Aus_Matl%C3%A1rh%C3%A1za',
    'https://de.wikisource.org/wiki/Der_Prozess/2._Kapitel',
    'https://de.wikisource.org/wiki/Der_Prozess/3._Kapitel',
    'https://de.wikisource.org/wiki/Vor_dem_Gesetz',

]

languages = [
    ('polish', polish, polishUrls),
    ('italian', italian, italianUrls),
    ('german', german, germanUrls),
]

for name, d, urls in languages:
    for url in urls:
        d = calcLang(url, d)

tests = [
    'https://it.wikisource.org/wiki/La_giunta_romana_ed_il_comizio_popolare_del_22_settembre_1870/Prefazione',
    'https://pl.wikisource.org/wiki/Potop_(Sienkiewicz)/Tom_I/Rozdzia%C5%82_V',
    'https://de.wikisource.org/wiki/Der_Prozess/1._Kapitel',

]

for url in tests:
    print(guessLang(languages, url))