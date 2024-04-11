import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogContentText from '@mui/material/DialogContentText';
import DialogTitle from '@mui/material/DialogTitle';
import Box from '@mui/material/Box';
import Fab from '@mui/material/Fab';
import AddIcon from '@mui/icons-material/Add';

export interface Item {
  id?: number;
  name: string;
  type: string;
  price: number;
  avilability: boolean;
  item: number;
}

export function FormDialog({items, setItems}: {items: Item[], setItems: React.Dispatch<React.SetStateAction<Item[]>>}) {
  const [open, setOpen] = React.useState(false);
  const handleClickOpen = () => {
    setOpen(true);
  };

  const handleClose = () => {
    setOpen(false);
  };

  return (
    <React.Fragment>
      <Box sx={{ '& > :not(style)': { m: 1 }, position: 'absolute', bottom: "20px", right: "20px"}}>
        <Fab color="secondary" aria-label="add" onClick={handleClickOpen}>
          <AddIcon />
        </Fab>
      </Box>
      <Dialog
        open={open}
        onClose={handleClose}
        PaperProps={{
          component: 'form',
          onSubmit: (event: React.FormEvent<HTMLFormElement>) => {
            event.preventDefault();
            const item = {
              id: Math.floor( Math.random() * 100000000 ),
              name: ( event.target as any ).name.value,
              type: ( event.target as any ).type.value,
              price: ( event.target as any ).price.value,
              avilability: true,
              item: ( event.target as any ).item.value,
            };
            setItems([...items, item]);
            handleClose();
          },
        }}
      >
        <DialogTitle>Add New Item</DialogTitle>
        <DialogContent>
          <DialogContentText>
            Please fill out the form below.
          </DialogContentText>
          <TextField
            autoFocus
            margin="dense"
            id="name"
            label="Name"
            type="text"
            fullWidth
          />
          <TextField
            margin="dense"
            id="type"
            label="Type"
            type="text"
            fullWidth
          />
          <TextField
            margin="dense"
            id="price"
            label="Price"
            type="number"
            inputProps={{ min: 0 }}
            fullWidth
          />
          <TextField
            margin="dense"
            id="item"
            label="Item"
            type="number"
            inputProps={{ min: 0 }}
            fullWidth
          />
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button type="submit">Add</Button>
        </DialogActions>
      </Dialog>
    </React.Fragment>
  );
}