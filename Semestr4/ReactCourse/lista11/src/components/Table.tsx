import { DataGrid, GridColDef } from "@mui/x-data-grid";


export const cols: GridColDef[] = [
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
];

export default function Table({ rows, columns }: { rows: any, columns: any }) {
  return (
    <div className="table">
      <DataGrid 
      rows={rows} 
      columns={columns}
      initialState={{
        pagination: {
          paginationModel: { page: 0, pageSize: 5 },
        },
      }}
      pageSizeOptions={[5, 10]}
      pagination
      hideFooterSelectedRowCount
      disableAutosize
       />
    </div>
  );
}