export interface IBook {
  "id": string,
  "title": string,
  "author": string,
  "year": number,
  "description": string,
  "copies": number,
  "price": number,
  "genreId": string,
}

export interface IGenre {
  "id": string,
  "name": string,
}