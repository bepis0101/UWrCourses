import asyncio
import aiohttp
from prywatne import apiKey as api_key

async def fetch(session, url):
    async with session.get(url) as response:
        res = await response.text()
    return res


async def fetch_weather(api_key, lat, lon):
    url = f'https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={api_key}'
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            return await response.json()

urls = ['https://jsonplaceholder.typicode.com/todos/1', 'https://jsonplaceholder.typicode.com/posts/1']

async def testNoKey():
    async with aiohttp.ClientSession() as session:
        reqs = [fetch(session, url) for url in urls]
        pages = await asyncio.gather(*reqs)
        for page in pages:
            print(page)

async def testKey():
    async with aiohttp.ClientSession() as session:
        reqs = [fetch_weather(api_key, 52, 21)]
        pages = await asyncio.gather(*reqs)
        for page in pages:
            print(page)

asyncio.run(testNoKey())
asyncio.run(testKey())
