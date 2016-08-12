#ifndef __DISPLAY__
#define __DISPLAY__ 1

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

#include <iostream>

namespace NS_DisplayExtension {

	class Display
	{
	public:
		/*The constructor for creating the Display extension*/
		Display();

		/*Get the ID property of the Display */
		std::string getID();
		
		/*Set the ID property of the Display */
		void setID( const std::string & displayID );

        /*Get width of Display */
        double getWidth();
        
        double getWidth() const;
        
        /*Get height of Display */
        double getHeight();
        
        double getHeight() const;
        
        /*Get Type of Display */
        const std::string & getType();
        
        const std::string & getType() const;
        
        /*Set width of Display */
        void setWidth(const double & displayWidth);
        
        /*Set height of Display */
        void setHeight(const double & displayHeight);
		
        /*Set type of display */
        void setType(const std::string & displayType);
        
	protected:
		
		std::string			_id;
		//std::string			_name;
		double				_width;
        double              		_height;
        std::string         		_type;
	};
}

#endif  // __Display__
