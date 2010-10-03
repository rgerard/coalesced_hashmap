// This is the main DLL file.

#include "CoalescedHashMap.h"

CharacterMap::CharacterMap(int size) {
	bucket = new Bucket[size];
	m_size = size;
}

CharacterMap::~CharacterMap() {
	delete [] bucket;
}
 
bool CharacterMap::put(char key, long value) {
	int index = hash(key);
	
	if(contains(key)) {
		return false;	
	}

	// Create the new bucket and add it to the hashmap
	Bucket new_bucket;
	new_bucket.key = key;
	new_bucket.valueOrPointer = value;
	new_bucket.isPointer = false;
	bucket[index] = new_bucket;

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