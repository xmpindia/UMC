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
#include <string.h>

class AddingAudioVideoSourceTests : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE(AddingAudioVideoSourceTests);

	CPPUNIT_TEST(basicTest);
	CPPUNIT_TEST(NegativeTest);
	CPPUNIT_TEST(MultipleAudioSourcesTest);
	CPPUNIT_TEST(MultipleVideoSourcesTest);
	CPPUNIT_TEST(UniqueIdTests);
	CPPUNIT_TEST(RemoveSourcesTests);

	CPPUNIT_TEST_SUITE_END();


protected:
	void basicTest();
	void NegativeTest();
	void MultipleAudioSourcesTest();
	void MultipleVideoSourcesTest();
	void UniqueIdTests();
	void RemoveSourcesTests();

public:
	virtual void setUp();
	virtual void tearDown();

};

CPPUNIT_TEST_SUITE_REGISTRATION(AddingAudioVideoSourceTests);

using namespace UMC;
#include "interfaces/IUMC.h"
#include "interfaces/IAudioSource.h"
#include "interfaces/IVideoSource.h"


void AddingAudioVideoSourceTests::setUp() 
{
	UMC_Initialize();
}

void AddingAudioVideoSourceTests::tearDown() 
{
	UMC_Terminate();
}

void AddingAudioVideoSourceTests::basicTest() 
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIAudioSource audioS = sp->AddAudioSource();
	audioS->SetAudioEditRate((EditRate)48000);
	audioS->SetClipName("My First Clip");
	audioS->SetDuration((EditUnitDuration)25);
	audioS->SetInCount((EditUnitInCount)5);
	TimeCode ts(TimeCode::k23_976Fps, "02:04:12:21");
	audioS->SetTimeCode(ts);
	audioS->SetUniqueID("1");
	
	spIVideoSource videoS = sp->AddVideoSource();
	videoS->SetVideoEditRate((EditRate)48000);
	videoS->SetAudioEditRate((EditRate)56000);
	videoS->SetClipName("My Second Clip");
	videoS->SetDuration((EditUnitDuration)50);
	videoS->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k30Fps, "03:05:22:41");
	videoS->SetTimeCode(ts1);
	videoS->SetUniqueID("2");
	
	CPPUNIT_ASSERT(audioS->GetAudioEditRate()==48000);
	CPPUNIT_ASSERT(strcmp(audioS->GetClipName().c_str(),"My First Clip")==0);
	CPPUNIT_ASSERT(audioS->GetDuration()==25);
	CPPUNIT_ASSERT(audioS->GetInCount() == 5);;
	CPPUNIT_ASSERT(audioS->GetNodeType() == IUMCNode::kNodeTypeSource);

	CPPUNIT_ASSERT(ts.Hours()==2);
	CPPUNIT_ASSERT(ts.Minutes() == 04);
	CPPUNIT_ASSERT(ts.Seconds() == 12);
	CPPUNIT_ASSERT(ts.StandardFrameRate()== TimeCode::k23_976Fps);	

	
	CPPUNIT_ASSERT(videoS->GetVideoEditRate() == 48000);
	CPPUNIT_ASSERT(videoS->GetAudioEditRate() == 56000);
	CPPUNIT_ASSERT(strcmp(videoS->GetClipName().c_str(), "My Second Clip") == 0);
	CPPUNIT_ASSERT(videoS->GetDuration() ==50);
	CPPUNIT_ASSERT(videoS->GetInCount() == 15);
	CPPUNIT_ASSERT(videoS->GetNodeType() == IUMCNode::kNodeTypeSource);

	CPPUNIT_ASSERT(ts1.Hours() == 03);
	CPPUNIT_ASSERT(ts1.Minutes() == 05);
	CPPUNIT_ASSERT(ts1.Seconds() == 22);
	CPPUNIT_ASSERT(ts1.StandardFrameRate() == TimeCode::k30Fps);
	
//	printf("DONE\n");
}

void AddingAudioVideoSourceTests::NegativeTest()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	// NULL ClipName
	spIAudioSource audioS1 = sp->AddAudioSource();
