export default function Menu({ score, onclick }: { score: number, onclick: () => void }){
  return (
    <div className="container">
      <h1>Quiz Over!</h1>
      <h2>Your score is {score}</h2>
      <h2>High Score: {localStorage.highScore}</h2>
      <button className="categoryButton" onClick={onclick}>Play Again</button>
    </div>
  );
}