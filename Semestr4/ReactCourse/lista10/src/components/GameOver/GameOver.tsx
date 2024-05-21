export default function GameOver({onclickpotions, onclickspells}: { onclickpotions: () => void, onclickspells: () => void }){
  
  return (
  <div className="container">
    <h1>Harry Potter Quiz</h1>
    <button className="categoryButton" onClick={onclickpotions}>Start Potions Quiz</button>
    <button className="categoryButton" onClick={onclickspells}>Start Spells Quiz</button>
    <h2>High Score: {localStorage.highScore}</h2>
  </div>
  );
}