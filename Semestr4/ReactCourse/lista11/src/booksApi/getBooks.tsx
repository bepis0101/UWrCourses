
export default async function fetchBooks() {
  const response = await fetch("http://localhost:3000/books");
  const data = await response.json();
  return data;
}
