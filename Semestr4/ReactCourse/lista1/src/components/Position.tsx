import React from "react";

interface PositionProps {
  position: string;
}

export default function Position({ position }: PositionProps) {
  return (
    <>
      <div className="position">
        <h3>{position}</h3>
      </div>
    </>
  );
}
