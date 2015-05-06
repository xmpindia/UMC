#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

#include "implHeaders/UniqueIDAndReferenceTrackerImpl.h"

class UniqueIDAndReferenceTrackerTests : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( UniqueIDAndReferenceTrackerTests );
		CPPUNIT_TEST( AddingRemovingIDs );
		CPPUNIT_TEST( AddingRemovingReferences );
	CPPUNIT_TEST_SUITE_END();

protected:
	void AddingRemovingIDs();
	void AddingRemovingReferences();
};

void UniqueIDAndReferenceTrackerTests::AddingRemovingIDs() {
	// add couple of ids
	using namespace INT_UMC;
	UniqueIDAndReferenceTrackerImpl obj;
	CPPUNIT_ASSERT_EQUAL( obj.AddUniqueID( "1" ), true );

	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "2" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), kMaxsize_t );

	CPPUNIT_ASSERT_EQUAL( obj.AddUniqueID( "2" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "2" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), ( size_t ) 0 );


	// try to add an existing uniqueID should return false and reference count should be preserved
	CPPUNIT_ASSERT_EQUAL( obj.AddReference( "1" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.AddUniqueID( "1" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 1 );

	// try removing non existent ID
	CPPUNIT_ASSERT_EQUAL( obj.RemoveUniqueID( "3" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "3" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "3" ), kMaxsize_t );

	// remove all ids one by one, reference count does not matter
	CPPUNIT_ASSERT_EQUAL( obj.RemoveUniqueID( "2" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "2" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.RemoveUniqueID( "2" ), false );

	CPPUNIT_ASSERT_EQUAL( obj.RemoveUniqueID( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "1" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.RemoveUniqueID( "1" ), false );

}

void UniqueIDAndReferenceTrackerTests::AddingRemovingReferences() {
	using namespace INT_UMC;
	UniqueIDAndReferenceTrackerImpl obj;

	// Non existing id
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.AddReference( "1" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.RemoveReference( "1" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.IsUniqueIDPresent( "1" ), false );

	// existing id
	CPPUNIT_ASSERT_EQUAL( obj.AddUniqueID( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.AddUniqueID( "2" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "2" ), false );

	CPPUNIT_ASSERT_EQUAL( obj.AddReference( "2" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "2" ), true );

	CPPUNIT_ASSERT_EQUAL( obj.AddReference( "1" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.AddReference( "1" ), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "1" ), ( size_t ) 2 );
	CPPUNIT_ASSERT_EQUAL( obj.GetReferenceCount( "2" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "2" ), true );

	// remove references one by one
	CPPUNIT_ASSERT_EQUAL( obj.RemoveReference( "1" ), ( size_t ) 1 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), true );
	CPPUNIT_ASSERT_EQUAL( obj.RemoveReference( "2" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "2" ), false );
	CPPUNIT_ASSERT_EQUAL( obj.RemoveReference( "1" ), ( size_t ) 0 );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), false );

	// remove references after 0
	CPPUNIT_ASSERT_EQUAL( obj.RemoveReference( "1" ), kMaxsize_t );
	CPPUNIT_ASSERT_EQUAL( obj.IsReferenced( "1" ), false );
}

CPPUNIT_TEST_SUITE_REGISTRATION( UniqueIDAndReferenceTrackerTests );
