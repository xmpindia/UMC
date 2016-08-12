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
#include "interfaces/IUMC.h"
#include "Display.h"
#include "AvailableDisplays.h"
#include "DisplayExtensionHandler.h"

class ExtensionHandlerTests : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( ExtensionHandlerTests );
		CPPUNIT_TEST( ExtensionHandlerTestForCompositeData );
        CPPUNIT_TEST( ExtensionHandlerNegativeTest);
	CPPUNIT_TEST_SUITE_END();


protected:
	void ExtensionHandlerTestForCompositeData();
    void ExtensionHandlerNegativeTest();
public:
	virtual void setUp();
	virtual void tearDown();
private:
    static const int _noOfDisplays;
    void compareAvailableDisplaysObjects(const NS_DisplayExtension::AvailableDisplays & obj1 ,const NS_DisplayExtension::AvailableDisplays & obj2);
};

const int ExtensionHandlerTests::_noOfDisplays = 4;

CPPUNIT_TEST_SUITE_REGISTRATION( ExtensionHandlerTests );



void ExtensionHandlerTests::setUp() {
    UMC_Initialize();
}

void ExtensionHandlerTests::tearDown() {
	UMC_Terminate();
}

void ExtensionHandlerTests::compareAvailableDisplaysObjects(const NS_DisplayExtension::AvailableDisplays &obj1,const  NS_DisplayExtension::AvailableDisplays & obj2)
{
    const std::vector<NS_DisplayExtension::Display> devices1 = obj1.getDisplayList();
    const std::vector<NS_DisplayExtension::Display> devices2 = obj2.getDisplayList();
    
    CPPUNIT_ASSERT_EQUAL(obj1.getName(),obj2.getName());
    CPPUNIT_ASSERT_EQUAL(devices1.size(),devices2.size());
    
    for(int i = 0 ; i < devices1.size() ; i++){
        CPPUNIT_ASSERT_EQUAL(devices1[i].getWidth() , devices2[i].getWidth());
        CPPUNIT_ASSERT_EQUAL(devices1[i].getHeight() , devices2[i].getHeight());
        CPPUNIT_ASSERT_EQUAL(devices1[i].getType() , devices2[i].getType());
    }
    
}
void ExtensionHandlerTests::ExtensionHandlerTestForCompositeData() {
	using namespace NS_DisplayExtension;

    std::shared_ptr<NS_DisplayExtension::AvailableDisplays> customData = std::make_shared<AvailableDisplays> ();
	customData->setName("TV Displays");
	

    //std::shared_ptr<Display> display =  std::make_shared<Display> ();

	int w = 30;
	int h = 15;

	std::string displayType[] = {"HD","FULL HD"};

	for(int i = 0 ; i < _noOfDisplays ; i++)
	{
        std::shared_ptr<Display> display =  std::make_shared<Display> ();
        display->setID(std::to_string(i));
		display->setWidth(w);
		display->setHeight(h);
		display->setType(displayType[i%2]);

		customData->AddDisplay(*display);
		
		w += 10;
		h += 5;
	}

    shared_ptr<DisplayExtensionHandler> handler = std::make_shared< DisplayExtensionHandler >();
	UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName(), handler);
	auto umcObj = UMC::IUMC::CreateEmptyUMC();
	
	umcObj->SetCustomData(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName(), customData);
	auto rdfRepresentationOfUMCWithExtension = umcObj->SerializeToBuffer();
	
	std::ofstream fileWriter("UMCExtension.xmp");
	fileWriter << rdfRepresentationOfUMCWithExtension;
	
	fileWriter.close();
    
    auto parsedUMCObject = UMC::IUMC::CreateUMCFromBuffer(rdfRepresentationOfUMCWithExtension);
    
    std::shared_ptr< AvailableDisplays >parsedAvailableDisplays = std::dynamic_pointer_cast< AvailableDisplays >( parsedUMCObject->GetCustomData(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName()));
	
    compareAvailableDisplaysObjects(*parsedAvailableDisplays,*customData);
    
}

void ExtensionHandlerTests::ExtensionHandlerNegativeTest(){
    
    using namespace NS_DisplayExtension;
    
    std::shared_ptr<NS_DisplayExtension::AvailableDisplays> customData = std::make_shared<AvailableDisplays> ();
    customData->setName("TV Displays");
    
    shared_ptr<DisplayExtensionHandler> handler = std::make_shared< DisplayExtensionHandler >();
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(), "", handler),false);
    
    
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler("", AvailableDisplays::GetPropertyName(), handler),false);
    
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(),AvailableDisplays::GetPropertyName() , handler),true);
    
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(),AvailableDisplays::GetPropertyName() , handler),false);
    
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(),AvailableDisplays::GetPropertyName() , nullptr),true);
    
    CPPUNIT_ASSERT_EQUAL(UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(),AvailableDisplays::GetPropertyName() , nullptr),false);
    
    auto umcObj = UMC::IUMC::CreateEmptyUMC();
    
    CPPUNIT_ASSERT_EQUAL(umcObj->SetCustomData(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName(), customData),false);
    
    UMC::IUMC::RegisterCustomNodeHandler(AvailableDisplays::GetNameSpace(),AvailableDisplays::GetPropertyName() , handler);
                                         
    CPPUNIT_ASSERT_EQUAL(umcObj->SetCustomData(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName(), customData),true);
    
    CPPUNIT_ASSERT_EQUAL(umcObj->SetCustomData("", AvailableDisplays::GetPropertyName(), customData),false);
    
    CPPUNIT_ASSERT_EQUAL(umcObj->SetCustomData(AvailableDisplays::GetNameSpace(), AvailableDisplays::GetPropertyName(), NULL),false);
    
    CPPUNIT_ASSERT_EQUAL(umcObj->SetCustomData(AvailableDisplays::GetNameSpace(), "", nullptr),false);
    
    auto parsedUMCObject =  UMC::IUMC::CreateEmptyUMC();    
    std::shared_ptr< AvailableDisplays >parsedAvailableDisplays = std::dynamic_pointer_cast< AvailableDisplays >( parsedUMCObject->GetCustomData("", AvailableDisplays::GetPropertyName()));
    
    CPPUNIT_ASSERT_EQUAL(bool(parsedAvailableDisplays),false);
    
}
