
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

struct Kontak {
    QString nama; // nama kontak
    int jumlahUang; // tabungan kontak
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void lihatUang();
    void kirimUang();
    void tambahKontak();
    void hapusKontak();
    void lihatKontak();

private:
    int uang = 1000000; // tabungan awal sebesar 1 juta rupiah
    QVector<Kontak> daftar; // membuat objek daftar dengan tipe data kontak
};

#endif

