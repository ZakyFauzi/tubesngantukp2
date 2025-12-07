#include "tubesstd.h"

void initLibrary(Library &L){
    L.first = nullptr;
    L.last = nullptr;
}
SongNode* createSongNode(const Song &s){
    SongNode *p = new SongNode;
    p->info = s;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}
bool insertSongLast(Library &L, Song s){
    SongNode *p = createSongNode(s);
    if(L.first == nullptr){
        L.first = L.last = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
    return true;
}
SongNode* findSongById(Library &L, int id){
    SongNode *p = L.first;
    while(p){
        if(p->info.id == id) return p;
        p = p->next;
    }
    return nullptr;
}
SongNode* findSongByTitle(Library &L, const char title[]){
    SongNode *p = L.first;
    while(p){
        int i=0; bool same=true;
        while(title[i] != '\0' || p->info.title[i] != '\0'){
            if(title[i] != p->info.title[i]){ same=false; break; }
            i++;
        }
        if(same) return p;
        p = p->next;
    }
    return nullptr;
}
bool updateSong(Library &L, int id, const Song &newData){
    SongNode *p = findSongById(L,id);
    if(!p) return false;
    p->info = newData;
    return true;
}
bool deleteSong(Library &L, int id){
    SongNode *p = findSongById(L,id);
    if(!p) return false;
    if(p->prev) p->prev->next = p->next; else L.first = p->next;
    if(p->next) p->next->prev = p->prev; else L.last = p->prev;
    delete p;
    return true;
}
void viewAllSongs(Library &L){
    if(!L.first){ cout<<"Library kosong.\n"; return; }
    SongNode *p = L.first;
    cout<<"Daftar Lagu di Library:\n";
    while(p){
        cout<<"ID: "<<p->info.id<<" | "<<p->info.title<<" - "<<p->info.artist
            <<" ("<<p->info.year<<") ["<<p->info.genre<<"]\n";
        p = p->next;
    }
}
int nextId(Library &L){
    int maxid = 0;
    SongNode *p = L.first;
    while(p){
        if(p->info.id > maxid) maxid = p->info.id;
        p = p->next;
    }
    return maxid + 1;
}



void initPlaylist(Playlist &P, const char name[]){
    int i=0;
    while(name[i] != '\0' && i<30){ P.name[i]=name[i]; i++; }
    P.name[i]='\0';
    P.head = nullptr;
}
bool addToPlaylist(Playlist &P, SongNode *songPtr){
    if(!songPtr) return false;
    PlaylistNode *q = new PlaylistNode;
    q->songPtr = songPtr;
    q->next = nullptr;
    if(P.head == nullptr){
        P.head = q;
    } else {
        PlaylistNode *t = P.head;
        while(t->next) t = t->next;
        t->next = q;
    }
    return true;
}
bool removeFromPlaylistById(Playlist &P, int songId){
    PlaylistNode *cur = P.head;
    PlaylistNode *prev = nullptr;
    while(cur){
        if(cur->songPtr->info.id == songId){
            if(prev) prev->next = cur->next; else P.head = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}
void viewPlaylist(Playlist &P){
    if(!P.head){ cout<<"Playlist \""<<P.name<<"\" kosong.\n"; return; }
    cout<<"Playlist \""<<P.name<<"\":\n";
    PlaylistNode *p = P.head;
    while(p){
        cout<<"ID "<<p->songPtr->info.id<<": "<<p->songPtr->info.title
            <<" - "<<p->songPtr->info.artist<<"\n";
        p = p->next;
    }
}
void clearPlaylist(Playlist &P){
    PlaylistNode *p = P.head;
    while(p){
        PlaylistNode *q = p->next;
        delete p;
        p = q;
    }
    P.head = nullptr;
}




static SongNode *playing = nullptr;
void playSong(SongNode *s){
    if(!s){ cout<<"Tidak ada lagu untuk diputar.\n"; return; }
    playing = s;
    cout<<"=== PLAY ===\n";
    showSongInfo(s->info);
    cout<<"(Simulasi: lagu sedang diputar...)\n";
}
void stopSong(){
    if(!playing){ cout<<"Tidak ada lagu yang sedang diputar.\n"; return; }
    cout<<"=== STOP === Lagu dihentikan: "<<playing->info.title<<" - "<<playing->info.artist<<"\n";
    playing = nullptr;
}
void showSongInfo(const Song &s){
    cout<<"ID: "<<s.id<<"\nJudul: "<<s.title<<"\nPenyanyi: "<<s.artist
        <<"\nAlbum: "<<s.album<<"\nGenre: "<<s.genre<<"\nTahun: "<<s.year<<"\n";
}




SongNode* findSimilar(Library &L, SongNode *current){
    if(!current) return nullptr;
    // cek artis yang sama
    SongNode *p = L.first;
    while(p){
        if(p != current){
            // compare artist strings
            int i=0; bool same=true;
            while(current->info.artist[i] != '\0' || p->info.artist[i] != '\0'){
                if(current->info.artist[i] != p->info.artist[i]){ same=false; break; }
                i++;
            }
            if(same) return p;
        }
        p = p->next;
    }
    // cek genre yang sama
    p = L.first;
    while(p){
        if(p != current){
            int i=0; bool same=true;
            while(current->info.genre[i] != '\0' || p->info.genre[i] != '\0'){
                if(current->info.genre[i] != p->info.genre[i]){ same=false; break; }
                i++;
            }
            if(same) return p;
        }
        p = p->next;
    }
    // library selanjutnya
    if(current->next) return current->next;
    if(L.first && L.first != current) return L.first;
    return nullptr;


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
            // set context jika song di playlist
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
        } else if(opt==4){
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
        } else if(opt==5){
            if(inPlaylistContext && currentPlaylistNode){
                //find prev
                PlaylistNode *pn = pl.head; PlaylistNode *prev = nullptr;
                while(pn && pn != currentPlaylistNode){ prev = pn; pn = pn->next; }
                if(prev){ currentPlaylistNode = prev; playSong(currentPlaylistNode->songPtr); currentPlaying = currentPlaylistNode->songPtr; }
                else cout<<"Ini lagu pertama di playlist.\n";
            } else {
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
