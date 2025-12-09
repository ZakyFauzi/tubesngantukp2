#include "tubesstd.h"
void createListLagu(ListLagu &L) {
    L.first = NULL;
    L.last = NULL;
}
adrLagu allocateLagu(Lagu x) {
    adrLagu p = new ElmLagu;
    p->info = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
void insertLagu(ListLagu &L, Lagu x) {
    adrLagu p = allocateLagu(x);
    if (L.first == NULL) {
        L.first = L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}
void showLibrary(ListLagu L) {
    adrLagu p = L.first;
    while (p != NULL) {
        cout << p->info.id << " - " << p->info.judul << " - " 
             << p->info.artis << " - " << p->info.genre 
             << " (" << p->info.tahun << ")\n";
        p = p->next;
    }
}
adrLagu findLaguById(ListLagu L, int id) {
    adrLagu p = L.first;
    while (p != NULL) {
        if (p->info.id == id) return p;
        p = p->next;
    }
    return NULL;
}
void updateLagu(adrLagu p, Lagu baru) {
    if (p != NULL) p->info = baru;
}
void deleteLagu(ListLagu &L, int id) {
    adrLagu p = findLaguById(L, id);
    if (p == NULL) return;
    if (p == L.first && p == L.last) {
        L.first = L.last = NULL;
    } else if (p == L.first) {
        L.first = p->next;
        L.first->prev = NULL;
    } else if (p == L.last) {
        L.last = p->prev;
        L.last->next = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    delete p;
}

void createPlaylist(Playlist &P) {
    P.first = P.last = NULL;
}
void addToPlaylist(Playlist &P, adrLagu song) {
    adrPlay p = new ElmPlay;
    p->song = song;
    p->next = NULL;
    if (P.first == NULL) {
        P.first = P.last = p;
    } else {
        P.last->next = p;
        P.last = p;
    }
}
void removeFromPlaylist(Playlist &P, int id) {
    adrPlay p = P.first, prev = NULL;
    while (p != NULL) {
        if (p->song->info.id == id) {
            if (p == P.first) {
                P.first = p->next;
                if (p == P.last) P.last = NULL;
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
    while (p != NULL) {
        cout << p->song->info.id << " - " << p->song->info.judul 
             << " (" << p->song->info.artis << ")\n";
        p = p->next;
    }
}
void createStack(Stack &S) { S.top = NULL; }
void push(Stack &S, adrLagu x) {
    adrS p = new ElmStack;
    p->song = x;
    p->next = S.top;
    S.top = p;
}
adrLagu pop(Stack &S) {
    if (S.top == NULL) return NULL;
    adrS p = S.top;
    S.top = p->next;
    adrLagu x = p->song;
    delete p;
    return x;
}
void createQueue(Queue &Q) {
    Q.head = Q.tail = NULL;
}
void enqueue(Queue &Q, adrLagu x) {
    adrQ p = new ElmQueue;
    p->song = x;
    p->next = NULL;
    if (Q.head == NULL) Q.head = Q.tail = p;
    else {
        Q.tail->next = p;
        Q.tail = p;
    }
}
adrLagu dequeue(Queue &Q) {
    if (Q.head == NULL) return NULL;
    adrQ p = Q.head;
    Q.head = p->next;
    if (Q.head == NULL) Q.tail = NULL;
    adrLagu x = p->song;
    delete p;
    return x;
}
void playSong(adrLagu song) {
    if (song == NULL) return;
    cout << "Memutar lagu: " << song->info.judul 
         << " - " << song->info.artis << endl;
}
adrLagu nextSimilar(ListLagu L, adrLagu current) {
    adrLagu p = L.first;
    while (p != NULL) {
        if (p != current && strcmp(p->info.artis, current->info.artis) == 0)
            return p;
        p = p->next;
    }
    p = L.first;
    while (p != NULL) {
        if (p != current && strcmp(p->info.genre, current->info.genre) == 0)
            return p;
        p = p->next;
    }
    return L.first; // fallback
}
