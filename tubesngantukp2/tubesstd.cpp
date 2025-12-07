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