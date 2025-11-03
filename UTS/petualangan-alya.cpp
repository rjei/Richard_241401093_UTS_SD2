#include <iostream>
#include <string>
#include <limits> 
#include <cctype>  // utnuk toUpper

using namespace std;

struct pesanan_ajaib {
    string nama_hewan;
    string menu_pesanan;
    int waktu_kedatangan;
    int status_vip; // 1 = biasa, 2 = vip
};

// Fungsi untuk mengubah string ke huruf kapital
string stringToUpper(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

// Fungsi swap untuk Selection Sort
void swap(pesanan_ajaib &a, pesanan_ajaib &b) {
    pesanan_ajaib temp = a;
    a = b;
    b = temp;
}

int main() {
    int n;
    cout << "Masukkan jumlah pesanan: ";
    cin >> n;
    cout << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    pesanan_ajaib* daftar = new pesanan_ajaib[n];

    // Input pesanan
    for (int i = 0; i < n; i++) {
        cout << "Pesanan " << i + 1 << ":\n"; // 
        cout << "Nama hewan: ";
        getline(cin, daftar[i].nama_hewan);
        
        cout << "Menu pesanan: ";
        getline(cin, daftar[i].menu_pesanan);

        cout << "Status VIP (1=biasa, 2=VIP): "; // 
        cin >> daftar[i].status_vip;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        daftar[i].waktu_kedatangan = i + 1; 

        cout << endl; 
    }

    //LOGIKA SELECTION SORT 
    for (int i = 0; i < n - 1; i++) {
        // 1. Asumsikan item terbaik (prioritas tertinggi) ada di 'i'
        int best_index = i;
        // 2. Cari item yang 'lebih baik' di sisa array
        for (int j = i + 1; j < n; j++) {
            // Aturan Prioritas:
            // 1: Apakah 'j' lebih prioritas dari 'best_index?
            if (daftar[j].status_vip > daftar[best_index].status_vip) { 
                best_index = j; 
            } 
            // 2: Jika statusnya sama
            else if (daftar[j].status_vip == daftar[best_index].status_vip) {
                // Cek siapa yang datang duluan 
                if (daftar[j].waktu_kedatangan < daftar[best_index].waktu_kedatangan) { 
                    best_index = j;
                }
            }
        }
            // 3. Tukar item di 'i' dengan item 'terbaik' yang ditemukan
            if (i != best_index) {
                swap(daftar[i], daftar[best_index]);
            }
    }

    // 4. mencetak seluruh array yang sudah terurut
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << stringToUpper(daftar[i].nama_hewan) 
             << " - " << daftar[i].menu_pesanan;
        
        if (daftar[i].status_vip == 2) {
            cout << " [VIP]"; // 
        }
        cout << "\n";
    }

    delete[] daftar;
    return 0;
}