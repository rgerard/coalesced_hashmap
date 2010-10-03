/*
 *  CoalescedHashMapTest.cpp
 *  charmap
 */

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <string>
#include "CoalescedHashMap.h"

class CoalescedHashMapTest : public CppUnit::TestFixture  {
	
	CPPUNIT_TEST_SUITE( CoalescedHashMapTest );
	
	CPPUNIT_TEST( testBasic );
	CPPUNIT_TEST( testOverwrite );
	CPPUNIT_TEST( testMany );
	CPPUNIT_TEST( testFlush );
	CPPUNIT_TEST( testCollision );
	CPPUNIT_TEST( testNullChar );
	CPPUNIT_TEST( testOverflow );
	CPPUNIT_TEST( testAllCharacters );
	
	CPPUNIT_TEST_SUITE_END();
	
private:
	CharacterMap* map;

	void assertValue(char key, long expectedValue) {
		std::ostringstream os;
			os << "Value for '" << key << "' should be " << expectedValue;
			std::string message(os.str());

		long result;

		CPPUNIT_ASSERT_MESSAGE(message, map->contains(key));
		CPPUNIT_ASSERT_MESSAGE(message, map->get(key, result));
		CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expectedValue, result);
  	}

public:
	void setUp() {
		map = new CharacterMap(10);
	}
	
	void tearDown() {
		delete map;
	}
	
	void testBasic() {
		CPPUNIT_ASSERT(!map->contains('a'));
		map->put('a', 100);
		assertValue('a', 100);
	}

	void testOverwrite() {
		map->put('a', 100);
		assertValue('a', 100);

		map->put('a', 200);
		assertValue('a', 200);

		map->put('a', 0);
		assertValue('a', 0);
	}

	void testMany() {
		map->put('a', 100);
		map->put('b', 200);
		map->put('c', 300);
		map->put('d', 400);

		assertValue('a', 100);
		assertValue('b', 200);
		assertValue('c', 300);
		assertValue('d', 400);
	}

	void testFlush() {
		testMany();
		
		FILE *fp = fopen("C:\\test.bin", "wb");
		CPPUNIT_ASSERT(map->flush(fp));
		fclose(fp);

		fp = fopen("C:\\test.bin", "r+b");
		delete map;
		map = new CharacterMap(10, fp);

		assertValue('a', 100);
		assertValue('b', 200);
		assertValue('c', 300);
		assertValue('d', 400);

		fclose(fp);
	}

	void testCollision() {
		int increment = 10 * m_percentrestrict;

		for (int i = 0; i < 5; i++) {
			map->put('a' + increment * i, i * 100);
		}

		for (int i = 0; i < 5; i++) {
			assertValue('a' + increment * i, i * 100);
		}
	}

	void testNullChar() {
		map->put(0, 1000);
		assertValue(0, 1000);
	}

	void testOverflow() {
		for (int i = 0; i < 10; i++) {
			map->put('a' + i, i);
		}
		map->put('z', 100);
		CPPUNIT_ASSERT(map->getSize() >= 11);

		for (int i = 0; i < 10; i++) {
			assertValue('a' + i, i);
		}
		assertValue('z', 100);
	}

	void testAllCharacters() {
		for (int i = 0; i < 255; i++) {
			map->put(i, i + 100);
		}

		for (int i = 0; i < 255; i++) {
			assertValue(i, i + 100);
		}

		CPPUNIT_ASSERT_EQUAL(256, map->getSize());

		for (int i = 0; i < 255; i++) {
			map->put(i, i + 200);
		}

		for (int i = 0; i < 255; i++) {
			assertValue(i, i + 200);
		}
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( CoalescedHashMapTest );