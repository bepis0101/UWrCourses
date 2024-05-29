
export default async function fetchGenre(id: string) {
  try {
    const res = await fetch(`http://localhost:3000/genres/${id}`);
    return await res.json();
  } catch (error) {
    return error;
  }
}
