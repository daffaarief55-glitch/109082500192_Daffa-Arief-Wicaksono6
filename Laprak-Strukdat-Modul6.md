

### A. Doubly Linked List

Doubly Linked List adalah struktur data linear yang setiap elemennya
disebut node. Setiap node menyimpan data dan dua pointer, yaitu `next`
untuk menunjuk node berikutnya serta `prev` untuk menunjuk node
sebelumnya. Karena memiliki dua arah penghubung, penelusuran data bisa
dilakukan dari awal ke akhir maupun dari akhir ke awal \[1\].

#### 1. Struktur Elemen pada Doubly Linked List

Pada praktikum ini, data buku disimpan dalam `infotype` yang berisi
`kodeBuku`, `judul`, dan `thnTerbit`. Struktur `ElmList` menyimpan data
tersebut pada bagian `info`, serta pointer `next` dan `prev`. Sementara
itu, struktur `List` memiliki `First` dan `Last` untuk menunjuk node
pertama dan terakhir. Ketika list kosong, kedua pointer tersebut
bernilai `nullptr`.

#### 2. Pointer dan Alokasi Memori

Pointer menyimpan alamat dari suatu objek. Pada linked list, pointer
digunakan untuk menghubungkan node tanpa harus menempatkan semua data
secara berurutan di memori. Fungsi `alokasi()` membuat node baru dengan
`new`, mengisi informasi buku, lalu mengatur `next` dan `prev` ke
`nullptr`. Sebaliknya, `dealokasi()` menggunakan `delete` untuk
membebaskan memori node yang sudah tidak digunakan \[2\]\[3\].

#### 3. Penambahan Elemen di Akhir List

Operasi `insertLast()` menambahkan node baru pada bagian akhir list.
Jika list masih kosong, node baru menjadi `First` sekaligus `Last`. Jika
list sudah berisi data, node terakhir sebelumnya dihubungkan ke node
baru melalui `next`, sedangkan `prev` node baru diarahkan ke node
terakhir sebelumnya. Setelah itu, `Last` diperbarui ke node baru.

### B. Operasi pada Doubly Linked List

#### 1. Searching atau Pencarian Elemen

Searching adalah proses mencari data tertentu dengan menelusuri node
satu per satu. Fungsi `findElm()` memulai pencarian dari `First`,
kemudian membandingkan `kodeBuku` setiap node dengan kode yang dicari.
Fungsi mengembalikan alamat node jika data ditemukan dan `nullptr` jika
data tidak ada.

#### 2. Penghapusan Elemen

Penghapusan node harus memperbarui pointer agar node yang dihapus tidak
lagi menjadi bagian dari list. `deleteFirst()` menghapus node pertama
dan memperbarui `First`; `deleteLast()` menghapus node terakhir dan
memperbarui `Last`; sedangkan `deleteAfter()` menghapus node setelah
node pendahulu (`Prec`). Kasus list kosong, list yang hanya memiliki
satu node, dan hubungan `next` serta `prev` perlu diperhatikan supaya
list tetap tersambung dengan benar \[1\].

#### 3. Implementasi ADT dengan C++

Program dibagi menjadi tiga file: `Buku.h` untuk deklarasi tipe data dan
fungsi, `Buku.cpp` untuk implementasi operasi, dan `main.cpp` untuk
menjalankan serta menguji program. Pembagian ini membuat struktur data
terpisah dari logika program utama. Program juga memeriksa kode buku
yang sudah terdaftar sebelum menambahkan data baru agar tidak terjadi
duplikasi sesuai instruksi modul.

## Guided

### 1. Buku.h

``` cpp
#ifndef BUKU_H
#define BUKU_H

#include <string>
using namespace std;

struct buku {
    string kodeBuku;
    string judul;
    int thnTerbit;
};

typedef buku infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address First;
    address Last;
};

void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(const List &L);
void insertLast(List &L, address P);
address findElm(const List &L, const infotype &x);
void deleteFirst(List &L, address &P);
void deleteLast(List &L, address &P);
void deleteAfter(address Prec, address &P);

#endif
```

File `Buku.h` berisi tipe data buku, struktur node, struktur list, dan
deklarasi fungsi yang digunakan. `First` menunjuk node pertama,
sedangkan `Last` menunjuk node terakhir. Setiap node memiliki dua
pointer supaya hubungan antar-node bisa dijalankan dari dua arah.

### 2. Buku.cpp

``` cpp
#include <iostream>
#include "Buku.h"
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
    L.Last = nullptr;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void printInfo(const List &L) {
    address P = L.First;

    if (P == nullptr) {
        cout << "List buku kosong." << endl;
        return;
    }

    while (P != nullptr) {
        cout << "Kode Buku    : " << P->info.kodeBuku << endl;
        cout << "Judul        : " << P->info.judul << endl;
        cout << "Tahun Terbit : " << P->info.thnTerbit << endl;
        P = P->next;
    }
}

void insertLast(List &L, address P) {
    if (P == nullptr) {
        return;
    }

    P->next = nullptr;
    P->prev = L.Last;

    if (L.First == nullptr) {
        L.First = P;
        L.Last = P;
    } else {
        L.Last->next = P;
        L.Last = P;
    }
}

address findElm(const List &L, const infotype &x) {
    address P = L.First;

    while (P != nullptr) {
        if (P->info.kodeBuku == x.kodeBuku) {
            return P;
        }
        P = P->next;
    }

    return nullptr;
}

void deleteFirst(List &L, address &P) {
    if (L.First == nullptr) {
        P = nullptr;
        return;
    }

    P = L.First;
    L.First = P->next;

    if (L.First != nullptr) {
        L.First->prev = nullptr;
    } else {
        L.Last = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

void deleteLast(List &L, address &P) {
    if (L.Last == nullptr) {
        P = nullptr;
        return;
    }

    P = L.Last;
    L.Last = P->prev;

    if (L.Last != nullptr) {
        L.Last->next = nullptr;
    } else {
        L.First = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

void deleteAfter(address Prec, address &P) {
    if (Prec == nullptr || Prec->next == nullptr) {
        P = nullptr;
        return;
    }

    P = Prec->next;
    Prec->next = P->next;

    if (P->next != nullptr) {
        P->next->prev = Prec;
    }

    P->next = nullptr;
    P->prev = nullptr;
}
```

