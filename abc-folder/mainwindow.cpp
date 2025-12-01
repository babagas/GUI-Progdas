#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(650, 500); // tampilan ukuran widget 
    setMinimumSize(600, 450);
    setWindowTitle("Bank BGA");

    QWidget *w = new QWidget();
    auto *layout = new QVBoxLayout();

    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(20);


    QPushButton *btnLihat = new QPushButton("Lihat Tabungan"); 
    QPushButton *btnKirim = new QPushButton("Kirim Uang");
    QPushButton *btnTambah = new QPushButton("Tambah Kontak");
    QPushButton *btnHapus = new QPushButton("Hapus Kontak");
    QPushButton *btnLihatKontak = new QPushButton("Lihat Kontak");


    int tinggi = 50;
    btnLihat->setMinimumHeight(tinggi);
    btnKirim->setMinimumHeight(tinggi);
    btnTambah->setMinimumHeight(tinggi);
    btnHapus->setMinimumHeight(tinggi);
    btnLihatKontak->setMinimumHeight(tinggi);

    layout->addWidget(btnLihat); // tombol pada gui
    layout->addWidget(btnKirim);
    layout->addWidget(btnTambah);
    layout->addWidget(btnHapus);
    layout->addWidget(btnLihatKontak);

    connect(btnLihat, &QPushButton::clicked, this, &MainWindow::lihatUang); // membuat tombol terklik menjalankan fungsi tertentu 
    connect(btnKirim, &QPushButton::clicked, this, &MainWindow::kirimUang);
    connect(btnTambah, &QPushButton::clicked, this, &MainWindow::tambahKontak);
    connect(btnHapus, &QPushButton::clicked, this, &MainWindow::hapusKontak);
    connect(btnLihatKontak, &QPushButton::clicked, this, &MainWindow::lihatKontak);

    w->setLayout(layout);
    setCentralWidget(w);
}

void MainWindow::lihatUang() {
    QMessageBox::information(this, "Uang", "Tabungan Anda (Rupiah): " + QString::number(uang)); //menampillkan jumlah tabungan
}

void MainWindow::kirimUang() {
    if (daftar.isEmpty()) {
        QMessageBox::warning(this, "Kosong", "Belum ada kontak!"); //jika kontak kosong maka akan dapat peringatan belum ada kontak
        return;
    }

    QString nama = QInputDialog::getText(this, "Kirim Uang", "Nama kontak tujuan:");
    bool found = false;

    for (auto &k : daftar) { // mengirim sejumlah uang ke kontak yang tersedia
        if (k.nama == nama) {
            found = true;

            int jumlah = QInputDialog::getInt(this, "Jumlah",  "Masukkan jumlah uang (Rupiah):");

            if (uang >= jumlah) {
                k.jumlahUang += jumlah;
                uang -= jumlah;
                QMessageBox::information(this, "Sukses", "Uang berhasil dikirim."); // jika uang yang dikirim lebih kecil sama dengan dari tabungan maka uang berhasil dikirm
            } else {
                QMessageBox::warning(this, "Gagal", "Uang tidak cukup."); // jika uang yang dikirim lebih besar dari tabungan maka akan gagal mengirim uang
            }
            break;
        }
    }

    if (!found)
        QMessageBox::warning(this, "Tidak Ditemukan", "Nama kontak tidak ditemukan."); // jika nama kontak tujuan tidak ada akan mendapat peringatan nama kontak tidak ditemukan 
}

void MainWindow::tambahKontak() {
    QString nama = QInputDialog::getText(this, "Tambah Kontak", "Masukkan nama:"); // 

    for (auto &k : daftar) {
        if (k.nama == nama) {
            QMessageBox::warning(this, "Ada", "Nama sudah ada!"); // jika nama kontak yang ingin ditambahkan ke dalam kontak sudah ada , nama kontak tidak akan ditambahkan
            return;
        }
    }

    int uang = QInputDialog::getInt(this, "Tambah Uang",  "Masukkan tabungan awal (Rupiah):");

    daftar.push_back({nama, uang});
    QMessageBox::information(this, "Sukses", "Kontak berhasil ditambahkan."); // jika nama kontak yang ingin ditambahkan ke dalam kontak belum ada , nama kontak akan ditambahkan
}

void MainWindow::hapusKontak() {
    if (daftar.isEmpty()) {
        QMessageBox::warning(this, "Kosong", "Daftar kontak kosong."); // jika tombol hapus kontak terklik dan kontak kosong maka akan dapat peringatan daftar kontak kosong
        return;
    }

    QString nama = QInputDialog::getText(this, "Hapus Kontak", "Masukkan nama:");

    for (int i = 0; i < daftar.size(); i++) {
        if (daftar[i].nama == nama) {
            daftar.remove(i);
            QMessageBox::information(this, "Sukses", "Kontak berhasil dihapus."); // menghapus kontak yang sesuai nasabah ketik
            return;
        }
    }

    QMessageBox::warning(this, "Tidak Ada", "Nama tidak ditemukan."); //gagal menghapus jika nama kontak yang nasabah ketik tidak ada di dalam kontak
}

void MainWindow::lihatKontak() {
    if (daftar.isEmpty()) {
        QMessageBox::information(this, "Kontak", "Tidak ada kontak."); // jika tidak ada kontak maka akan dpat peringatan tidak ada kontak
        return;
    }

    QString text;
    for (auto &k : daftar)
        text += k.nama + " — Tabungan: Rp" + QString::number(k.jumlahUang) + "\n"; // menampilkan kontak dan tabungannya

    QMessageBox::information(this, "Daftar Kontak", text);
}
