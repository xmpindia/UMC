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
#include <stdexcept>
#include "TestUtils.h"

class AddingVideoFrameTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE(AddingVideoFrameTests);

	CPPUNIT_TEST(basicTest);
	CPPUNIT_TEST(NegativeTest);
	CPPUNIT_TEST(MultipleVideoFrameSourcesTest);
	CPPUNIT_TEST(RemoveSourcesTests);

	CPPUNIT_TEST_SUITE_END();


protected:
	void basicTest();
	void NegativeTest();
	void MultipleVideoFrameSourcesTest();
	void RemoveSourcesTests();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION(AddingVideoFrameTests);

using namespace UMC;
#include "interfaces/IUMC.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IVideoSource.h"
#include "interfaces/IVideoFrameSource.h"

void AddingVideoFrameTests::setUp()
{
	UMC_Initialize();
}

void AddingVideoFrameTests::tearDown()
{
	UMC_Terminate();
}

void AddingVideoFrameTests::basicTest()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIVideoSource videoS = sp->AddVideoSource();
	videoS->SetVideoEditRate((EditRate)48000);
	videoS->SetAudioEditRate((EditRate)56000);
	videoS->SetClipName("My Second Clip");
	videoS->SetDuration((EditUnitDuration)50);
	videoS->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k30Fps, "03:05:22:41");
	videoS->SetTimeCode(ts1);
	videoS->SetUniqueID("2");

	spIVideoFrameSource frVideo=sp->AddVideoFrameSource(videoS);
	frVideo->SetClipName("My ThirdClip");
	frVideo->SetInCount((EditUnitInCount)10);
	frVideo->SetUniqueID("3");

	CPPUNIT_ASSERT(videoS->GetVideoEditRate() == 48000);
	CPPUNIT_ASSERT(videoS->GetAudioEditRate() == 56000);
	CPPUNIT_ASSERT(strcmp(videoS->GetClipName().c_str(), "My Second Clip") == 0);
	CPPUNIT_ASSERT(videoS->GetDuration() == 50);
	CPPUNIT_ASSERT(videoS->GetInCount() == 15);
	CPPUNIT_ASSERT(videoS->GetNodeType() == IUMCNode::kNodeTypeSource);

	CPPUNIT_ASSERT(ts1.Hours() == 03);
	CPPUNIT_ASSERT(ts1.Minutes() == 05);
	CPPUNIT_ASSERT(ts1.Seconds() == 22);
	CPPUNIT_ASSERT(ts1.StandardFrameRate() == TimeCode::k30Fps);

	CPPUNIT_ASSERT(frVideo->GetVideoSource()==videoS);
	CPPUNIT_ASSERT(frVideo->GetInCount()==10);
	CPPUNIT_ASSERT(strcmp(frVideo->GetClipName().c_str(),"3")==0);

}

void AddingVideoFrameTests::NegativeTest()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIVideoSource videoS = sp->AddVideoSource();
	videoS->SetVideoEditRate((EditRate)48000);
	videoS->SetAudioEditRate((EditRate)56000);
	videoS->SetClipName("My Second Clip");
	videoS->SetDuration((EditUnitDuration)50);
	videoS->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k30Fps, "03:05:22:41");
	videoS->SetTimeCode(ts1);
	videoS->SetUniqueID("2");

	spIVideoFrameSource frVideo1 = sp->AddVideoFrameSource(videoS);
	frVideo1->SetInCount((EditUnitInCount)55);

	std::string buffer = sp->SerializeToBuffer();
}

