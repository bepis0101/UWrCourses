import React from 'react'
import ReactDOM from 'react-dom/client'
import RootLayout from './layout/RootLayout.tsx'
import './index.css'
import {
  RouterProvider,
  createBrowserRouter,
} from 'react-router-dom'
import AboutMe from './routes/AboutMe.tsx'
import Home from './routes/Home.tsx'
import Projects from './routes/Projects.tsx'
import Contact from './routes/Contact.tsx'

const router = createBrowserRouter([
  {
    path: '/',
    element: <RootLayout />,
    children: [
      { path: '/', element: <Home /> },
      { path: '/about', element: <AboutMe /> },
      { path: '/projects', element: <Projects /> },
      { path: '/contact', element: <Contact />},
      // { path: '/:catchAll', element: <NotFound /> },
    ]
  }
]);

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>,
)
