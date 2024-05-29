
export default async function fetchGenres() {
  const response = await fetch("http://localhost:3000/genres");
  const data = await response.json();
  return data;
}