void AddingVideoFrameTests::MultipleVideoFrameSourcesTest()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIVideoSource videoS1 = sp->AddVideoSource();
	videoS1->SetVideoEditRate((EditRate)48000);
	videoS1->SetClipName("My First Clip");
	videoS1->SetDuration((EditUnitDuration)25);
	videoS1->SetInCount((EditUnitInCount)5);
	TimeCode ts(TimeCode::k23_976Fps, "02:04:12:21");
	videoS1->SetTimeCode(ts);
	videoS1->SetUniqueID("1");

	spIVideoSource VideoS2 = sp->AddVideoSource();
	VideoS2->SetVideoEditRate((EditRate)56000);
	VideoS2->SetClipName("My Second Clip");
	VideoS2->SetDuration((EditUnitDuration)12);
	VideoS2->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k23_976Fps, "02:04:12:21");
	VideoS2->SetTimeCode(ts1);
	VideoS2->SetUniqueID("8");


	spIVideoFrameSource frVideo1 = sp->AddVideoFrameSource(videoS1);
	frVideo1->SetClipName("1st frame");
	frVideo1->SetInCount(10);
	frVideo1->SetUniqueID("2");

	spIVideoFrameSource frVideo2 = sp->AddVideoFrameSource(videoS1);
	frVideo2->SetClipName("2nd frame");
	frVideo2->SetInCount(20);
	frVideo2->SetUniqueID("4");

	sp->AddVideoFrameSource(videoS1);

	sp->AddVideoFrameSource(VideoS2);
	sp->AddVideoFrameSource(VideoS2);
	sp->AddVideoFrameSource(videoS1);


	std::string buffer = sp->SerializeToBuffer();

	auto VframeSources=sp->GetAllVideoFrameSources();
	CPPUNIT_ASSERT(strcmp(VframeSources[0]->GetUniqueID().c_str(), "2") == 0);
	CPPUNIT_ASSERT(VframeSources[0]->GetInCount()==10);
	CPPUNIT_ASSERT(strcmp(VframeSources[0]->GetClipName().c_str(), "1st frame") == 0);

	CPPUNIT_ASSERT(strcmp(VframeSources[1]->GetUniqueID().c_str(), "4") == 0);
	CPPUNIT_ASSERT(VframeSources[1]->GetInCount()==20);
	CPPUNIT_ASSERT(strcmp(VframeSources[1]->GetClipName().c_str(), "2nd frame") == 0);

	CPPUNIT_ASSERT(strcmp(VframeSources[2]->GetUniqueID().c_str(), "5") == 0);
	CPPUNIT_ASSERT(strcmp(VframeSources[3]->GetUniqueID().c_str(), "6") == 0);
	CPPUNIT_ASSERT(strcmp(VframeSources[4]->GetUniqueID().c_str(), "7") == 0);
	CPPUNIT_ASSERT(strcmp(VframeSources[5]->GetUniqueID().c_str(), "9") == 0);
}


void AddingVideoFrameTests::RemoveSourcesTests()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIVideoSource videoS1 = sp->AddVideoSource();
	videoS1->SetVideoEditRate((EditRate)48000);
	videoS1->SetClipName("My First Clip");
	videoS1->SetDuration((EditUnitDuration)25);
	videoS1->SetInCount((EditUnitInCount)5);
	TimeCode ts(TimeCode::k23_976Fps, "02:04:12:21");
	videoS1->SetTimeCode(ts);
	videoS1->SetUniqueID("1");

	spIVideoSource VideoS2 = sp->AddVideoSource();
	VideoS2->SetVideoEditRate((EditRate)56000);
	VideoS2->SetClipName("My Second Clip");
	VideoS2->SetDuration((EditUnitDuration)12);
	VideoS2->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k23_976Fps, "02:04:12:21");
	VideoS2->SetTimeCode(ts1);
	VideoS2->SetUniqueID("2");

	spIVideoFrameSource frVideo1 = sp->AddVideoFrameSource(videoS1);
	spIVideoFrameSource frVideo2 = sp->AddVideoFrameSource(videoS1);
	spIVideoFrameSource frVideo3 = sp->AddVideoFrameSource(videoS1);
	auto frVideo4 = sp->AddVideoFrameSource(VideoS2);

	int count = sp->RemoveAllVideoFramesSources();
	CPPUNIT_ASSERT(count == 4);

	bool result1 = sp->RemoveVideoFrameSource("5");
	CPPUNIT_ASSERT(result1==false);

	result1 = sp->RemoveVideoFrameSource("String");
	CPPUNIT_ASSERT(result1 == false);

	sp->AddVideoFrameSource(videoS1);
	sp->AddVideoFrameSource(VideoS2);
	result1 = sp->RemoveVideoFrameSource("5");
	CPPUNIT_ASSERT(result1 == true);

}
