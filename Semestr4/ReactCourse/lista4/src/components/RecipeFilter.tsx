interface FilterProps {
    setOnlyFavorites: () => void;
    onlyFavorites: boolean;
    setFilter: (filter: string) => void;
    filter: string;
}

export function RecipeFilter({ setOnlyFavorites, onlyFavorites, setFilter, filter }: FilterProps) {
    return (
        <div className="filtercontainer">
            <input
                type="text"
                value={filter}
                onChange={(e) => setFilter(e.target.value)}
                placeholder="lookin for something?"
            />
            <button onClick={setOnlyFavorites}>
                {onlyFavorites ? "Show All" : "Show Only Favorites"}
            </button>
        </div>
    );
}