import { useTheme } from "../providers/Theme";
import React from "react";


export default function ThemeWrapper({ children }: { children: React.ReactNode }) {
  const { theme } = useTheme();
  return (
    <div className={`portfolio ${theme === 'dark' ? "dark-theme" : "light-theme"}`}>
      {children}
    </div>
  );
}