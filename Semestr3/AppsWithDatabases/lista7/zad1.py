from pymongo import MongoClient

client = MongoClient('localhost', 27017)
library = client['library']
booksCollection = library['books1']
booksCollection.insert_many([
    {"title": "Book1", "author": "Author1", "year": 2020},
    {"title": "Book2", "author": "Author2", "year": 2021},
    {"title": "Book3", "author": "Author3", "year": 2022}
])
print("Books:")

for book in booksCollection.find():
    print(book)