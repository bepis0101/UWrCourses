import { useTheme } from "../providers/Theme";


export default function Navbar(elements: string[]) {
  const { theme, toggleTheme } = useTheme();

  return (
    <div className="navbar">
      {elements.map((element) => (
        <a href={`#${element.toLowerCase()}`}>{element}</a>
      ))}

      <button onClick={toggleTheme} className="theme-toggle-button">
        {theme === "light" ? "Light Mode" : "Dark Mode"}
      </button>
    </div>
  )
}