#include "tubesstd.h"
void createListLagu(ListLagu &L) {
    L.first = nullptr;
    L.last = nullptr;
}
adrLagu allocateLagu(Lagu x) {
    adrLagu p = new ElmLagu;
    p->info = x;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}
void insertLagu(ListLagu &L, Lagu x) {
    adrLagu p = allocateLagu(x);
    if (L.first == nullptr) {
        L.first = L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}
void showLibrary(ListLagu L) {
    adrLagu p = L.first;
    while (p != nullptr) {
        cout << p->info.id << " - " << p->info.judul << " - " 
             << p->info.artis << " - " << p->info.genre 
             << " (" << p->info.tahun << ")\n";
        p = p->next;
    }
}
adrLagu findLaguById(ListLagu L, int id) {
    adrLagu p = L.first;
    while (p != nullptr) {
        if (p->info.id == id){
            return p;
        }    
        p = p->next;
    }
    return nullptr;
}
void updateLagu(adrLagu p, Lagu baru) {
    if (p != nullptr){
         p->info = baru;
    }
}
void deleteLagu(ListLagu &L, int id) {
    adrLagu p = findLaguById(L, id);
    adrLagu temp;
    if (p != nullptr) {
        temp = p;
        if (temp == L.first && temp == L.last) {
            L.first = L.last = nullptr;
        } else if (temp == L.first) {
            L.first = temp->next;
            L.first->prev = nullptr;
        } else if (temp == L.last) {
            L.last = temp->prev;
            L.last->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        temp->next = nullptr;
        temp->prev = nullptr;
    }
}
void createPlaylist(Playlist &P) {
    P.first = P.last = nullptr;
}
void addToPlaylist(Playlist &P, adrLagu song) {
    adrPlay p = new ElmPlay;
    p->song = song;
    p->next = nullptr;
    if (P.first == nullptr) {
        P.first = P.last = p;
    } else {
        P.last->next = p;
        P.last = p;
    }
}
void removeFromPlaylist(Playlist &P, int id) {
    adrPlay curr = P.first;
    adrPlay prev = nullptr;
    adrPlay temp = nullptr;
    bool found = false;
    while (curr != nullptr && !found) {
        if (curr->song->info.id == id) {
            temp = curr;
            found = true;
            if (temp == P.first) {
                P.first = temp->next;
                if (temp == P.last) {
                    P.last = nullptr;
                }
            } else {
                prev->next = temp->next;
                if (temp == P.last) {
                    P.last = prev;
                }
            }
            temp->next = nullptr;
            temp->song = nullptr;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}
void showPlaylist(Playlist P) {
    adrPlay p = P.first;
    while (p != nullptr) {
        cout << p->song->info.id << " - " << p->song->info.judul 
             << " (" << p->song->info.artis << ")\n";
        p = p->next;
    }
}
void createStack(Stack &S) {
    S.top = nullptr;
}
void push(Stack &S, adrLagu x) {
    adrS p = new ElmStack;
    p->song = x;
    p->next = S.top;
    S.top = p;
}
adrLagu pop(Stack &S) {
    adrS p;
    adrLagu x = nullptr;
    if (S.top != nullptr) {
        p = S.top;
        S.top = p->next;    
        x = p->song;        
        p->next = nullptr;  
        p->song = nullptr; 
    }
    return x;
}
void createQueue(Queue &Q) {
    Q.head = Q.tail = nullptr;
}
void enqueue(Queue &Q, adrLagu x) {
    adrQ p = new ElmQueue;
    p->song = x;
    p->next = nullptr;
    if (Q.head == nullptr){
        Q.head = Q.tail = p;
    }else {
        Q.tail->next = p;
        Q.tail = p;
    }
}
adrLagu dequeue(Queue &Q) {
    adrQ p;
    adrLagu x = nullptr;
    if (Q.head != nullptr) {
        p = Q.head;          
        Q.head = p->next;    
        if (Q.head == nullptr) {
            Q.tail = nullptr;
        }
        x = p->song;        
        p->next = nullptr;   
        p->song = nullptr;
    }
    return x;
}
void removeFromAllPlaylists(Playlist &P, int id) {
    adrPlay curr = P.first;
    adrPlay prev = nullptr;
    adrPlay temp;
    while (curr != nullptr) {
        if (curr->song->info.id == id) {
            temp = curr;
            if (temp == P.first) {
                P.first = temp->next;
                curr = P.first;
                if (temp == P.last) {
                    P.last = nullptr;
                }
            } else {
                prev->next = temp->next;
                curr = temp->next;
                if (temp == P.last) {
                    P.last = prev;
                }
            }
            temp->next = nullptr;
            temp->song = nullptr;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}
void playSong(adrLagu song, Stack &S) {
    if (song == nullptr){
        cout << "Lagu masih kosong!" << endl;
    }else{
        cout << "\nSedang memutar: " << song->info.judul 
         << " - " << song->info.artis << "\n" << endl;
        push(S, song);
    }
}
adrLagu nextSimilar(ListLagu L, adrLagu current) {
    if (current == nullptr) return L.first;
    adrLagu p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.artis == current->info.artis){
            return p;
        }    
        p = p->next;
    }
    p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.genre == current->info.genre){
            return p;
        }  
        p = p->next;
    }
    if (current->next != nullptr) {
        return current->next;
    }
    return L.first; 
}
adrLagu previousSong(Stack &S) {
    return pop(S);
}
