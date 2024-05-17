import React, { useState, useEffect } from 'react';
import './index.css';


interface Potion {
  name: string;
  image: string;
  effect: string;
  ingredients: string;
  wikiLink: string;
}

interface Spell {
  name: string;
  image: string;
  effect: string;
  ingredients: string;
  wiki: string;
}

async function getSpells() {
  const res = await fetch(`https://api.potterdb.com/v1/spells`);
  const data = await res.json();
  return data;
}

async function getPotions() {
  const res = await fetch(`https://api.potterdb.com/v1/potions`);
  const data = await res.json();
  return data;
}

function shuffleArray(array: any[]) {
  return [...array].sort(() => Math.random() - 0.5);
}

function randomNames(items: (Potion | Spell)[], correct: string, limit: number) {
  const shuffled = shuffleArray(items);
  const unique = new Set<string>();
  shuffled.forEach((item) => {
      if(item.name !== correct && unique.size < limit) {
        unique.add(item.name)
      }
    }
  );
  unique.add(correct);

  return Array.from(unique).sort(() => Math.random() - 0.5);
}



function App() {
  const [loading, setLoading] = useState(false);
  const [score, setScore] = useState(0);
  const [start, setStart] = useState(false);
  const [potions, setPotions] = useState<Potion[]>([]);
  const [spells, setSpells] = useState<Spell[]>([]);
  const [round, setRound] = useState(0);
  const [category, setCategory] = useState<null | 'potions' | 'spells'>(null);
  const [highScore, setHighScore] = useState(0);

  function updateHighScore() {
    if(score > highScore) {
      localStorage.setItem('highScore', score.toString());
      setHighScore(score);
    }
  }
  const handleStart = (category: 'potions' | 'spells') => {
    setCategory(category);
    setStart(true);
    setScore(0);
    setRound(0);
  }

  return (

    <div className="container">
      
    </div>
  )
}

export default App
