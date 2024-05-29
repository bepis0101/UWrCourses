import { IBook } from "../types/types"; 

export default async function addBook(book: IBook) {
    const res = await fetch("http://localhost:3000/books", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(book),
    });
    return await res.json();
}