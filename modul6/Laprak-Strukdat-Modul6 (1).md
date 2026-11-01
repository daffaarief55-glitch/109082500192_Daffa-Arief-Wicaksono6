\#
```{=html}
<h1 align="center">
```
Laporan Praktikum Modul 6 - Doubly Linked List
```{=html}
</h1>
```
```{=html}
<p align="center">
```
Daffa Arief Wicaksono - 109082500192
```{=html}
</p>
```
## Dasar Teori

### A. Doubly Linked List

Doubly Linked List adalah struktur data linear yang setiap elemennya
disebut node. Setiap node menyimpan data dan dua pointer, yaitu `next`
untuk menunjuk node berikutnya serta `prev` untuk menunjuk node
sebelumnya. Karena memiliki dua arah penghubung, penelusuran data bisa
dilakukan dari awal ke akhir maupun dari akhir ke awal \[1\].

#### 1. Struktur Elemen pada Doubly Linked List

Setiap node menyimpan informasi sesuai latihan yang dikerjakan. Pada bagian Guided, data yang digunakan adalah kendaraan dengan atribut `nopol`, `warna`, dan `thnBuat`. Pada bagian Unguided, data yang digunakan adalah buku dengan atribut `kodeBuku`, `judul`, dan `thnTerbit`. Keduanya menggunakan node dengan pointer `next` dan `prev`, serta list dengan penunjuk `First` dan `Last`. Ketika list kosong, kedua pointer tersebut bernilai `nullptr` atau `Nil`.

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

### 1. Doublylist.h

```cpp
#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>

#define Nil NULL

// Latihan 1
struct infotype {
    std::string nopol;
    std::string warna;
    int thnBuat;
};
typedef struct elmlist *address;
struct elmlist {
    infotype info;
    address next;
    address prev;
};
struct List {
    address First;
    address Last;
};

// Latihan 1
void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertLast(List &L, address P);

// Latihan 2
address findElm(List L, std::string nopol);

// Latihan 3
void deleteFirst(List &L, address &P);
void deleteLast(List &L, address &P);
void deleteAfter(List &L, address Prec, address &P);
void deleteElm(List &L, std::string nopol, bool &status);

#endif
```

File `Doublylist.h` berisi deklarasi struktur data dan fungsi yang digunakan dalam program. `infotype` menyimpan nomor polisi, warna, dan tahun pembuatan kendaraan. Setiap elemen memiliki pointer `next` dan `prev`, sedangkan `First` dan `Last` menunjuk elemen pertama dan terakhir dalam list.

### 2. Doublylist.cpp

```cpp
#include "Doublylist.h"

// Latihan 1
void CreateList(List &L) {
    L.First = Nil;
    L.Last = Nil;
}

address alokasi(infotype x) {
    address P = new elmlist;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void dealokasi(address &P) {
    delete P;
}

void printInfo(List L) {
    address P = L.Last;
    if (P == Nil) {
        std::cout << "List kosong." << std::endl;
        return;
    }
    while (P != Nil) {
        std::cout << "no polisi : " << P->info.nopol << std::endl;
        std::cout << "warna     : " << P->info.warna << std::endl;
        std::cout << "tahun     : " << P->info.thnBuat << std::endl;
        P = P->prev;
    }
}

void insertLast(List &L, address P) {
    if (L.First == Nil) {
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;
        (L.Last)->next = P;
        L.Last = P;
    }
}

// Latihan 2
address findElm(List L, std::string nopol) {
    address P = L.First;
    while (P != Nil) {
        if (P->info.nopol == nopol) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

// Latihan 3
void deleteFirst(List &L, address &P) {
    if (L.First == Nil) return;

    P = L.First;
    if (L.First == L.Last) {
        L.First = Nil;
        L.Last = Nil;
    } else {
        L.First = P->next;
        (L.First)->prev = Nil;
        P->next = Nil;
    }
}

void deleteLast(List &L, address &P) {
    if (L.First == Nil) return;

    P = L.Last;
    if (L.First == L.Last) {
        L.First = Nil;
        L.Last = Nil;
    } else {
        L.Last = P->prev;
        (L.Last)->next = Nil;
        P->prev = Nil;
    }
}

void deleteAfter(List &L, address Prec, address &P) {
    if (Prec == Nil || Prec->next == Nil) return;

    P = Prec->next;
    if (P == L.Last) {
        deleteLast(L, P);
    } else {
        Prec->next = P->next;
        (P->next)->prev = Prec;
        P->next = Nil;
        P->prev = Nil;
    }
}

void deleteElm(List &L, std::string nopol, bool &status) {
    address P = findElm(L, nopol);
    status = false;

    if (P != Nil) {
        if (P == L.First) {
            deleteFirst(L, P);
        } else if (P == L.Last) {
            deleteLast(L, P);
        } else {
            address Prec = P->prev;
            deleteAfter(L, Prec, P);
        }
        dealokasi(P);
        status = true;
    }
}
```