//	audioS1->SetClipName(NULL);
	audioS1->SetInCount((EditUnitInCount)-5);

	spIVideoSource videoS1 = sp->AddVideoSource();
	videoS1->SetClipName("");
	videoS1->SetInCount((EditUnitInCount)-10);

	spIAudioSource audioS2 = sp->AddAudioSource();
	audioS2->SetDuration((EditUnitDuration)10);
	audioS2->SetInCount((EditUnitInCount)20);

	spIVideoSource videoS2 = sp->AddVideoSource();
	videoS2->SetDuration((EditUnitDuration)20);
	videoS2->SetInCount((EditUnitInCount)30);

	std::string buffer=sp->SerializeToBuffer();
//	printf("DONE\n");
}

void AddingAudioVideoSourceTests::MultipleAudioSourcesTest()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	spIAudioSource audioS1 = sp->AddAudioSource();
	audioS1->SetAudioEditRate((EditRate)48000);
	audioS1->SetClipName("My First Clip");
	audioS1->SetDuration((EditUnitDuration)25);
	audioS1->SetInCount((EditUnitInCount)5);
	TimeCode ts(TimeCode::k23_976Fps, "02:04:12:21");
	audioS1->SetTimeCode(ts);
	audioS1->SetUniqueID("1");

	spIAudioSource audioS2 = sp->AddAudioSource();
	audioS2->SetAudioEditRate((EditRate)56000);
	audioS2->SetClipName("My Second Clip");
	audioS2->SetDuration((EditUnitDuration)12);
	audioS2->SetInCount((EditUnitInCount)15);
	TimeCode ts1(TimeCode::k23_976Fps, "02:04:12:21");
	audioS2->SetTimeCode(ts1);
	audioS2->SetUniqueID("2");

	spIAudioSource audioS3 = sp->AddAudioSource();

	std::string buffer = sp->SerializeToBuffer();

	auto audioSources = sp->GetAllAudioSources();
	CPPUNIT_ASSERT(audioSources[0]->GetAudioEditRate() == 48000);
	CPPUNIT_ASSERT(audioSources[0]->GetDuration() == 25);
	CPPUNIT_ASSERT(audioSources[0]->GetInCount() == 5);
	CPPUNIT_ASSERT(audioSources[0]->GetTimeCode() == ts);
	CPPUNIT_ASSERT(audioSources[0]->GetUniqueID() == "1");

	CPPUNIT_ASSERT(audioSources[1]->GetAudioEditRate() == 56000);
	CPPUNIT_ASSERT(audioSources[1]->GetDuration() == 12);
	CPPUNIT_ASSERT(audioSources[1]->GetInCount() == 15);
	CPPUNIT_ASSERT(audioSources[1]->GetTimeCode() == ts1);
	CPPUNIT_ASSERT(audioSources[1]->GetUniqueID() == "2");

	CPPUNIT_ASSERT(audioSources[2]->GetUniqueID() == "3");

	printf("PASS");

	auto audioS4=sp->AddAudioSource();
	bool resultUid1=audioS4->SetUniqueID("String");
	

	auto audioS5 = sp->AddAudioSource();
	bool resultuID2=audioS5->SetUniqueID("");
	CPPUNIT_ASSERT(resultuID2 == false);

	sp->AddAudioSource();
	buffer = sp->SerializeToBuffer();

//	printf("DONE\n");
}

void AddingAudioVideoSourceTests::MultipleVideoSourcesTest()
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

	spIVideoSource VideoS3 = sp->AddVideoSource();

	std::string buffer = sp->SerializeToBuffer();

	auto VideoSources = sp->GetAllVideoSources();
	CPPUNIT_ASSERT(VideoSources[0]->GetVideoEditRate() == 48000);
	CPPUNIT_ASSERT(VideoSources[0]->GetDuration() == 25);
	CPPUNIT_ASSERT(VideoSources[0]->GetInCount() == 5);
	CPPUNIT_ASSERT(VideoSources[0]->GetTimeCode() == ts);
	CPPUNIT_ASSERT(VideoSources[0]->GetUniqueID() == "1");

	CPPUNIT_ASSERT(VideoSources[1]->GetVideoEditRate() == 56000);
	CPPUNIT_ASSERT(VideoSources[1]->GetDuration() == 12);
	CPPUNIT_ASSERT(VideoSources[1]->GetInCount() == 15);
	CPPUNIT_ASSERT(VideoSources[1]->GetTimeCode() == ts1);
	CPPUNIT_ASSERT(VideoSources[1]->GetUniqueID() == "2");

	CPPUNIT_ASSERT(VideoSources[2]->GetUniqueID() == "3");

	printf("PASS");

	auto VideoS4 = sp->AddVideoSource();
	bool resultUid1 = VideoS4->SetUniqueID("String");


	auto VideoS5 = sp->AddVideoSource();
	bool resultuID2 = VideoS5->SetUniqueID("");
	CPPUNIT_ASSERT(resultuID2 == false);

	sp->AddVideoSource();
	buffer = sp->SerializeToBuffer();
