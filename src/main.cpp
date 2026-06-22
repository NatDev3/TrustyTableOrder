#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


const int MAX_MENU_MAKANAN = 6;
const int MAX_MENU_MINUMAN = 4;
const int MAX_SERVICES = 3;
const int BARIS_KURSI = 3;
const int KOLOM_KURSI = 4;

string namaMakanan[MAX_MENU_MAKANAN]   = {"Nasi Goreng", "Mie Ayam", "Ayam Geprek", "Telur Dadar", "Soto Ayam", "Gado-Gado"};
int    hargaMakanan[MAX_MENU_MAKANAN]  = {15000, 12000, 18000, 8000, 13000, 10000};

string namaMinuman[MAX_MENU_MINUMAN]   = {"Es Teh", "Jus Alpukat", "Kopi Hitam", "Air Mineral"};
int    hargaMinuman[MAX_MENU_MINUMAN]  = {5000, 12000, 8000, 3000};

string namaServices[MAX_SERVICES]      = {"Top Up Game (Rp 50.000)", "Workshop Memasak (Rp 75.000)", "Birthday Package (Rp 150.000)"};
int    hargaServices[MAX_SERVICES]     = {50000, 75000, 150000};

int denahKursi[BARIS_KURSI][KOLOM_KURSI] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int hitungBiayaAdminRekursif(int n) {
    if (n <= 1) return 2000;
    return 1000 + hitungBiayaAdminRekursif(n - 1);
}

void urutkanMakananTermurah() {
    for (int i = 0; i < MAX_MENU_MAKANAN - 1; i++) {
        for (int j = 0; j < MAX_MENU_MAKANAN - i - 1; j++) {
            if (hargaMakanan[j] > hargaMakanan[j + 1]) {
                swap(hargaMakanan[j], hargaMakanan[j + 1]);
                swap(namaMakanan[j], namaMakanan[j + 1]);
            }
        }
    }
}

int cariMakanan(string keyword) {
    for (int i = 0; i < MAX_MENU_MAKANAN; i++) {
        if (namaMakanan[i] == keyword) return i;
    }
    return -1;
}

void tampilkanGaris(char c = '-', int panjang = 45) {
    for (int i = 0; i < panjang; i++) cout << c;
    cout << endl;
}

void tampilkanHeader(string judul) {
    tampilkanGaris('=');
    cout << setw(30) << judul << endl;
    tampilkanGaris('=');
}

//USER

class User {
private:
    string username, password, email;
    bool sudahLogin = false;

    int keranjangMakananIdx[MAX_MENU_MAKANAN];
    int keranjangMakananQty[MAX_MENU_MAKANAN];
    int jumlahItemMakanan = 0;

    int keranjangMinumanIdx[MAX_MENU_MINUMAN];
    int keranjangMinumanQty[MAX_MENU_MINUMAN];
    int jumlahItemMinuman = 0;

    int servicesIdx[MAX_SERVICES];
    int servicesQty[MAX_SERVICES];
    int jumlahServices = 0;

    int kursiDireservasi[BARIS_KURSI * KOLOM_KURSI][2];
    int jumlahReservasi = 0;

public:
    //MENU DAFTAR

    void buatAkun() {
        tampilkanHeader("BUAT AKUN BARU");
        cout << "Username : "; cin >> username;
        cout << "Password : "; cin >> password;
        cout << "Email    : "; cin >> email;

        ofstream file("akun.txt", ios::app);
        file << username << " " << password << " " << email << "\n";
        file.close();

        cout << "\nAkun berhasil dibuat! Silakan login.\n";
    }

    bool login() {
        tampilkanHeader("LOGIN");
        string u, p;
        cout << "Username : "; cin >> u;
        cout << "Password : "; cin >> p;

        ifstream file("akun.txt");
        string fu, fp, fe;
        while (file >> fu >> fp >> fe) {
            if (fu == u && fp == p) {
                username = u; password = p; email = fe;
                sudahLogin = true;
                file.close();
                cout << "\nSelamat datang, " << username << "!\n";
                return true;
            }
        }
        file.close();
        cout << "\nUsername atau password salah.\n";
        return false;
    }

