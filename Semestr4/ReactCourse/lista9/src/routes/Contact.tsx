import '../index.css';
import Avatar from '@mui/material/Avatar';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import ListItemAvatar from '@mui/material/ListItemAvatar';

export default function Contact() {
  return (
    <div className="content">
      <h1>
        Contact me:
      </h1>
      <List>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/email.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Email" secondary="borysadamiak101@gmail.com"/>
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/linkedin.png" />
            </Avatar>
          </ListItemAvatar>
          <a className='links' href="https://www.linkedin.com/in/borys-adamiak-3b5b8b1b3/">
            <ListItemText primary="LinkedIn" secondary="https://www.linkedin.com/in/borys-adamiak-3b5b8b1b3/"/>
          </a>
        </ListItem>
        <ListItem>
          <ListItemAvatar>
            <Avatar>
              <img src="https://img.icons8.com/material-outlined/24/000000/phone.png" />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Phone number" secondary="+48 698 715 253"/>
        </ListItem>
      </List>
    </div>
  );
}