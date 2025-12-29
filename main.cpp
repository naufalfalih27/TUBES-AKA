#include <iostream>
#include <iomanip>
#include <chrono>
#include "kontenlms.h"

using namespace std;
using namespace std::chrono;

// Fungsi untuk menampilkan header tabel (hanya NO dan KONTEN PEMBELAJARAN)
void displayHeader() {
    cout << "\n" << string(65, '=') << endl;
    cout << left << setw(5) << "NO" 
         << setw(60) << "KONTEN PEMBELAJARAN" << endl;
    cout << string(65, '=') << endl;
}

// Fungsi untuk menampilkan satu baris konten (hanya NO dan KONTEN PEMBELAJARAN)
void displayKonten(int no, const KontenLMS& konten) {
    cout << left << setw(5) << no 
         << setw(60) << konten.judulKonten << endl;
}

// Fungsi untuk menampilkan semua konten pembelajaran
void displayAllKonten(const vector<KontenLMS>& data) {
    displayHeader();
    for (size_t i = 0; i < data.size(); i++) {
        displayKonten(i + 1, data[i]);
    }
    cout << string(65, '=') << endl;
}

// Mmebuat data uji dengan ukuran n, data asli akan diulang agar dapat mensimulasikan input besar
vector<KontenLMS> buatDataUji(const vector<KontenLMS>& dataAsli, int n) {
    vector<KontenLMS> dataUji;
    dataUji.reserve(n);

    for (int i = 0; i < n; i++) {
        dataUji.push_back(dataAsli[i % dataAsli.size()]);
    }
    return dataUji;
}

