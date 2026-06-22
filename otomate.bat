@echo off
title Setup Proyek TrustyTableOrder - NatDev3
clc

echo =======================================================
echo   SETUP STRUKTUR FOLDER & LINK REPOSITORY GITHUB
echo =======================================================
echo.

:: 1. Membuat folder src
echo [1/5] Membuat folder src...
if not exist "src" mkdir src
timeout /t 1 >nul

:: 2. Membuat file main.cpp dan user.txt KOSONG di dalam folder src
echo [2/5] Membuat file main.cpp dan user.txt kosong...
if not exist "src\main.cpp" type nul > "src\main.cpp"
if not exist "src\user.txt" type nul > "src\user.txt"
timeout /t 1 >nul

:: 3. Membuat file .gitignore
echo [3/5] Membuat file .gitignore...
echo *.exe > .gitignore
echo *.o >> .gitignore
echo .DS_Store >> .gitignore
timeout /t 1 >nul

:: 4. Inisialisasi Git dan Menghubungkan ke Link GitHub NatDev3
echo [4/5] Menghubungkan repository lokal ke GitHub NatDev3...
git init
:: Menghapus remote origin lama jika ada, lalu memasang yang baru
git remote remove origin >nul 2>&1
git remote add origin https://github.com/NatDev3/TrustyTableOrder.git
git branch -M main
timeout /t 1 >nul

:: 5. Proses Push ke GitHub
echo [5/5] Melakukan push otomatis ke GitHub...
echo.
git add .
git commit -m "Initial setup: Struktur folder src/ dengan file cpp dan txt kosong"
git push -u origin main

echo.
echo =======================================================
echo   SUKSES! File kosong berhasil dibuat di folder 'src'.
echo   Silahkan buka 'src\main.cpp' untuk mengisi kode C++.
echo =======================================================
pause