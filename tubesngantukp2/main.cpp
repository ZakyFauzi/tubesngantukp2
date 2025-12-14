#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "tubesstd.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ListLagu L; 
    Playlist P; 
    // History terpisah per mode
    Stack historyLib; 
    Stack historyPl; 
    Stack historyQ; 
    Queue Q;

    createListLagu(L);
    createPlaylist(P);
    createStack(historyLib);
    createStack(historyPl);
    createStack(historyQ);
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

    auto clearScreen = [](){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    };

    int role = 0;
    bool running = true;
    while (running) {
        clearScreen();
        cout << "\n+====================================+\n";
        cout << "|      CONSOLE MUSIC PLAYER NGANTUK   |\n";
        cout << "+====================================+\n";
        cout << "| [1] Login sebagai Admin             |\n";
        cout << "| [2] Login sebagai User              |\n";
        cout << "| [3] Exit                            |\n";
        cout << "+------------------------------------+\n";
        cout << "Pilih role: ";
        cin >> role;
        clearInputBuffer();
    
    //Menu Admin
    if (role == 1) {
        int menu = 1;
        while (menu != 0) {
            clearScreen();
            cout << "\n+======================================+\n";
            cout <<   "|          MENU ADMIN NGANTUK         |\n";
            cout <<   "+======================================+\n";
            cout <<   "| [1] Tambah Lagu ke Library          |\n";
            cout <<   "| [2] Tampilkan Semua Lagu            |\n";
            cout <<   "| [3] Update Data Lagu                |\n";
            cout <<   "| [4] Hapus Lagu dari Library         |\n";
            cout <<   "| [0] Logout (Menu Login)             |\n";
            cout <<   "+--------------------------------------+\n";
            cout << "Pilihan: ";
            cin >> menu;
            clearInputBuffer();
            
            if (menu == 1) {
                Lagu x;
                cout << "\n--- Tambah Lagu Baru ---\n";
                cout << "ID Lagu: "; cin >> x.id;
                clearInputBuffer();
                // Cegah duplikasi ID (unik)
                if (findLaguById(L, x.id) != nullptr) {
                    cout << "\n[ERROR] ID lagu sudah digunakan. Gunakan ID lain.\n";
                    cout << "\nTekan Enter untuk kembali..."; cin.get();
                    continue;
                }
                cout << "Judul Lagu: "; getline(cin, x.judul);
                cout << "Nama Artis: "; getline(cin, x.artis);
                cout << "Genre: "; getline(cin, x.genre);
                cout << "Tahun Rilis: "; cin >> x.tahun;
                clearInputBuffer();
                insertLagu(L, x);
                cout << "\nLagu berhasil ditambahkan ke Library!\n";
                cout << "\nTekan Enter untuk kembali..."; cin.get();
            }
            else if (menu == 2) {
                cout << "\n=== LIBRARY LAGU NGANTUK ===\n";
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    sortLibraryById(L);
                    showLibrary(L);
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
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
                    clearInputBuffer();
                    baru.id = id;
                    updateLagu(p, baru);
                    cout << "\nData lagu berhasil diupdate!\n";
                    cout << "  (Perubahan otomatis terefleksi di Playlist karena pointer)\n";
                } else {
                    cout << "\nLagu dengan ID " << id << " tidak ditemukan!\n";
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
            }
            else if (menu == 4) {
                int id; 
                cout << "\nMasukkan ID lagu yang ingin dihapus: ";
                cin >> id;
                clearInputBuffer();
                adrLagu p = findLaguById(L, id);
                if (p != nullptr) {
                    removeFromAllPlaylists(P, id);
                    removeFromQueue(Q, id);
                    clearSongFromStacks(historyLib, id);
                    clearSongFromStacks(historyPl, id);
                    clearSongFromStacks(historyQ, id);
                    deleteLagu(L, id);
                    cout << "\nLagu berhasil dihapus dari Library, Playlist, Queue, dan History!\n";
                } else {
                    cout << "\nLagu dengan ID " << id << " tidak ditemukan!\n";
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
            }
        }
        continue; // kembali ke menu login
    }
    //Menu User
    else if (role == 2) {
        int menu = 1;
        adrLagu current = nullptr;
        bool playingFromPlaylist = false; 
        adrPlay currentPlayNode = nullptr; 
        PlayerMode currentMode = MODE_LIBRARY;
        bool isPlaying = false;

        auto headline = [](const string &title){
            const int innerWidth = 36;
            const string bar = "+" + string(innerWidth + 2, '-') + "+\n";
            string label = title;
            if ((int)label.size() > innerWidth) {
                label = label.substr(0, innerWidth);
            }
            string padding(innerWidth - (int)label.size(), ' ');
            cout << "\n" << bar;
            cout << "| " << label << padding << " |\n";
            cout << bar;
        };

        while (menu != 0) {
            clearScreen();
            headline("MENU USER NGANTUK");
            if (current) {
                cout << "[Now] " << current->info.judul << " - " << current->info.artis;
                if (!isPlaying) cout << " (paused)";
                cout << "\n------------------------------------\n";
            }
            cout << "1. Library" << "\n";
            cout << "2. Cari & Pilih" << "\n";
            cout << "3. Playlist" << "\n";
            cout << "4. Antrian" << "\n";
            cout << "5. Now Playing" << "\n";
            cout << "0. Logout" << "\n";
            cout << "Pilihan: ";
            cin >> menu;
            clearInputBuffer();

            // Submenu Library
            if (menu == 1) {
                clearScreen();
                headline("LIBRARY");
                if (L.first == nullptr) {
                    cout << "Library masih kosong.\n";
                } else {
                    sortLibraryById(L);
                    showLibrary(L);
                    cout << "\nPilih ID lagu untuk set sebagai current (0 untuk batal): ";
                    int id; cin >> id; clearInputBuffer();
                    if (id != 0) {
                        adrLagu p = findLaguById(L, id);
                        if (p) { current = p; playingFromPlaylist = false; cout << "Dipilih.\n"; }
                        else cout << "ID tidak ditemukan.\n";
                    }
                }
                cout << "Tekan Enter untuk kembali..."; cin.get();
            }
            // Submenu Cari
            else if (menu == 2) {
                clearScreen(); headline("CARI LAGU");
                cout << "1. Berdasarkan ID\n2. Berdasarkan Judul\n3. Berdasarkan Artis\n4. Berdasarkan Genre\nPilihan: ";
                int sm; cin >> sm; clearInputBuffer();
                adrLagu r = nullptr;
                if (sm == 1) {
                    int id; cout << "Masukkan ID: "; cin >> id; clearInputBuffer();
                    r = findLaguById(L, id);
                } else if (sm == 2) {
                    string j; cout << "Masukkan Judul: "; getline(cin, j); r = findLaguByTitle(L, j);
                } else if (sm == 3) {
                    string a; cout << "Masukkan Artis: "; getline(cin, a); r = findLaguByArtist(L, a);
                } else if (sm == 4) {
                    string g; cout << "Masukkan Genre: "; getline(cin, g); r = findLaguByGenre(L, g);
                }
                if (r) {
                    current = r; playingFromPlaylist = false;
                    cout << "\nDitemukan: " << r->info.judul << " - " << r->info.artis << "\n";
                    cout << "Putar sekarang? (y/n): ";
                    char c; cin >> c; clearInputBuffer();
                    if (c == 'y' || c == 'Y') {
                        currentMode = MODE_LIBRARY;
                        playSong(current, historyLib); isPlaying = true;
                    }
                } else {
                    cout << "\nTidak ditemukan.\n";
                }
                cout << "Tekan Enter untuk kembali..."; cin.get();
            }
            // Submenu Playlist
            else if (menu == 3) {
                int pm = 1;
                while (pm != 0) {
                    clearScreen(); headline("PLAYLIST");
                    cout << "1. Lihat Playlist\n";
                    cout << "2. Tambah Lagu (ID)\n";
                    cout << "3. Hapus Lagu (ID)\n";
                    cout << "4. Putar dari Playlist (awal)\n";
                    cout << "0. Kembali\n";
                    cout << "Pilihan: "; cin >> pm; clearInputBuffer();
                    if (pm == 1) {
                        if (P.first == nullptr) cout << "Playlist kosong.\n"; else showPlaylist(P);
                        cout << "Tekan Enter..."; cin.get();
                    } else if (pm == 2) {
                        int id; cout << "ID lagu: "; cin >> id; clearInputBuffer();
                        adrLagu p = findLaguById(L, id);
                        if (!p) {
                            cout << "Tidak ditemukan.\n";
                        } else if (isInPlaylist(P, id)) {
                            cout << "Sudah ada di playlist.\n";
                        } else {
                            addToPlaylist(P, p); cout << "Ditambahkan.\n";
                        }
                        cout << "Tekan Enter..."; cin.get();
                    } else if (pm == 3) {
                        int id; cout << "ID lagu yang dihapus: "; cin >> id; clearInputBuffer();
                        removeFromPlaylist(P, id); cout << "Dihapus jika ada.\n";
                        cout << "Tekan Enter..."; cin.get();
                    } else if (pm == 4) {
                        if (P.first) {
                            currentPlayNode = P.first; current = currentPlayNode->song;
                            playingFromPlaylist = true; currentMode = MODE_PLAYLIST;
                            playSong(current, historyPl); isPlaying = true;
                        } else cout << "Playlist kosong.\n";
                        cout << "Tekan Enter..."; cin.get();
                    }
                }
            }
            // Submenu Antrian
            else if (menu == 4) {
                int qm = 1;
                while (qm != 0) {
                    clearScreen(); headline("ANTRIAN");
                    cout << "1. Tambah ke Antrian (ID)\n";
                    cout << "2. Lihat Antrian\n";
                    cout << "3. Putar Lagu Berikutnya (dequeue)\n";
                    cout << "0. Kembali\n";
                    cout << "Pilihan: "; cin >> qm; clearInputBuffer();
                    if (qm == 1) {
                        int id; cout << "ID lagu: "; cin >> id; clearInputBuffer();
                        adrLagu p = findLaguById(L, id);
                        if (!p) {
                            cout << "Tidak ditemukan.\n";
                        } else if (isInQueue(Q, id)) {
                            cout << "Sudah ada di antrian.\n";
                        } else {
                            enqueue(Q, p); cout << "Ditambahkan ke antrian.\n";
                        }
                        cout << "Tekan Enter..."; cin.get();
                    } else if (qm == 2) {
                        showQueue(Q);
                        cout << "Tekan Enter..."; cin.get();
                    } else if (qm == 3) {
                        adrLagu nxt = dequeue(Q);
                        if (nxt) { current = nxt; playingFromPlaylist = false; currentMode = MODE_QUEUE; playSong(current, historyQ); isPlaying = true; }
                        else cout << "Antrian kosong.\n";
                        cout << "Tekan Enter..."; cin.get();
                    }
                }
            }
            // Submenu Now Playing (kontrol utama)
            else if (menu == 5) {
                int nm = 1;
                while (nm != 0) {
                    clearScreen(); headline("NOW PLAYING");
                    if (current) {
                        cout << "[Now] " << current->info.judul << " - " << current->info.artis << "\n";
                    } else {
                        cout << "Belum ada lagu dipilih.\n";
                    }
                    cout << "1. Putar lagu saat ini\n";
                    cout << "2. Stop\n";
                    cout << "3. Next (mirip / playlist / queue)\n";
                    cout << "4. Previous (history)\n";
                    cout << "0. Kembali\n";
                    cout << "Pilihan: "; cin >> nm; clearInputBuffer();
                    if (nm == 1) {
                        if (current) {
                            if (playingFromPlaylist) { currentMode = MODE_PLAYLIST; playSong(current, historyPl); }
                            else if (currentMode == MODE_QUEUE) { playSong(current, historyQ); }
                            else { currentMode = MODE_LIBRARY; playSong(current, historyLib); }
                            isPlaying = true;
                        } else cout << "Belum memilih lagu.\n";
                        cout << "Tekan Enter..."; cin.get();
                    } else if (nm == 2) {
                        stopSong(isPlaying); cout << "Tekan Enter..."; cin.get();
                    } else if (nm == 3) {
                        if (current) {
                            if (playingFromPlaylist && currentPlayNode) {
                                if (currentPlayNode->next) { currentPlayNode = currentPlayNode->next; current = currentPlayNode->song; currentMode = MODE_PLAYLIST; playSong(current, historyPl); isPlaying = true; }
                                else cout << "Sudah lagu terakhir di playlist.\n";
                            } else {
                                adrLagu cand = nextSimilar(L, current);
                                if (cand) { current = cand; currentMode = MODE_LIBRARY; playSong(current, historyLib); isPlaying = true; }
                                else if (L.first) { current = L.first; currentMode = MODE_LIBRARY; playSong(current, historyLib); isPlaying = true; }
                                else cout << "Tidak ada lagu mirip atau berikutnya.\n";
                            }
                        } else cout << "Belum ada lagu yang diputar.\n";
                        cout << "Tekan Enter..."; cin.get();
                    } else if (nm == 4) {
                        adrLagu prev = nullptr;
                        if (currentMode == MODE_PLAYLIST) prev = previousSong(historyPl);
                        else if (currentMode == MODE_QUEUE) prev = previousSong(historyQ);
                        else prev = previousSong(historyLib);
                        if (prev) { current = prev; cout << "Kembali ke: " << current->info.judul << "\n"; }
                        else cout << "History kosong.\n";
                        cout << "Tekan Enter..."; cin.get();
                    }
                }
            }
        }
        continue; // kembali ke menu login
    }
    else if (role == 3) {
        cout << "\nTerima kasih telah menggunakan Music Player Ngantuk!\n";
        running = false; // end program
    }
    else {
        cout << "\nPilihan tidak valid!\n";
    }
    }
    return 0;
}
