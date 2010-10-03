// This is the main DLL file.

#include "CoalescedHashMap.h"

CharacterMap::CharacterMap(int size) {
	bucket = new Bucket[size];
	m_size = size;
	for (int i = 0; i < size; i++) {
		bucket[i].used = false;
	}
}

CharacterMap::~CharacterMap() {
	delete [] bucket;
}
 
bool CharacterMap::put(char key, long value) {
	int index = hash(key);
	
	if(contains(key)) {
		return false;	
	}

	bucket[index].key = key;
	bucket[index].valueOrPointer = value;
	bucket[index].used = true;

	return true;
}

bool CharacterMap::get(char key, long &result) {
	int index = hash(key);

	if(!contains(key, index)) {
		result = 0;
		return false;
	} else {
		result = bucket[index].valueOrPointer;
		return true;
	}
}

bool CharacterMap::contains(char key) {
	int index = hash(key);
	return contains(key, index);
}

bool CharacterMap::contains(char key, int index) {
	if(index >= m_size) {
		return false;
	}

	// Check to see if the keys match
	if(bucket[index].key == key) {
		return true;
	} else {
		return false;
	}
}

int CharacterMap::hash(char key) {
	return key % m_size;
}