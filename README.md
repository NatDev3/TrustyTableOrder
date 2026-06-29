# TrustyTableOrder v1.0.0-alpha

Aplikasi pemesanan berbasis terminal, dibuat dengan C++ untuk tugas kuliah Pemrograman Dasar UAD.

## Cara Menjalankan program

```bash
g++ -o TrustyTableOrder TrustyTableOrder.cpp
./TrustyTableOrder
```

Windows:
```bash
g++ -o TrustyTableOrder TrustyTableOrder.cpp
TrustyTableOrder.exe
```

## Fitur

- Daftar akun, login, lupa password (data disimpan ke `akun.txt`)
- Lihat menu, cari makanan, urutkan harga
- Pesan makanan, minuman, dan layanan tambahan
- Reservasi meja dengan denah visual dan waiting list
- Pembayaran dengan diskon otomatis dan cetak struk

## Materi C++ yang Dipakai

| Materi | Implementasi |
|---|---|
| Array 1 Dimensi | Daftar menu dan keranjang belanja |
| Array 2 Dimensi | Denah meja reservasi 3x4 |
| Linear Search | Cari makanan berdasarkan nama |
| Bubble Sort | Urutkan menu dari harga termurah |
| Rekursi | Hitung biaya admin waiting list |
| File I/O | Simpan dan baca data akun |

## Struktur File

```
TrustyTableOrder/
├── TrustyTableOrder.cpp
├── README.md
└── akun.txt  ← dibuat otomatis oleh program
```

## Informasi

- Bahasa: C++
- Platform: Windows / Linux / Mac
- Universitas: Universitas Ahmad Dahlan (UAD)
