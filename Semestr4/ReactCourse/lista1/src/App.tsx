import "./styles.css";
import React from "react";
import Card from "./components/Card";

const text: string =
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

export default function App() {
  return (
    <div className="App">
      <Card
        image={{
          image: "https://via.placeholder.com/150",
          alt: "John Doe",
        }}
        info={{
          name: "John Doe",
          number: "123-456-7890",
          email: "dHqQ8@example.com",
        }}
        position="Software Developer"
        aboutMe={text}
        skill={
          [
            {
              name: "C++",
              level: 5,
            },
            {
              name: "Python",
              level: 3,
            },
          ]        
        }
      />
    </div>
  );
}
