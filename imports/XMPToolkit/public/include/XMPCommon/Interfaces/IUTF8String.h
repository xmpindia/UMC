#ifndef __IUTF8String_h__
#define __IUTF8String_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 02-09-14 ADC 1.0-m003 Re-factoring of XMPCommon Framework
// 02-05-14 ADC 1.0-m002 Some changes in the common framework
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

#include "XMPCommon/XMPCommonDefines.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/XMPCommonFwdDeclarations.h"

#include <string>

namespace NS_XMPCOMMON {

	//!
	//! \brief Version1 of the interface that represents an UTF8String.
	//! \details Provides all the functions to access properties of the string object, append or assign content
	//! to the existing string objects and clone existing string objects.
	//! \attention Support Multi-threading at object level using locks but it controllable through flag during
	//! cloning operation.
	//!
	class XMP_PUBLIC IUTF8String_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Appends more content into the existing string object through a pointer to char buffer.
		//! \param[in] buf pointer to a constant char buffer containing new content. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length in case buf is not null
		//! terminated. In case buf is null terminated it can be set to its default value ( std::string::npos ).
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String append( const char * buf, SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Appends the contents of another string into the existing string.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String whose contents will be
		//! appended to existing content in the object. Invalid shared pointer will be treated as empty string.
		//! \param[in] srcPos a value of #NS_XMPCOMMON::SizeT indicating the position of the first character
		//! in src that is inserted into the object as a substring. If this is greater than src's length,
		//! nothing gets inserted into the object.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length of the substring to be copied
		//! (if the string is shorter, as many characters as possible are copied). A value of npos indicates all
		//! characters until the end of src.
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String append( const spcIUTF8String & src,
			SizeT srcPos = 0, SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Overwrites new string content into the existing string object through a pointer to char buffer.
		//! \param[in] buf pointer to a constant char buffer containing new content. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length in case buf is not null
		//! terminated. In case buf is null terminated it can be set to its default value ( std::string::npos ).
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String assign( const char * buf, SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Overwrites the contents with contents of another string.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String whose contents will
		//! overwrite existing content in the object. Invalid shared pointer will be treated as empty string.
		//! \param[in] srcPos a value of #NS_XMPCOMMON::SizeT indicating the position of the first character
		//! in src that is inserted into the object as a substring. If this is greater than src's length,
		//! nothing gets inserted into the object.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length of the substring to be copied
		//! (if the string is shorter, as many characters as possible are copied). A value of npos indicates all
		//! characters until the end of src. If this is greater than the available characters in the substring
		//! then copying is limited to the number of available characters.
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String assign( const spcIUTF8String & src, SizeT srcPos = 0,
			SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

#if XMP_NOT_YET_IMPLEMENTED
		//!
		//! Inserts additional characters into the string right before the character indicated by pos.
		//! \param[in] pos Insertion point: The new contents are inserted before the character at position pos.
		//! \param[in] buf pointer to a constant char buffer containing new content. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length in case buf is not null
		//! terminated. In case buf is null terminated it can be set to its default value ( std::string::npos ).
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String insert( SizeT pos, const char * buf,
			SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Inserts additional characters into the string right before the character indicated by pos.
		//! \param[in] pos Insertion point: The new contents are inserted before the character at position pos.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String whose contents will
		//! be copied and pushed into the object. Invalid shared pointer will be treated as empty string.
		//! \param[in] srcPos a value of #NS_XMPCOMMON::SizeT indicating the position of the first character
		//! in src that is inserted into the object as a substring. If this is greater than src's length,
		//! nothing gets inserted into the object.
		//! \param[in] count a value of #NS_XMPCOMMON::SizeT indicating the length of the substring to be copied
		//! (if the string is shorter, as many characters as possible are copied). A value of npos indicates all
		//! characters until the end of src. If this is greater than the available characters in the substring
		//! then copying is limited to the number of available characters.
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String insert( SizeT pos, const spcIUTF8String & src,
			SizeT srcPos = 0, SizeT count = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Erases part of the string, reducing its length.
		//! \param[in] pos Position of the first character to be erased.
		//! If this is greater than the string length, nothing is erased.
		//! \param[in] count Number of characters to erase (if the string is shorter, as many characters as
		//! possible are erased). A value of string::npos indicates all characters until the end of the string.
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String erase( SizeT pos = 0, SizeT count = std::string::npos );

		//!
		//! Replace portion of string.
		//! \param[in] pos Position of the first character to be replaced. If this is greater than the string length,
		//! nothing is replaced.
		//! \param[in] count Number of characters to replace (if the string is shorter, as many characters as possible
		//! are replaced). A value of string::npos indicates all characters until the end of the string.
		//! \param[in] buf pointer to a constant char buffer containing new content. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] srcCount a value of #NS_XMPCOMMON::SizeT indicating the length in case buf is not null
		//! terminated. In case buf is null terminated it can be set to its default value ( std::string::npos ).
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String replace( SizeT pos, SizeT count, const char * buf,
			SizeT srcCount = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Replace portion of string.
		//! \param[in] pos Position of the first character to be replaced. If this is greater than the string length,
		//! nothing is replaced.
		//! \param[in] count Number of characters to replace (if the string is shorter, as many characters as possible
		//! are replaced). A value of string::npos indicates all characters until the end of the string.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String whose contents will
		//! be copied and pushed into the object. Invalid shared pointer will be treated as empty string.
		//! \param[in] srcPos Position of the first character in str that is copied to the object as replacement.
		//! If this is greater than src's length nothing is copied.
		//! \param[in] srcCount Length of the substring to be copied (if the string is shorter, as many characters
		//! as possible are copied). A value of string::npos indicates all characters until the end of str.
		//! \return the shared pointer to itself of type #NS_XMPCOMMON::IUTF8String.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String replace( SizeT pos, SizeT count, const spcIUTF8String & src,
			SizeT srcPos = 0, SizeT srcCount = std::string::npos ) MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Copy sequence of characters from string.
		//! \detail Copies a substring of the current value of the string object into the array. This substring
		//! contains the len characters that start at position pos.
		//! \param[in,out] buf Pointer to an array of characters. The array shall contain enough storage for the copied
		//! characters.
		//! \param[in] pos Position of the first character to be copied. If this is greater than the string length, then
		//! nothing is copied.
		//! \param[in] count Number of characters to copy (if the string is shorter, as many characters as possible are
		//! copied).
		//! \return The number of characters copied to the array. This may be equal to count or to size() - pos.
		//! \note The function does not append a null character at the end of the copied content.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT copy( char * buf, SizeT pos = 0, SizeT count = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Find content in string.
		//! \detail Searches the string for the first occurrence of the sequence specified by its arguments. When pos
		//! is specified, the search only includes characters at or after position pos, ignoring any possible
		//! occurrences that include characters before pos.
		//! \param[in] buf pointer to a constant char buffer containing content to be matched. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] pos Position of the first character in the string to be considered in the search.
		//! If this is greater than the string length, the function never finds matches.
		//! \param[in] count Length of sequence of characters to match.
		//! \return The position of the first character of the first match. If no matches were found, the function
		//! returns std::string::npos.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT find( const char * buf, SizeT pos = 0,
			SizeT count = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Find content in string.
		//! \detail Searches the string for the first occurrence of the sequence specified by its arguments. When pos
		//! is specified, the search only includes characters at or after position pos, ignoring any possible
		//! occurrences that include characters before pos.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String containing content to be matched. Invalid
		//! shared pointer will be treated as empty string.
		//! \param[in] pos Position of the first character in the string to be considered in the search.
		//! If this is greater than the string length, the function never finds matches.
		//! \param[in] srcPos Position of the first character in src that is to be used for comparing purpose.
		//! If this is greater than src's length nothing is compared.
		//! \param[in] count Length of sequence of characters to match.
		//! \return The position of the first character of the first match. If no matches were found, the function
		//! returns std::string::npos.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT find( const spcIUTF8String & src, SizeT pos = 0,
			SizeT srcPos = 0, SizeT count = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Find last occurrence of content in string.
		//! \detail Searches the string for the last occurrence of the sequence specified by its arguments. When pos
		//! is specified, the search only includes sequences of characters that begin at or before position pos,
		//! ignoring any possible match beginning after pos.
		//! \param[in] buf pointer to a constant char buffer containing content to be matched. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] pos Position of the last character in the string to be considered as the beginning of a match.
		//! Any value greater or equal than the string length (including string::npos) means that the entire string is
		//! searched.
		//! \param[in] count Length of sequence of characters to match.
		//! \return The position of the fist character of the last match. If no matches were found, the function
		//! returns std::string::npos.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT rfind( const char * buf, SizeT pos = std::string::npos,
			SizeT count = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! \brief Find last occurrence of content in string.
		//! \detail Searches the string for the last occurrence of the sequence specified by its arguments. When pos
		//! is specified, the search only includes sequences of characters that begin at or before position pos,
		//! ignoring any possible match beginning after pos.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String containing content to be matched. Invalid
		//! shared pointer will be treated as empty string.
		//! \param[in] pos Position of the last character in the string to be considered as the beginning of a match.
		//! Any value greater or equal than the string length (including string::npos) means that the entire string is
		//! searched.
		//! \param[in] count Length of sequence of characters to match.
		//! \return The position of the fist character of the last match. If no matches were found, the function
		//! returns std::string::npos.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED SizeT rfind( const spcIUTF8String & src, SizeT pos = std::string::npos,
			SizeT count = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Compare strings.
		//! Compares the value of the string object (or a substring) to the sequence of characters specified by its
		//! arguments.
		//! \param[in] buf pointer to a constant char buffer containing content to be compared. It can be null
		//! terminated or not. NULL pointer will be treated as empty string.
		//! \param[in] pos Position of the first character in the compared string. If this is greater than the string
		//! length, it is treated as empty string.
		//! \param[in] count Length of compared string (if the string is shorter, as many characters as possible).
		//! A value of string::npos indicates all characters until the end of the string.
		//! \param[in] srcCount Number of characters to compare.
		//! \return Returns a signed integral indicating the relation between the strings
		//! | value | relation between compared string and comparing string |
		//! | :---: | :-----------------------------------------------------|
		//! | 0     | They compare equal                                    |
		//! | <0    | Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter. |
		//! | >0    | Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer. |
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED UInt32 compare( const char * buf, SizeT pos = 0,
			SizeT count = std::string::npos, SizeT srcCount = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Compare strings.
		//! Compares the value of the string object (or a substring) to the contents of an string or substring object
		//! specified by its arguments.
		//! \param[in] src shared pointer to const #NS_XMPCOMMON::IUTF8String containing content to be compared. Invalid
		//! shared pointer will be treated as empty string.
		//! \param[in] pos Position of the first character in the compared string. If this is greater than the string
		//! length, it is treated as empty string.
		//! \param[in] count Length of compared string (if the string is shorter, as many characters as possible).
		//! A value of string::npos indicates all characters until the end of the string.
		//! \param[in] srcPos Position of the first character in the comparing string. If this is greater than the
		//! comparing string length, it is treated as empty string.
		//! \param[in] srcCount Length of comparing string (if the string is shorter, as many characters as possible).
		//! \return Returns a signed integral indicating the relation between the strings
		//! | value | relation between compared string and comparing string |
		//! | :---: | :-----------------------------------------------------|
		//! | 0     | They compare equal                                    |
		//! | <0    | Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter. |
		//! | >0    | Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer. |
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED UInt32 compare( const spcIUTF8String & src, SizeT pos = 0,
			SizeT count = std::string::npos, SizeT srcPos = 0, SizeT srcCount = std::string::npos ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;
#endif  // XMP_NOT_YET_IMPLEMENTED

		//!
		//! Virtual Copy Constructor.
		//! \param[in] pos Position of the first character to be copied. If this is greater than the string length, then
		//! nothing is copied.
		//! \param[in] count Number of characters to copy (if the string is shorter, as many characters as possible are
		//! copied).
		//! \param[in] multithreadingSupport a value of type #NS_XMPCOMMON::eMultiThreadingSupport controlling whether
		//! the new object created should be thread safe or not. By default new object created will inherit its setting from
		//! the #NS_XMPCOMMON::IConfigurationManager.
		//! \return a shared pointer to NS_XMPCOMMON::IUTF8String which is exact replica of the current object.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED spIUTF8String clone( SizeT pos = 0, SizeT count = std::string::npos,
			eMultiThreadingSupport multithreadingSupport = kMultiThreadingConfiguredAtInitialization ) const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Indicates whether the string object is empty or not.
		//! \return a value of type bool; true in case the contents of the string object is empty.
		//!
		XMP_PRIVATE VIRTUAL_IF_SOURCE_COMPILED bool empty() const MARK_PURE_VIRTUAL_IF_SOURCE_COMPILED;

		//!
		//! Provides access to the actual location where contents of string are stored.
		//! \return a pointer to a buffer of const chars containing the contents of the string object.
		//!
		virtual const char * c_str() const __NOTHROW__ = 0;

		//!
		//! Clears the contents of the string object.
		//!
		virtual void clear() __NOTHROW__ = 0;

		//!
		//! Indicates the number of bytes used by the contents of the string object.
		//! \return an object of type #NS_XMPCOMMON::SizeT containing the number of bytes used to store the contents fo the string object.
		//!
		virtual SizeT size() const __NOTHROW__ = 0;

#if !SOURCE_COMPILED
	protected:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual pIUTF8String_base assign( const char * buffer, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIUTF8String_base assign( const pcIUTF8String_base str, SizeT srcPos, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;

		virtual pIUTF8String_base append( const char * buffer, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIUTF8String_base append( const pcIUTF8String_base str, SizeT srcPos, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;

#if XMP_NOT_YET_IMPLEMENTED
		virtual pIUTF8String_base insert( SizeT pos, const char * buf, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIUTF8String_base insert( SizeT pos, pcIUTF8String_base src, SizeT srcPos, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;

		virtual pIUTF8String_base erase( SizeT pos, SizeT count, pcIError_base & error ) __NOTHROW__ = 0;

		virtual pIUTF8String_base replace( SizeT pos, SizeT count, const char * buf, SizeT srcCount, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIUTF8String_base replace( SizeT pos, SizeT count, pcIError_base src, SizeT srcPos, SizeT srcCount, pcIError_base & error ) __NOTHROW__ = 0;

		virtual SizeT copy( char * buf, SizeT pos, SizeT count, pcIError_base & error ) const __NOTHROW__ = 0;

		virtual SizeT find( const char * buf, SizeT pos, SizeT count, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual SizeT find( pcIUTF8String_base src, SizeT pos, SizeT count, pcIError_base & error ) const __NOTHROW__ = 0;

		virtual SizeT rfind( const char * buf, SizeT pos, SizeT count, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual SizeT rfind( pcIUTF8String_base src, SizeT pos, SizeT count, pcIError_base & error ) const __NOTHROW__ = 0;

		virtual UInt32 compare( const char * buf, SizeT pos, SizeT count, SizeT srcCount, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual UInt32 compare( pcIUTF8String_base src, SizeT pos, SizeT count, SizeT srcPos, SizeT srcCount, pcIError_base & error ) const __NOTHROW__ = 0;
#endif  // XMP_NOT_YET_IMPLEMENTED

		virtual pIUTF8String_base clone( SizeT pos, SizeT count, UInt32 multiThreadingSupport, pcIError_base & error ) const __NOTHROW__ = 0;

		virtual UInt32 empty( pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond
#endif

	protected:
		//!
		//! protected Virtual Destructor
		//!
		virtual ~IUTF8String_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IUTF8String_v1::~IUTF8String_v1() __NOTHROW__ { }

};

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
#include "XMPCommon/Utilities/TWrapperFunctions.h"

//! \cond XMP_INTERNAL_DOCUMENTATION
namespace NS_XMPCOMMON {
	inline spIUTF8String IUTF8String_v1::append( const char * buf, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, const char *, SizeT >(
			this, &IUTF8String_v1::append, buf, count );
	}

	inline spIUTF8String IUTF8String_v1::append( const spcIUTF8String & src, SizeT srcPos, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer<IUTF8String_v1, pIUTF8String_base, IUTF8String, pcIUTF8String_base, SizeT, SizeT >(
			this, &IUTF8String_v1::append, src.get(), srcPos, count );
	}

	inline spIUTF8String IUTF8String_v1::assign( const char * buf, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, const char *, SizeT >(
			this, &IUTF8String_v1::assign, buf, count );
	}

	inline spIUTF8String IUTF8String_v1::assign( const spcIUTF8String & src, SizeT srcPos, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, pcIUTF8String_base, SizeT, SizeT >(
			this, &IUTF8String_v1::assign, src.get(), srcPos, count );
	}

#if XMP_NOT_YET_IMPLEMENTED
	inline spIUTF8String IUTF8String_v1::insert( SizeT pos, const char * buf, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, const char *, SizeT >(
			this, &IUTF8String_v1::insert, pos, buf, count );
	}

	inline spIUTF8String IUTF8String_v1::insert( SizeT pos, const spcIUTF8String & src, SizeT srcPos, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, pcIUTF8String_base, SizeT, SizeT >(
			this, &IUTF8String_v1::insert, pos, src.get(), srcPos, count );
	}

	inline spIUTF8String IUTF8String_v1::erase( SizeT pos, SizeT count ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, SizeT >(
			this, &IUTF8String_v1::erase, pos, count );
	}

	inline spIUTF8String IUTF8String_v1::replace( SizeT pos, SizeT count, const char * buf, SizeT srcCount ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, SizeT, const char *, SizeT >(
			this, &IUTF8String_v1::replace, pos, count, buf, srcCount );
	}

	inline spIUTF8String IUTF8String_v1::replace( SizeT pos, SizeT count, const spcIUTF8String & src, SizeT srcPos, SizeT srcCount ) {
		return NS_XMPCOMMON::CallSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, SizeT, pcIUTF8String_base, SizeT, SizeT >(
			this, &IUTF8String_v1::replace, pos, count, src.get(), srcPos, srcCount );
	}

	inline SizeT IUTF8String_v1::copy( char * buf, SizeT pos, SizeT count ) const {
		NS_XMPCOMMON::CallConstSafeFunction< IUTF8String_v1, SizeT, SizeT, char *, SizeT, SizeT >(
			this, &IUTF8String_v1::copy, buf, pos, count );
	}

	inline SizeT IUTF8String_v1::find( const char * buf, SizeT pos, SizeT count ) const {
		NS_XMPCOMMON::CallConstSafeFunction< IUTF8String_v1, SizeT, SizeT, char *, SizeT, SizeT >(
			this, &IUTF8String_v1::find, buf, pos, count );
	}

	inline SizeT IUTF8String_v1::find( const spcIUTF8String & src, SizeT pos, SizeT srcPos, SizeT count ) const {

	}
#endif  // XMP_NOT_YET_IMPLEMENTED

	inline spIUTF8String IUTF8String_v1::clone( SizeT pos, SizeT count, eMultiThreadingSupport multithreadingSupport ) const {
		return NS_XMPCOMMON::CallConstSafeFunctionReturningPointer< IUTF8String_v1, pIUTF8String_base, IUTF8String, SizeT, SizeT, UInt32 >(
			this, &IUTF8String_v1::clone, pos, count, static_cast< UInt32 >( multithreadingSupport ) );
	}

	inline bool IUTF8String_v1::empty() const {
		return NS_XMPCOMMON::CallConstSafeFunction< IUTF8String_v1, bool, UInt32 >(
			this, &IUTF8String_v1::empty );
	}

}
//! \endcond
#endif  // !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB


#endif  // __IUTF8String_h__
