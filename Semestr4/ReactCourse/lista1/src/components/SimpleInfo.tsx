import React from "react";

interface InfoProps {
  name: string;
  number: string;
  email: string;
}

export default function Info({ name, number, email }: InfoProps) {
  return (
    <div className="info">
      <h2>{name}</h2>
      <p>{number}</p>
      <p>{email}</p>
    </div>
  );
}
export { InfoProps };
