// Gudang.cpp
#include "Gudang.h"  // Sertakan header Gudang
#include <iostream>  // Untuk cout
#include <iomanip>   // Untuk setw
#include <limits>    // Untuk numeric_limits (untuk membersihkan buffer)
#include "DateUtils.h" // Untuk fungsi tanggal
#include <algorithm> // Untuk std::remove_if, std::find_if

using namespace std; // Menggunakan namespace standar

void bannerG() {
    cout << "###########################################################################\n";    
    cout << "    _____   ___    ___   ___        ____   ___   __ __  ______    ___ 		\n";
    cout << "   |     | /   \\  /   \\ |   \\      |    \\ /   \\ |  |  ||      |  /  _]	\n";
    cout << "   |   __||     ||     ||    \\     |  D  )     ||  |  ||      | /  [_ 	\n";
    cout << "   |  |_  |  O  ||  O  ||  D  |    |    /|  O  ||  |  ||_|  |_||    _]		\n";
    cout << "   |   _] |     ||     ||     | __ |    \\|     ||  :  |  |  |  |   [_ 	\n";
    cout << "   |  |   |     ||     ||     ||  ||  .  \\     ||     |  |  |  |     |	\n";
    cout << "   |__|    \\___/  \\___/ |_____||__||__|\\_|\\___/  \\__,_|  |__|  |_____|	\n";
    cout << "\n";
    cout << "###########################################################################\n";
}

// Implementasi konstruktor Gudang
Gudang::Gudang(string namaGudang, int jarakKeJakarta)
    : namaGudang(move(namaGudang)),
      jarakKeJakarta(jarakKeJakarta) {}

// Implementasi getter
const string& Gudang::getNamaGudang() const {
    return namaGudang;
}

int Gudang::getJarakKeJakarta() const {
    return jarakKeJakarta;
}

const vector<Barang>& Gudang::getItems() const {
    return items;
}

// Implementasi metode addBarang
void Gudang::addBarang(const Barang& item) {
    items.push_back(item);
}

// Implementasi metode displayItems
void Gudang::displayItems() const {
    bannerG();
    cout << "\n";
    cout << "   --- BARANG DI GUDANG " << namaGudang << " ---\n";
    cout << "\n";

    if (items.empty()) {
        cout << "   # Belum ada barang di gudang ini.\n";
    } else {
        // Header tabel: Tambah Kolom "Kode Barang"
        cout << left << setw(10) << "Kode"
                  << setw(15) << "Nama Barang"
                  << setw(15) << "Tgl. Panen"
                  << setw(15) << "Masa Simpan"
                  << setw(8) << "Stock"
                  //<< setw(15) << "Umur Skrg"
                  << setw(15) << "Kadaluarsa" << endl;
        cout << string(75, '-') << endl; // Garis pemisah disesuaikan

        // Isi tabel
        for (const auto& item : items) {
            int sisaUmur = item.calculateRemainingShelfLife();
            //long long umurSekarang = DateUtils::getDaysDifference(item.tanggalPanen);

            cout << left << setw(10) << item.kodeBarang // Tampilkan kode barang
                      << setw(15) << item.nama
                      << setw(15) << item.tanggalPanen
                      << setw(3) << item.umurSimpan << "Hari        "
                      << setw(1) << item.stock << " KG   "
                      //<< setw(15) << umurSekarang
                      << setw(1) << (sisaUmur < 0 ? "Busuk" : to_string(sisaUmur)) << " Hari" << endl;
        }
    }
}

// Implementasi metode removeBarang
bool Gudang::removeBarang(const string& identifier, bool isKodeBarang) {
    bool removed = false;
    auto it = remove_if(items.begin(), items.end(), [&](const Barang& b) {
        if (!removed) { // Hapus hanya satu instansi pertama yang ditemukan
            if (isKodeBarang) {
                if (b.kodeBarang == identifier) {
                    removed = true;
                    return true;
                }
            } else { // Jika bukan kode barang, berarti nama barang
                if (b.nama == identifier) {
                    removed = true;
                    return true;
                }
            }
        }
        return false;
    });

    if (removed) {
        items.erase(it, items.end()); // Hapus elemen dari vektor
    }
    return removed;
}

// Implementasi metode updateBarang
bool Gudang::updateBarang(const string& identifier, bool isKodeBarang, const string& newTanggalPanen, int newUmurSimpan, int newStock) {
    // Cari barang berdasarkan identifier
    auto it = find_if(items.begin(), items.end(), [&](Barang& b) {
        if (isKodeBarang) {
            return b.kodeBarang == identifier;
        } else {
            return b.nama == identifier;
        }
    });

    if (it != items.end()) { // Jika barang ditemukan
        // Update properti barang
        it->tanggalPanen = newTanggalPanen;
        it->umurSimpan = newUmurSimpan;
        it->stock = newStock;
        // Regenerasi kode barang jika tanggal panen berubah
        it->kodeBarang = DateUtils::generateKodeBarang(it->nama, newTanggalPanen);
        return true; // Berhasil diupdate
    }
    return false; // Barang tidak ditemukan
}
