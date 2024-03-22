import { IRecipe } from "../types/Recipe.type";
import { useRecipe } from "../providers/RecipeProvider/useRecipe";

export function Recipe(recipe: IRecipe) {
    const { removeRecipe, toggleFavorite } = useRecipe();

    return (
        <>
            <li>
                <h2>{recipe.isFavorite ? recipe.title + '⭐' : recipe.title}</h2>
                <div className="hidden">
                    <ul>
                        {recipe.ingredients.map((ingredient, index) => (
                            <li key={index}>{ingredient}</li>
                        ))}
                    </ul>
                    <p>{recipe.instructions}</p>
                </div>
                <div className="buttons">
                <button className="remove" onClick={() => removeRecipe(recipe.id)}>Remove</button>
                <button className="addfav" onClick={() => toggleFavorite(recipe.id)}>Favorite</button>
                </div>
            </li>
        </>
    )
}