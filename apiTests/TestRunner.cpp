#include "cppunit/ui/text/TestRunner.h"
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/TestResult.h"

int main(int argc, char* argv[]) {

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
   
    CppUnit::TestResult controller;
    
    // parameter parsing ////////////////////////////////////////////////
    std::string testPath = "";
    
    if(argc>1){
        // in this case store it as single test
        testPath = std::string(argv[1]);
        
        runner.run(controller,testPath);
    }
    else
        runner.run();
    
    

	return 0;
}