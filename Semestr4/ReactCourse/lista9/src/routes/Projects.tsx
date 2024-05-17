import '../index.css';


export default function Projects() {
  return (
    <div className="content">
      <h1>Projects:</h1>
      <ul id="projects">
        <li>
          <a href="https://github.com/bepis0101/OnlineShop">
            <h2>Star Wars merch</h2>
            <p>
              Backend implementation of a Star Wars merchandise store in express.js
            </p>
          </a>
        </li>
        <li>
          <a href="https://github.com/bepis0101/Pentago">
            <h2>
              Pentago with GUI
            </h2>
            <p>
              Pentago game implementation with a GUI in pygame library in python
            </p>
          </a>
        </li>
        <li>
          <a href="/">
            <h2>
              My Portfolio
            </h2>
            <p>
              This website was created with React and TypeScript
            </p>
          </a>
        </li>
        <li>
          <a href="">
            <h2>
              Tetris
            </h2>
            <p>
              Group project in C++ with ncurses library
            </p>
          </a>
        </li>
      </ul>
    </div>
  );
}