// DateUtils.h
#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string> // Untuk string
#include <ctime>  // Untuk tm

using namespace std; // Menggunakan namespace standar

namespace DateUtils {
    // Fungsi untuk mengonversi string tanggal (YYYY-MM-DD) ke struct tm
    tm stringToTm(const string& dateStr);

    // Fungsi untuk menghitung selisih hari antara tanggal saat ini dan tanggal awal
    // Mengembalikan jumlah hari berlalu sejak tanggal awal
    long long getDaysDifference(const string& startDateStr);

    // Fungsi untuk menghasilkan kode barang unik (YYXXMM)
    string generateKodeBarang(const string& namaBarang, const string& tanggalPanen);

    // Fungsi untuk memeriksa apakah string sesuai format kode barang (YYXXMM)
    bool isKodeBarangFormat(const string& s);
}

#endif // DATE_UTILS_H
