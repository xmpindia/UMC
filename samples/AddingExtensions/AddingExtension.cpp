/*
*  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
*  This file is licensed to you under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License. You may obtain a copy
*  of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software distributed under
*  the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
*  OF ANY KIND, either express or implied. See the License for the specific language
*  governing permissions and limitations under the License.
*
*/


/*
 This sample seeks to demonstrate adding an extension to the UMC. It more specifically elucidates creating an extension,
 creating an extension handler, registering an extension handler, adding the extension to the UMC object and retrieving
 the extension from the UMC object. Although this sample adds an extension to the top level UMC object, it is also
 possible to add extensions to all source and output objects.For more details, programmer's guide and interface
 documentation should be referred.
 */


#include <iostream>
#include <fstream>
#include <iomanip>

#include "interfaces/IUMC.h"
#include "interfaces/ITrack.h"
#include "DisplayExtensionHandler.h"

#include "SampleUtils.h"

#include "SampleUtils.h"



using namespace SampleUtils;

/*Printing values of the Display Extension properties in a human readable format*/
void printDisplayExtension( std::shared_ptr< NS_DisplayExtension::Display> & displayObj) {

	using namespace std;
	

	cout << setw(maxFieldWidth) << "Display Name" <<  defaultIndent << setw(maxFieldWidth) << displayObj->getName()  << endl;
    
	cout << setw(maxFieldWidth) << "Display Id" <<  defaultIndent<< setw(maxFieldWidth) << displayObj->getID() << defaultIndent << endl;
    
	cout << setw(maxFieldWidth) << "Display Diagonal Size" <<  defaultIndent << setw(maxFieldWidth) << displayObj->getDiagonalSize() << defaultIndent << endl;
    
	cout << endl;
}

int main() {

	//get set delete modify
	using namespace NS_DisplayExtension;


	/*
	Initializing the UMC SDK is necessary before using any of the UMC APIs
	*/
	UMC_Initialize();

	/*Register the extension handler for the display extension*/
	UMC::IUMC::RegisterCustomNodeHandler(Display::GetNameSpace(), NS_DisplayExtension::Display::GetPropertyName(), std::make_shared< DisplayHandler >());
	
	/*Creaty an empty UMC object*/
	auto umcObj = UMC::IUMC::CreateEmptyUMC();

	/*Create an object of the Display extension*/
	std::shared_ptr< Display > display = std::make_shared< Display >();

	/*Set the id of the display extension*/
	display->setID("1");

	/*Set the name of the display extension*/
	display->setName("TV Display");

	/*Set the diagonal size of the display extension*/
	display->setDiagonalSize(52.0);

	/*Add the custom data to the UMC object*/
	umcObj->SetCustomData( Display::GetNameSpace(), Display::GetPropertyName(), display);

	std::cout << defaultIndent << " Printing the contents of the display extension" << std::endl<< std::endl;;

	/*Print the contents of the display extension*/
	printDisplayExtension(display);


	/*Serialing the umc object to RDF format*/
	auto rdfRepresentationOfUMCWithExtension = umcObj->SerializeToBuffer();

	/*Creating a file stream for dumping rdf serialization of the UMC object*/
	std::ofstream fileWriter("rdfRepresentationOfUMCWithExtension.xmp");

	/*Dumping the RDF serialization on to the file stream*/
	fileWriter << rdfRepresentationOfUMCWithExtension;

	/*Closing the file stream*/
	fileWriter.close();

	/*Creating a UMC object by parsing the RDF serialization*/
	auto parsedUMCObject = UMC::IUMC::CreateUMCFromBuffer(rdfRepresentationOfUMCWithExtension);

	/*Getting the display extension from the parsed UMC object*/
	std::shared_ptr< Display >parsedDisplay = std::dynamic_pointer_cast< Display >( parsedUMCObject->GetCustomData(Display::GetNameSpace(), Display::GetPropertyName()));
	
	std::cout << defaultIndent << " Printing the contents of the parsed display extension" << std::endl << std::endl;

	/*Displaying the content of the parsed display extension*/
	printDisplayExtension(parsedDisplay);

	/*
	There must be a matching UMC_Terminate() call for each UMC_Initialize() call
	*/
	UMC_Terminate();
}