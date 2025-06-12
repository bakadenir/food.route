// Gudang.h
#ifndef GUDANG_H
#define GUDANG_H

#include <string>   // Untuk string
#include <vector>   // Untuk vector
#include "Barang.h" // Sertakan header Barang

using namespace std; // Menggunakan namespace standar

// Kelas Gudang untuk merepresentasikan gudang penyimpanan
class Gudang {
private:
    string namaGudang; // Nama gudang (Solo atau Padang)
    int jarakKeJakarta;     // Jarak tempuh ke Jakarta dalam hari
    vector<Barang> items; // Daftar barang di gudang ini

public:
    // Konstruktor
    Gudang(string namaGudang, int jarakKeJakarta);

    // Getter
    const string& getNamaGudang() const;
    int getJarakKeJakarta() const;
    const vector<Barang>& getItems() const; // Mengembalikan referensi const ke items

    // Metode untuk menambahkan barang baru ke gudang
    void addBarang(const Barang& item);

    // Metode untuk menampilkan semua barang di gudang
    void displayItems() const;

    // Metode untuk menghapus barang berdasarkan identifier (nama atau kode)
    // isKodeBarang: true jika identifier adalah kode barang, false jika nama barang
    bool removeBarang(const string& identifier, bool isKodeBarang);

    // Metode untuk mengupdate barang berdasarkan identifier (nama atau kode)
    // isKodeBarang: true jika identifier adalah kode barang, false jika nama barang
    bool updateBarang(const string& identifier, bool isKodeBarang, const string& newTanggalPanen, int newUmurSimpan, int newStock);
};

#endif // GUDANG_H
