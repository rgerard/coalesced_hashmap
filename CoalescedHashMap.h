// CoalescedHashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

static const float m_percentrestrict = 0.86;

struct Bucket {
       bool used;
       char key;
       long valueOrPointer;
	   Bucket *next;
};

class CharacterMap {
private:
       ~CharacterMap();
	   int hash(char key);
	   
	   Bucket *m_bucket;
	   int m_actualsize;
	   int m_restrictedsize;
public:
       CharacterMap(int size);
       bool contains(char key);
	   bool contains(char key, int index);
       bool put(char key, long value);
       bool get(char key, long &result);
       // void flush(); ??
};

#endif