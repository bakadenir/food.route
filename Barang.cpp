// Barang.cpp
#include "Barang.h" // Sertakan header Barang

using namespace std; // Menggunakan namespace standar

// Implementasi konstruktor Barang
Barang::Barang(string kodeBarang, string nama, string tanggalPanen, int umurSimpan, int stock, string gudangAsal)
    : kodeBarang(move(kodeBarang)), // Inisialisasi kodeBarang
      nama(move(nama)), // Gunakan move untuk efisiensi
      tanggalPanen(move(tanggalPanen)),
      umurSimpan(umurSimpan),
      stock(stock),
      gudangAsal(move(gudangAsal)) {}

// Implementasi metode calculateRemainingShelfLife
int Barang::calculateRemainingShelfLife() const {
    // Gunakan fungsi dari DateUtils untuk menghitung hari berlalu sejak panen
    long long daysSinceHarvest = DateUtils::getDaysDifference(tanggalPanen);
    return umurSimpan - static_cast<int>(daysSinceHarvest);
}
