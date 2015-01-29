add_definitions(-DWIN_ENV=1 -D_CRT_SECURE_NO_WARNINGS=1 -D_SCL_SECURE_NO_WARNINGS=1  /J /fp:precise)

set (OS_FOLDER_NAME "windows_x64")
set (BUILD_CONFIGURATION "$(Configuration)")

function( GetFullSharedLibraryName shortName fullName )
	set( fullName ${shortName}.dll)
endfunction( GetFullSharedLibraryName )