Fungsi `insertLast()` menyambungkan node baru ke ujung list. `findElm()`
mencari kode buku secara berurutan. Pada fungsi penghapusan, pointer
node yang dilepas dikembalikan melalui parameter `P`, kemudian node
tersebut bisa dibebaskan dengan `dealokasi()`. Fungsi `deleteAfter()`
mengikuti prototipe pada soal dan digunakan untuk menghapus node setelah
`Prec`; karena prototipe tersebut tidak menerima `List`, fungsi ini
tidak memperbarui `Last` apabila node yang dihapus merupakan node
terakhir. Pada program pengujian, fungsi ini digunakan untuk menghapus
node tengah B003.

### 3. main.cpp

``` cpp
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
```

File `main.cpp` menjadi bagian untuk memasukkan data buku, memeriksa
duplikasi kode, menampilkan list, mencari buku berdasarkan kode, dan
menghapus buku yang dipilih. Jika buku yang dihapus berada di awal atau
akhir, program memanggil fungsi penghapusan yang sesuai. Jika berada di
tengah, program menggunakan `deleteAfter()` dengan node sebelumnya
sebagai `Prec`.

### 4. Cara Kompilasi dan Pengujian

Simpan ketiga file dalam folder yang sama, kemudian jalankan perintah
berikut pada terminal yang berada di folder tersebut:

``` bash
g++ main.cpp Buku.cpp -o main
./main
```

Pada Windows, program dapat dijalankan dengan:

``` powershell
g++ main.cpp Buku.cpp -o main.exe
.\main.exe
```

Contoh pengujian berdasarkan data pada modul:

``` text
Jumlah data buku yang ingin dimasukkan: 4

Masukkan kode buku: B001
Masukkan judul buku: Algoritma
Masukkan tahun terbit: 2020

Masukkan kode buku: B003
Masukkan judul buku: Struktur_Data
Masukkan tahun terbit: 2018

Masukkan kode buku: B001
Masukkan judul buku: Basis_Data
Masukkan tahun terbit: 2021
kode buku sudah terdaftar

Masukkan kode buku: B004
Masukkan judul buku: Jaringan_Komputer
Masukkan tahun terbit: 2022

DATA LIST 1
Kode Buku    : B001
Judul        : Algoritma
Tahun Terbit : 2020
Kode Buku    : B003
Judul        : Struktur_Data
Tahun Terbit : 2018
Kode Buku    : B004
Judul        : Jaringan_Komputer
Tahun Terbit : 2022
```

Selanjutnya, masukkan `B001` sebagai kode yang dicari. Program akan
menampilkan data buku Algoritma. Untuk menguji penghapusan sesuai soal,
masukkan `B003`. Setelah penghapusan, list berisi B001 dan B004. Urutan
tampilan mengikuti arah penelusuran dari `First` ke `Last`, sehingga
hasilnya mengikuti urutan penambahan `insertLast()`.

Catatan: contoh keluaran pada PDF menampilkan data dalam urutan
terbalik, sedangkan ADT yang diminta menggunakan `insertLast()`.
Implementasi laporan ini mengikuti fungsi `insertLast()` secara
konvensional, sehingga penampilan list dimulai dari node `First`.

## Kesimpulan

Berdasarkan praktikum Modul 6, Doubly Linked List merupakan struktur
data yang menghubungkan setiap node dengan node sebelum dan sesudahnya
melalui pointer `prev` dan `next`. Pointer `First` dan `Last` membantu
mengelola node pertama serta node terakhir. Melalui implementasi ADT
pada C++, praktikum ini melatih pembuatan node, penambahan data di akhir
list, pemeriksaan duplikasi kode buku, pencarian dengan `findElm()`,
serta penghapusan elemen di awal, akhir, dan setelah node tertentu. Saat
menghapus data, hubungan pointer harus diperbarui agar list tetap
tersambung dan memori node yang dihapus dapat dibebaskan.

## Referensi

\[1\] OpenDSA. "Doubly Linked Lists." Virginia Tech. Tersedia di:
https://opendsa-server.cs.vt.edu/ODSA/StandaloneModules/20231208145515/html/ListDouble.html

\[2\] cppreference.com. "new expression." Tersedia di:
https://en.cppreference.com/w/cpp/language/new

\[3\] cppreference.com. "delete expression." Tersedia di:
https://en.cppreference.com/w/cpp/language/delete

\[4\] Telkom University. "Latihan Praktikum Modul 6: Doubly Linked
List." Dokumen praktikum yang diberikan pada tugas.
