#include <iostream>
#include <limits>
#include "tubesstd.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ListLagu L; 
    Playlist P; 
    Stack S; 
    Queue Q;

    createListLagu(L);
    createPlaylist(P);
    createStack(S);
    createQueue(Q);

    //Data Dummy (15 Lagu)
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

    int role;
    cout << "\n====================================\n";
    cout << "   CONSOLE MUSIC PLAYER NGANTUK\n";
    cout << "====================================\n";
    cout << "1. Login sebagai Admin\n";
    cout << "2. Login sebagai User\n";
    cout << "3. Exit\n";
    cout << "====================================\n";
    cout << "Pilih role: ";
    cin >> role;
    clearInputBuffer();
    
    //Menu Admin
    if (role == 1) {
        int menu = 1;
        while (menu != 0) {
            cout << "\n====================================\n";
            cout << " MENU ADMIN NGANTUK\n";
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
                Lagu x;
                cout << "\n--- Tambah Lagu Baru ---\n";
                cout << "ID Lagu: "; cin >> x.id;
                clearInputBuffer();
                cout << "Judul Lagu: "; getline(cin, x.judul);
                cout << "Nama Artis: "; getline(cin, x.artis);
                cout << "Genre: "; getline(cin, x.genre);
                cout << "Tahun Rilis: "; cin >> x.tahun;
                insertLagu(L, x);
                cout << "\nLagu berhasil ditambahkan ke Library!\n";
            }
            else if (menu == 2) {
                cout << "\n====================================\n";
                cout << " LIBRARY LAGU NGANTUK\n";
                cout << "====================================\n";
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    showLibrary(L);
                }
            }
            else if (menu == 3) {
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
                    cout << "\nData lagu berhasil diupdate!\n";
                    cout << "  (Perubahan otomatis terefleksi di Playlist karena menggunakan pointer)\n";
                } else {
                    cout << "\nLagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
            else if (menu == 4) {
                int id; 
                cout << "\nMasukkan ID lagu yang ingin dihapus: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    removeFromAllPlaylists(P, id);
                    deleteLagu(L, id);
                    cout << "\nLagu berhasil dihapus dari Library dan Playlist!\n";
                } else {
                    cout << "\nLagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
        }
    }
    //Menu User
    else if (role == 2) {
        int menu = 1;
        adrLagu current = nullptr;
        bool playingFromPlaylist = false; 
        adrPlay currentPlayNode = nullptr; 
        
        while (menu != 0) {
            cout << "\n====================================\n";
            cout << "  MENU USER NGANTUK\n";
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
                cout << "Now: " << current->info.judul << " - " << current->info.artis << "\n";
            }
            cout << "Pilihan: ";
            cin >> menu;
            clearInputBuffer();

            if (menu == 1) {
                cout << "\n====================================\n";
                cout << " LIBRARY LAGU NGANTUK\n";
                cout << "====================================\n";
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    showLibrary(L);
                }
            }
            else if (menu == 2) {
                int id; 
                cout << "\nMasukkan ID Lagu: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    cout << "\nLagu ditemukan!\n";
                    cout << "  " << p->info.judul << " - " << p->info.artis 
                         << " (" << p->info.genre << ", " << p->info.tahun << ")\n";
                    current = p;
                    playingFromPlaylist = false;
                } else {
                    cout << "\nLagu dengan ID " << id << " tidak ditemukan!\n";
                }
            }
            else if (menu == 3) {
                if (current != nullptr) {
                    playSong(current, S);
                } else {
                    cout << "\nBelum memilih lagu! Gunakan menu 2 untuk memilih lagu.\n";
                }
            }
            else if (menu == 4) {
                if (current != nullptr) {
                    if (playingFromPlaylist && currentPlayNode != nullptr) {
                        if (currentPlayNode->next != nullptr) {
                            currentPlayNode = currentPlayNode->next;
                            current = currentPlayNode->song;
                            cout << "\nNext (Playlist Mode)\n";
                            playSong(current, S);
                        } else {
                            cout << "\nSudah lagu terakhir di playlist!\n";
                        }
                    }
                    else {
                        current = nextSimilar(L, current);
                        cout << "\nNext (Library Mode - Cari Lagu Mirip)\n";
                        playSong(current, S);
                    }
                } else {
                    cout << "\nBelum ada lagu yang diputar!\n";
                }
            }
            else if (menu == 5) {
                adrLagu prev = previousSong(S);
                if (prev != nullptr) {
                    current = prev;
                    cout << "\nKembali ke lagu sebelumnya (History)\n";
                    cout << "  " << current->info.judul << " - " << current->info.artis << "\n";
                } else {
                    cout << "\nHistory kosong!\n";
                }
            }
            else if (menu == 6) {
                int id; 
                cout << "\nMasukkan ID Lagu: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    addToPlaylist(P, p); 
                    cout << "\nLagu ditambahkan ke Playlist!\n";
                } else {
                    cout << "\nLagu tidak ditemukan!\n";
                }
            }
            else if (menu == 7) {
                cout << "\n====================================\n";
                cout << "PLAYLIST NGANTUK SAYA\n";
                cout << "====================================\n";
                if (P.first == nullptr) {
                    cout << "Playlist masih kosong.\n";
                } else {
                    showPlaylist(P);
                }
            }
            else if (menu == 8) {
                int id; 
                cout << "\nMasukkan ID Lagu yang ingin dihapus dari playlist: "; 
                cin >> id;
                removeFromPlaylist(P, id);
                cout << "\nLagu dihapus dari playlist!\n";
            }
            else if (menu == 9) {
                if (P.first != nullptr) {
                    currentPlayNode = P.first;
                    current = currentPlayNode->song;
                    playingFromPlaylist = true;
                    cout << "\nMemutar dari Playlist\n";
                    playSong(current, S);
                } else {
                    cout << "\nPlaylist kosong!\n";
                }
            }
            else if (menu == 10) {
                int id; 
                cout << "\nMasukkan ID Lagu untuk antrian: "; 
                cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    enqueue(Q, p);
                    cout << "\nLagu ditambahkan ke Antrian!\n";
                } else {
                    cout << "\nLagu tidak ditemukan!\n";
                }
            }
            else if (menu == 11) {
                adrLagu next = dequeue(Q);
                if (next != nullptr) {
                    current = next;
                    playingFromPlaylist = false;
                    playSong(current, S);
                } else {
                    cout << "\nAntrian kosong!\n";
                }
            }
        }
    }
    else if (role == 3) {
        cout << "\nTerima kasih telah menggunakan Music Player Ngantuk!\n";
    }
    else {
        cout << "\nPilihan tidak valid!\n";
    }
    return 0;
}
