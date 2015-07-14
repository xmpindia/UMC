// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2015 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================


#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

class AddingCustomDataNamespaceTests : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( AddingCustomDataNamespaceTests );
		CPPUNIT_TEST( SetCustomDataTest1 );
		CPPUNIT_TEST( SetCustomDataTest2 );
	CPPUNIT_TEST_SUITE_END();


protected:
	void SetCustomDataTest1();
	void SetCustomDataTest2();

public:
	virtual void setUp();
	virtual void tearDown();
};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingCustomDataNamespaceTests );

#include "interfaces/IUMC.h"
#include "DoViDisplayHandler.h"

void AddingCustomDataNamespaceTests::setUp() {

}

void AddingCustomDataNamespaceTests::tearDown() {
	
}

void AddingCustomDataNamespaceTests::SetCustomDataTest1() {
	int count = 1103;
	for(int i=1; i<=count; i++)
	{
		UMC_Initialize();
		UMC::IUMC::RegisterCustomNodeHandler( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(),
			std::make_shared< DoVi::DisplayHandler >() );

		auto umc = UMC::IUMC::CreateEmptyUMC();
		std::shared_ptr< DoVi::Display > display = std::make_shared< DoVi::Display >();
		display->setID( "id-1");
		display->setName( "reference display - 1" );
		display->setDiagonalSize( 52.0 );
		umc->SetCustomData( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(), display );

		if ( i==count )
		{
			auto rdfRep = umc->SerializeToBuffer();
			std::cout<<" ******* AddingCustomDataNamespaceTests::SetCustomDataTest1 *****\n";
			std::cout << rdfRep << std::endl;
		}

		UMC_Terminate();
	}
}



void AddingCustomDataNamespaceTests::SetCustomDataTest2() {
	UMC_Initialize();
	UMC::IUMC::RegisterCustomNodeHandler( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(),
		std::make_shared< DoVi::DisplayHandler >() );

	int count = 1103;
	for(int i=1; i<=count; i++)
	{
		auto umc = UMC::IUMC::CreateEmptyUMC();
		std::shared_ptr< DoVi::Display > display = std::make_shared< DoVi::Display >();
		display->setID( "id-1");
		display->setName( "reference display - 1" );
		display->setDiagonalSize( 52.0 );
		umc->SetCustomData( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(), display );

		if ( i==count )
		{
			auto rdfRep = umc->SerializeToBuffer();
			std::cout<<" ******* AddingCustomDataNamespaceTests::SetCustomDataTest2 *****\n";
			std::cout << rdfRep << std::endl;
		}
	}

	UMC_Terminate();
}

