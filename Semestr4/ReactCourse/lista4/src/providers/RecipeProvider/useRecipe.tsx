import { useContext } from 'react';
import { RecipeContext } from './RecipeProvider';

export function useRecipe() {
  return useContext(RecipeContext);
}
