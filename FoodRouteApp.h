// FoodRouteApp.h
#ifndef FOOD_ROUTE_APP_H
#define FOOD_ROUTE_APP_H

#include <string>  // Untuk string
#include <vector>  // Untuk vector
#include "Gudang.h" // Sertakan header Gudang

using namespace std; // Menggunakan namespace standar

// Kelas utama aplikasi FoodRoute
class FoodRouteApp {
private:
    Gudang gudangSolo;   // Objek Gudang Solo
    Gudang gudangPadang; // Objek Gudang Padang

    // Fungsi pembantu untuk membersihkan layar
    void clearScreen() const;
    // Fungsi pembantu untuk menunggu input Enter
    void pressEnterToContinue() const;
    // Fungsi pembantu untuk validasi input numerik
    int getValidatedIntegerInput(const string& prompt, int min, int max) const;

    // Menu dan Fungsionalitas Gudang
    void showWarehouseMenu(Gudang& gudang);
    void inputBarangToWarehouse(Gudang& gudang);
    void displayWarehouseItems(const Gudang& gudang) const;
    void deleteBarangFromWarehouse(Gudang& gudang);
    void updateBarangInWarehouse(Gudang& gudang);

    // Fungsionalitas utama aplikasi
    void listGudangMenu();
    void rekomendasiPengiriman();
    void stockBarang();

public:
    // Konstruktor
    FoodRouteApp();

    // Metode untuk menjalankan aplikasi
    void run();
};

#endif // FOOD_ROUTE_APP_H
