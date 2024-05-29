import './index.css'
import Header from './components/Header'
import Table from './components/Table'
import { GridColDef } from "@mui/x-data-grid";
import { useState } from 'react';
import { IGenre, IBook } from './types/types';
import { useMutation, useQuery, useQueryClient } from '@tanstack/react-query';
import { cols } from './components/Table';
import AlertDialog from './components/Alert';
import fetchBooks from './booksApi/getBooks';
import fetchGenres from './genresApi/getGenres';
import addBook from './booksApi/addBook';
import removeBook from './booksApi/removeBook';
import editBook from './booksApi/editBook';


function App() {
  const queryClient = useQueryClient();
  const books = useQuery({queryKey: ['books'], queryFn: fetchBooks});
  const genres = useQuery({queryKey: ['genres'], queryFn: fetchGenres});
  const addBookMutation = useMutation({
    mutationFn: addBook,
    onSuccess: () => {
      queryClient.invalidateQueries({queryKey: ['books']});
    }
  })
  const deleteBookMutation = useMutation({
    mutationFn: removeBook,
    onSuccess: () => {
      queryClient.invalidateQueries({queryKey: ['books']});
    }
  })
  const editBookMutation = useMutation({
    mutationFn: editBook,
    onSuccess: () => {
      queryClient.invalidateQueries({queryKey: ['books']});
    }
  });
  const [bookDelete, setBookDelete] = useState<string>('');
  const [bookEdit, setBookEdit] = useState<string>('');
  const [dialogOpen, setDialogOpen] = useState<boolean>(false);

  const columns: GridColDef[] = [
    ...cols, 
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

  const booksData = books.data;
  const genresData = genres.data;
  if(books.isLoading || genres.isLoading) return <div>Loading...</div>
  if(books.isError || genres.isError) return <div>Error</div>
  const rows = booksData.map((book: IBook) => {
    const genre = genresData.find((genre: IGenre) => genre.id === book.genreId);
    return {
      ...book,
      genre: genre?.name,
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
          deleteBookMutation.mutate(bookDelete);
          console.log('delete', bookDelete);
          setDialogOpen(false);
          setBookDelete('');
        }
      } />


    </div>
  )
}

export default App
