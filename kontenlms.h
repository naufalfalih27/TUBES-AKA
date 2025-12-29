#ifndef KONTEN_LMS_H
#define KONTEN_LMS_H

#include <string>
#include <vector>
using namespace std;

struct KontenLMS {
    string idKonten;        // Contoh : MW01, QW01, TW01, PW01, VW01, RW01
    string judulKonten;     // Judul konten (digunakan sebagai key pencarian, dan pencarian harus sesuai dengan judul konten yang tertera seperti besar kecilnya)
    string jenisKonten;     // Contoh : Materi, Quiz, PR, Tugas, Video, Referensi
    int ukuranMB;           // Ukuran data dalam satuan MB untuk keperluan simulasi perhitungan running time
};

int searchJudulIterative(const vector<KontenLMS>& data, const string& targetJudul);

int searchJudulRecursive(const vector<KontenLMS>& data, const string& targetJudul, int index);

#endif