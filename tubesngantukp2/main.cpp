#include <iostream>
#include "tubesstd.h"
using namespace std;
int main(){
    Library lib;
    initLibrary(lib);

    //sample
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
