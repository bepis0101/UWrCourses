import React from "react";

type Skill = {
  name: string;
  level: number;
};

export interface SkillsProps {
  skill: Skill[];
}

function stars(n: number): string {
  let s: string = "";
  for (let i = 0; i < n; i++) {
    s += "⭐";
  }
  return s;
}

export default function Skills({ skill }: SkillsProps) {
  return (
    <div className="skillZ">
      <h2>Skills</h2>
      <ul>
        {skill.map(({ name, level }) => {
          return (
            <li className="skill">
              <div>{name}</div>
              <div>{stars(level)}</div>
            </li>
          );
        })}
      </ul>
    </div>
  );
}
