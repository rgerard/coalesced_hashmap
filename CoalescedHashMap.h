// CoalescedHashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <iostream>

static const float m_percentrestrict = 0.86;

struct Bucket {
       bool used;
       char key;
       long value;
	   short indexOfNext;
};

class CharacterMap {
private:
	   int hash(char key);
	   void init(int size);
	   void resize(int newSize);
	   
	   // File I/O
	   bool readfile();
	   int readfilecount();

	   Bucket *m_bucket;
	   int m_actualsize;
	   int m_restrictedsize;
	   FILE *m_filepointer;
public:
	   CharacterMap(int size);
       CharacterMap(FILE *filepointer);
       ~CharacterMap();

       bool contains(char key);
	   bool contains(char key, int index);
       bool put(char key, long value);
       bool get(char key, long &result);
       std::string toDebugString();
       int getSize();
	   bool flush(FILE *filepointer);
};

#endif