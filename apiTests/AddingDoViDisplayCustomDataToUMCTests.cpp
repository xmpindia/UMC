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

class AddingDoViDisplayCustomDataToUMC : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( AddingDoViDisplayCustomDataToUMC );
		CPPUNIT_TEST( SetCustomDataTest );
		CPPUNIT_TEST( GetCustomDataTest );
	CPPUNIT_TEST_SUITE_END();


protected:
	void SetCustomDataTest();
	void GetCustomDataTest();

public:
	virtual void setUp();
	virtual void tearDown();
};

CPPUNIT_TEST_SUITE_REGISTRATION( AddingDoViDisplayCustomDataToUMC );

#include "interfaces/IUMC.h"
#include "DoViDisplayHandler.h"

void AddingDoViDisplayCustomDataToUMC::setUp() {
	UMC_Initialize();
	UMC::IUMC::RegisterCustomNodeHandler( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(),
		std::make_shared< DoVi::DisplayHandler >() );
}

void AddingDoViDisplayCustomDataToUMC::SetCustomDataTest() {
	auto umc = UMC::IUMC::CreateEmptyUMC();
	std::shared_ptr< DoVi::Display > display = std::make_shared< DoVi::Display >();
	display->setID( "id-1");
	display->setName( "reference display - 1" );
	display->setDiagonalSize( 52.0 );
	umc->SetCustomData( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName(), display );

	auto rdfRep = umc->SerializeToBuffer();

	auto um1 = UMC::IUMC::CreateUMCFromBuffer( rdfRep );
	std::shared_ptr< DoVi::Display >parsedDisplay =  std::dynamic_pointer_cast< DoVi::Display >(
		um1->GetCustomData( DoVi::Display::GetNameSpace(), DoVi::Display::GetPropertyName() ) );

	//std::cout<<" ******* AddingDoViDisplayCustomDataToUMC::Test *****\n";
	//std::cout<<rdfRep<<"\n\n\n\n\n";
}

void AddingDoViDisplayCustomDataToUMC::tearDown() {
	UMC_Terminate();
}

void AddingDoViDisplayCustomDataToUMC::GetCustomDataTest() {
	
}

