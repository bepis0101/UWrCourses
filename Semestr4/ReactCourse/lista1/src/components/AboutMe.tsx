import React from "react";

interface AMProps {
  text: string;
}

export default function AboutMe({ text }: AMProps) {
  return (
    <div className="about-me">
      <h2>About Me</h2>
      <p>{text}</p>
    </div>
  );
}
