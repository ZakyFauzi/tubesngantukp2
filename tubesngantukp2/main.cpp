#include <iostream>
#include "tubesstd.h"
using namespace std;
int main() {
    ListLagu L;
    Playlist P;
    Stack S;
    Queue Q;

    createListLagu(L);
    createPlaylist(P);
    createStack(S);
    createQueue(Q);

    int role;
    cout << "1. Admin\n2. User\nPilih role: ";
    cin >> role;
    if (role == 1) {
        int menu = 1;
        while (menu != 0) {
            cout << "\n=== MENU ADMIN ===\n";
            cout << "1. Tambah lagu\n";
            cout << "2. Lihat library\n";
            cout << "3. Update lagu\n";
            cout << "4. Hapus lagu\n";
            cout << "0. Keluar\n";
            cin >> menu;
            if (menu == 1) {
                Lagu x;
                cout << "ID: "; cin >> x.id;
                cout << "Judul: "; cin >> x.judul;
                cout << "Artis: "; cin >> x.artis;
                cout << "Genre: "; cin >> x.genre;
                cout << "Tahun: "; cin >> x.tahun;
                insertLagu(L, x);
            }
            else if (menu == 2) showLibrary(L);
            else if (menu == 3) {
                int id; cout << "ID lagu: "; cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != NULL) {
                    Lagu baru;
                    cout << "Judul baru: "; cin >> baru.judul;
                    cout << "Artis baru: "; cin >> baru.artis;
                    cout << "Genre baru: "; cin >> baru.genre;
                    cout << "Tahun baru: "; cin >> baru.tahun;
                    baru.id = id;
                    updateLagu(p, baru);
                }
            }
            else if (menu == 4) {
                int id; cout << "ID hapus: "; cin >> id;
                deleteLagu(L, id);
            }
        }
    }
    else if (role == 2) {
        int menu = 1;
        adrLagu current = NULL;
        while (menu != 0) {
            cout << "\n=== MENU USER ===\n";
            cout << "1. Lihat library\n";
            cout << "2. Cari lagu\n";
            cout << "3. Putar lagu\n";
            cout << "4. Next (mirip)\n";
            cout << "5. Tambah ke playlist\n";
            cout << "6. Lihat playlist\n";
            cout << "0. Keluar\n";
            cin >> menu;

            if (menu == 1) showLibrary(L);
            else if (menu == 2) {
                int id; cout << "Masukkan ID: "; cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != NULL) cout << "Lagu ditemukan!\n";
                current = p;
            }
            else if (menu == 3) {
                if (current != NULL) playSong(current);
                else cout << "Belum memilih lagu!\n";
            }
            else if (menu == 4) {
                if (current != NULL) {
                    current = nextSimilar(L, current);
                    playSong(current);
                }
            }
            else if (menu == 5) {
                int id; cout << "ID lagu: "; cin >> id;
                adrLagu p = findLaguById(L, id);
                if (p != NULL) addToPlaylist(P, p);
            }
            else if (menu == 6) showPlaylist(P);
        }
    }
    return 0;
}
