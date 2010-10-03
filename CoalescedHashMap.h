// CoalescedHashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

struct Bucket {
       bool used;
       char key;
       long valueOrPointer;
};

class CharacterMap {
private:
	   int hash(char key);
	   Bucket *bucket;
	   int m_size;
public:
       CharacterMap(int size);
       ~CharacterMap();       
       bool contains(char key);
	   bool contains(char key, int index);
       bool put(char key, long value);
       bool get(char key, long &result);
       // void flush(); ??
};

#endif