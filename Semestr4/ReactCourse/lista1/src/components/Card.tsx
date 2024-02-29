import React from "react";
import Image from "./Image";
import { ImageProps } from "./Image";
import Info from "./SimpleInfo";
import { InfoProps } from "./SimpleInfo";
import Position from "./Position";
import AboutMe from "./AboutMe";
import Skills from "./Skills";
import { SkillsProps } from "./Skills";

interface CardProps {
  image: ImageProps;
  info: InfoProps;
  position: string;
  aboutMe: string;
  skill: SkillsProps;
}

export default function Card({
  image,
  info,
  position,
  aboutMe,
  skill,
}: CardProps) {
  return (
    <div className="card">
      <Image image={image.image} alt={image.alt} />
      <Info name={info.name} number={info.number} email={info.email} />
      <Position position={position} />
      <AboutMe text={aboutMe} />
      <Skills skill={skill.skill} />
    </div>
  );
}
