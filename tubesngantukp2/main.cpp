#include <iostream>
#include "tubesstd.h"
using namespace std;

/* Simple UI untuk Admin & User */
void adminMenu(Library &lib);
void userMenu(Library &lib, Playlist &pl);

int main(){
    Library lib;
    initLibrary(lib);

    // seed sample songs (optional)
    Song s1; s1.id=1; strcpy(s1.title,"Satu Hari"); strcpy(s1.artist,"ArtisA");
    strcpy(s1.genre,"Pop"); strcpy(s1.album,"Album1"); s1.year=2020;
    insertSongLast(lib,s1);
    Song s2; s2.id=2; strcpy(s2.title,"Dua Malam"); strcpy(s2.artist,"ArtisB");
    strcpy(s2.genre,"Rock"); strcpy(s2.album,"Album2"); s2.year=2019;
    insertSongLast(lib,s2);
    Song s3; s3.id=3; strcpy(s3.title,"Satu Lagi"); strcpy(s3.artist,"ArtisA");
    strcpy(s3.genre,"Pop"); strcpy(s3.album,"Album3"); s3.year=2021;
    insertSongLast(lib,s3);

    Playlist userPl;
    initPlaylist(userPl, "MyPlaylist");

    int choice;
    do{
        cout<<"\n=== Aplikasi Pemutar Musik ===\n";
        cout<<"1. Masuk sebagai Admin\n2. Masuk sebagai User\n0. Keluar\nPilih: ";
        cin>>choice; cin.ignore();
        if(choice==1) adminMenu(lib);
        else if(choice==2) userMenu(lib,userPl);
    } while(choice!=0);

    // cleanup
    clearPlaylist(userPl);
    // delete library nodes
    SongNode *p = lib.first;
    while(p){ SongNode *q = p->next; delete p; p = q; }

    cout<<"Selesai.\n";
    return 0;
}

/* ---------- Admin menu ---------- */
void adminMenu(Library &lib){
    int opt;
    do{
        cout<<"\n--- Admin ---\n1. Tambah lagu\n2. Lihat semua lagu\n3. Ubah lagu\n4. Hapus lagu\n0. Kembali\nPilih: ";
        cin>>opt; cin.ignore();
        if(opt==1){
            Song s; s.id = nextId(lib);
            cout<<"Masukkan judul: "; cin.getline(s.title,51);
            cout<<"Masukkan penyanyi: "; cin.getline(s.artist,51);
            cout<<"Masukkan genre: "; cin.getline(s.genre,31);
            cout<<"Masukkan album: "; cin.getline(s.album,51);
            cout<<"Masukkan tahun: "; cin>>s.year; cin.ignore();
            insertSongLast(lib,s);
            cout<<"Lagu ditambahkan dengan ID "<<s.id<<"\n";
        } else if(opt==2){
            viewAllSongs(lib);
        } else if(opt==3){
            int id; cout<<"ID lagu yang diubah: "; cin>>id; cin.ignore();
            SongNode *node = findSongById(lib,id);
            if(!node){ cout<<"Lagu tidak ditemukan.\n"; continue; }
            Song s = node->info;
            cout<<"Judul ("<<s.title<<"): "; cin.getline(s.title,51);
            cout<<"Penyanyi ("<<s.artist<<"): "; cin.getline(s.artist,51);
            cout<<"Genre ("<<s.genre<<"): "; cin.getline(s.genre,31);
            cout<<"Album ("<<s.album<<"): "; cin.getline(s.album,51);
            cout<<"Tahun ("<<s.year<<"): "; cin>>s.year; cin.ignore();
            updateSong(lib,id,s);
            cout<<"Data lagu diperbarui.\n";
        } else if(opt==4){
            int id; cout<<"ID lagu yang dihapus: "; cin>>id; cin.ignore();
            bool ok = deleteSong(lib,id);
            if(ok) cout<<"Lagu dihapus dari library. (Jika ada di playlist, pointer menjadi invalid; playlist harus dikelola oleh user.)\n";
            else cout<<"Lagu tidak ditemukan.\n";
        }
    } while(opt!=0);
}

