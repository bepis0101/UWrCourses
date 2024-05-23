import { useMutation, useQueryClient } from "@tanstack/react-query";
import { IBook } from "../types/types"; 


async function addBook(book: IBook) {
    const res = await fetch("http://localhost:3000/books", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(book),
    });
    return await res.json();
}

export default function useAddBook() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: addBook,
    onSuccess: () => {
      queryClient.invalidateQueries({
        queryKey: ["books", "list"],
      });
      queryClient.invalidateQueries({
        queryKey: ["books", "list", { searchAuthor: "", searchGenre: "", searchTitle: "" }],
      });
    },
  });
}