import pymongo
from bson.objectid import ObjectId
from datetime import datetime
from datetime import timedelta

# Create a MongoClient to the running mongod instance
client = pymongo.MongoClient('localhost', 27017)

# Get the library database
db = client['library']

# Insert books
books = db['books']
books.delete_many({})
book1_id = books.insert_one({
    'title': 'Book 1',
    'author': 'Author 1',
    'isbn': 'ISBN1',
    'copies': [
        {'copy_number': 1, 'available': True},
        {'copy_number': 2, 'available': False},
        {'copy_number': 3, 'available': True}
    ]
}).inserted_id

book2_id = books.insert_one({
    'title': 'Book 2',
    'author': 'Author 2',
    'isbn': 'ISBN2',
    'copies': [
        {'copy_number': 1, 'available': True},
        {'copy_number': 2, 'available': True},
        {'copy_number': 3, 'available': False}
    ]
}).inserted_id

# Insert readers
readers = db['readers']
reader1_id = readers.insert_one({'name': 'Reader 1', 'email': 'reader1@example.com'}).inserted_id
reader2_id = readers.insert_one({'name': 'Reader 2', 'email': 'reader2@example.com'}).inserted_id

# Insert borrowings
borrowings = db['borrowings']
borrowings.insert_many([
    {'book_id': book1_id, 'reader_id': reader1_id, 'borrow_date': datetime.now(), 'return_date': datetime.now()+timedelta(days=7)},
    {'book_id': book1_id, 'reader_id': reader2_id, 'borrow_date': datetime.now(), 'return_date': datetime.now()+timedelta(days=7)},
    {'book_id': book2_id, 'reader_id': reader1_id, 'borrow_date': datetime.now(), 'return_date': datetime.now()+timedelta(days=7)},
    {'book_id': book2_id, 'reader_id': reader2_id, 'borrow_date': datetime.now(), 'return_date': datetime.now()+timedelta(days=7)}
])
books_schema = {
    '$jsonSchema': {
        'bsonType': 'object',
        'required': ['title', 'author', 'isbn', 'copies'],
        'properties': {
            'title': {
                'bsonType': 'string',
                'description': 'must be a string and is required'
            },
            'author': {
                'bsonType': 'string',
                'description': 'must be a string and is required'
            },
            'isbn': {
                'bsonType': 'string',
                'description': 'must be a string and is required'
            },
            'copies': {
                'bsonType': 'array',
                'description': 'must be an array and is required',
                'items': {
                    'bsonType': 'object',
                    'required': ['copy_number', 'available'],
                    'properties': {
                        'copy_number': {
                            'bsonType': 'int',
                            'description': 'must be an integer and is required'
                        },
                        'available': {
                            'bsonType': 'bool',
                            'description': 'must be a boolean and is required'
                        }
                    }
                }
            }
        }
    }
}
readers_schema = {
    '$jsonSchema': {
        'bsonType': 'object',
        'required': ['name', 'email'],
        'properties': {
            'name': {
                'bsonType': 'string',
                'description': 'must be a string and is required'
            },
            'email': {
                'bsonType': 'string',
                'description': 'must be a string and is required'
            }
        }
    }
}

# Validation schema for borrowings
borrowings_schema = {
    '$jsonSchema': {
        'bsonType': 'object',
        'required': ['book_id', 'reader_id', 'borrow_date'],
        'properties': {
            'book_id': {
                'bsonType': 'objectId',
                'description': 'must be an objectId and is required'
            },
            'reader_id': {
                'bsonType': 'objectId',
                'description': 'must be an objectId and is required'
            },
            'borrow_date': {
                'bsonType': 'date',
                'description': 'must be a date and is required'
            },
            'return_date': {
                'bsonType': 'date',
                'description': 'must be a date'
            }
        }
    }
}

client.library.command('collMod', 'books', validator=books_schema)
client.library.command('collMod', 'readers', validator=readers_schema)
client.library.command('collMod', 'borrowings', validator=borrowings_schema)

## Task 4

# Get the full documents list, sorted in an explicit order, and limited to the middle 2 items
result = books.find().sort('_id', pymongo.ASCENDING).skip(1).limit(2)

for document in result:
    print(document)

result = books.find({'copies.available': True})

for document in result:
    print(document)