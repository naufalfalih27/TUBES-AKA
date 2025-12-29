#include "kontenlms.h"
#include <algorithm>
#include <cctype>

// Fungsi helper untuk mengubah string menjadi lowercase (agar saat pencarian tidak case sensitive)
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Fungsi untuk mencari konten berdasarkan judul secara "iterative"
int searchJudulIterative(const vector<KontenLMS>& data, const string& targetJudul) {
    string target = toLower(targetJudul);
    
    for (size_t i = 0; i < data.size(); i++) { // Looping semua data yang tersedia
        string judul = toLower(data[i].judulKonten); // Bandingkan semua judul konten pembelajaran dengan keyword pencarian
        if (judul.find(target) != string::npos) {
            return i; // Return index jika ditemukan sesuai keyword
        }
    }
    return -1; // Return -1 jika tidak ditemukan
}

// Fungsi untuk mencari konten berdasarkan judul secara "recursive"
int searchJudulRecursive(const vector<KontenLMS>& data, const string& targetJudul, int index) {
    // Base case: jika index melebihi ukuran data, return -1
    if (index >= (int)data.size()) {
        return -1;
    }
    
    // Bandingkan target judul
    string target = toLower(targetJudul);
    string judul = toLower(data[index].judulKonten);
    
    // Jika keyword judul ditemukan, return index
    if (judul.find(target) != string::npos) {
        return index;
    }
    
    // Recursive case: lanjut ke index berikutnya pencariannya
    return searchJudulRecursive(data, targetJudul, index + 1);
}