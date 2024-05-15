import React from "react";
import '../index.css';
import Avatar from '@mui/material/Avatar';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import ListItemAvatar from '@mui/material/ListItemAvatar';

export default function Home() {
  return (
    <div className="content">
      <Avatar
        alt="Remy Sharp"
        src="https://avatars.githubusercontent.com/u/1014995?v=4"
        sx={{ width: 200, height: 200, position: 'absolute', top: '30%', left: '80%' }}
      />
      <h1>
        Borys Adamiak
      </h1>
      <h2>
        Software Engineer
      </h2>
     <h4>
     Here are some of my socials: 
     </h4>
      <List>
        <a href="https://github.com/bepis0101">
          <ListItem>
            <ListItemAvatar>
              <Avatar>
                <img src="https://img.icons8.com/material-outlined/24/000000/github.png" />
              </Avatar>
            </ListItemAvatar>
            <ListItemText primary="Github" />
          </ListItem>
        </a>
        <a href="https://www.linkedin.com/in/borys-adamiak-b08583279/">
          <ListItem>
            <ListItemAvatar>
              <Avatar>
                <img src="https://img.icons8.com/material-outlined/24/000000/linkedin.png" />
              </Avatar>
            </ListItemAvatar>
            <ListItemText primary="LinkedIn" />
          </ListItem>
        </a>
      </List>

    </div>
  );
}