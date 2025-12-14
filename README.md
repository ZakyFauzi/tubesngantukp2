# 🎵 Tugas Besar Struktur Data - Console Music Player

Aplikasi console music player dengan role Admin dan User yang dibangun menggunakan linked-list data structures (DLL, SLL, Stack, Queue).

---

## 📋 Daftar Isi
- [Fitur Utama](#-fitur-utama)
- [Struktur Data](#-struktur-data)
- [Struktur File](#-struktur-file)
- [Instalasi & Kompilasi](#-instalasi--kompilasi)
- [Cara Penggunaan](#-cara-penggunaan)
- [Detail Implementasi](#-detail-implementasi)
- [Anggota Kelompok](#-anggota-kelompok)

---

## ✨ Fitur Utama

### Mode Admin
- **Tambah Lagu**: Menambahkan lagu baru ke library dengan ID unik
- **Lihat Library**: Menampilkan semua lagu dalam format tabel terurut berdasarkan ID
- **Update Lagu**: Mengubah data lagu (judul, artis, genre, tahun)
- **Hapus Lagu**: Menghapus lagu dari library dan membersihkan semua referensi di playlist, queue, dan history

### Mode User
- **Library Browser**: Jelajahi dan pilih lagu dari library
- **Pencarian Lanjutan**: Cari lagu berdasarkan ID, Judul, Artis, atau Genre
- **Playlist Management**: 
  - Buat playlist pribadi dengan pointer ke lagu library
  - Tambah/hapus lagu dengan proteksi duplikasi
  - Putar playlist secara berurutan
- **Queue System**: 
  - Antrian putar dengan sistem FIFO
  - Lihat daftar antrian
  - Proteksi duplikasi
- **Player Control**:
  - Play/Stop lagu
  - Next (lagu mirip berdasarkan artis/genre/urutan)
  - Previous (dari history stack)
  - Now Playing status bar dengan indikator paused/playing

### Keunggulan Sistem
- ✅ **Memory Safe**: Proper cleanup untuk menghindari dangling pointer
- ✅ **Mode-Aware History**: Terpisah untuk library, playlist, dan queue
- ✅ **Smart Recommendations**: Next song berdasarkan kesamaan artis atau genre
- ✅ **UI Clean**: Tampilan tabel rapi dengan `setw` formatting
- ✅ **Duplicate Prevention**: Cek otomatis sebelum tambah ke playlist/queue

---

## 🗂️ Struktur Data

### 1. Library (Doubly Linked List)
```
struct ElmLagu {
    Lagu info;           // Data lagu (ID, judul, artis, genre, tahun)
    adrLagu next;        // Pointer ke lagu berikutnya
    adrLagu prev;        // Pointer ke lagu sebelumnya
};

struct ListLagu {
    adrLagu first;       // Pointer lagu pertama
    adrLagu last;        // Pointer lagu terakhir
};
```
**Fungsi**: Menyimpan master data semua lagu dengan akses bi-directional.

### 2. Playlist (Singly Linked List dengan Pointer)
```
struct ElmPlay {
    adrLagu song;        // Pointer ke node lagu di library
    adrPlay next;        // Pointer ke item playlist berikutnya
};

struct Playlist {
    adrPlay first;
    adrPlay last;
};
```
**Fungsi**: Koleksi pointer ke lagu library (tidak duplikasi data). Update lagu di library otomatis terrefleksi di playlist.

### 3. Queue (Singly Linked List FIFO)
```
struct ElmQueue {
    adrLagu song;        // Pointer ke lagu
    adrQ next;
};

struct Queue {
    adrQ head;           // Front (dequeue)
    adrQ tail;           // Rear (enqueue)
};
```
**Fungsi**: Antrian lagu yang akan diputar dengan sistem First-In-First-Out.

### 4. History Stack (LIFO per Mode)
```
struct ElmStack {
    adrLagu song;
    adrS next;
};

struct Stack {
    adrS top;
};
```
**Fungsi**: Menyimpan history pemutaran terpisah untuk mode library, playlist, dan queue (untuk fitur Previous).

---

## 📁 Struktur File

```
tubesngantukp2/
├── README.md                    # Dokumentasi project
├── tubesngantukp2/
│   ├── main.cpp                 # Entry point & UI (login, menu admin/user)
│   ├── tubesstd.h               # Header file (struct, typedef, function declarations)
│   ├── tubesstd.cpp             # Implementasi semua fungsi operasi data
│   ├── pseudocode.txt           # Pseudocode algoritma (32 fungsi)
│   ├── tubesngantukp2.cbp       # Code::Blocks project file
│   └── tubesngantukp2.layout    # Code::Blocks layout
```

---

## 🔧 Instalasi & Kompilasi

### Requirements
- C++ Compiler dengan support C++17
- Windows (untuk `cls`), Linux/Mac (untuk `clear`)

### Compile dengan g++
```bash
cd tubesngantukp2
g++ -std=c++17 main.cpp tubesstd.cpp -o music_player
```

### Compile dengan Code::Blocks
1. Buka file `tubesngantukp2.cbp`
2. Build → Build (Ctrl+F9)
3. Build → Run (Ctrl+F10)

### Run
```bash
# Windows
music_player.exe

# Linux/Mac
./music_player
```

---

## 🎮 Cara Penggunaan

### Menu Login
```
[1] Login sebagai Admin
[2] Login sebagai User
[3] Exit
```

### Workflow Admin
1. Login sebagai Admin (pilih 1)
2. Tambah lagu baru atau kelola library
3. Update/hapus lagu akan otomatis update playlist user
4. Logout kembali ke menu login

### Workflow User
1. Login sebagai User (pilih 2)
2. **Jelajah Library** → Pilih lagu untuk set as current
3. **Buat Playlist** → Tambah lagu favorit (by ID)
4. **Putar** → Library / Playlist / Queue
5. **Control** → Next (mirip) / Previous (history) / Stop
6. Logout kembali ke menu login

### Tips Penggunaan
- 🔍 **Cari lagu** dengan berbagai kriteria untuk menemukan lagu cepat
- 📝 **Gunakan Queue** untuk mengatur urutan lagu yang akan diputar
- 📜 **History** akan menyimpan lagu yang sudah diputar per mode
- ⏭️ **Next** akan mencari lagu mirip (artis → genre → berikutnya)

---

## 🔬 Detail Implementasi

### Highlight Features

#### 1. Smart Delete System
Saat admin hapus lagu, sistem otomatis:
```cpp
removeFromAllPlaylists(P, id);    // Hapus dari playlist
removeFromQueue(Q, id);            // Hapus dari antrian
clearSongFromStacks(historyLib, id);  // Bersihkan history
clearSongFromStacks(historyPl, id);
clearSongFromStacks(historyQ, id);
deleteLagu(L, id);                 // Hapus dari library
```

#### 2. Duplicate Prevention
```cpp
if (!isInPlaylist(P, id)) {
    addToPlaylist(P, song);
}
```

#### 3. Mode-Aware History
```cpp
if (currentMode == MODE_PLAYLIST)      prev = previousSong(historyPl);
else if (currentMode == MODE_QUEUE)    prev = previousSong(historyQ);
else                                   prev = previousSong(historyLib);
```

#### 4. Next Similar Song
```cpp
// Prioritas: Artis sama → Genre sama → Berikutnya di list → First
adrLagu nextSimilar(ListLagu L, adrLagu current)
```

### Memory Management
- ✅ Semua `new` dipasangkan dengan `delete`
- ✅ Pointer cleanup sebelum delete node
- ✅ Stack rebuild untuk clear deleted songs
- ✅ Null pointer checks sebelum akses

### UI Formatting
Menggunakan `<iomanip>` untuk tabel rapi:
```cpp
cout << left << setw(5) << "ID" 
     << setw(30) << "Judul" 
     << setw(25) << "Artis" 
     << setw(15) << "Genre" 
     << "Tahun" << "\n";
```

---

## 📊 Data Dummy

Aplikasi memuat 15 lagu dummy saat startup:
- **Pop**: Shape of You, Blinding Lights, Someone Like You, Perfect, Rolling in the Deep, Stay, Levitating
- **Rock**: Bohemian Rhapsody, Stairway to Heaven, Hotel California, Smells Like Teen Spirit, Wonderwall
- **Hip-Hop**: Lose Yourself, Rap God, God's Plan

---

## 👥 Anggota Kelompok

| Nama | NIM |
|------|-----|
| Zaky Muhammad Fauzi | 103052400064 |
| Brama Hartouo | 103052400030 |

**Mata Kuliah**: Struktur Data  
**Semester**: 3 (Ganjil 2025/2026)  
**Institusi**: Telkom University

---

## 📝 Catatan Pengembangan

- Pseudocode lengkap tersedia di `pseudocode.txt`
- UI menggunakan karakter ASCII: `-`, `|`, `+`, `=`
- Input buffer handling untuk menghindari bug input
- Clear screen per platform (Windows/Unix)

---

**© 2025 - Tugas Besar Struktur Data - Kelompok NGANTUK**
