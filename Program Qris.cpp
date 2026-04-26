#include <iostream>
#include <string>
using namespace std;

int main() {
    // Data QRIS (contoh sederhana, bisa dimodifikasi sesuai kebutuhan)
    string qrisData =
        "00020101021126680012ID.CO.QRIS.WWW01189360091123456789000203ID"
        "5913DOYZ STORE6007Semarang6105123456234040005303360540410005802ID"
        "5909Pembayaran";

    cout << "=== PROGRAM QRIS SEDERHANA ===" << endl;
    cout << "Data QRIS: " << endl;
    cout << qrisData << endl;

    cout << "\nCatatan:" << endl;
    cout << "Salin data QRIS di atas ke generator QR online untuk membuat QR Code visual." << endl;
    cout << "Kamu bisa ubah bagian Nama Toko, Lokasi, atau Nominal sesuai kebutuhan." << endl;

    return 0;
}

