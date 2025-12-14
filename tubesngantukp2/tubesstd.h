#ifndef TUBESSTD_H_INCLUDED
#define TUBESSTD_H_INCLUDED
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
typedef struct ElmLagu *adrLagu;
typedef struct ElmPlay *adrPlay;
typedef struct ElmStack *adrS;
typedef struct ElmQueue *adrQ;
// Mode pemutaran untuk mengelola history terpisah
enum PlayerMode { MODE_LIBRARY = 1, MODE_PLAYLIST = 2, MODE_QUEUE = 3 };
typedef struct Lagu {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};
struct ElmLagu {
    Lagu info;
    adrLagu next;
    adrLagu prev;
};
struct ListLagu {
    adrLagu first;
    adrLagu last;
};
struct ElmPlay {
    adrLagu song;
    adrPlay next;
};
struct Playlist {
    adrPlay first;
    adrPlay last;
};
struct ElmStack {
    adrLagu song;
    adrS next;
};
struct Stack {
    adrS top;
};
struct ElmQueue {
    adrLagu song;
    adrQ next;
};
struct Queue {
    adrQ head;
    adrQ tail;
};
// Utility
void sortLibraryById(ListLagu &L);
// Library
void createListLagu(ListLagu &L);
adrLagu allocateLagu(Lagu x);
void insertLagu(ListLagu &L, Lagu x);
void showLibrary(ListLagu L);
adrLagu findLaguById(ListLagu L, int id);
void updateLagu(adrLagu p, Lagu baru);
void deleteLagu(ListLagu &L, int id);
// Playlist
void createPlaylist(Playlist &P);
void addToPlaylist(Playlist &P, adrLagu song);
void removeFromPlaylist(Playlist &P, int id);
void showPlaylist(Playlist P);
// Stack
void createStack(Stack &S);
void push(Stack &S, adrLagu x);
adrLagu pop(Stack &S);
void clearSongFromStacks(Stack &S, int id);
// Queue
void createQueue(Queue &Q);
void enqueue(Queue &Q, adrLagu x);
adrLagu dequeue(Queue &Q);
bool isInQueue(Queue Q, int id);
void showQueue(Queue Q);
void removeFromQueue(Queue &Q, int id);
// Player
void playSong(adrLagu song, Stack &S);
adrLagu nextSimilar(ListLagu L, adrLagu current);
adrLagu previousSong(Stack &S);
void stopSong(bool &isPlaying);
// Helper
void removeFromAllPlaylists(Playlist &P, int id);
bool isInPlaylist(Playlist P, int id);
adrLagu findLaguByTitle(ListLagu L, const string &judul);
adrLagu findLaguByArtist(ListLagu L, const string &artis);
adrLagu findLaguByGenre(ListLagu L, const string &genre);
#endif // TUBESSTD_H_INCLUDED
