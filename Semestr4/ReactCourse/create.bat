@echo off
set name=%1
call npm create vite@latest %name% -- --template react-ts
cd %name%
npm i