File `Doublylist.cpp` berisi implementasi operasi Doubly Linked List. `CreateList()` menginisialisasi list kosong, `alokasi()` membuat node baru, dan `insertLast()` menambahkan kendaraan di akhir list. `printInfo()` menampilkan data dari `Last` ke arah `First`. Fungsi `findElm()` mencari kendaraan berdasarkan nomor polisi, sedangkan fungsi `deleteFirst()`, `deleteLast()`, `deleteAfter()`, dan `deleteElm()` menangani penghapusan elemen.

### 3. main.cpp

```cpp
#include <iostream>
#include "Doublylist.h"
using namespace std;

void inputData(List &L) {
    infotype data;
    address P;

    cout << "masukkan nomor polisi: "; cin >> data.nopol;
    cout << "masukkan warna kendaraan: "; cin >> data.warna;
    cout << "masukkan tahun kendaraan: "; cin >> data.thnBuat;

    cout << endl;

    if (findElm(L, data.nopol) == Nil) {
        P = alokasi(data);
        insertLast(L, P);
    } else {
        cout << "nomor polisi sudah terdaftar" << endl;
    }
}

int main() {
    List L;
    CreateList(L);
    address P;

    // Latihan 1
    inputData(L);
    inputData(L);
    inputData(L);
    inputData(L);

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    // Latihan 2
    string nopolCari;
    cout << "\nMasukkan Nomor Polisi yang dicari : ";
    cin >> nopolCari;

    P = findElm(L, nopolCari);
    if (P != Nil) {
        cout << "Nomor Polisi : " << P->info.nopol << endl;
        cout << "Warna        : " << P->info.warna << endl;
        cout << "Tahun        : " << P->info.thnBuat << endl;
    } else {
        cout << "Data dengan nomor polisi " << nopolCari << " tidak ditemukan." << endl;
    }

    // Latihan 3
    string nopolHapus;
    bool hapusBerhasil;

    cout << "\nMasukkan Nomor Polisi yang akan dihapus : ";
    cin >> nopolHapus;

    deleteElm(L, nopolHapus, hapusBerhasil);

    if (hapusBerhasil) {
        cout << "Data dengan nomor polisi " << nopolHapus << " berhasil dihapus." << endl;
    } else {
        cout << "Data dengan nomor polisi " << nopolHapus << " tidak ditemukan." << endl;
    }

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    return 0;
}
```

File `main.cpp` menjadi program utama untuk menerima empat data kendaraan. Sebelum data ditambahkan, program mengecek apakah nomor polisi sudah ada agar tidak terjadi duplikasi. Setelah itu, program menampilkan isi list, mencari kendaraan berdasarkan nomor polisi, dan menghapus kendaraan berdasarkan nomor polisi yang dimasukkan pengguna.

### 4. Cara Kompilasi dan Pengujian

Simpan `Doublylist.h`, `Doublylist.cpp`, dan `main.cpp` dalam folder yang sama. Jalankan perintah berikut di terminal:

```bash
g++ main.cpp Doublylist.cpp -o main
./main
```

Pada Windows, gunakan:

```powershell
g++ main.cpp Doublylist.cpp -o main.exe
.\main.exe
```

Program meminta empat data kendaraan, lalu meminta nomor polisi yang ingin dicari dan dihapus. Untuk menguji pengecekan duplikasi, masukkan nomor polisi yang sama pada dua input berbeda. Program akan menampilkan pesan `nomor polisi sudah terdaftar` dan tidak menambahkan data duplikat.

---

## Unguided

