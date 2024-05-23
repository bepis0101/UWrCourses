import { useQuery } from "@tanstack/react-query";

async function fetchGenre(id: string) {
  try {
    const res = await fetch(`http://localhost:3000/genres/${id}`);
    return await res.json();
  } catch (error) {
    return error;
  }
}

export default function useGenre(id: string) {
  return useQuery({
    queryKey: ["genres", "genre", id],
    queryFn: () => fetchGenre(id),
  });
}
