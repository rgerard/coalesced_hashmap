// CoalescedHashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

struct Bucket {
       char key;
       bool isPointer;
       long valueOrPointer;
};

class CharacterMap {
private:
       ~CharacterMap();
	   int hash(char key);
	   Bucket *bucket;
	   int m_size;
public:
       CharacterMap(int size);
       bool contains(char key);
	   bool contains(char key, int index);
       bool put(char key, long value);
       bool get(char key, long &result);
       // void flush(); ??
};

#endif