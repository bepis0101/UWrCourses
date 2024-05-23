import { useQuery } from "@tanstack/react-query";

async function fetchBook(id: string) {
  try {
    const res = await fetch(`http://localhost:3000/books/${id}`);
    return await res.json();
  } catch (error) {
    return error;
  }
}

export default function useBook(id: string) {
  return useQuery({
    queryKey: ["books", "book", id],
    queryFn: () => fetchBook(id),
  });
}
