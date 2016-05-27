#ifndef DoViDisplay_h__
#define DoViDisplay_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2016 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "interfaces/ICustomData.h"
#include "interfaces/IUMCNode.h"

namespace NS_DisplayExtension {
	using namespace UMC;

	/*Implement the ICustomData interface in order to create an extension*/
	class Display
		: public UMC::ICustomData
	{
	public:
		/*The constructor for creating the Display extension*/
		Display();

		/*Get the ID property of the Display */
		std::string getID();
		
		/*Set the ID property of the Display */
		void setID( const std::string & displayID );
		
		/*Get the Name property of the Display */
		std::string getName();

		/*Set the Name property of the Display */
		void setName( const std::string & displayName );

		/*Get the diagonal size property of the Display */
		double getDiagonalSize();

		/*Set the diagonal size property of the Display */
		void setDiagonalSize( const double & displayDiagonalSize );

		/*Set the parent node of the Display */
		virtual void SetParentNode( const wpIUMCNode & parentNode );

		/*Get the parent node of the Display */
		virtual wpcIUMCNode GetParentNode() const;
		virtual wpIUMCNode GetParentNode();

		virtual ~Display();

		/*Set the parent node of the Display */
		static const std::string & GetNameSpace();
		static const std::string & GetPropertyName();

	protected:
		
		wpIUMCNode			_parent;
		std::string			_id;
		std::string			_name;
		double				_diagonalSize;
	};
}

#endif  // DoViDisplay_h__
