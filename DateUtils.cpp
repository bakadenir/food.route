// DateUtils.cpp
#include "DateUtils.h" // Sertakan header yang sesuai
#include <sstream>     // Untuk istringstream
#include <iomanip>     // Untuk get_time, put_time
#include <stdexcept>   // Untuk runtime_error
#include <cctype>      // Untuk toupper, isdigit, isupper
#include <algorithm>   // Untuk transform, remove_if

using namespace std; // Menggunakan namespace standar

namespace DateUtils {
    // Implementasi fungsi stringToTm
    tm stringToTm(const string& dateStr) {
        tm t = {}; // Inisialisasi dengan nol
        istringstream ss(dateStr); // Gunakan stringstream untuk parsing
        ss >> get_time(&t, "%Y-%m-%d"); // Parsing format YYYY-MM-DD
        if (ss.fail()) {
            throw runtime_error("Gagal parsing tanggal. Format harus YYYY-MM-DD.");
        }
        return t;
    }

    // Implementasi fungsi getDaysDifference
    long long getDaysDifference(const string& startDateStr) {
        // Tanggal saat ini
        time_t now = time(0); // Dapatkan waktu saat ini dalam detik sejak epoch
        tm* ltm_now = localtime(&now); // Konversi ke struct tm lokal

        // Atur tanggal saat ini ke awal hari untuk perhitungan yang akurat
        ltm_now->tm_hour = 0;
        ltm_now->tm_min = 0;
        ltm_now->tm_sec = 0;
        time_t today_t = mktime(ltm_now); // Konversi kembali ke time_t

        // Tanggal awal (tanggal panen)
        tm start_tm;
        try {
            start_tm = stringToTm(startDateStr);
        } catch (const runtime_error& e) {
            // Tangani error parsing tanggal, kembalikan nilai default atau throw
            return -1; // Contoh: mengembalikan -1 jika tanggal tidak valid
        }
        time_t start_t = mktime(&start_tm); // Konversi ke time_t

        // Hitung selisih dalam detik, lalu konversi ke hari
        long long diff_seconds = today_t - start_t;
        return diff_seconds / (60 * 60 * 24); // Konversi detik ke hari
    }

    // Implementasi fungsi generateKodeBarang
    string generateKodeBarang(const string& namaBarang, const string& tanggalPanen) {
        string kode = "";

        // Bagian YY (2 digit tahun panen)
        if (tanggalPanen.length() >= 4) {
            kode += tanggalPanen.substr(2, 2); // Ambil 2 digit terakhir tahun
        } else {
            kode += "YY"; // Fallback jika format tanggal tidak sesuai
        }

        // Bagian XX (2 huruf kapital pertama dari nama barang)
        string cleanedNama = namaBarang;
        // Hapus spasi dari nama barang
        cleanedNama.erase(remove_if(cleanedNama.begin(), cleanedNama.end(), ::isspace), cleanedNama.end());
        // Ubah ke huruf kapital
        transform(cleanedNama.begin(), cleanedNama.end(), cleanedNama.begin(), ::toupper);

        if (cleanedNama.length() >= 2) {
            kode += cleanedNama.substr(0, 2);
        } else if (cleanedNama.length() == 1) {
            kode += cleanedNama + "_"; // Tambahkan underscore jika hanya 1 huruf
        } else {
            kode += "__"; // Fallback jika nama kosong
        }

        // Bagian MM (2 digit bulan panen)
        if (tanggalPanen.length() >= 7) { // Cukup panjang untuk YYYY-MM
            kode += tanggalPanen.substr(5, 2); // Ambil 2 digit bulan
        } else {
            kode += "MM"; // Fallback jika format tanggal tidak sesuai
        }

        return kode;
    }

    // Implementasi fungsi isKodeBarangFormat
    bool isKodeBarangFormat(const string& s) {
        // Kode barang memiliki format YYXXMM (misal: 25PS06)
        // Panjang harus 6 karakter
        if (s.length() != 6) {
            return false;
        }

        // YY (digit)
        if (!isdigit(s[0]) || !isdigit(s[1])) {
            return false;
        }

        // XX (huruf kapital atau underscore)
        if (!((isupper(s[2]) || s[2] == '_') && (isupper(s[3]) || s[3] == '_'))) {
            return false;
        }

        // MM (digit)
        if (!isdigit(s[4]) || !isdigit(s[5])) {
            return false;
        }

        return true;
    }
}
