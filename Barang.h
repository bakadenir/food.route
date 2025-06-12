// Barang.h
#ifndef BARANG_H
#define BARANG_H

#include <string> // Untuk string
#include "DateUtils.h" // Sertakan DateUtils untuk fungsi tanggal

using namespace std; // Menggunakan namespace standar

// Kelas Barang untuk merepresentasikan satu item produk
class Barang {
public:
    string kodeBarang;         // Kode barang unik (YYXXMM)
    string nama;               // Nama barang (cth: Apel, Pisang)
    string tanggalPanen;       // Tanggal panen dalam format YYYY-MM-DD
    int umurSimpan;            // Umur simpan awal dalam hari (sebelum busuk)
    int stock;                 // Jumlah stock barang
    string gudangAsal;         // Gudang asal barang (Solo atau Padang)

    // Konstruktor
    Barang(string kodeBarang, string nama, string tanggalPanen, int umurSimpan, int stock, string gudangAsal);

    // Metode untuk menghitung sisa umur simpan
    int calculateRemainingShelfLife() const;
};

#endif // BARANG_H
