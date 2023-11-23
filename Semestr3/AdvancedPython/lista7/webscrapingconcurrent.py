from bs4 import BeautifulSoup
import urllib.request
import re
import threading


visited = {}

url = 'https://ii.uni.wroc.pl/'





def crawl(start_page, distance, action):
    try:
        response = urllib.request.urlopen(start_page)
    except urllib.error.URLError:
        print('URL Error')
        return
    except urllib.error.HTTPError:
        print('HTTP Error')
        return
    except:
        print('Unknown Error')
        return
        
    html = response.read()
    soup = BeautifulSoup(html, 'html.parser')
    visited[start_page] = True
    try:
        res = action(html.decode('utf-8'))
    except UnicodeDecodeError:
        res = 'Failed to decode'
    yield (start_page, res)
    threads = []
    results = []
    if distance > 0:
        for link in soup.find_all('a', attrs={'href': re.compile("^https://")}):
            if link.get('href') not in visited:
                threads.append(threading.Thread(
                    target = lambda args, results: [results.append(result) for result in crawl(*args)],
                    args = ((link.get('href'), distance - 1, action), results)
                ))
        [thread.start() for thread in threads]
        [thread.join() for thread in threads]
        for result in results:
            yield result

for url, wynik in crawl(url, 2, lambda tekst: 'Python' in tekst):
    print(f'{url}: {wynik}')