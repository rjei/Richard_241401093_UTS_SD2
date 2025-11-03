#include <iostream>
#include <string>
#include <limits>


using namespace std;

struct Node {
    string nama_barang;
    int harga_barang;
    int jumlah_barang;
    Node *next;
};

Node *head = NULL;
Node *tail = NULL;

//untuk output rupiahnya ada titik
string formatRupiah(long long n) {
    // 1. Ubah angka ke string
    string s = to_string(n);
    // String untuk menampung hasil terbalik
    string reversed_with_dots = "";
    int count = 0;
    // 2. Loop dari belakang string angka
    for (int i = s.length() - 1; i >= 0; i--) {
        // 3. Tambahkan karakter ke string terbalik
        reversed_with_dots += s[i];
        count++;
        // 4. Tambahkan titik setiap 3 angka (dan bukan di akhir)
        if (count % 3 == 0 && i != 0) {
            reversed_with_dots += ".";
        }
    }
        // 5. Balikkan string "reversed_with_dots" secara manual
        string formatted = "";
        for (int i = reversed_with_dots.length() - 1; i >= 0; i--) {
            formatted += reversed_with_dots[i];
    }
    if (formatted == "") return "0"; 

    return formatted;
}

// copas dari fungsi insertlast yang dibahas di kelas
void insertLast(string nama, int harga, int jumlah) {
    Node *newNode = new Node;
    newNode->nama_barang = nama;
    newNode->harga_barang = harga;
    newNode->jumlah_barang = jumlah;
    newNode->next = NULL;

    if (tail == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// copas dari fungsi deleteByNama yang dibahas di kelas
void deleteByNama(string nama) {
    if (head == NULL) {
        cout << "Keranjang kosong!\n";
        return;
    }
    Node *temp;
    if (head->nama_barang == nama) {
        temp = head;
        head = head->next;
        if (head == NULL) tail = NULL;
        delete temp;
        return;
    }
    Node *p = head;
    while (p->next != NULL && p->next->nama_barang != nama) {
        p = p->next;
    }
    if (p->next == NULL) {
        cout << "Barang dengan nama '" << nama << "' tidak ditemukan!\n"; // 
    } 
    else {
        temp = p->next;
        if (temp == tail) {
            tail = p;
        }
        p->next = temp->next;
        delete temp;
    }
}
// sedikit tambahan dari contoh printlist
void tampilkanKeranjang() {
    Node *temp = head;
    int total_barang = 0;
    long long total_harga = 0; 

    while (temp != NULL) {
       
        cout << temp->nama_barang << " - Rp" << formatRupiah(temp->harga_barang)
             << " x" << temp->jumlah_barang << endl;

        total_barang++; 
        total_harga += (long long)temp->harga_barang * temp->jumlah_barang;

        temp = temp->next;
    }

    cout << "\n";
    cout << "Total barang: " << total_barang << endl;
    
    cout << "Total harga: Rp" << formatRupiah(total_harga) << endl; 
}

int main() {
    int jumlah_awal;
    cout << "Masukkan jumlah barang awal: "; 
    cin >> jumlah_awal;
    cout << '\n';

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    for (int i = 0; i < jumlah_awal; i++) {
        string nama;
        int harga;
        int jumlah;

        cout << "Barang " << i + 1 << ":\n"; 
        cout << "Nama: ";
        getline(cin, nama);  
        cout << "Harga: ";
        cin >> harga; 
        cout << "Jumlah: ";
        cin >> jumlah; 
        cout << '\n';
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        insertLast(nama, harga, jumlah); 
    }

    char hapus;
    cout << "Apakah ingin menghapus barang? (y/n): "; 
    cin >> hapus;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (hapus == 'y' || hapus == 'Y') {
        string nama_hapus;
        cout << "Masukkan nama barang yang ingin dihapus: ";  
        getline(cin, nama_hapus);
        deleteByNama(nama_hapus);
    }


    tampilkanKeranjang();

    return 0;
}