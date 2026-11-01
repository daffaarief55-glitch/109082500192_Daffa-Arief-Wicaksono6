#include <iostream>
#include <limits>
#include "Buku.h"
using namespace std;

int main() {
    List L;
    CreateList(L);

    int jumlahData;
    cout << "Jumlah data buku yang ingin dimasukkan: ";
    cin >> jumlahData;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < jumlahData; i++) {
        infotype data;

        cout << "\nMasukkan kode buku: ";
        getline(cin, data.kodeBuku);

        cout << "Masukkan judul buku: ";
        getline(cin, data.judul);

        cout << "Masukkan tahun terbit: ";
        cin >> data.thnTerbit;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (findElm(L, data) != nullptr) {
            cout << "kode buku sudah terdaftar" << endl;
        } else {
            insertLast(L, alokasi(data));
        }
    }

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    infotype cari;
    cout << "\nMasukkan Kode Buku yang dicari : ";
    getline(cin, cari.kodeBuku);

    address hasil = findElm(L, cari);
    if (hasil != nullptr) {
        cout << "\nKode Buku    : " << hasil->info.kodeBuku << endl;
        cout << "Judul        : " << hasil->info.judul << endl;
        cout << "Tahun Terbit : " << hasil->info.thnTerbit << endl;
    } else {
        cout << "Data buku tidak ditemukan." << endl;
    }

    infotype hapus;
    cout << "\nMasukkan Kode Buku yang akan dihapus : ";
    getline(cin, hapus.kodeBuku);

    address target = findElm(L, hapus);
    if (target == nullptr) {
        cout << "Data buku tidak ditemukan." << endl;
    } else {
        address P = nullptr;

        if (target == L.First) {
            deleteFirst(L, P);
        } else if (target == L.Last) {
            deleteLast(L, P);
        } else {
            deleteAfter(target->prev, P);
        }

        if (P != nullptr) {
            cout << "Data dengan kode buku " << P->info.kodeBuku
                 << " berhasil dihapus." << endl;
            dealokasi(P);
        }
    }

    cout << "\nDATA LIST 1 SETELAH PENGHAPUSAN" << endl;
    printInfo(L);

    while (L.First != nullptr) {
        address P = nullptr;
        deleteFirst(L, P);
        dealokasi(P);
    }

    return 0;
}