//	printf("DONE\n");
}

void AddingAudioVideoSourceTests::UniqueIdTests()
{
	spIUMC sp = IUMC::CreateEmptyUMC();

	// Assigning a string id
 	auto audioS4 = sp->AddAudioSource();
	bool resultUid1 = audioS4->SetUniqueID("String");
	std::cout << audioS4->GetUniqueID();
	CPPUNIT_ASSERT(resultUid1 == true); 

	std::string buffer = sp->SerializeToBuffer();

	// Assigning a empty string as id
	auto audioS5 = sp->AddAudioSource();
	bool resultuID2 = audioS5->SetUniqueID("");
	CPPUNIT_ASSERT(resultuID2 == false);

	//Different permutation of already set unique id
	auto audioS8 = sp->AddAudioSource();
	resultUid1 = audioS8->SetUniqueID("Srting");
	CPPUNIT_ASSERT(resultUid1 == true);

	// Assigning already set unique id
	auto audioS9 = sp->AddAudioSource();
	resultUid1 = audioS9->SetUniqueID("String");
	CPPUNIT_ASSERT(resultUid1 == false);

	// Assigning uppercase form of already set unique id
	auto audioS10 = sp->AddAudioSource();
	resultUid1 = audioS10->SetUniqueID("STRING");
	CPPUNIT_ASSERT(resultUid1 == true);

	// Assigning null character as id
	auto audioS6 = sp->AddAudioSource();
	bool resultuID3 = audioS6->SetUniqueID("\0");
	CPPUNIT_ASSERT(resultuID3 == false);

	// Checking for duplicate id
	auto audioS7 = sp->AddAudioSource();
	bool resultuID4 = audioS7->SetUniqueID("1");
	CPPUNIT_ASSERT(resultuID4 == true);

	sp->AddAudioSource();
	
	CPPUNIT_ASSERT(strcmp(audioS5->GetUniqueID().c_str(), "2") == 0);
	CPPUNIT_ASSERT(strcmp(audioS6->GetUniqueID().c_str(), "6") == 0);

	 buffer = sp->SerializeToBuffer();
//	 printf("DONE\n");
}

void AddingAudioVideoSourceTests::RemoveSourcesTests()
{
	spIUMC sp = IUMC::CreateEmptyUMC();
	sp->AddAudioSource();
	sp->AddAudioSource();
	sp->AddAudioSource();
	sp->AddAudioSource();
	sp->AddVideoSource();
	sp->AddVideoSource();

	int count=sp->RemoveAllAudioSources();
	CPPUNIT_ASSERT(count == 4);

	count = sp->RemoveAllVideoSources();
	CPPUNIT_ASSERT(count == 2);

	sp->AddAudioSource();
	sp->AddAudioSource();

	bool result1=sp->RemoveAudioSource("7");
	CPPUNIT_ASSERT(result1 == true);
	result1 = sp->RemoveAudioSource("8");
	CPPUNIT_ASSERT(result1 == true);
	result1 = sp->RemoveAudioSource("1");
	CPPUNIT_ASSERT(result1 == false);

	sp->AddVideoSource();

//	result1 = sp->RemoveAudioSource(NULL);
	CPPUNIT_ASSERT(result1 == false);

//	result1 = sp->RemoveVideoSource(NULL);
	CPPUNIT_ASSERT(result1 == false);

	count=sp->RemoveAllVideoSources();
	CPPUNIT_ASSERT(count == 1);

	count=sp->RemoveAllVideoSources();
//	printf("DONE\n");
}
