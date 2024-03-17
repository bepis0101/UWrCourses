import React from "react";
import { useState } from "react";
import { ToDoList } from "./ToDoList";
export function Container() {
  const [items, setItems] = useState([]);

  return (
    <div className="container">
      <h1>TO DO LIST</h1>
      <ToDoList />
    </div>
  );
}