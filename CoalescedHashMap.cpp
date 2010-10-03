// This is the main DLL file.

#include "CoalescedHashMap.h"
#include <algorithm>
#include <sstream>


CharacterMap::CharacterMap(int size) {
	init(size);
}


void CharacterMap::init(int size) {
	m_bucket = new Bucket[size];

	m_actualsize = size;
	m_restrictedsize = (size * m_percentrestrict);

	for (int i = 0; i < size; i++) {
		m_bucket[i].used = false;
		m_bucket[i].indexOfNext = -1;
	}
}

CharacterMap::~CharacterMap() {
	delete [] m_bucket;
}
 
void CharacterMap::put(char key, long value) {
	int index = hash(key);
	
	// If the location is null, insert a new bucket to hashmap
	if(m_bucket[index].used == false || m_bucket[index].key == key) {
		m_bucket[index].key = key;
		m_bucket[index].value = value;
		m_bucket[index].used = true;
		return;
	}

	// Find the right location in the cellar for this new value, starting at (tablesize - 1)
	int cursor = m_actualsize - 1;
	while ( cursor >= 0 && m_bucket[cursor].used && m_bucket[cursor].key != key) {
		--cursor;
    }

	if ( cursor == -1 ) {
		// Table is full: re-size and try again.
		resize(std::max(m_actualsize * 2, 256));
		put(key, value);
		return;
    }

	// Insert new bucket at the cursor location
	m_bucket[cursor].key = key;
	m_bucket[cursor].value = value;
	m_bucket[cursor].used = true;

	// Point the colliding node to this new node
	while ( m_bucket[index].indexOfNext != -1 ) {
		index = m_bucket[index].indexOfNext;
    }

    m_bucket[index].indexOfNext = cursor;
}

bool CharacterMap::get(char key, long &result) {
	int index = hash(key);

	if (!m_bucket[index].used) {
		return false;
	}

	while (index != -1 && m_bucket[index].key != key) {
		index = m_bucket[index].indexOfNext;
	}

	if (index == -1) {
		return false;
	}

	result = m_bucket[index].value;
	return true;
}

bool CharacterMap::contains(char key) {
	long ignoredResult;
	return get(key, ignoredResult);
}

int CharacterMap::hash(char key) {
	return key % m_restrictedsize;
}

std::string CharacterMap::toDebugString() {
	std::ostringstream os;
	for (int i = 0; i < m_actualsize; i++) {
		Bucket bucket = m_bucket[i];
		os << i << ": ";
		if (bucket.used) {
			os << bucket.key << " " << bucket.value << " -> " << bucket.indexOfNext;
		} else {
			os << "empty ";
		}
		os << std::endl;
	}

	std::string message(os.str());
	return message;
}

void CharacterMap::resize(int newSize) {
	int oldSize = m_actualsize;
	Bucket *oldItems = m_bucket;

	init(newSize);

	for (int i = 0; i < oldSize; i++) {
		Bucket item = oldItems[i];
		if (item.used) {
			put(item.key, item.value);
		}
	}

	delete [] oldItems;
}

int CharacterMap::getSize() {
	return m_actualsize;
}
