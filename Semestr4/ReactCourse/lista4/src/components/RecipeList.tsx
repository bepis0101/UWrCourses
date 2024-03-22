import { Recipe } from "./Recipe";
import { useRecipe } from "../providers/RecipeProvider/useRecipe";

interface RecipeFilterProps {
  filter: string;
  favorites: boolean;
}

export function RecipeList({ filter, favorites }: RecipeFilterProps) {
  const { recipies } = useRecipe();
  return (
    <div className="lista">
      <ul>
      {recipies
        .filter((recipe) => (
         (favorites ? recipe.isFavorite : true) &&
         (recipe.title.toLowerCase().includes(filter.toLowerCase()) ||
          recipe.ingredients.join("").toLowerCase().includes(filter.toLowerCase()) ||
          recipe.instructions.toLowerCase().includes(filter.toLowerCase())
         )
        ))
        .map((recipe) => (
          <Recipe key={recipe.id} {...recipe} />
      ))}
      </ul>
    </div>
  );
}