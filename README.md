										README FILE FOR XMP MEDIA PRODUCTION SDK
										
1 XMP Media Production SDK Overview

The Adobe Extensible Metadata Platform (XMP) is an international standard [ISO 16684-1]. The standardized data model and the associated operations are fully implemented as an XMP Toolkit Software Development Kit (SDK) by Adobe .

As part of enabling custom metadata for digital video production and distribution workflows via XMP, the XMP Media Production SDK is an extension layer over XMP Toolkit SDK which should allow convenient editing and storing of static, temporal and other custom metadata. The XMP Media Production SDK provides an extension mechanism for storing vendor specific metadata and other custom metadata to be carried along with the composition throughout the video production and editing workflows.

2. XMP Media Production SDK Layout

The following directories are present in the XMP Media Production SDK root directory	 :-

A. /	The root directory contains CmakeLists.txt, LICENSE file and Common Defines.cmake files. It contains
build, public, private, imports and samples directories 
B. ./build	It contains Shared Config files for different platforms and all the build solutions/projects are generated here.
C. ./samples	It contains the samples for XMP Media Production SDK and the Cmake script to build samples.
D. ./public/include	It contains the public headers of the XMP Media Production SDK
E. ./public/source	It contains the public sources of the XMP Media Production SDK
F. ./private	It contains include and source directories and contains the Cmake script for building the XMP Media Production SDK library.
G. ./private/include	It contains the private headers of the XMP Media Production SDK
H. ./private/source	It contains the private source files of the XMP Media Production SDK
I ./imports	It contains the XMPToolkit SDK which is the required dependency for XMP Media Production SDK.

3. SETTING UP THE XMP Media Production SDK
The root directory of the XMP Media Production SDK is referred as the XMP_MP_ROOT_DIR.


 3.1 Supported Platforms
The XMP Media Production SDK is officially supported on the following platforms :-

•	Windows ( Compiler used Microsoft Visual Studio 14 2015)
•	Macintosh ( Compiler used XCode 7.2)
•	Unix ( RHEL 7 and Compiler used gcc 4.8.2)


However, it is possible to build XMP Media Production SDK on other platforms as well by making some minor changes in the Cmake build scripts.



3.2 REQUIRED DEPENDENCIES FOR BUILDING XMP Media Production SDK

In the top level directory of XMP Media Production SDK, there will be an imports directory.
It should contain the following the latest available Adobe XMP Toolkit SDK which can be obtained from the XMP Devnet page. 

The XMP Toolkit SDK root directory should be copied into the imports directory of the XMP Media Production SDK such that imports should contain the following path.
XMP_MP_ROOT_DIR/imports/XMPToolkit/ .

The XMP Toolkit SDK binaries should be built following the steps described in the XMP Toolkit SDK Programmer’s Guide.





3.3 STEPS TO BUILD THE XMP Media Production SDK
The root directory of the XMP Media Production SDK is referred as the XMP_MP_ROOT_DIR.

3.3.1 Installing Cmake

•	Cmake is required to build the SDK.
•	Cmake : minimum version should be 2.8.6

Obtain a copy of the CMake distribution for your platform from cmake official site.

Cmake-gui tools comes bundled with Cmake for Macintosh and Windows platforms. 
For Unix platforms, Cmake-gui can be conveniently installed by a command like 
yum install cmake-gui.

The steps given in this guide will use the Cmake gui tool as this is the most convenient way to build XMP Media Productions SDK.

3.3.2 Steps to build the XMP Media Production SDK on Windows

1.	Extract the latest XMP Toolkit SDK into the XMP_MP_ROOT_DIR and build the XMP Toolkit SDK 64 bit dynamic binaries for Windows using the steps mentioned in the XMP Toolkit Programmer’s Guide.

2.	Open the CMake GUI tool.

3.	Set the path of the Source Code as the root directory of XMP Media Production SDK which is XMP_MP_ROOT_DIR.

4.	Set the path to build the binaries as XMP_MP_ROOT_DIR/build/.

