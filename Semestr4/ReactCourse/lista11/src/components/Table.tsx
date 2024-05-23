import { DataGrid } from "@mui/x-data-grid";


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