int main() {
    // Inisialisasi data konten LMS
    vector<KontenLMS> dataKonten = {
        {"MW01", "Materi Week 1         \"Storage Management\"",  "Materi",    12},
        {"QW01", "Quiz 1                \"Storage Management\"",  "Quiz",      4},
        {"TW01", "Tugas 1               \"Storage Management\"",  "Tugas",     18},
        {"PW01", "PR 1                  \"Storage Management\"",  "PR",        15},
        {"VW01", "Video Pembelajaran    \"Storage Management\"",  "Video",     420},
        {"RW01", "Referensi Materi      \"Storage Management\"",  "Referensi", 55},
        {"KW01", "Tugas Kelompok Week 1 \"Storage Management\"",  "Tugas",     90},
        {"MW02", "Materi Week 2         \"Indexing\"",            "Materi",    14},
        {"QW02", "Quiz 2                \"Indexing\"",            "Quiz",      5},
        {"TW02", "Tugas 2               \"Indexing\"",            "Tugas",     22},
        {"PW02", "PR 2                  \"Indexing\"",            "PR",        17},
        {"VW02", "Video Pembelajaran    \"Indexing\"",            "Video",     510},
        {"RW02", "Referensi Materi      \"Indexing\"",            "Referensi", 63},
        {"MW03", "Materi Week 3         \"Query Processing\"",    "Materi",    16},
        {"QW03", "Quiz 3                \"Query Processing\"",    "Quiz",      6},
        {"TW03", "Tugas 3               \"Query Processing\"",    "Tugas",     25},
        {"PW03", "PR 3                  \"Query Processing\"",    "PR",        19},
        {"VW03", "Video Pembelajaran    \"Query Processing\"",    "Video",     680},
        {"RW03", "Referensi Materi      \"Query Processing\"",    "Referensi", 72},
        {"KW03", "Tugas Kelompok Week 3 \"Query Processing\"",    "Tugas",     110},
        {"MW04", "Materi Week 4         \"Concurrency Control\"", "Materi",    15},
        {"QW04", "Quiz 4                \"Concurrency Control\"", "Quiz",      6},
        {"TW04", "Tugas 4               \"Concurrency Control\"", "Tugas",     28},
        {"PW04", "PR 4                  \"Concurrency Control\"", "PR",        21},
        {"VW04", "Video Pembelajaran    \"Concurrency Control\"", "Video",     750},
        {"RW04", "Referensi Materi      \"Concurrency Control\"", "Referensi", 80},
        {"MW05", "Materi Week 5         \"Backup and Recovery\"", "Materi",    18},
        {"QW05", "Quiz 5                \"Backup and Recovery\"", "Quiz",      7},
        {"TW05", "Tugas 5               \"Backup and Recovery\"", "Tugas",     30},
        {"PW05", "PR 5                  \"Backup and Recovery\"", "PR",        23},
        {"VW05", "Video Pembelajaran    \"Backup and Recovery\"", "Video",     920},
        {"RW05", "Referensi Materi      \"Backup and Recovery\"", "Referensi", 95},
        {"KW05", "Tugas Kelompok Week 5 \"Backup and Recovery\"", "Tugas",     135}
    };
    
    int pilihan;
    string keyword;

    // Jumlah pengulangan pencarian untuk mendapatkan rata-rata running time
    const int REPEAT = 100000;
    
    do {
        // Menu utama program
        cout << "\n========== SISTEM KONTEN LMS ==========\n";
        cout << "1. Tampilkan Semua Konten Pembelajaran\n";
        cout << "2. Cari Konten Pembelajaran (dengan Running Time)\n";
        cout << "0. Keluar\n";
        cout << "=======================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
        
        switch (pilihan) {
            case 1:
                // Menampilkan seluruh data konten
                displayAllKonten(dataKonten);
                break;
                
            case 2: {
                // Memasukkan keyword pencarian oleh user
                cout << "Masukkan kata kunci pencarian: ";
                getline(cin, keyword);

                // Variasi ukuran input (n), untuk analisis running time yang berfungsi untuk melihat pengaruh jumlah data thdp waktu eksekusi
                vector<int> ukuranInput = {1, 10, 20, 100, 1000, 10000};

                // Var untuk menampung total waktu iteratif
                long long totalIter = 0;
                // Var untuk menampung total waktu rekursif
                long long totalRec  = 0; 

                // Output header table analisis running time
                cout << "\n===== ANALISIS RUNNING TIME BERDASARKAN UKURAN INPUT =====\n";
                cout << left << setw(10) << "n"
                    << setw(20) << "Iteratif (ns)"
                    << setw(20) << "Rekursif (ns)" << endl;
                cout << string(50, '-') << endl;

                // Loop untuk tiap ukuran input n
                for (int n : ukuranInput) {
                    // Data uji dengan ukuran n dari data konten pembelajaran asli
                    vector<KontenLMS> dataUji = buatDataUji(dataKonten, n);

                    // Hitung waktu dan mencatat waktu dengan metode iteratif
                    auto startIter = high_resolution_clock::now();
                    // Mengulang pencarian sebanyak repeat kali agar hasil lebih stabil
                    for (int i = 0; i < REPEAT; i++) {
                        searchJudulIterative(dataUji, keyword);
                    }
                    // Mencatat waktu selesai pencarian secara iteratif
                    auto stopIter = high_resolution_clock::now();

                    // Menghitung rata-rata waktu eksekusi metode iteratif
                    long long timeIter =
                        duration_cast<nanoseconds>(stopIter - startIter).count() / REPEAT;

                    // Hitung waktu dan mencatat waktu dengan metode rekursif
                    auto startRec = high_resolution_clock::now();
                    // Mengulang pencarian sebanyak repeat kali agar hasil lebih stabil
                    for (int i = 0; i < REPEAT; i++) {
                        searchJudulRecursive(dataUji, keyword, 0);
                    }
                    // Mencatat waktu selesai pencarian secara rekursif
                    auto stopRec = high_resolution_clock::now();
                    // Menghitung rata-rata waktu eksekusi metode rekursif
                    long long timeRec =
                        duration_cast<nanoseconds>(stopRec - startRec).count() / REPEAT;

                    // Akumulasi waktu ke total perhitungan rata-rata keseluruhan
                    totalIter += timeIter;
                    totalRec  += timeRec;

                    // Menampilkan hasil waktu eksekusi untuk ukuran input n
                    cout << left << setw(10) << n
                        << setw(20) << timeIter
                        << setw(20) << timeRec << endl;
                }

                // Hitung rata-rata waktu dari semua ukuran input
                long long avgIter = totalIter / ukuranInput.size();
                long long avgRec  = totalRec  / ukuranInput.size();

                // Tampilkan kesimpulan rata-rata dari tiap metode
                cout << "\n===== KESIMPULAN =====\n";
                cout << "Rata-rata waktu metode Iteratif : " << avgIter << " ns\n";
                cout << "Rata-rata waktu metode Rekursif : " << avgRec  << " ns\n\n";

                // Menentukan metode yg lebih efektif
                if (avgIter < avgRec) {
                    cout << "> Metode ITERATIF lebih efektif dari segi waktu eksekusi.\n";
                } else if (avgRec < avgIter) {
                    cout << "> Metode REKURSIF lebih efektif dari segi waktu eksekusi.\n";
                } else {
                    cout << "> Metode ITERATIF dan REKURSIF memiliki waktu eksekusi yang sebanding.\n";
                }

                break;
            }

            // Keluar dari program
            case 0:
                cout << "\nTerima kasih telah menggunakan sistem!\n";
                break;
                
            default:
                // Validasi input menu
                cout << "\n Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
    
    return 0;
}