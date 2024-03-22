import { useState } from "react";
import { useRecipe } from "../providers/RecipeProvider/useRecipe";

export function RecipeAdd() {
    const { addRecipe } = useRecipe();
    const [title, setTitle] = useState<string>("");
    const [ingredients, setIngredients] = useState<string[]>([]);
    const [instructions, setInstructions] = useState<string>("");
    const [error, setError] = useState(false);

    function submitRecipe(event: any) {
        event.preventDefault();
        if(title.trim() !== "" && ingredients.length > 0 && instructions.trim() !== "") {
            addRecipe({
                id: Math.floor(Math.random() * 100000000),
                title: title,
                isFavorite: false,
                ingredients: ingredients,
                instructions: instructions,
            });
            setTitle("");
            setIngredients([]);
            setInstructions("");
            setError(false);
        } else {
            setError(true);
        }
    }

    return (
        <div className="recipeadder">
            <form onSubmit={submitRecipe}>
                <input 
                    type="text"
                    placeholder="Recipe name"
                    value={title}
                    onChange={(event) => setTitle(event.target.value)}
                />
                <textarea 
                    placeholder="Ingredients (separated by ,)"
                    value={ingredients}
                    onChange={(event) => setIngredients(event.target.value.split(","))}/>
               <textarea
                    placeholder="Instructions"
                    value={instructions}
                    onChange={(event) => setInstructions(event.target.value)} 
                />
                <button type="submit">
                    Add Recipe
                </button>
                {error && <p>Invalid input</p>}
            </form>
        </div>
    )

}