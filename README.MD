# FoodRoute: Sistem Manajemen Rantai Pasok Makanan Segar

Aplikasi konsol sederhana yang dirancang untuk mengelola dan mengoptimalkan distribusi produk makanan segar dari gudang ke toko.

## 🚀 Gambaran Umum Proyek

**FoodRoute** adalah simulasi sistem manajemen rantai pasok yang membantu melacak inventaris produk segar di berbagai gudang, memprioritaskan pengiriman berdasarkan masa simpan, serta memfasilitasi operasi data dasar seperti penambahan, pembaruan, dan penghapusan barang. Aplikasi ini dikembangkan menggunakan **C++** dan beroperasi melalui antarmuka baris perintah (CLI).

Proyek ini adalah implementasi studi kasus untuk menunjukkan pemahaman tentang konsep-konsep **struktur data** dan **algoritma** dasar dalam konteks aplikasi dunia nyata yang sederhana.

## ✨ Fitur Utama

-   **Manajemen Gudang:**
    
    -   Dua gudang yang telah ditentukan: Gudang Solo (1 hari ke Jakarta) dan Gudang Padang (3 hari ke Jakarta).
        
    -   **Input Barang:** Tambah produk baru dengan Nama Barang, Tanggal Panen, Umur Simpan (hari), dan Stok.
        
    -   **Kode Barang Otomatis:** Setiap barang secara otomatis diberi kode unik (format `YYXXMM` - 2 digit terakhir Tahun + 2 huruf pertama Nama + 2 digit Bulan).
        
    -   **Tampilkan Barang:** Lihat daftar detail barang di gudang tertentu, termasuk Kode Barang, Umur Sekarang, dan Sisa Umur Simpan.
        
    -   **Update Barang:** Perbarui detail barang yang ada (Tanggal Panen, Umur Simpan, Stok) berdasarkan **Nama Barang** atau **Kode Barang** (sistem akan mendeteksi otomatis).
        
    -   **Delete Barang:** Hapus barang dari gudang berdasarkan **Nama Barang** atau **Kode Barang** (sistem akan mendeteksi otomatis).
        
-   **Rekomendasi Pengiriman:**
    
    -   Cari rekomendasi pengiriman untuk suatu barang berdasarkan nama.
        
    -   Pilih kriteria rekomendasi:
        
        -   **Berdasarkan Umur Barang:** Prioritaskan barang yang paling cepat busuk saat tiba di Jakarta.
            
    -   Output adalah satu rekomendasi terbaik (Kode Barang, Gudang, Nama Barang, Sisa Umur, Stok).
        
-   **Stock Barang Global:**
    
    -   Lihat semua stok barang dari kedua gudang.
        
    -   Saring tampilan berdasarkan Nama Barang atau Kode Barang.
        
    -   Daftar barang **diurutkan** menggunakan **Insertion Sort** berdasarkan sisa umur simpan (yang paling cepat busuk akan muncul di atas).
        

## 🛠️ Cara Menjalankan Proyek

### Prasyarat

-   Kompiler C++ (direkomendasikan **GCC/G++**)
    
-   Sistem Operasi: Windows, Linux, atau macOS.
    

### Langkah-langkah Kompilasi & Eksekusi

1.  **Kloning Repositori (atau Buat File Secara Manual):** Jika Anda mendapatkan ini sebagai arsip ZIP, ekstrak isinya. Jika ini akan diunggah ke GitHub, pengguna akan mengkloningnya:
    
    ```
    git clone <URL_REPO_ANDA>
    cd FoodRoute
    
    ```
    
2.  **Buat Struktur File:** Pastikan Anda memiliki struktur file berikut di dalam folder proyek Anda:
    
    ```
    FoodRoute/
    ├── DateUtils.h
    ├── DateUtils.cpp
    ├── Barang.h
    ├── Barang.cpp
    ├── Gudang.h
    ├── Gudang.cpp
    ├── FoodRouteApp.h
    ├── FoodRouteApp.cpp
    └── main.cpp
    
    ```
    
