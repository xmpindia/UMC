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

class SerializingSourcesTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE( SerializingSourcesTests );
		CPPUNIT_TEST( SerializingSources );
	CPPUNIT_TEST_SUITE_END();


protected:
	void SerializingSources();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SerializingSourcesTests );

#include "TestUtils.h"
#include "interfaces/IUMC.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IImageSource.h"
#include "interfaces/IVideoFrameSource.h"

void SerializingSourcesTests::setUp() {
	UMC_Initialize();
}

void SerializingSourcesTests::tearDown() {
	UMC_Terminate();
}

void SerializingSourcesTests::SerializingSources() {
	using namespace UMC;
	spIUMC umc = TestUtils::CreateDefaultUMC();
	auto sourceList = umc->GetAllSources();
	for ( size_t i = 0, total = sourceList.size(); i < total; ++i ) {
		std::string serializedSource = sourceList[i]->Serialize();
		//std::cout<< "******** Source # "<<i <<" ***********\n";
		//std::cout<<serializedSource;
		//std::cout<<"\n\n\n";
	}
}

