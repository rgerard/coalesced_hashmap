/*
 *  CoalescedHashMapTest.cpp
 *  charmap
 */

#include <cppunit/extensions/HelperMacros.h>
#include "CoalescedHashMap.h"

class CoalescedHashMapTest : public CppUnit::TestFixture  {
	
	CPPUNIT_TEST_SUITE( CoalescedHashMapTest );
	
	CPPUNIT_TEST( testBasic );
	CPPUNIT_TEST( testOverwrite );
	CPPUNIT_TEST( testMany );
	
	CPPUNIT_TEST_SUITE_END();
	
private:
  CharacterMap* map;

  void assertValue(char key, long expectedValue) {
  	long result;
  	CPPUNIT_ASSERT(map->contains(key));
		CPPUNIT_ASSERT(map->get(key, result));
		CPPUNIT_ASSERT_EQUAL(expectedValue, result);
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
		CPPUNIT_ASSERT(map->contains('a'));

		long result;
		CPPUNIT_ASSERT(map->get('a', result));
		CPPUNIT_ASSERT_EQUAL(100L, result);
	}

	void testOverwrite() {
		map->put('a', 100);
		assertValue('a', 100);

		map->put('a', 200);
		assertValue('a', 200);
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
};


CPPUNIT_TEST_SUITE_REGISTRATION( CoalescedHashMapTest );