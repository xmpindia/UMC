#ifndef DoViDisplay_h__
#define DoViDisplay_h__ 1

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
