export default function Question({ effect }: { effect: string }) {
  return (
    <div className="question">
      <p>{effect}</p>
    </div>
  )
}