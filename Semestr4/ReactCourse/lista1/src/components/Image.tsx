import React from "react";

interface ImageProps {
  image: string;
  alt: string;
}

export default function Image({ image, alt }: ImageProps) {
  return (
    <div className="image">
      <img src={image} alt={alt} />
    </div>
  );
}
export { ImageProps };
