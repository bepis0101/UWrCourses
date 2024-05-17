import '../index.css';
import Avatar from '@mui/material/Avatar';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import ListItemAvatar from '@mui/material/ListItemAvatar';

export default function AboutMe() {
  return (
    <div className="content">
      <h1>
        About me:
      </h1>
      
      <p>
        I am a software engineer with a passion for learning and creating new things. 
        I speak polish and english fluently and I am currently learning german and spanish.
        I am looking for a software engineering internship based basically anyehere in the world.
        I am passionate about Star Wars, snowboarding, and sailing.
      </p>
      <h2>Education:</h2>
      <List>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/school.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="University of Wroclaw" secondary="Bachelor's degree in Computer Science" />
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/school.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="XIVLO in Wrocław" secondary="High school" />
        </ListItem>
      </List>
      <h2>Experience:</h2>
      <List>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/work.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Software Engineering Intern at Google" secondary="2021" />
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/work.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Software Engineering Intern at Facebook" secondary="2020" />
        </ListItem>
      </List>
      <h2>Skills:</h2>
      <List>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/code.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Programming" secondary="C++, Python, Java, JavaScript, TypeScript" />
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/code.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Frameworks" secondary="React, Angular, Vue, Django, Flask" />
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/code.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Databases" secondary="SQL, NoSQL, MongoDB, MySQL, PostgreSQL" />
        </ListItem>
      </List>
    </div>
  );
}