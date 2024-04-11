
interface HeaderProps {
  name: string;
  slogan: string;

}

export default function Header({ name, slogan }: HeaderProps) {
  return (
    <header id="header" className="header">
      <div className="header-content">
        <h1>{name}</h1>
        <p>{slogan}</p>
      </div>
    </header>
  );
}