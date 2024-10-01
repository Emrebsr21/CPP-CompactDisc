// Your solution may ONLY use functions from the following
// included C and C++ library header files.

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

// You may add your own helper functions or symbolic constants here.
// The member functions below must ALL be correctly coded

struct song {
    char title[121];
    int track;
    float time;
};

class CompactDisc {
      struct song *p;
      char artist[121];
      int total, current;
   public:
      CompactDisc();
      CompactDisc(int, const char *);
      int setSong(struct song, int);
      void getSong(struct song *);
      song& getSong(int);
      int operator+=(struct song);
      CompactDisc(const CompactDisc &);
      CompactDisc& operator=(const CompactDisc &);
      ~CompactDisc();
      int getTotal();
      int getCurrent();
      const char* getArtist();
};

void showSong(struct song);
void initSong(struct song *, const char *, int, float);

int main() {
   int i, status;
   char artists[3][41] = { "Styx", "Rush", "Tears For Fears" };
   char stringData[4][41] = { "Pieces Of Eight", "The Camera Eye", "Listen", "Everybody Wants To Rule The World" };
   struct song x1, x2, x3, x4, temp;

   initSong(&x1, stringData[0], 9, 4.44);
   initSong(&x2, stringData[1], 5, 10.58);
   initSong(&x3, stringData[2], 4, 6.48);
   initSong(&x4, stringData[3], 3, 4.10);

   cout << "initialized 4 song structures..." << endl;

   cout << "about to create CompactDiscs d1 and d2..." << endl;
   CompactDisc d1;                  // d1 can contain a total of 20 song structures
   CompactDisc d2(2, artists[2]);   // d2 can contain only 2 song structures
   cout << "created CompactDiscs d1 and d2..." << endl;

   cout << "checking d1.setSong(x3, 0)..." << endl;
   d1.setSong(x3, 0);
   cout << "checking d1.getSong(&temp)..." << endl;
   d1.getSong(&temp);     // temp should be set to: "Listen", 4, 6.48
   showSong(temp);

   cout << "attempting to overfill the d2 CompactDisc..." << endl;
   status = d2 += x1; // OK
   cout << "return from d2 += x1: " << status << endl;
   status = d2 += x2; // OK
   cout << "return from d2 += x2: " << status << endl;
   status = d2 += x3; // this should fail
   cout << "return from d2 += x3: " << status << endl;

   cout << "filling CompactDisc d1 with x1, x2, and x3..." << endl;
   d1 += x1;
   d1.getSong(&temp);     // temp should be set to: "Pieces Of Eight", 9, 4.44
   showSong(temp);

   d1 += x2;
   d1.getSong(&temp);     // temp should be set to: "The Camera Eye", 5, 10.58
   showSong(temp);

   d1 += x3;
   d1.getSong(&temp);     // temp should be set to: "Listen", 4, 6.48
   showSong(temp);

   d1.setSong(x4, 17);    // setting song[17] to: "Everybody Wants to Rule The World", 3, 4.10

   cout << endl << "displaying all songs in CompactDisc 1..." << endl << endl;
   for(i = 0; i < 20; i++) {
      cout << "index: " << i << " ";
      temp = d1.getSong(i);
      showSong(temp);
   }

   cout << endl << "displaying artist names..." << endl;
   cout << "CompactDisc d1 artist: " << d1.getArtist() << endl;
   cout << "CompactDisc d2 artist: " << d2.getArtist() << endl;

   return 0;
}

void showSong(struct song x) {
   cout << "song title: " << x.title << " track: " << x.track <<
      " time: " << x.time << endl;
}

void initSong(struct song *pp, const char *s, int trk, float tm) {
   strcpy(pp->title, s);
   pp->track = trk;
   pp->time = tm;
}

CompactDisc::CompactDisc() {
    total = 20;
    current = 0;
    p = new song[total];
    for(int i = 0; i < total; i++) {
        strcpy(p[i].title, "not-available");
        p[i].track = 0;
        p[i].time = 0;
    }
    strcpy(artist, "not-available");
}

CompactDisc::CompactDisc(int num, const char *name) {
    p = new song[num];
    for(int i = 0; i < num; i++) {
        strcpy(p[i].title, "not-available");
        p[i].track = 0;
        p[i].time = 0;
    }
    strcpy(artist, name);
}

int CompactDisc::setSong(struct song x, int index) {
    if(index < 0 || index >= total) {
        return false;
    }
    strcpy(p[index].title, x.title);
    p[index].track = x.track;
    p[index].time = x.time;
    return true;
}

void CompactDisc::getSong(struct song *ps) {
    if(current != 0) {
        *ps = p[current - 1];
    }
    else {
        strcpy(ps->title, "not-available");
        ps->track = 0;
        ps->time = 0;
    }
}

song& CompactDisc::getSong(int pos) {
    return p[pos];
}

int CompactDisc::operator+=(struct song copy) {
    if(current < total) {
        setSong(copy, current);
        current++;
        return 1;
    }
    else {
        return false;
    }
}

CompactDisc::CompactDisc(const CompactDisc &from) {
    total = from.total;
    current = from.current;
    p = new song[total];
    for(int i = 0; i < total; i++) {
        p[i] = from.p[i];
    }
    strcpy(artist, from.artist);
}

CompactDisc& CompactDisc::operator=(const CompactDisc &from) {
    if(this == &from) {
        return *this;
    }
    delete[] p;
    total = from.total;
    current = from.current;
    p = new song[total];
    for(int i = 0; i < total; i++) {
        p[i] = from.p[i];
    }
    strcpy(artist, from.artist);
    return *this;
}

CompactDisc::~CompactDisc() {
    delete[] p;
}

int CompactDisc::getTotal() {
    return total;
}

int CompactDisc::getCurrent() {
    return current;
}

const char* CompactDisc::getArtist() {
    return artist;
}
