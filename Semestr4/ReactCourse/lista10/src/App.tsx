import { useState, useEffect } from 'react';
import './index.css';
import Question from './components/Question/Question';
import Button from './components/AnsButton/Button';
import GameOver from './components/GameOver/GameOver';
import Menu from './components/Menu/Menu';

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
  wikiLink: string;
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
  const [isCorrect, setIsCorrect] = useState<null | boolean>(null);
  const [category, setCategory] = useState<null | 'potions' | 'spells'>(null);
  const [highScore, setHighScore] = useState(0);


  const handleStart = (category: 'potions' | 'spells') => {
    setCategory(category);
    setStart(true);
    setScore(0);
    setRound(0);
  }

  useEffect(() => {
    async function fetchData() {
      setLoading(true);
      const potions = await getPotions();
      const spells = await getSpells();
      const randomPotions = shuffleArray(potions.data).slice(0, 48).map((potion: any) => ({
        name: potion.attributes.name,
        image: potion.attributes.image,
        effect: potion.attributes.effect,
        ingredients: potion.attributes.ingredients,
        wikiLink: potion.attributes.wiki
      }));
      const randomSpells = shuffleArray(spells.data).slice(0, 48).map((spell: any) => ({
        name: spell.attributes.name,
        image: spell.attributes.image,
        effect: spell.attributes.effect,
        ingredients: spell.attributes.ingredients,
        wikiLink: spell.attributes.wiki
      }));
      setPotions(randomPotions);
      setSpells(randomSpells);
      setLoading(false);
    }
    fetchData();
  },[]);

  if(loading) {
    return <div>Loading...</div>
  }

  if(!start) {
    return (
      <>
        <GameOver onclickpotions={()=>handleStart('potions')} onclickspells={()=>handleStart('spells')} />      
      </>
    )

  }
  if(round === 10) {
   return (
    <>
      <Menu score={score} onclick={()=>setStart(false)} />
    </>
   )
  }

  const items = category === 'potions' ? potions : spells;
  let correct = items[Math.floor(Math.random() * items.length)];
  while(correct.name == "") {
    correct = items[Math.floor(Math.random() * items.length)];
  }
  const names = randomNames(items, correct.name, 3);


  return (
    <div className="container">
      <div className="round">Round: {round}/10</div>
      <Question effect={correct.effect} />
      <div className="options">
        {names.map((name) => (
          <Button key={name} name={name} onClick={() => {
            if(name === correct.name) {
              setScore(score + 1);
              if(score+1 > localStorage.highScore) {
                setHighScore(score+1);
                localStorage.setItem('highScore', (score+1).toString());
              }
              setIsCorrect(true);
            } else {
              setIsCorrect(false);
            }
            setRound(round + 1);
          }
          } />
        ))}
        </div>
        <div className="score">Score: {score}/{round}</div>
    </div>
  )
}

export default App
