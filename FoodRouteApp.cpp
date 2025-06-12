// FoodRouteApp.cpp
#include "FoodRouteApp.h" // Sertakan header FoodRouteApp
#include <iostream>       // Untuk cout, cin
#include <limits>         // Untuk numeric_limits
#include <algorithm>      // Untuk sort
#include <iomanip>        // Untuk setw
#include <stdexcept>      // Untuk runtime_error (jika diperlukan)
#include "DateUtils.h"    // Untuk fungsi generateKodeBarang dan isKodeBarangFormat

using namespace std; // Menggunakan namespace standar


//banner
void banner() {
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

// Implementasi konstruktor FoodRouteApp
FoodRouteApp::FoodRouteApp()
    : gudangSolo("SOLO", 1), // Inisialisasi Gudang Solo dengan jarak 1 hari
      gudangPadang("PADANG", 3) {} // Inisialisasi Gudang Padang dengan jarak 3 hari

// Implementasi fungsi pembantu clearScreen
void FoodRouteApp::clearScreen() const {
    #ifdef _WIN32
        // For Windows
        system("cls");
    #elif __APPLE__
        // For macOS
        system("clear");
    #else
        // For other Unix-like systems (Linux, BSD, etc.)
        // A common way to clear screen on Unix-like systems
        system("clear");
    #endif
}

// Implementasi fungsi pembantu pressEnterToContinue
void FoodRouteApp::pressEnterToContinue() const {
    cout << "\n ## Tekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer
    cin.get(); // Tunggu Enter
}

// Implementasi fungsi pembantu getValidatedIntegerInput
int FoodRouteApp::getValidatedIntegerInput(const string& prompt, int min, int max) const {
    int value;
    cout << prompt;
    while (!(cin >> value) || (value < min || value > max)) {
        cout << "\n";
        cout << "   # Pilihan tidak valid. Masukkan angka antara " << min << "-" << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

// Implementasi metode showWarehouseMenu
void FoodRouteApp::showWarehouseMenu(Gudang& gudang) {
    int pilihan;
    do {
        clearScreen();
        banner();
        cout << "\n";
        cout << "   --- GUDANG " << gudang.getNamaGudang() << " ---\n";
        cout << "\n";
        cout << "       1. > Input Barang\n";
        cout << "       2. > Tampilkan Barang\n";
        cout << "       3. > Update Barang\n";
        cout << "       4. > Delete Barang\n";
        cout << "       5. > Kembali\n";
        cout << "\n";
        pilihan = getValidatedIntegerInput("    Pilih menu : ", 1, 5);

        switch (pilihan) {
            case 1:
                inputBarangToWarehouse(gudang);
                break;
            case 2:
                displayWarehouseItems(gudang);
                pressEnterToContinue();
                break;
            case 3:
                updateBarangInWarehouse(gudang);
                break;
            case 4:
                deleteBarangFromWarehouse(gudang);
                break;
            case 5:
                cout << "Kembali ke menu List Gudang.\n";
                break;
        }
    } while (pilihan != 5);
}

// Implementasi metode inputBarangToWarehouse
void FoodRouteApp::inputBarangToWarehouse(Gudang& gudang) {
    clearScreen();
    banner();
    cout << "\n";
    cout << "   --- INPUT BARANG KE GUDANG " << gudang.getNamaGudang() << " ---\n";
    cout << "\n";
    string namaBarang, tanggalPanen;
    int umurSimpan, stock;

    cout << "   > Nama Barang             : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer input
    getline(cin, namaBarang);

    cout << "   > Tgl. Panen (YYYY-MM-DD) : ";
    getline(cin, tanggalPanen);

    // Validasi tanggal panen
    try {
        tm temp_tm = DateUtils::stringToTm(tanggalPanen);
        time_t now_t = time(0);
        tm* ltm_now = localtime(&now_t);
        ltm_now->tm_hour = 0; ltm_now->tm_min = 0; ltm_now->tm_sec = 0;
        time_t today_t = mktime(ltm_now);

        if (mktime(&temp_tm) > today_t) {
            cout << "   ** Error: Tanggal Panen tidak boleh melebihi tanggal hari ini.\n";
            pressEnterToContinue();
            return;
        }
    } catch (const runtime_error& e) {
        cout << "\n   ** Error: " << e.what() << "\n";
        pressEnterToContinue();
        return;
    }

    cout << "   > Umur Simpan (hari)      : ";
    while (!(cin >> umurSimpan) || umurSimpan <= 0) {
        cout << "Input tidak valid. Masukkan angka positif untuk Umur Simpan: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "   > Stock Barang (KG)       : ";
    while (!(cin >> stock) || stock < 0) {
        cout << "Input tidak valid. Masukkan angka non-negatif untuk Stock: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Hasilkan kode barang otomatis
    string kodeBarang = DateUtils::generateKodeBarang(namaBarang, tanggalPanen);

    // Buat objek Barang baru dan tambahkan ke gudang
    gudang.addBarang(Barang(kodeBarang, namaBarang, tanggalPanen, umurSimpan, stock, gudang.getNamaGudang()));
    cout << "\n   ^ Barang dengan Kode " << kodeBarang << " berhasil ditambahkan!\n";
    pressEnterToContinue();
}

// Implementasi metode displayWarehouseItems
void FoodRouteApp::displayWarehouseItems(const Gudang& gudang) const {
    clearScreen();
    gudang.displayItems(); // Panggil metode displayItems dari objek Gudang
}

// Implementasi metode deleteBarangFromWarehouse
void FoodRouteApp::deleteBarangFromWarehouse(Gudang& gudang) {
    clearScreen();
    banner();
    cout << "\n";
    cout << "   --- DELETE BARANG DARI GUDANG " << gudang.getNamaGudang() << " ---\n";
    cout << "\n";
    string identifier;
    
    // Instruksikan user untuk input nama atau kode
    cout << "   > Masukkan Nama atau Kode Barang yang ingin dihapus : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, identifier);

    // Deteksi apakah input adalah kode barang atau nama barang
    bool isKodeBarang = DateUtils::isKodeBarangFormat(identifier);

    if (gudang.removeBarang(identifier, isKodeBarang)) {
        cout << "\n   ^ Barang \"" << identifier << "\" berhasil dihapus dari Gudang " << gudang.getNamaGudang() << ".\n";
    } else {
        cout << "\n   ^ Barang \"" << identifier << "\" tidak ditemukan di Gudang " << gudang.getNamaGudang() << ".\n";
    }
    pressEnterToContinue();
}

// Implementasi metode updateBarangInWarehouse
void FoodRouteApp::updateBarangInWarehouse(Gudang& gudang) {
    clearScreen();
    banner();
    cout << "\n";
    cout << "   --- UPDATE BARANG DI GUDANG " << gudang.getNamaGudang() << " ---\n";
    cout << "\n";
    string identifier;
    
    // Instruksikan user untuk input nama atau kode
    cout << "   > Masukkan Nama atau Kode Barang yang ingin diupdate: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, identifier);

    // Deteksi apakah input adalah kode barang atau nama barang
    bool isKodeBarang = DateUtils::isKodeBarangFormat(identifier);

    // Ambil input untuk data baru
    string newTanggalPanen;
    int newUmurSimpan, newStock;

    cout << "\n   > Masukkan data baru untuk \"" << identifier << "\"\n";

    cout << "   .Tanggal Panen Baru (YYYY-MM-DD) : ";
    getline(cin, newTanggalPanen);

    // Validasi tanggal panen baru
    try {
        tm temp_tm = DateUtils::stringToTm(newTanggalPanen);
        time_t now_t = time(0);
        tm* ltm_now = localtime(&now_t);
        ltm_now->tm_hour = 0; ltm_now->tm_min = 0; ltm_now->tm_sec = 0;
        time_t today_t = mktime(ltm_now);

        if (mktime(&temp_tm) > today_t) {
            cout << "   ** Error: Tanggal Panen baru tidak boleh melebihi tanggal hari ini.\n";
            pressEnterToContinue();
            return;
        }
    } catch (const runtime_error& e) {
        cout << "\n   ** Error: " << e.what() << "\n";
        pressEnterToContinue();
        return;
    }

    cout << "   .Umur Simpan Baru (hari)         : ";
    while (!(cin >> newUmurSimpan) || newUmurSimpan <= 0) {
        cout << "   * Input tidak valid. Masukkan angka positif untuk Umur Simpan Baru: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "   .Stock Baru (KG)                 : ";
    while (!(cin >> newStock) || newStock < 0) {
        cout << "   * Input tidak valid. Masukkan angka non-negatif untuk Stock Baru: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Panggil metode updateBarang di objek Gudang
    if (gudang.updateBarang(identifier, isKodeBarang, newTanggalPanen, newUmurSimpan, newStock)) {
        cout << "\n   ^ Barang \"" << identifier << "\" berhasil diupdate di Gudang " << gudang.getNamaGudang() << ".\n";
    } else {
        cout << "\n   ^ Barang \"" << identifier << "\" tidak ditemukan di Gudang " << gudang.getNamaGudang() << ".\n";
    }
    pressEnterToContinue();
}


// Implementasi metode listGudangMenu
void FoodRouteApp::listGudangMenu() {
    int pilihan;
    do {
        clearScreen();
        banner();
        cout << "\n";
        cout << "   --- LIST GUDANG ---\n";
        cout << "\n";
        cout << "       1. > Gudang Solo (Jarak tempuh " << gudangSolo.getJarakKeJakarta() << " hari)\n";
        cout << "       2. > Gudang Padang (Jarak tempuh " << gudangPadang.getJarakKeJakarta() << " hari)\n";
        cout << "       3. > Kembali\n";
        cout << "\n";
        pilihan = getValidatedIntegerInput("    Pilih gudang: ", 1, 3);

        switch (pilihan) {
            case 1:
                showWarehouseMenu(gudangSolo);
                break;
            case 2:
                showWarehouseMenu(gudangPadang);
                break;
            case 3:
                cout << "Kembali ke menu utama.\n";
                break;
        }
    } while (pilihan != 3);
}

// Implementasi metode rekomendasiPengiriman
void FoodRouteApp::rekomendasiPengiriman() {
    clearScreen();
    banner();
    cout << "\n";
    cout << "   --- REKOMENDASI PENGIRIMAN ---\n";
    cout << "\n";
    string namaBarangCari;
    cout << "   > Nama atau Kode barang yang dicari : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, namaBarangCari);

    Barang* bestRecommendation = nullptr; // Pointer ke barang terbaik
    int bestEffectiveShelfLife = -1;     // Sisa umur simpan efektif terbaik (lebih rendah = lebih prioritas)
    string bestGudang = "";         // Gudang dari rekomendasi terbaik

    // Lambda function untuk memeriksa dan memperbarui rekomendasi
    auto checkAndSetRecommendation = [&](const Barang& item, int jarakTempuh) {
        if (item.nama == namaBarangCari && item.stock > 0) {
            int currentRemainingShelfLife = item.calculateRemainingShelfLife();
            int effectiveShelfLife = currentRemainingShelfLife - jarakTempuh;

            if (effectiveShelfLife >= 0) {
                if (bestRecommendation == nullptr || effectiveShelfLife < bestEffectiveShelfLife) {
                    bestRecommendation = const_cast<Barang*>(&item); // Konversi ke non-const untuk penyimpanan pointer
                    bestEffectiveShelfLife = effectiveShelfLife;
                    bestGudang = item.gudangAsal;
                }
            }
        }
    };

    // Cek Gudang Solo
    for (const auto& item : gudangSolo.getItems()) {
        checkAndSetRecommendation(item, gudangSolo.getJarakKeJakarta());
    }

    // Cek Gudang Padang
    for (const auto& item : gudangPadang.getItems()) {
        checkAndSetRecommendation(item, gudangPadang.getJarakKeJakarta());
    }

    // Tampilkan hasil rekomendasi
    if (bestRecommendation != nullptr) {
        cout << "\n   .Rekomendasi Pengiriman untuk " << namaBarangCari << ":\n";
        cout << "\n";
        // Tambah Kolom "Kode Barang" pada Rekomendasi Pengiriman
        cout << left << setw(15) << "Kode Barang"
                  << setw(10) << "Gudang"
                  << setw(20) << "Nama Barang"
                  << setw(20) << "Masa Simpan (tiba)"
                  << setw(8) << "Stock" << endl;
        cout << string(75, '-') << endl; // Garis pemisah disesuaikan
        cout << left << setw(15) << bestRecommendation->kodeBarang // Tampilkan kode barang
                  << setw(10) << bestGudang
                  << setw(20) << bestRecommendation->nama
                  << setw(20) << bestEffectiveShelfLife
                  << setw(8) << bestRecommendation->stock << endl;
    } else {
        cout << "\n   * Tidak ada rekomendasi pengiriman untuk \"" << namaBarangCari
                  << "\" yang tidak busuk saat tiba di Jakarta, atau barang tidak ditemukan/stok kosong.\n";
    }
    pressEnterToContinue();
}

// Implementasi metode stockBarang
void FoodRouteApp::stockBarang() {
    clearScreen();
    banner();
    cout << "\n";
    cout << "   --- STOCK BARANG (Semua Gudang) ---\n";
    cout << "\n";
    string identifierFilter; // Mengubah nama variabel menjadi identifierFilter
    cout << "   > Masukkan Nama atau Kode Barang : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, identifierFilter);

    vector<Barang> allItems;
    // Tambahkan item dari Gudang Solo
    for (const auto& item : gudangSolo.getItems()) {
        allItems.push_back(item);
    }
    // Tambahkan item dari Gudang Padang
    for (const auto& item : gudangPadang.getItems()) {
        allItems.push_back(item);
    }

    // Filter berdasarkan nama barang atau kode barang jika ada input
    if (!identifierFilter.empty()) {
        vector<Barang> filteredItems;
        // Deteksi apakah input adalah kode barang atau nama barang
        bool isKodeBarang = DateUtils::isKodeBarangFormat(identifierFilter);

        for (const auto& item : allItems) {
            if (isKodeBarang) {
                if (item.kodeBarang == identifierFilter) {
                    filteredItems.push_back(item);
                }
            } else { // Jika bukan kode barang, berarti nama barang
                if (item.nama == identifierFilter) {
                    filteredItems.push_back(item);
                }
            }
        }
        allItems = filteredItems;
    }

    // Urutkan barang berdasarkan sisa umur simpan (yang paling cepat busuk di atas)
    sort(allItems.begin(), allItems.end(), [](const Barang& a, const Barang& b) {
        int sisaUmurA = a.calculateRemainingShelfLife();
        int sisaUmurB = b.calculateRemainingShelfLife();
        // Barang yang sudah busuk (<0) didahulukan
        if (sisaUmurA < 0 && sisaUmurB >= 0) return true;
        if (sisaUmurA >= 0 && sisaUmurB < 0) return false;
        // Jika keduanya busuk atau keduanya belum, urutkan berdasarkan sisa umur simpan (paling kecil duluan)
        return sisaUmurA < sisaUmurB;
    });

    if (allItems.empty()) {
        cout << "\n   * Tidak ada barang yang ditemukan atau stok kosong.\n";
    } else {
        // Header tabel Tambah Kolom "Kode Barang"
        cout << "\n";
        cout << left << setw(10) << "Kode"
                  << setw(10) << "Gudang"
                  << setw(15) << "Nama Barang"
                  << setw(15) << "Tgl. Panen"
                  //<< setw(10) << "Umur Simpan"
                  << setw(8) << "Stock"
                  << setw(15) << "Kadaluarsa" << endl;
        cout << string(75, '-') << endl; // Garis pemisah disesuaikan

        // Isi tabel
        for (const auto& item : allItems) {
            int sisaUmur = item.calculateRemainingShelfLife();
            cout << left << setw(10) << item.kodeBarang // Tampilkan kode barang
                      << setw(10) << item.gudangAsal
                      << setw(15) << item.nama
                      << setw(15) << item.tanggalPanen
                      //<< setw(10) << item.umurSimpan
                      << setw(1) << item.stock << " KG   "
                      << setw(1) << (sisaUmur < 0 ? "Busuk" : to_string(sisaUmur)) << " Hari" << endl;
        }
    }
    pressEnterToContinue();
}

// Implementasi metode run (menu utama aplikasi)
void FoodRouteApp::run() {
    int pilihan;
    do {
        clearScreen();
        banner();
        cout << "\n";
        cout << "   --- SISTEM MANAGEMENT RANTAI PASOK ---\n";
        cout << "\n";
        cout << "       1. > List Gudang\n";
        cout << "       2. > Pengiriman\n";
        cout << "       3. > Stock Barang\n";
        cout << "       4. > Keluar Aplikasi\n";
        cout << "\n";
        pilihan = getValidatedIntegerInput("   Masukkan pilihan Anda (1 - 4) : ", 1, 4);

        switch (pilihan) {
            case 1:
                listGudangMenu();
                break;
            case 2:
                rekomendasiPengiriman();
                break;
            case 3:
                stockBarang();
                break;
            case 4:
                cout << "\n   # Terima kasih telah menggunakan aplikasi FoodRoute. Sampai jumpa!\n";
                break;
        }
    } while (pilihan != 4);
}
