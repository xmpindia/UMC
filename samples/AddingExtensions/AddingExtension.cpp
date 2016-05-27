// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include <iostream>
#include <fstream>

#include "interfaces/IUMC.h"
#include "interfaces/ITrack.h"
#include "DisplayExtensionHandler.h"


/*Printing values of the Display Extension properties in a human readable format*/
void printDisplayExtension( std::shared_ptr< NS_DisplayExtension::Display> & displayObj) {

	using namespace std;

	cout << "Display Name" << displayObj->getName() << endl;
	cout << "Display Id" << displayObj->getID() << endl;
	cout << "Display Diagonal Size" << displayObj->getDiagonalSize() << endl;
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
	
	/*Displaying the content of the parsed display extension*/
	printDisplayExtension(parsedDisplay);
	/*
	There must be a matching UMC_Terminate() call for each UMC_Initialize() call
	*/
	UMC_Terminate();
}