import { useQuery } from "@tanstack/react-query";

async function fetchGenres() {
  const response = await fetch("http://localhost:3000/genres");
  const data = await response.json();
  return data;
}

export default function useGenres() {
  return useQuery({
    queryKey: ["genres", "list"],
    queryFn: fetchGenres,
  });
}