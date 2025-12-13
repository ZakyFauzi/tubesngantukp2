#include <iostream>
#include <limits>
#include "tubesstd.h"
using namespace std;

// Helper function untuk clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ListLagu L;      // Library Utama (Doubly Linked List)
    Playlist P;      // Playlist User (Single Linked List dengan pointer ke Library)
    Stack S;         // History lagu yang sudah diputar
    Queue Q;         // Antrian lagu

    createListLagu(L);
    createPlaylist(P);
    createStack(S);
    createQueue(Q);

    // ========== DATA DUMMY (15 Lagu) ==========
    Lagu dummy[15] = {
        {1, "Shape of You", "Ed Sheeran", "Pop", 2017},
        {2, "Blinding Lights", "The Weeknd", "Pop", 2019},
        {3, "Someone Like You", "Adele", "Pop", 2011},
        {4, "Bohemian Rhapsody", "Queen", "Rock", 1975},
        {5, "Stairway to Heaven", "Led Zeppelin", "Rock", 1971},
        {6, "Hotel California", "Eagles", "Rock", 1977},
        {7, "Lose Yourself", "Eminem", "Hip-Hop", 2002},
        {8, "Rap God", "Eminem", "Hip-Hop", 2013},
        {9, "God's Plan", "Drake", "Hip-Hop", 2018},
        {10, "Perfect", "Ed Sheeran", "Pop", 2017},
        {11, "Rolling in the Deep", "Adele", "Pop", 2010},
        {12, "Smells Like Teen Spirit", "Nirvana", "Rock", 1991},
        {13, "Wonderwall", "Oasis", "Rock", 1995},
        {14, "Stay", "The Kid LAROI & Justin Bieber", "Pop", 2021},
        {15, "Levitating", "Dua Lipa", "Pop", 2020}
    };
    
    for (int i = 0; i < 15; i++) {
        insertLagu(L, dummy[i]);
    }
    
    cout << "\n[INFO] Library berhasil di-load dengan 15 lagu dummy.\n";

    int role;
    cout << "\n====================================\n";
    cout << "   CONSOLE MUSIC PLAYER v1.0\n";
    cout << "====================================\n";
    cout << "1. Login sebagai Admin\n";
    cout << "2. Login sebagai User\n";
    cout << "3. Exit\n";
    cout << "====================================\n";
    cout << "Pilih role: ";
    cin >> role;
    clearInputBuffer();
    
    // ========== MENU ADMIN ==========
    if (role == 1) {
        int menu = 1;
        while (menu != 0) {
            cout << "\n====================================\n";
            cout << "         MENU ADMIN\n";
            cout << "====================================\n";
            cout << "1. Tambah Lagu ke Library\n";
            cout << "2. Tampilkan Semua Lagu (Library)\n";
            cout << "3. Update Data Lagu\n";
            cout << "4. Hapus Lagu dari Library\n";
            cout << "0. Logout (Kembali ke Menu Utama)\n";
            cout << "====================================\n";
            cout << "Pilihan: ";
            cin >> menu;
            clearInputBuffer();
            
            if (menu == 1) {
                // Tambah Lagu (Insert ke DLL)
                Lagu x;
                cout << "\n--- Tambah Lagu Baru ---\n";
                cout << "ID Lagu: "; cin >> x.id;
                clearInputBuffer();
                cout << "Judul Lagu: "; getline(cin, x.judul);
                cout << "Nama Artis: "; getline(cin, x.artis);
                cout << "Genre: "; getline(cin, x.genre);
                cout << "Tahun Rilis: "; cin >> x.tahun;
                insertLagu(L, x);
                cout << "\n\u2713 Lagu berhasil ditambahkan ke Library!\n";
            }
            else if (menu == 2) {
                // Lihat Library (Traversal DLL)
                cout << "\n====================================\n";
                cout << "         LIBRARY LAGU\n";
                cout << "====================================\n";
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    showLibrary(L);
                }
            }
            else if (menu == 3) {
                // Update Lagu
                int id; 
                cout << "\nMasukkan ID lagu yang ingin diupdate: "; 
                cin >> id;
                clearInputBuffer();
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    Lagu baru;
                    cout << "\n--- Update Data Lagu ---\n";
                    cout << "Judul Baru: "; getline(cin, baru.judul);
                    cout << "Artis Baru: "; getline(cin, baru.artis);
                    cout << "Genre Baru: "; getline(cin, baru.genre);
                    cout << "Tahun Baru: "; cin >> baru.tahun;
                    baru.id = id;
                    updateLagu(p, baru);
                    cout << "\n\u2713 Data lagu berhasil diupdate!\n";
                    cout << "  (Perubahan otomatis terefleksi di Playlist karena menggunakan pointer)\n";
                } else {
                    cout << "\n\u2717 Lagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
            else if (menu == 4) {
                // Hapus Lagu (CRITICAL: Cek dangling pointer dulu)
                int id; 
                cout << "\nMasukkan ID lagu yang ingin dihapus: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    // CRITICAL LOGIC: Hapus dari playlist dulu untuk mencegah dangling pointer
                    removeFromAllPlaylists(P, id);
                    deleteLagu(L, id);
                    cout << "\n\u2713 Lagu berhasil dihapus dari Library dan Playlist!\n";
                } else {
                    cout << "\n\u2717 Lagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
        }
    }
    
    // ========== MENU USER ==========
    else if (role == 2) {
        int menu = 1;
        adrLagu current = nullptr;
        bool playingFromPlaylist = false;  // Flag untuk mode playlist
        adrPlay currentPlayNode = nullptr; // Pointer node playlist saat ini
        
        while (menu != 0) {
            cout << "\n====================================\n";
            cout << "          MENU USER\n";
            cout << "====================================\n";
            cout << "1. Lihat Library Lagu\n";
            cout << "2. Cari & Pilih Lagu\n";
            cout << "3. Putar Lagu (Play)\n";
            cout << "4. Next Song (Lagu Mirip/Playlist)\n";
            cout << "5. Previous (History)\n";
            cout << "6. Tambahkan Lagu ke Playlist\n";
            cout << "7. Lihat Playlist Saya\n";
            cout << "8. Hapus Lagu dari Playlist\n";
            cout << "9. Putar Dari Playlist\n";
            cout << "10. Tambah ke Antrian (Queue)\n";
            cout << "11. Putar dari Antrian\n";
            cout << "0. Logout (Kembali ke Menu Utama)\n";
            cout << "====================================\n";
            if (current != nullptr) {
                cout << "\u266b Now: " << current->info.judul << " - " << current->info.artis << "\n";
            }
            cout << "Pilihan: ";
            cin >> menu;
            clearInputBuffer();

            if (menu == 1) {
                // Lihat Library
                cout << "\n====================================\n";
                cout << "         LIBRARY LAGU\n";
                cout << "====================================\n";
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    showLibrary(L);
                }
            }
            else if (menu == 2) {
                // Cari Lagu berdasarkan ID
                int id; 
                cout << "\nMasukkan ID Lagu: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    cout << "\n\u2713 Lagu ditemukan!\n";
                    cout << "  " << p->info.judul << " - " << p->info.artis 
                         << " (" << p->info.genre << ", " << p->info.tahun << ")\n";
                    current = p;
                    playingFromPlaylist = false; // Reset mode ke library
                } else {
                    cout << "\n\u2717 Lagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
            else if (menu == 3) {
                // Putar Lagu
                if (current != nullptr) {
                    playSong(current, S); // Push ke history stack
                } else {
                    cout << "\n\u2717 Belum memilih lagu! Gunakan menu 2 untuk memilih lagu.\n";
                }
            }
            else if (menu == 4) {
                // Next Song dengan logic berbeda tergantung mode
                if (current != nullptr) {
                    // MODE A: Jika sedang putar dari playlist
                    if (playingFromPlaylist && currentPlayNode != nullptr) {
                        if (currentPlayNode->next != nullptr) {
                            currentPlayNode = currentPlayNode->next;
                            current = currentPlayNode->song;
                            cout << "\n\u25b6 Next (Playlist Mode)\n";
                            playSong(current, S);
                        } else {
                            cout << "\n\u2717 Sudah lagu terakhir di playlist!\n";
                        }
                    }
                    // MODE B: Jika sedang putar dari library (cari lagu mirip)
                    else {
                        current = nextSimilar(L, current);
                        cout << "\n\u25b6 Next (Library Mode - Cari Lagu Mirip)\n";
                        playSong(current, S);
                    }
                } else {
                    cout << "\n\u2717 Belum ada lagu yang diputar!\n";
                }
            }
            else if (menu == 5) {
                // Previous (ambil dari Stack history)
                adrLagu prev = previousSong(S);
                if (prev != nullptr) {
                    current = prev;
                    cout << "\n\u25c0 Kembali ke lagu sebelumnya (History)\n";
                    cout << "  " << current->info.judul << " - " << current->info.artis << "\n";
                } else {
                    cout << "\n\u2717 History kosong!\n";
                }
            }
            else if (menu == 6) {
                // Tambah ke Playlist (Menyimpan POINTER, bukan duplikasi data)
                int id; 
                cout << "\nMasukkan ID Lagu: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    addToPlaylist(P, p); // Simpan pointer ke Library
                    cout << "\n\u2713 Lagu ditambahkan ke Playlist!\n";
                } else {
                    cout << "\n\u2717 Lagu tidak ditemukan!\n";
                }
            }
            else if (menu == 7) {
                // Lihat Playlist
                cout << "\n====================================\n";
                cout << "       PLAYLIST SAYA\n";
                cout << "====================================\n";
                if (P.first == nullptr) {
                    cout << "Playlist masih kosong.\n";
                } else {
                    showPlaylist(P);
                }
            }
            else if (menu == 8) {
                // Hapus dari Playlist
                int id; 
                cout << "\nMasukkan ID Lagu yang ingin dihapus dari playlist: "; 
                cin >> id;
                removeFromPlaylist(P, id);
                cout << "\n\u2713 Lagu dihapus dari playlist!\n";
            }
            else if (menu == 9) {
                // Putar dari Playlist (MODE PLAYLIST)
                if (P.first != nullptr) {
                    currentPlayNode = P.first;
                    current = currentPlayNode->song;
                    playingFromPlaylist = true;
                    cout << "\n\u25b6 Memutar dari Playlist\n";
                    playSong(current, S);
                } else {
                    cout << "\n\u2717 Playlist kosong!\n";
                }
            }
            else if (menu == 10) {
                // Tambah ke Queue
                int id; 
                cout << "\nMasukkan ID Lagu untuk antrian: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    enqueue(Q, p);
                    cout << "\n\u2713 Lagu ditambahkan ke Antrian!\n";
                } else {
                    cout << "\n\u2717 Lagu tidak ditemukan!\n";
                }
            }
            else if (menu == 11) {
                // Putar dari Queue (FIFO)
                adrLagu next = dequeue(Q);
                if (next != nullptr) {
                    current = next;
                    playingFromPlaylist = false;
                    playSong(current, S);
                } else {
                    cout << "\n\u2717 Antrian kosong!\n";
                }
            }
        }
    }
    else if (role == 3) {
        cout << "\nTerima kasih telah menggunakan Music Player!\n";
    }
    else {
        cout << "\nPilihan tidak valid!\n";
    }
    
    return 0;
}
