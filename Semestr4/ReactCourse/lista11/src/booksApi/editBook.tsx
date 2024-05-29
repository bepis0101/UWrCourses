import { IBook } from '../types/types';
export default async function editBook(book: IBook) {
    const res = await fetch(`http://localhost:3000/books/${book.id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(book)
    });
    return await res.json();
}