### 1. Buku.h

``` cpp

#ifndef BUKU_H
#define BUKU_H

#include <iostream>
#include <string>
using namespace std;

typedef struct buku {
    string kodeBuku;
    string judul;
    int thnTerbit;
} infotype;

typedef struct ElmList *address;

typedef struct ElmList {
    infotype info;
    address next;
    address prev;
} ElmList;

typedef struct List {
    address First;
    address Last;
} List;

// ADT Doubly Linked List
void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertLast(List &L, address P);

// Searching
address findElm(List L, infotype x);

// Delete
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

#include "Buku.h"

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
    delete P;
    P = nullptr;
}

void printInfo(List L) {
    address P = L.First;

    while (P != nullptr) {
        cout << "kode buku     : " << P->info.kodeBuku << endl;
        cout << "judul         : " << P->info.judul << endl;
        cout << "tahun         : " << P->info.thnTerbit << endl;

        P = P->next;
    }
}

void insertLast(List &L, address P) {
    if (L.First == nullptr) {
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;
        L.Last->next = P;
        L.Last = P;
    }
}

address findElm(List L, infotype x) {
    address P = L.First;

    while (P != nullptr) {
        if (P->info.kodeBuku == x.kodeBuku) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

// Menghapus elemen pertama
void deleteFirst(List &L, address &P) {
    P = L.First;

    if (L.First == L.Last) {
        L.First = nullptr;
        L.Last = nullptr;
    } else {
        L.First = P->next;
        L.First->prev = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

// Menghapus elemen terakhir
void deleteLast(List &L, address &P) {
    P = L.Last;

    if (L.First == L.Last) {
        L.First = nullptr;
        L.Last = nullptr;
    } else {
        L.Last = P->prev;
        L.Last->next = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

// Menghapus elemen setelah Prec
void deleteAfter(address Prec, address &P) {
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
#include "Buku.h"
using namespace std;

void inputData(List &L) {
    infotype data;
    address P;

    cout << "masukkan kode buku: ";
    cin >> data.kodeBuku;

    cout << "masukkan judul buku: ";
    cin >> data.judul;

    cout << "masukkan tahun terbit: ";
    cin >> data.thnTerbit;

    cout << endl;

    if (findElm(L, data) == nullptr) {
        P = alokasi(data);
        insertLast(L, P);
    } else {
        cout << "kode buku sudah terdaftar" << endl;
    }
}

int main() {
    List L;
    CreateList(L);

    address P;
    infotype cari;

    // LATIHAN 1: INPUT DATA
    inputData(L);
    inputData(L);
    inputData(L);
    inputData(L);

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    // LATIHAN 2: SEARCHING
    cout << "\nMasukkan Kode Buku yang dicari : ";
    cin >> cari.kodeBuku;

    P = findElm(L, cari);

    if (P != nullptr) {
        cout << "\nKode Buku    : " << P->info.kodeBuku << endl;
        cout << "Judul        : " << P->info.judul << endl;
        cout << "Tahun Terbit : " << P->info.thnTerbit << endl;
    } else {
        cout << "Data buku tidak ditemukan." << endl;
    }

    // LATIHAN 3: DELETE
    cout << "\nMasukkan Kode Buku yang akan dihapus : ";
    cin >> cari.kodeBuku;

    P = findElm(L, cari);

    if (P != nullptr) {
        if (P == L.First) {
            deleteFirst(L, P);
        } else if (P == L.Last) {
            deleteLast(L, P);
        } else {
            deleteAfter(P->prev, P);
        }

        dealokasi(P);

        cout << "Data dengan kode buku "
             << cari.kodeBuku
             << " berhasil dihapus." << endl;
    } else {
        cout << "Data dengan kode buku "
             << cari.kodeBuku
             << " tidak ditemukan." << endl;
    }

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    return 0;
}

```

File `main.cpp` menjadi bagian untuk memasukkan data buku, memeriksa
duplikasi kode, menampilkan list, mencari buku berdasarkan kode, dan
menghapus buku yang dipilih. Jika buku yang dihapus berada di awal atau
akhir, program memanggil fungsi penghapusan yang sesuai. Jika berada di
tengah, program menggunakan `deleteAfter()` dengan node sebelumnya
sebagai `Prec`.


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
