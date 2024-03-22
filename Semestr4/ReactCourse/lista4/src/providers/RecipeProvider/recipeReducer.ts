import { IRecipe } from "../../types/Recipe.type";

type RecipeAction = 
  | {
      type: "ADD_RECIPE";
      payload: IRecipe;
    }
  | {
      type: "REMOVE_RECIPE";
      payload: number;
    }
  | {
      type: "TOGGLE_FAVORITE";
      payload: number;
    };

export const recipeReducer = (state: IRecipe[], action: RecipeAction) => {
  switch (action.type) {
    case "ADD_RECIPE":
      return [
        ...state,
        action.payload
      ]
    case "REMOVE_RECIPE":
      return state.filter(recipe => recipe.id !== action.payload);
    case "TOGGLE_FAVORITE":
      return state.map((recipe) => {
        if (recipe.id === action.payload) {
          return {
            ...recipe,
            isFavorite: !recipe.isFavorite
          }
        }
        return recipe;
      });
    default:
      return state;
  }
}