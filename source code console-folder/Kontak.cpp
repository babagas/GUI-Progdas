///////////////////////////////////////////////////////////
//  Kontak.cpp
//  Implementation of the Class Kontak
//  Created on:      30-Nov-2025 15:35:57
//  Original author: asus
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include "kontak.h"
#include "kelolaKontak.h"
#include "sistemUang.h"
using namespace std;

Kontak daftarKontak[100];
int jumlahKontak = 0;
int uang = 100000;

void SistemUang::lihatUang() {
    cout << "Uang anda sekarang: " << uang << endl; //menampilkan uang yang dimiliki 
}

void SistemUang::kirimUang() {
    if (jumlahKontak == 0) {
        cout << "Tidak ada kontak!\n"; //jika kontak 0 akan menampilkan 'tidak ada kontak'
        return;
    }

    string nama;
    int jumlah;
    cout << "Nama kontak tujuan: ";
    cin >> nama;
    cout << "Jumlah uang: ";
    cin >> jumlah;

    for (int i = 0; i < jumlahKontak; i++) {
        if (daftarKontak[i].nama == nama) {
            if (uang >= jumlah) {
                uang -= jumlah;
                daftarKontak[i].jumlahUang += jumlah;
                cout << "Berhasil mengirim " << jumlah << " ke " << nama << endl; // jika uang yang dikirim kurang dari uang yang dimiliki akan menampilkan 'berhasil dikirim'
            } else {
                cout << "Uang tidak cukup.\n"; // jika uang yang dikirim meleibihi uang yang dipunya akan menampilkan 'uang tidak cukup'
            }
            return;
        }
    }

    cout << "Nama tidak ditemukan.\n"; // jika nama yang diketik tidak ada di dalam kontak akan menampilkan 'Nama tidak ditemukan'
}

void KelolaKontak::tambahKontak() {
    if (jumlahKontak >= 100) {
        cout << "Daftar kontak penuh!\n"; // jika ingin menambahkan kontak dan kontak lebih dari sama dengan 100 maka akan menampilkan 'daftar kontak penuh'
        return;
    }

    Kontak k;
    cout << "Nama kontak: ";
    cin >> k.nama;
    cout << "Jumlah uang: ";
    cin >> k.jumlahUang;

    daftarKontak[jumlahKontak] = k;
    jumlahKontak++;

    cout << "Kontak ditambahkan!\n";
}

void KelolaKontak::hapusKontak() {
    string nama;
    cout << "Nama kontak yang dihapus: ";
    cin >> nama;

    int pos = -1;
    for (int i = 0; i < jumlahKontak; i++) {
        if (daftarKontak[i].nama == nama) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "Nama tidak ditemukan.\n";
        return;
    }

    for (int i = pos; i < jumlahKontak - 1; i++) {
        daftarKontak[i] = daftarKontak[i + 1]; //menghapus kontak dengan cara menggeser array  
    }

    jumlahKontak--;
    cout << "Kontak berhasil dihapus.\n";
}

void KelolaKontak::lihatKontak() {
    if (jumlahKontak == 0) {
        cout << "Tidak ada kontak.\n"; // jika tidak ada kontak akan menampilkan 'tidak ada kontak'
        return;
    }

    cout << "\nDaftar kontak:\n";
    for (int i = 0; i < jumlahKontak; i++) {
        cout << i + 1 << ". " << left << setw(12)
             << daftarKontak[i].nama
             << " | Uang: " << daftarKontak[i].jumlahUang << endl; //menampilkan kontak dan uang yang dimiliki kontak
    }
}

int main() {
    {
    ifstream file("input.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string nama, uangStr;
                if (getline(ss, nama, ',') && getline(ss, uangStr)) {
                    if (jumlahKontak < 100) {
                        daftarKontak[jumlahKontak].nama = nama;
                        try {
                            daftarKontak[jumlahKontak].jumlahUang = stoi(uangStr);
                        } catch (...) {
                            daftarKontak[jumlahKontak].jumlahUang = 0;
                        }
                        jumlahKontak++;
                    }
                }
            }
            file.close(); //membuka file input dan memasukkan data berupa kontak dan uang yang dimiliki ke daftarKontak[]
        }
    }
    while (true) {
        cout << "\n===== MENU BANK =====\n";
        cout << "1. Lihat Uang\n";
        cout << "2. Kirim Uang\n";
        cout << "3. Kontak\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";

        int pilih;
        cin >> pilih;

        switch(pilih)  {
            case 1:
                SistemUang::lihatUang();
                break;

            case 2:
                SistemUang::kirimUang();
                break;

            case 3: {
                cout << "\n-- Menu Kontak --\n";
                cout << "1. Tambah Kontak\n";
                cout << "2. Hapus Kontak\n";
                cout << "3. Lihat Kontak\n";
                cout << "4. Kembali ke menu utama\n";
                cout << "Pilih: ";
                int p;
                cin >> p;

                if (p == 1) KelolaKontak::tambahKontak();
                else if (p == 2) KelolaKontak::hapusKontak();
                else if (p == 3) KelolaKontak::lihatKontak();
                else break;
                break;
            }

            case 4:
                {
                ofstream file("output.txt", ios::trunc); // overwrite file lama
                for (int i = 0; i < jumlahKontak; i++) {
                    file << daftarKontak[i].nama << "," << daftarKontak[i].jumlahUang << endl;
                }
                file.close();
                cout << "Data kontak tersimpan. Program keluar.\n";
                return 0; //ketika keluar akan mengupdate file output.txt yang berisikan kontak beserta uang yang dimiliki
                }
            default:
                cout << "Pilihan salah!\n";
                break;
        }
    }
}
