import * as React from 'react';
import { DataGrid, GridColDef, } from '@mui/x-data-grid';
import { Item, FormDialog} from './AddingForm';
import DeleteIcon from '@mui/icons-material/Delete';
import IconButton from '@mui/material/IconButton';
import AlertDialog from './Alert';


const columns1: GridColDef[] = [
  // {field: 'id', headerName: 'ID', width: 90, disableColumnMenu: true, hideSortIcons: true},
  {field: 'name', headerName: 'Name', width: 130},
  {field: 'type', headerName: 'Type', width: 130},
  {field: 'price', headerName: 'Price', type: 'number', width: 100},
  {field: 'avilability', headerName: 'Is In Stock', type: 'boolean', width: 150},
  {field: 'item', headerName: 'Items', type: 'number', width: 100},
  {field: 'action', disableColumnMenu: true, display: 'flex', hideSortIcons: true, 
    renderCell: () => {
      return (
        <IconButton aria-label="delete">
          <DeleteIcon />
        </IconButton>
      );
    },
    renderHeader: () => {
      return (<></>);
    }
},
]
const rows1 = [
  { id: 1, name: 'Apple', type: 'Fruit', price: 1, avilability: true, item: 10 },
  { id: 2, name: 'Banana', type: 'Fruit', price: 2, avilability: true, item: 5 },
  { id: 3, name: 'Orange', type: 'Fruit', price: 3, avilability: false, item: 0 },
  { id: 4, name: 'Carrot', type: 'Vegetable', price: 1, avilability: true, item: 10 },
  { id: 5, name: 'Potato', type: 'Vegetable', price: 2, avilability: true, item: 5 },
  { id: 6, name: 'Tomato', type: 'Vegetable', price: 3, avilability: false, item: 0 },
  { id: 7, name: 'Milk', type: 'Dairy', price: 1, avilability: true, item: 10 },
  { id: 8, name: 'Cheese', type: 'Dairy', price: 2, avilability: true, item: 5 },
  { id: 9, name: 'Butter', type: 'Dairy', price: 3, avilability: false, item: 0 },
];

export default function DataTable() {
  const [items, setItems] = React.useState<Item[]>(rows1);
  const [deleteRow, setDeleteRow] = React.useState<number>(0);
  const [alertOpen, setAlertOpen] = React.useState(false);
  const [rowName, setRowName] = React.useState<string>('');

  function handleDeleteRow() {
    const itemsCopy = items.filter((item) => item.id !== deleteRow);
    setItems(itemsCopy);
    setAlertOpen(false);
    setDeleteRow(0);
  }

  return (
    <React.Fragment>
      <FormDialog items={items} setItems={setItems}/>
      <div style={{ height: 450, width: '100%' }}>
        <DataGrid
          rows={items}
          columns={columns1}
          initialState={{
            pagination: {
              paginationModel: { page: 0, pageSize: 5 },
            },
          }}
          pageSizeOptions={[5, 10]}
          pagination
          hideFooterSelectedRowCount
          onCellClick={(params) => {
            if (params.field === 'action') {
              setAlertOpen(true);
              setDeleteRow(params.row.id as number);
              setRowName(params.row.name as string);
            }
          }}
        />
      </div>
      <AlertDialog open={alertOpen} setOpen={setAlertOpen} rowName={rowName} deleteRow={handleDeleteRow}/>
    </React.Fragment>
  );
}