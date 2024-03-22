import { useState } from 'react'
import { RecipeProvider } from './providers/RecipeProvider/RecipeProvider'
import { RecipeList } from './components/RecipeList'
import { RecipeAdd } from './components/RecipeAdd'
import { RecipeFilter } from './components/RecipeFilter';


function App() {
  const [favorite, setFavorite] = useState<boolean>(false);
  const [filter, setFilter] = useState<string>("");

  return (
    <div className='container'>    
      <RecipeProvider>
        <div className='done'>
        <RecipeFilter 
          setOnlyFavorites={() => setFavorite(!favorite)}
          onlyFavorites={favorite}
          setFilter={setFilter}
          filter={filter}
          />
        <RecipeList 
          filter={filter}
          favorites={favorite}
        />
        </div>
        <RecipeAdd />
      </RecipeProvider>
    </div>
  );
}

export default App
