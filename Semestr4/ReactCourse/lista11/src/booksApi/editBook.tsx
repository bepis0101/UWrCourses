import { IBook } from '../types/types';
import { useMutation, useQueryClient } from '@tanstack/react-query';

async function editBook(book: IBook) {
    const res = await fetch(`http://localhost:3000/books/${book.id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(book)
    });
    return await res.json();
}

export default function useEditBook() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: editBook,
    onSuccess: () => {
      queryClient.invalidateQueries({
        queryKey: ['books', 'list']
      });
    }
  });
}