5.	Select the Visual Studio 14 2015 Win64 generator to build the solution and click Generate.

6.	The following projects are generated :-

1.	UMCSDK.sln is generated in the XMP_MP_ROOT_DIR/build/ directory.
2.	Samples.sln is generated in the XMP_MP_ROOT/build/samples/ directory.
3.	Individual sample solutions are generated as follows

•	AddingSources.sln is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions.sln is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs.sln is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.


7.	Open the UMCSDK.sln in Visual Studio and  select the ALL_BUILD target and build it. It will build all the UMC lib and the samples.
8.	The debug binaries will be generated at XMP_MP_ROOT_DIR/build/private/debug and the release binaries will be generated at XMP_MP_ROOT_DIR/build/private/release.


9.	The debug samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/debug directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/debug directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/debug directory.
10.	 The release samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.




3.3.3 Steps to build the XMP Media Production SDK on Macintosh



1.	Extract the latest XMP Toolkit SDK into the XMP_MP_ROOT_DIR and build the XMP Toolkit SDK 64 bit frameworks for Macintosh using the steps mentioned in the XMP Toolkit Programmer’s Guide.

2.	Open the CMake GUI tool.

3.	Set the path of the Source Code as the root directory of XMP Media Production SDK which is XMP_MP_ROOT_DIR.

4.	Set the path to build the binaries as XMP_MP_ROOT_DIR/build/.

5.	Select the XCode generator to build the xcode project and click Generate.

6.	The following xcode projects are generated :-

1.	UMCSDK.xcodeproj is generated in the XMP_MP_ROOT_DIR/build/ directory.
2.	Samples.xcodeproj is generated in the XMP_MP_ROOT/build/samples/ directory.
3.	Individual sample solutions are generated as follows

•	AddingSources.xcodeproj is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions.xcodeproj is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs.xcodeproj is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.

7.	Open the UMCSDK.xcodproj in Visual Studio and select the ALL_BUILD target and build it. It will build all the UMC lib and the samples.

8.	The debug binaries will be generated at XMP_MP_ROOT_DIR/build/private/debug and the release binaries will be generated at XMP_MP_ROOT_DIR/build/private/release.


9.	The debug samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/debug directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/debug directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/debug directory.

10.	 The release samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.




3.3.4 Steps to build the XMP Media Production SDK on LINUX

1.	Extract the latest XMP Toolkit SDK into the XMP_MP_ROOT_DIR and build the XMP Toolkit SDK 64 bit LINUX binaries using the steps mentioned in the XMP Toolkit Programmer’s Guide.

2.	Open the cmake-gui tool.

3.	Set the CMAKE_BUILD_TYPE variable in cmake-gui as either “debug” or “release” depending on whether you want to build the debug binaries or the release binaries.

4.	Set the path of the Source Code as the root directory of XMP Media Production SDK which is XMP_MP_ROOT_DIR.

5.	Set the path to build the binaries as XMP_MP_ROOT_DIR/build/.

6.	Select the LINUX Makefile generator to build the project and click Generate.

7.	The following Makefiles are generated :-

o	UMCSDK Makefile is generated in the XMP_MP_ROOT_DIR/build/ directory.
o	Samples Makefile is generated in the XMP_MP_ROOT/build/samples/ directory.
o	Individual sample solutions are generated as follows

•	AddingSources Makefile is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions Makefile is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs Makefile is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.


8.	To build the binaries or the executables run make –k all on the respective makefile.

9.	The debug binaries will be generated at XMP_MP_ROOT_DIR/build/private/debug and the release binaries will be generated at XMP_MP_ROOT_DIR/build/private/release.


10.	The debug samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/debug directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/debug directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/debug directory.
11.	 The release samples will be built as follows:


•	AddingSources executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingSources/build/ directory.

•	AddingExtensions executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingExtensions/build/ directory.

•	AddingOutputs executable is generated in the XMP_MP_ROOT_DIR/build/samples/AddingOutputs/build/ directory.

