#ifndef TUBESSTD_H_INCLUDED
#define TUBESSTD_H_INCLUDED

#include <iostream>
using namespace std;
struct Song {
    int id;
    char title[51];
    char artist[51];
    char genre[31];
    char album[51];
    int year;
};
struct SongNode {
    Song info;
    SongNode *prev;
    SongNode *next;
};
struct PlaylistNode {
    SongNode *songPtr;
    PlaylistNode *next;
};
struct Library {
    SongNode *first;
    SongNode *last;
};
struct Playlist {
    char name[31];
    PlaylistNode *head;
};
//library
void initLibrary(Library &L);
SongNode* createSongNode(const Song &s);
bool insertSongLast(Library &L, Song s);
SongNode* findSongById(Library &L, int id);
SongNode* findSongByTitle(Library &L, const char title[]);
bool updateSong(Library &L, int id, const Song &newData);
bool deleteSong(Library &L, int id); // returns true if deleted
void viewAllSongs(Library &L);
int nextId(Library &L);
//playlist
void initPlaylist(Playlist &P, const char name[]);
bool addToPlaylist(Playlist &P, SongNode *songPtr);
bool removeFromPlaylistById(Playlist &P, int songId);
void viewPlaylist(Playlist &P);
void clearPlaylist(Playlist &P);
//player
void playSong(SongNode *s);
void stopSong();
void showSongInfo(const Song &s);
//helper
SongNode* findSimilar(Library &L, SongNode *current); 
void adminMenu(Library &lib);
void userMenu(Library &lib, Playlist &pl);
#endif // TUBESSTD_H_INCLUDED
