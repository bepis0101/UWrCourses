export default function Footer(name: string){
  return (
    <footer className="footer">
      <div className="footer-content">
        <p>
          &copy; {new Date().getFullYear()} {name}
          </p>
      </div>
    </footer>
  );
}