// import React from "react";
import Header from "./components/Header";
import Table from "./components/Table";
import "./styles.css";
import { createTheme, ThemeProvider } from "@mui/material/styles";


const newTheme = createTheme({
  palette: {
    primary: {
      main: "#4caf50"
    },
    secondary: {
      main: "#ffeb3b",
    },
    error:{
      main: "#f44336"
    },
    warning: {
      main: "#ff9800"
    },
    info: {
      main: "#2196f3"
    },
    background: {
      default: "#ffffff",
      paper: "#f5f5f5"
    },
  }
});


export default function App() {
  return (
    <>
      <ThemeProvider theme={newTheme}>
        <Header />
        <Table />
      </ThemeProvider>
    </>
  );
}