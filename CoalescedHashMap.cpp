// This is the main DLL file.

#include "CoalescedHashMap.h"
#include <stdlib.h>

CharacterMap::CharacterMap(int size) {
	m_bucket = new Bucket[size];

	m_actualsize = size;
	m_restrictedsize = (size * m_percentrestrict);

	for (int i = 0; i < size; i++) {
		m_bucket[i].used = false;
	}
}

CharacterMap::~CharacterMap() {
	delete [] m_bucket;
}
 
bool CharacterMap::put(char key, long value) {
	int index = hash(key);
	
	// If the location is null, insert a new bucket to hashmap
	if(m_bucket[index].used == false) {
		Bucket new_bucket;
		new_bucket.key = key;
		new_bucket.valueOrPointer = value;
		new_bucket.used = true;
		m_bucket[index] = new_bucket;
		return true;
	}

	// Find the right location in the cellar for this new value, starting at (tablesize - 1)
	int cursor = m_actualsize = 1;
	while ( cursor >= 0 && m_bucket[cursor].used == false )
      --cursor;

	// Table is full, so return failure
	if ( cursor == -1 )
      return false;

	// Insert new bucket at the cursor location
	Bucket new_bucket;
	new_bucket.key = key;
	new_bucket.valueOrPointer = value;
	new_bucket.used = true;
	m_bucket[cursor] = new_bucket;

	// Point the colliding node to this new node
	Bucket it = m_bucket[index];
 
	while ( it.next != NULL && it.used == true )
      it = *(it.next);

	it.next = &(m_bucket[cursor]);

	return true;
}

bool CharacterMap::get(char key, long &result) {
	int index = hash(key);

	if(!contains(key, index)) {
		result = 0;
		return false;
	} else {
		result = m_bucket[index].valueOrPointer;
		return true;
	}
}

bool CharacterMap::contains(char key) {
	int index = hash(key);
	return contains(key, index);
}

bool CharacterMap::contains(char key, int index) {
	if(index >= m_restrictedsize) {
		return false;
	}

	// Check to see if the keys match
	if(m_bucket[index].key == key) {
		return true;
	} else {
		return false;
	}
}

int CharacterMap::hash(char key) {
	return key % m_restrictedsize;
}