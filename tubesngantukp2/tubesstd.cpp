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
        if (p->info.id == id) return p;
        p = p->next;
    }
    return nullptr;
}
void updateLagu(adrLagu p, Lagu baru) {
    if (p != nullptr) p->info = baru;
}
void deleteLagu(ListLagu &L, int id) {
    adrLagu p = findLaguById(L, id);
    if (p == nullptr) return;
    if (p == L.first && p == L.last) {
        L.first = L.last = nullptr;
    } else if (p == L.first) {
        L.first = p->next;
        L.first->prev = nullptr;
    } else if (p == L.last) {
        L.last = p->prev;
        L.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    delete p;
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
    adrPlay p = P.first, prev = nullptr;
    while (p != nullptr) {
        if (p->song->info.id == id) {
            if (p == P.first) {
                P.first = p->next;
                if (p == P.last) P.last = nullptr;
            } else {
                prev->next = p->next;
                if (p == P.last) P.last = prev;
            }
            delete p;
            return;
        }
        prev = p;
        p = p->next;
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
void createStack(Stack &S) { S.top = nullptr; }
void push(Stack &S, adrLagu x) {
    adrS p = new ElmStack;
    p->song = x;
    p->next = S.top;
    S.top = p;
}
adrLagu pop(Stack &S) {
    if (S.top == nullptr) return nullptr;
    adrS p = S.top;
    S.top = p->next;
    adrLagu x = p->song;
    delete p;
    return x;
}
void createQueue(Queue &Q) {
    Q.head = Q.tail = nullptr;
}
void enqueue(Queue &Q, adrLagu x) {
    adrQ p = new ElmQueue;
    p->song = x;
    p->next = nullptr;
    if (Q.head == nullptr) Q.head = Q.tail = p;
    else {
        Q.tail->next = p;
        Q.tail = p;
    }
}
adrLagu dequeue(Queue &Q) {
    if (Q.head == nullptr) return nullptr;
    adrQ p = Q.head;
    Q.head = p->next;
    if (Q.head == nullptr) Q.tail = nullptr;
    adrLagu x = p->song;
    delete p;
    return x;
}
void playSong(adrLagu song) {
    if (song == nullptr) return;
    cout << "Memutar lagu: " << song->info.judul 
         << " - " << song->info.artis << endl;
}
adrLagu nextSimilar(ListLagu L, adrLagu current) {
    adrLagu p = L.first;
    while (p != nullptr) {
        if (p != current && strcmp(p->info.artis, current->info.artis) == 0)
            return p;
        p = p->next;
    }
    p = L.first;
    while (p != nullptr) {
        if (p != current && strcmp(p->info.genre, current->info.genre) == 0)
            return p;
        p = p->next;
    }
    return L.first; // fallback
}

