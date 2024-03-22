import { createContext, useReducer } from "react";
import { IRecipe } from "../../types/Recipe.type";
import { recipeReducer } from "./recipeReducer";


export const RecipeContext = createContext<{
  recipies: IRecipe[];
  addRecipe: (recipe: IRecipe) => void;
  removeRecipe: (id: number) => void;
  toggleFavorite: (id: number) => void;
}>({
  recipies: [],
  addRecipe: () => {},
  removeRecipe: () => {},
  toggleFavorite: () => {}
});

const initialRecipes: IRecipe[] = [
  {
    id: 1,
    title: "Spaghetti",
    isFavorite: false,
    ingredients: ["pasta", "tomato sauce", "meatballs"],
    instructions: "Cook the pasta, add the tomato sauce and meatballs"
  }
]

export const RecipeProvider = ({ children }: { children: React.ReactNode }) => {
  const [recipies, dispatchRecipe] = useReducer(recipeReducer, initialRecipes);

  function addRecipe(recipe: IRecipe) {
    dispatchRecipe({ type: "ADD_RECIPE", payload: recipe });
  }

  function removeRecipe(id: number) {
    dispatchRecipe({ type: "REMOVE_RECIPE", payload: id });
  }

  function toggleFavorite(id: number) {
    dispatchRecipe({ type: "TOGGLE_FAVORITE", payload: id });
  }

  return (
    <RecipeContext.Provider value={{ recipies, addRecipe, removeRecipe, toggleFavorite }}>
      {children}
    </RecipeContext.Provider>
  )
}