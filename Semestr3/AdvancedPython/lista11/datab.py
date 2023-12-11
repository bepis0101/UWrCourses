from __future__ import annotations
from sqlalchemy import Table, Column, Integer, String, ForeignKey, create_engine
from sqlalchemy.orm import DeclarativeBase, relationship, mapped_column, Mapped, sessionmaker, validates
from typing import List
import argparse

engine = create_engine('sqlite:///library.db', echo=True)

class Base(DeclarativeBase):
    pass

class Book(Base):
    @validates('author')
    def validate_author(self, key, author):
        if author == '':
            raise ValueError('Author cannot be empty')
        return author
    __tablename__ = 'Books'
    id = mapped_column(Integer, primary_key=True)
    author = mapped_column(String, primary_key=False)
    title = mapped_column(String, primary_key=False)



class Friends(Base):
    __tablename__ = 'Friends'
    id = mapped_column(Integer, primary_key=True)
    @validates('name')
    def validate_name(self, key, name):
        if name == '':
            raise ValueError('Name cannot be empty')
        return name
    @validates('surname')
    def validate_surname(self, key, surname):
        if surname == '':
            raise ValueError('Surname cannot be empty')
        return surname
    
    name = mapped_column(String, primary_key=False)
    surname = mapped_column(String, primary_key=False)
    email = mapped_column(String, primary_key=False)

class Borrowed(Base):
    __tablename__ = 'Borrowed'
    id = mapped_column(Integer, primary_key=True)
    book_id = mapped_column(Integer, ForeignKey('Books.id'))
    friend_id = mapped_column(Integer, ForeignKey('Friends.id'))
    book = relationship('Book', back_populates='Borrowed')
    friend = relationship('Friends', back_populates='Borrowed')


session = sessionmaker(engine)
with session() as s:
    # tests
    b = [
        Book(author='Adam Mickiewicz', title='Pan Tadeusz'),
        Book(author='Henryk Sienkiewicz', title='W pustyni i w puszczy'),
        Book(author='Henryk Sienkiewicz', title='Krzyżacy'),
        Book(author='Adam Mickiewicz', title='Dziady'), 
        Book(author='Bolesław Prus', title='Lalka')
    ]
    s.add_all(b)
    f = [
        Friends(name='Jan', surname='Kowalski', email='b@a.com'),
        Friends(name='Adam', surname='Nowak', email='a@b.net')
    ]
    s.add_all(f)
    bor = [
        Borrowed(book_id=1, friend_id=1),
        Borrowed(book_id=2, friend_id=1),
        Borrowed(book_id=3, friend_id=2),
        Borrowed(book_id=4, friend_id=2),
        Borrowed(book_id=5, friend_id=2)
    ]
    s.add_all(bor)
    s.commit()
    lista = s.query(Book).filter(Book.author == 'Adam Mickiewicz').all()
    print(lista)
    lista = s.query(Borrowed).filter(Borrowed.friend_id == 1).all()
    print(lista)