3.  **Kompilasi Kode:** Buka terminal atau Command Prompt, navigasikan ke direktori `FoodRoute` Anda, lalu jalankan perintah kompilasi berikut:
    
    ```
    g++ DateUtils.cpp Barang.cpp Gudang.cpp FoodRouteApp.cpp main.cpp -o foodroute_app -std=c++11 -Wall
    
    ```
    
    -   `-o foodroute_app`: Membuat file _executable_ bernama `foodroute_app` (atau `foodroute_app.exe` di Windows).
        
    -   `-std=c++11`: Memastikan kompilasi menggunakan standar C++11 atau yang lebih baru, yang diperlukan untuk fitur seperti _lambda functions_ dan fungsi tanggal.
        
    -   `-Wall`: Mengaktifkan semua peringatan kompiler untuk membantu mendeteksi potensi masalah.
        
4.  **Jalankan Aplikasi:** Setelah kompilasi berhasil, jalankan _executable_:
    
    ```
    ./foodroute_app
    
    ```
    
    (Untuk Windows, mungkin `foodroute_app.exe`)
    

## 📁 Struktur Proyek

Proyek ini diorganisir dalam beberapa file untuk modularitas yang lebih baik:

-   `DateUtils.h` / `DateUtils.cpp`: Utilitas untuk operasi tanggal dan waktu, termasuk pembuatan dan validasi format kode barang.
    
-   `Barang.h` / `Barang.cpp`: Definisi dan implementasi kelas `Barang`, merepresentasikan satu item produk segar.
    
-   `Gudang.h` / `Gudang.cpp`: Definisi dan implementasi kelas `Gudang`, mengelola kumpulan `Barang` untuk gudang tertentu.
    
-   `FoodRouteApp.h` / `FoodRouteApp.cpp`: Definisi dan implementasi kelas `FoodRouteApp`, yang merupakan inti aplikasi, mengelola menu, navigasi, dan logika bisnis utama.
    
-   `main.cpp`: Titik masuk utama program yang menginisialisasi dan menjalankan `FoodRouteApp`.
    

## 💡 Konsep Struktur Data dan Algoritma

Proyek ini mengimplementasikan konsep-konsep kunci dalam struktur data dan algoritma:

-   **Konsep Hash Table:** Diwujudkan melalui penggunaan `kodeBarang` unik otomatis (`YYXXMM`) yang berfungsi sebagai kunci identifikasi cepat untuk setiap item. Meskipun penyimpanan utama adalah `std::vector`, `kodeBarang` mendukung pencarian data yang efisien, mirip dengan konsep _hash table_. Fungsi deteksi format kode otomatis (`DateUtils::isKodeBarangFormat`) juga berperan dalam proses "hashing" input pengguna untuk menentukan metode pencarian.
    
-   **Konsep Graph:** Jaringan distribusi (gudang ke Jakarta) diimplementasikan secara implisit. Node adalah gudang (Solo, Padang) dan tujuan (Jakarta), dengan _edge_ yang memiliki atribut jarak tempuh. Algoritma di `rekomendasiPengiriman()` berfungsi sebagai algoritma seleksi jalur optimal sederhana untuk menemukan "jalur" terbaik berdasarkan kriteria yang dipilih.
    
-   **Algoritma Sorting (Insertion Sort):** Digunakan secara eksplisit di fungsi `FoodRouteApp::stockBarang()` untuk mengurutkan daftar barang. **Insertion Sort** dipilih karena kesederhanaan implementasi dan efisiensinya yang memadai untuk dataset berukuran kecil hingga sedang, serta kemudahan dalam menjelaskan cara kerjanya. Item diurutkan berdasarkan sisa umur simpan, memastikan produk yang paling mendesak untuk dikirim atau dijual berada di bagian atas daftar.
    

## 🤝 Kontribusi

Proyek ini dikembangkan sebagai tugas kuliah. Kontribusi dalam bentuk perbaikan atau fitur tambahan dipersilakan untuk pembelajaran lebih lanjut.
