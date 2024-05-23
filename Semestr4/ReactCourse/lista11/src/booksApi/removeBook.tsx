import { useMutation, useQueryClient } from '@tanstack/react-query';

async function removeBook(id: string) {
    const res = await fetch(`http://localhost:3000/books/${id}`, {
        method: 'DELETE',
        headers: {
          'Content-Type': 'application/json'
        }
    });
    return await res.json();
}

export default function useRemoveBook() {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: removeBook,
    onSuccess: () => {
      queryClient.invalidateQueries({
        queryKey: ['books', 'list']
      });
    }
  });
}