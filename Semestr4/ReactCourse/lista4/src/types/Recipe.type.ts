export interface IRecipe {
  id: number;
  title: string;
  isFavorite: boolean;
  ingredients: string[];
  instructions: string;
}