/* ---------- User menu ---------- */
void userMenu(Library &lib, Playlist &pl){
    int opt;
    SongNode *currentPlaying = nullptr;
    PlaylistNode *currentPlaylistNode = nullptr;
    bool inPlaylistContext = false;

    do{
        cout<<"\n--- User ---\n1. Cari lagu (by id/title)\n2. Play lagu dari library\n3. Stop\n4. Next\n5. Prev\n6. Playlist: tambah lagu\n7. Playlist: hapus lagu\n8. Lihat playlist\n9. Lihat library\n0. Kembali\nPilih: ";
        cin>>opt; cin.ignore();
        if(opt==1){
            cout<<"Cari berdasarkan: 1=ID, 2=Title: "; int t; cin>>t; cin.ignore();
            if(t==1){
                int id; cout<<"ID: "; cin>>id; cin.ignore();
                SongNode *n = findSongById(lib,id);
                if(n) showSongInfo(n->info); else cout<<"Tidak ditemukan.\n";
            } else {
                char title[51]; cout<<"Judul (case-sensitive exact): "; cin.getline(title,51);
                SongNode *n = findSongByTitle(lib,title);
                if(n) showSongInfo(n->info); else cout<<"Tidak ditemukan.\n";
            }
        } else if(opt==2){
            cout<<"Masukkan ID lagu untuk play: "; int id; cin>>id; cin.ignore();
            SongNode *n = findSongById(lib,id);
            if(!n) { cout<<"Lagu tidak ditemukan.\n"; continue; }
            playSong(n);
            currentPlaying = n;
            // if song is in playlist, set context
            inPlaylistContext = false;
            PlaylistNode *pn = pl.head;
            while(pn){
                if(pn->songPtr == n){ currentPlaylistNode = pn; inPlaylistContext=true; break; }
                pn = pn->next;
            }
        } else if(opt==3){
            stopSong();
            currentPlaying = nullptr;
            inPlaylistContext = false;
            currentPlaylistNode = nullptr;
        } else if(opt==4){ // Next
            if(inPlaylistContext && currentPlaylistNode){
                if(currentPlaylistNode->next){
                    currentPlaylistNode = currentPlaylistNode->next;
                    playSong(currentPlaylistNode->songPtr);
                    currentPlaying = currentPlaylistNode->songPtr;
                } else cout<<"Ini lagu terakhir di playlist.\n";
            } else {
                if(currentPlaying){
                    SongNode *sim = findSimilar(lib, currentPlaying);
                    if(sim){ playSong(sim); currentPlaying = sim; inPlaylistContext=false; currentPlaylistNode=nullptr; }
                    else cout<<"Tidak ada lagu mirip atau lagu selanjutnya.\n";
                } else cout<<"Tidak ada lagu yang sedang diputar.\n";
            }
        } else if(opt==5){ // Prev
            if(inPlaylistContext && currentPlaylistNode){
                // need to find previous in playlist
                PlaylistNode *pn = pl.head; PlaylistNode *prev = nullptr;
                while(pn && pn != currentPlaylistNode){ prev = pn; pn = pn->next; }
                if(prev){ currentPlaylistNode = prev; playSong(currentPlaylistNode->songPtr); currentPlaying = currentPlaylistNode->songPtr; }
                else cout<<"Ini lagu pertama di playlist.\n";
            } else {
                // in library context: use prev pointer
                if(currentPlaying){
                    if(currentPlaying->prev){ playSong(currentPlaying->prev); currentPlaying = currentPlaying->prev; inPlaylistContext=false; currentPlaylistNode=nullptr; }
                    else cout<<"Tidak ada lagu sebelumnya.\n";
                } else cout<<"Tidak ada lagu yang sedang diputar.\n";
            }
        } else if(opt==6){
            cout<<"Masukkan ID lagu untuk ditambahkan ke playlist: "; int id; cin>>id; cin.ignore();
            SongNode *n = findSongById(lib,id);
            if(!n) { cout<<"Lagu tidak ditemukan.\n"; continue; }
            addToPlaylist(pl,n);
            cout<<"Lagu ditambahkan ke playlist \""<<pl.name<<"\".\n";
        } else if(opt==7){
            cout<<"Masukkan ID lagu untuk dihapus dari playlist: "; int id; cin>>id; cin.ignore();
            bool ok = removeFromPlaylistById(pl,id);
            if(ok) cout<<"Dihapus dari playlist.\n"; else cout<<"Tidak ditemukan di playlist.\n";
        } else if(opt==8){
            viewPlaylist(pl);
        } else if(opt==9){
            viewAllSongs(lib);
        }
    } while(opt!=0);
}