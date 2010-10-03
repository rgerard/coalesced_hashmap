// CoalescedHashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>

static const float m_percentrestrict = 0.86;

struct Bucket {
	bool used;
	char key;
	short indexOfNext;
	long value;
};

class CharacterMap {
private:
	int hash(char key);
	   
	Bucket *m_bucket;
	int m_actualsize;
	int m_restrictedsize;

	void init(int size);
	void resize(int newSize);
public:
	CharacterMap(int size);
    ~CharacterMap();

	bool contains(char key);
    bool put(char key, long value);
    bool get(char key, long &result);
    std::string toDebugString();
    int getSize();
};

#endif