    void lupaPassword() {
        tampilkanHeader("LUPA PASSWORD");
        string e;
        cout << "Masukkan email Anda: "; cin >> e;

        ifstream file("akun.txt");
        string fu, fp, fe;
        bool ketemu = false;
        while (file >> fu >> fp >> fe) {
            if (fe == e) {
                cout << "Password Anda: " << fp << endl;
                ketemu = true;
                break;
            }
        }
        file.close();
        if (!ketemu) cout << "Email tidak ditemukan.\n";
    }

    //MENU LOGIN

    bool menuAwal() {
        int pilihan;
        do {
            tampilkanHeader("TRUSTY TABLE ORDER");
            cout << "1. Buat Akun\n";
            cout << "2. Login\n";
            cout << "3. Lupa Password\n";
            cout << "0. Keluar\n";
            tampilkanGaris();
            cout << "Pilihan: "; cin >> pilihan;

            switch (pilihan) {
                case 1: buatAkun(); break;
                case 2: if (login()) return true; break;
                case 3: lupaPassword(); break;
                case 0: cout << "Sampai jumpa!\n"; return false;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (true);
    }

    //MENU MAKANAN & MINUMAN

    void menuFoodDrink() {
        int pilihan;
        do {
            tampilkanHeader("FOOD & BEVERAGE");
            cout << "1. Lihat Menu Makanan\n";
            cout << "2. Cari Makanan\n";
            cout << "3. Urutkan Makanan (Termurah)\n";
            cout << "4. Lihat Menu Minuman\n";
            cout << "5. Pesan Makanan\n";
            cout << "6. Pesan Minuman\n";
            cout << "0. Kembali\n";
            tampilkanGaris();
            cout << "Pilihan: "; cin >> pilihan;

            if (pilihan == 1) {
                tampilkanGaris();
                cout << left << setw(5) << "No"
                     << setw(20) << "Nama Makanan"
                     << "Harga" << endl;
                tampilkanGaris();
                for (int i = 0; i < MAX_MENU_MAKANAN; i++) {
                    cout << left << setw(5) << (i + 1)
                         << setw(20) << namaMakanan[i]
                         << "Rp " << hargaMakanan[i] << endl;
                }
                tampilkanGaris();
            }
            else if (pilihan == 2) {
                string keyword;
                cout << "Cari makanan: "; cin.ignore(); getline(cin, keyword);
                int idx = cariMakanan(keyword);
                if (idx != -1)
                    cout << "Ditemukan: " << namaMakanan[idx] << " - Rp " << hargaMakanan[idx] << endl;
                else
                    cout << "Makanan tidak ditemukan.\n";
            }
            else if (pilihan == 3) {
                urutkanMakananTermurah();
                cout << "Menu makanan sudah diurutkan dari termurah.\n";
            }
            else if (pilihan == 4) {
                tampilkanGaris();
                cout << left << setw(5) << "No"
                     << setw(20) << "Nama Minuman"
                     << "Harga" << endl;
                tampilkanGaris();
                for (int i = 0; i < MAX_MENU_MINUMAN; i++) {
                    cout << left << setw(5) << (i + 1)
                         << setw(20) << namaMinuman[i]
                         << "Rp " << hargaMinuman[i] << endl;
                }
                tampilkanGaris();
            }
            else if (pilihan == 5) {
                cout << "Pilih nomor makanan (1-" << MAX_MENU_MAKANAN << "): ";
                int no; cin >> no;
                if (no >= 1 && no <= MAX_MENU_MAKANAN) {
                    cout << "Jumlah: ";
                    int qty; cin >> qty;
                    keranjangMakananIdx[jumlahItemMakanan] = no - 1;
                    keranjangMakananQty[jumlahItemMakanan] = qty;
                    jumlahItemMakanan++;
                    cout << qty << "x " << namaMakanan[no - 1] << " ditambahkan ke keranjang.\n";
                } else {
                    cout << "Nomor tidak valid.\n";
                }
            }
            else if (pilihan == 6) {
                cout << "Pilih nomor minuman (1-" << MAX_MENU_MINUMAN << "): ";
                int no; cin >> no;
                if (no >= 1 && no <= MAX_MENU_MINUMAN) {
                    cout << "Jumlah: ";
                    int qty; cin >> qty;
                    keranjangMinumanIdx[jumlahItemMinuman] = no - 1;
                    keranjangMinumanQty[jumlahItemMinuman] = qty;
                    jumlahItemMinuman++;
                    cout << qty << "x " << namaMinuman[no - 1] << " ditambahkan ke keranjang.\n";
                } else {
                    cout << "Nomor tidak valid.\n";
                }
            }
        } while (pilihan != 0);
    }

    //MENU SERVICES

    void menuServices() {
        int pilihan;
        do {
            tampilkanHeader("SERVICES");
            cout << "1. Lihat Layanan\n";
            cout << "2. Pesan Layanan\n";
            cout << "0. Kembali\n";
            tampilkanGaris();
            cout << "Pilihan: "; cin >> pilihan;

            if (pilihan == 1) {
                tampilkanGaris();
                cout << left << setw(5) << "No" << setw(30) << "Layanan" << "Harga" << endl;
                tampilkanGaris();
                for (int i = 0; i < MAX_SERVICES; i++) {
                    cout << left << setw(5) << (i + 1)
                         << setw(30) << namaServices[i]
                         << "Rp " << hargaServices[i] << endl;
                }
                tampilkanGaris();
            }
            else if (pilihan == 2) {
                cout << "Pilih nomor layanan (1-" << MAX_SERVICES << "): ";
                int no; cin >> no;
                if (no >= 1 && no <= MAX_SERVICES) {
                    cout << "Jumlah: ";
                    int qty; cin >> qty;
                    servicesIdx[jumlahServices] = no - 1;
                    servicesQty[jumlahServices] = qty;
                    jumlahServices++;
                    cout << qty << "x " << namaServices[no - 1] << " ditambahkan.\n";
                } else {
                    cout << "Nomor tidak valid.\n";
                }
            }
        } while (pilihan != 0);
    }

    //MENU RESERVASI

    void tampilkanDenah() {
        cout << "\n  Denah Meja (O=Kosong, X=Terisi)\n";
        cout << "  ";
        for (int k = 0; k < KOLOM_KURSI; k++) cout << "  " << (k + 1);
        cout << "\n";
        for (int i = 0; i < BARIS_KURSI; i++) {
            cout << (char)('A' + i) << " ";
            for (int j = 0; j < KOLOM_KURSI; j++) {
                cout << " [" << (denahKursi[i][j] == 0 ? 'O' : 'X') << "]";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void menuReservasi() {
        int pilihan;
        do {
            tampilkanHeader("RESERVASI & WAITING LIST");
            cout << "1. Lihat Denah Meja\n";
            cout << "2. Reservasi Meja\n";
            cout << "3. Batalkan Reservasi\n";
            cout << "0. Kembali\n";
            tampilkanGaris();
            cout << "Pilihan: "; cin >> pilihan;

            if (pilihan == 1) {
                tampilkanDenah();
            }
            else if (pilihan == 2) {
                tampilkanDenah();
                char baris; int kolom;
                cout << "Pilih baris (A-" << (char)('A' + BARIS_KURSI - 1) << "): "; cin >> baris;
                cout << "Pilih kolom (1-" << KOLOM_KURSI << "): "; cin >> kolom;

                int b = baris - 'A';
                int k = kolom - 1;

                if (b < 0 || b >= BARIS_KURSI || k < 0 || k >= KOLOM_KURSI) {
                    cout << "Posisi tidak valid.\n";
                } else if (denahKursi[b][k] == 1) {
                    cout << "Meja sudah terisi. Anda masuk waiting list.\n";
                    int nomorAntrean = jumlahReservasi + 1;
                    int biayaAdmin = hitungBiayaAdminRekursif(nomorAntrean);
                    cout << "Nomor antrean Anda: " << nomorAntrean << endl;
                    cout << "Biaya admin waiting list: Rp " << biayaAdmin << endl;
                } else {
                    denahKursi[b][k] = 1;
                    kursiDireservasi[jumlahReservasi][0] = b;
                    kursiDireservasi[jumlahReservasi][1] = k;
                    jumlahReservasi++;
                    cout << "Meja " << baris << kolom << " berhasil direservasi!\n";
                }
            }
            else if (pilihan == 3) {
                tampilkanDenah();
                char baris; int kolom;
                cout << "Baris (A-" << (char)('A' + BARIS_KURSI - 1) << "): "; cin >> baris;
                cout << "Kolom (1-" << KOLOM_KURSI << "): "; cin >> kolom;

                int b = baris - 'A';
                int k = kolom - 1;

                if (b < 0 || b >= BARIS_KURSI || k < 0 || k >= KOLOM_KURSI) {
                    cout << "Posisi tidak valid.\n";
                } else if (denahKursi[b][k] == 0) {
                    cout << "Meja sudah kosong.\n";
                } else {
                    denahKursi[b][k] = 0;
                    cout << "Reservasi meja " << baris << kolom << " dibatalkan.\n";
                }
            }
        } while (pilihan != 0);
    }

    //SISTEM PEMBAYARAN

    int hitungTotal() {
        int total = 0;
        for (int i = 0; i < jumlahItemMakanan; i++)
            total += hargaMakanan[keranjangMakananIdx[i]] * keranjangMakananQty[i];
        for (int i = 0; i < jumlahItemMinuman; i++)
            total += hargaMinuman[keranjangMinumanIdx[i]] * keranjangMinumanQty[i];
        for (int i = 0; i < jumlahServices; i++)
            total += hargaServices[servicesIdx[i]] * servicesQty[i];
        return total;
    }

    void cetakStruk(int total, int diskon, int bayar, string metodePembayaran) {
        tampilkanGaris('=');
        cout << setw(28) << "STRUK PEMBAYARAN" << endl;
        cout << "TrustyTableOrder - " << username << endl;
        tampilkanGaris();

        cout << "MAKANAN:\n";
        for (int i = 0; i < jumlahItemMakanan; i++) {
            int idx = keranjangMakananIdx[i];
            int qty = keranjangMakananQty[i];
            cout << left << setw(20) << namaMakanan[idx]
                 << setw(4) << ("x" + to_string(qty))
                 << "Rp " << (hargaMakanan[idx] * qty) << endl;
        }

        cout << "\nMINUMAN:\n";
        for (int i = 0; i < jumlahItemMinuman; i++) {
            int idx = keranjangMinumanIdx[i];
            int qty = keranjangMinumanQty[i];
            cout << left << setw(20) << namaMinuman[idx]
                 << setw(4) << ("x" + to_string(qty))
                 << "Rp " << (hargaMinuman[idx] * qty) << endl;
        }

        cout << "\nSERVICES:\n";
        for (int i = 0; i < jumlahServices; i++) {
            int idx = servicesIdx[i];
            int qty = servicesQty[i];
            cout << left << setw(20) << namaServices[idx]
                 << setw(4) << ("x" + to_string(qty))
                 << "Rp " << (hargaServices[idx] * qty) << endl;
        }

        tampilkanGaris();
        cout << left << setw(25) << "Subtotal" << "Rp " << total << endl;

        if (diskon > 0)
            cout << left << setw(25) << "Diskon" << "- Rp " << diskon << endl;

        cout << left << setw(25) << "Total Bayar" << "Rp " << (total - diskon) << endl;
        cout << left << setw(25) << "Metode" << metodePembayaran << endl;

        if (bayar > 0) {
            cout << left << setw(25) << "Uang Diterima" << "Rp " << bayar << endl;
            cout << left << setw(25) << "Kembalian" << "Rp " << (bayar - (total - diskon)) << endl;
        }

        tampilkanGaris('=');
        cout << "        Terima kasih telah berkunjung!\n";
        tampilkanGaris('=');
    }

    void menuPembayaran() {
        int total = hitungTotal();
        if (total == 0) {
            cout << "Keranjang kosong. Silakan pesan terlebih dahulu.\n";
            return;
        }

        tampilkanHeader("PEMBAYARAN");
        cout << "Total belanja Anda: Rp " << total << endl;

        int diskon = 0;
        if (total > 100000) {
            diskon = total * 10 / 100;
            cout << "Selamat! Anda mendapat diskon 10%: Rp " << diskon << endl;
        } else if (total > 50000) {
            diskon = total * 5 / 100;
            cout << "Selamat! Anda mendapat diskon 5%: Rp " << diskon << endl;
        }

        int totalBayar = total - diskon;
        cout << "Total setelah diskon: Rp " << totalBayar << endl;

        cout << "\nPilih metode pembayaran:\n";
        cout << "1. Tunai\n";
        cout << "2. Transfer Bank\n";
        cout << "3. E-Wallet (OVO/GoPay/Dana)\n";
        cout << "Pilihan: ";
        int pilihanBayar; cin >> pilihanBayar;

        string metodePembayaran;
        int uangDiterima = 0;

        switch (pilihanBayar) {
            case 1:
                metodePembayaran = "Tunai";
                do {
                    cout << "Masukkan uang: Rp "; cin >> uangDiterima;
                    if (uangDiterima < totalBayar)
                        cout << "Uang kurang. Total: Rp " << totalBayar << ". Coba lagi.\n";
                } while (uangDiterima < totalBayar);
                break;
            case 2:
                metodePembayaran = "Transfer Bank";
                cout << "Transfer ke: BCA 1234-5678-9012 a.n. TrustyTableOrder\n";
                cout << "Tekan Enter setelah transfer...";
                cin.ignore(); cin.get();
                break;
            case 3:
                metodePembayaran = "E-Wallet";
                cout << "Scan QR Code atau masukkan nomor: 0812-3456-7890\n";
                cout << "Tekan Enter setelah pembayaran...";
                cin.ignore(); cin.get();
                break;
            default:
                metodePembayaran = "Tidak Diketahui";
        }

        cetakStruk(total, diskon, uangDiterima, metodePembayaran);

        jumlahItemMakanan = 0;
        jumlahItemMinuman = 0;
        jumlahServices = 0;
    }

    //MENU UTAMA

    void menuUtama() {
        int pilihan;
        do {
            tampilkanHeader("MENU UTAMA");
            cout << "Halo, " << username << "!\n";
            tampilkanGaris();
            cout << "1. Food & Beverage\n";
            cout << "2. Services\n";
            cout << "3. Reservasi & Waiting List\n";
            cout << "4. Pembayaran\n";
            cout << "0. Logout\n";
            tampilkanGaris();
            cout << "Pilihan: "; cin >> pilihan;

            switch (pilihan) {
                case 1: menuFoodDrink(); break;
                case 2: menuServices(); break;
                case 3: menuReservasi(); break;
                case 4: menuPembayaran(); break;
                case 0: cout << "Logout berhasil. Sampai jumpa, " << username << "!\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 0);
    }

    void jalankan() {
        if (menuAwal()) {
            menuUtama();
        }
    }
};



int main() {
    User app;
    app.jalankan();
    return 0;
}
