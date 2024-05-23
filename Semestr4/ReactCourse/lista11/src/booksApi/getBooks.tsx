import { useQuery } from "@tanstack/react-query";

async function fetchBooks() {
  const response = await fetch("http://localhost:3000/books");
  const data = await response.json();
  return data;
}

export default function useBooks( searchAuthor?: string, searchGenre?: string, searchTitle?: string ) {
  return useQuery({
    queryKey: ["books", "list", { searchAuthor, searchGenre, searchTitle }],
    queryFn: fetchBooks,
  });
}