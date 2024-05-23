import './index.css'
import Header from './components/Header'
import Table from './components/Table'
import useBooks from './booksApi/getBooks';
import useGenres from './genresApi/getGenres';
import { GridColDef } from "@mui/x-data-grid";
import { useState } from 'react';
import { IGenre, IBook } from './types/types';
import useRemoveBook from './booksApi/removeBook';
import AlertDialog from './components/Alert';

function App() {
  const [bookDelete, setBookDelete] = useState<string>('');
  const [bookEdit, setBookEdit] = useState<string>('');
  const [dialogOpen, setDialogOpen] = useState<boolean>(false);

  const columns: GridColDef[] = [
    {
      field: "title",
      headerName: "Title",
      width: 150,
    },
    {
      field: "author",
      headerName: "Author",
      width: 150,
    },
    {
      field: "year",
      headerName: "Year",
      width: 90,
    },
    {
      field: "description",
      headerName: "Description",
      width: 150,
    },
    {
      field: "copies",
      headerName: "Copies",
      width: 90,
    },
    {
      field: "price",
      headerName: "Price",
      width: 90,
    },
    {
      field: "genre",
      headerName: "Genre",
      width: 90,
    },
    {
      field: "actions",
      headerName: "Actions",
      width: 150,
      disableColumnMenu: true, 
      display: 'flex', 
      hideSortIcons: true,
      renderCell: (params) => {
        return (
          <div className='buttons'>
            <button className="btn" onClick={()=>{
              setBookEdit(params.row.id);
            }} >Edit</button>
            <button className="btn" onClick={()=>{
              setBookDelete(params.row.id);
              setDialogOpen(true);
            }}>Delete</button>
          </div>
        );
      },
    }
  ];
  
  function handleEdit(id: string) {

  }

  const rowsQuery = useBooks();
  const genresQuery = useGenres();


  if(rowsQuery.isLoading || genresQuery.isLoading) {
    return <div>Loading...</div>   
  }
  const rows = rowsQuery.data as IBook[];
  const genres = genresQuery.data as IGenre[];
  rows.forEach((row: any) => {
    for(let genre of genres) {
      if (row.genreId === genre.id) {
        row.genre = genre.name;
      }
    }
  });

  return (
    <div className='container'>
      <Header />
      <Table columns={columns} rows={rows} />
      <AlertDialog 
        open={dialogOpen} 
        onClose={() => setDialogOpen(false)} 
        onMutate={() => {
          useRemoveBook().mutate(bookDelete);
          console.log('delete', bookDelete);
          setDialogOpen(false);
          setBookDelete('');
        }
      } />
    </div>
  )
}

export default App
