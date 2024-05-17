import { NavLink, Outlet, useLocation } from "react-router-dom";
import { Tabs, Tab } from "@mui/material";
import HomeSharpIcon from '@mui/icons-material/HomeSharp';
import InsertEmoticonSharpIcon from '@mui/icons-material/InsertEmoticonSharp';
import AccountTreeSharpIcon from '@mui/icons-material/AccountTreeSharp';
import AlternateEmailSharpIcon from '@mui/icons-material/AlternateEmailSharp';

export default function RootLayout() {
  const location = useLocation();
  return (
    <div className="navigation">
      <nav>
        <Tabs sx={{
          margin: '10px',
        }}>
          <Tab sx={{
            color: location.pathname === '/' ? 'black' : 'gray',
          }} label="Home" component={NavLink} to="/" icon={<HomeSharpIcon />}/>
          <Tab sx={{
            color: location.pathname === '/about' ? 'black' : 'gray',
          }} label="About Me" component={NavLink} to="/about" icon={<InsertEmoticonSharpIcon />} />
          <Tab sx={{
            color: location.pathname === '/projects' ? 'black' : 'gray',
          }} label="Projects" component={NavLink} to="/projects" icon={<AccountTreeSharpIcon />} />
          <Tab sx={{
            color: location.pathname === '/contact' ? 'black' : 'gray',
          }} label="Contact" component={NavLink} to="/contact" icon={<AlternateEmailSharpIcon/>} />
        </Tabs>        
      </nav>
      <Outlet />
      
    </div>
  );
}