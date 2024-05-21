export default function Button({ name, onClick }: { 
    name: string, 
    onClick: () => void, 
  }) {
  return (
    <button className="answerButton" onClick={onClick}>{name}</button>
  )
}