# Tugas Besar Struktur Data

Console Music Player (Admin/User) with linked-list data structures.

## Fitur
- Admin: tambah, lihat, update, hapus lagu di library (ID unik, auto-urutan ID saat tampil).
- User: putar lagu dari library/playlist/antrian, cari (ID/judul/artis/genre), history per sumber, next/prev mirip, stop.
- Playlist: pointer ke node library, tambah/hapus dengan cek duplikat.
- Queue: antrian putar dengan cek duplikat dan tampilan isi.
- Now Playing bar dan status (paused/playing), UI ASCII-only.

## Struktur Data
- Library: doubly linked list (L.first, L.last).
- Playlist: singly linked list berisi pointer ke node library.
- Queue: singly linked list (head/tail).
- History: stack per mode (library/playlist/queue).

## Berkas Utama
- tubesngantukp2/main.cpp — menu login, admin, user, kontrol player.
- tubesngantukp2/tubesstd.h / tubesngantukp2/tubesstd.cpp — definisi struct, utilitas list/playlist/queue/stack, pemutaran.

## Build & Run (Windows, g++)
```bash
cd tubesngantukp2
g++ -std=c++17 main.cpp tubesstd.cpp -o music_player
music_player.exe
```

## Catatan
- Data dummy 15 lagu dimuat otomatis saat start.
- UI memakai karakter ASCII: '-', '|', '+', '='.
