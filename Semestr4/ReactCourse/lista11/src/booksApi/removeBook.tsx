export default async function removeBook(id: string) {
    const res = await fetch(`http://localhost:3000/books/${id}`, {
        method: 'DELETE',
        headers: {
          'Content-Type': 'application/json'
        }
    });
    return await res.json();
}
