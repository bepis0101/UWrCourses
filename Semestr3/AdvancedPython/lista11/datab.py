from __future__ import annotations
from sqlalchemy import Table, Column, Integer, String, ForeignKey, create_engine
from sqlalchemy.orm import DeclarativeBase, relationship, mapped_column, Mapped, sessionmaker, validates
from sqlalchemy.orm.session import Session
from typing import List
import argparse

engine = create_engine('sqlite:///database.db', echo=True)

class Base(DeclarativeBase):
    pass

class Books(Base):
    __tablename__ = 'books'
    id = Column(Integer, primary_key=True)
    author = Column(String)
    title = Column(String)
    year = Column(Integer)

    @validates('year')
    def validate_year(self, key, value):
        assert value > 0 and value < 2024
        return value
    
class Friends(Base):
    __tablename__ = 'friends'
    id = Column(Integer, primary_key=True)
    name = Column(String)
    surname = Column(String)
    email = Column(String)

    @validates('age')
    def validate_age(self, key, value):
        assert value > 0 and value < 150
        return value
    
class Lends(Base):
    __tablename__ = 'lends'
    id = Column(Integer, primary_key=True)
    book_id = Column(Integer, ForeignKey('books.id'))
    friend_id = Column(Integer, ForeignKey('friends.id'))
    book = relationship("Books", backref="lends")
    friend = relationship("Friends", backref="lends")

Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

parser = argparse.ArgumentParser(description='Manage the database')
