import React from "react";
import { ItemProps, Item } from "./Item";
import { useState } from "react";

type List = ItemProps[];
const items: List = [];
export function ToDoList() {
  const [Items, setItems] = useState(items);
  const [Search, setSearch] = useState("");
  const [text, setText] = useState("");
  const [addText, setAddText] = useState("");
  const [Filter, setFilter] = useState("all");
  return (
    <>
      <div className="filters">
        <button onClick={() => setFilter("all")}>All</button>
        <button onClick={() => setFilter("active")} id="active">
          Active
        </button>
        <button onClick={() => setFilter("completed")} id="compl">
          Completed
        </button>
      </div>
      <div className="searches">
        <div className="search">
          <form>
            <input
              type="text"
              value={text}
              onChange={(e) => setText(e.target.value)}
              placeholder="Search"
            />
            <button
              onClick={(e) => {
                e.preventDefault();
                setSearch(text);
                setText("");
              }}
            >
              Filter
            </button>
          </form>
        </div>
        <div className="add">
          <form onSubmit={(e) => e.preventDefault()}>
            <input
              placeholder="Add new item"
              type="text"
              value={addText}
              onChange={(e) => setAddText(e.target.value)}
            />
            <button
              onClick={() => {
                if (addText === "") return;
                setItems([...Items, { text: addText, done: false }]);
                setAddText("");
              }}
            >
              Add
            </button>
          </form>
        </div>
      </div>
      <div className="todo-list">
        <ul>
          {Items.filter(
            (i) =>
              Filter === "all" ||
              (Filter === "active" && !i.done) ||
              (Filter === "completed" && i.done)
          )
            .filter((i) => i.text.includes(Search))
            .map((item) => (
              <Item
                {...item}
                onDelete={() => {
                  setItems(Items.filter((i) => i !== item));
                }}
                onDone={() => {
                  const updatedItems = Items.map((i) => {
                    if (i === item) {
                      const newItem = {...i, done: !i.done};
                      return newItem;
                    }
                    return i;
                  });
                  setItems(updatedItems);
                }}
              />
            ))}
        </ul>
      </div>
    </>
  );
}