#if ! __WXMPMeta_hpp__
#define __WXMPMeta_hpp__ 1

// =================================================================================================
// Copyright 2002 Adobe Systems Incorporated
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
//  AWL Alan Lillich
//  FNO Frank Nocke
//  ADC	Amandeep Chawla
//	SKP Sunil Kishor pathak
//  AJ Abhishek Jindal
//
// mm-dd-yy who Description of changes, most recent on top.
//
// 01-09-14 AJ 5.6-c031 Renamed UseNewCoreAPIs() to Use_CPP_DOM_APIs()
// 12-05-14 SKP 5.6-c030 Renamed GetNewMetadataObject() to GetIXMPMetadata()
// 02-24-14 ADC 5.6-c001 XMPCommon Framework and XMPCore new APIs ported to Mac Environment.
//
// 05-13-13 ADC 5.5-c018 Removing usage of bool in APIs exposed at DLL boundaries.
// 08-01-12 AWL 5.5-c004 Implement public API and glue layer for XMPCore error notifications.
//
// 07-16-09 AWL 5.0-c045 [2379902] Restore M4 signature for WXMPMeta_RegisterAssertNotify_1.
// 06-11-09 AWL 5.0-c034 Finish threading revamp, implement friendly reader/writer locking.
// 05-27-09 AWL 5.0-c033 Remove XMPMeta::SendAssertNotify.
// 05-21-09 AWL 5.0-c032 Revamp glue again to pass SetClientString with each function.
// 05-19-09 AWL 5.0-c031 First part of threading improvements, revamp the client glue.
// 02-16-09 FNO 5.0-c008 [1647989] Adding 3rd patch by H. Figuiere: adding delete-localized-text function.
//
// 02-28-08 AWL 4.2-c046 Add SXMPMeta::Erase.
// 08-27-07 AWL 4.2-c020 Add Sort, change the Dump* routines to hexify non-ASCII characters.
//
// 10-12-06 AWL 4.1-c021 [1235816] Remove the new/delete overrides from static builds.
//
// 03-24-06 AWL 4.0 Adapt for move to ham-perforce, integrate XMPFiles, bump version to 4.
//
// 07-18-05 AWL 3.3-002 Add GetMemProcs so that DocMetaLib can use the same ones as XMP.
//
// 05-16-05 AWL 3.2-100 Complete the deBIBification, integrate the internal and SDK source.
// 04-14-05 AWL 3.2-018 Move the padding param, add overloads to simplify use of SerializeToBuffer.
// 02-11-05 AWL 3.2-002 Add client reference counting.
// 01-28-05 AWL Remove BIB.
//
// 10-20-04 AWL 3.1.1-085 [1084185] Fix XMP_InternalRef to not depend on BIBContainerBase layout.
// 04-16-04 AWL Add forward declaration of class CXMPMeta for AIX.
// 02-14-04 AWL Remove all default parameters from the CXMP* classes.
// 01-17-04 AWL Move into new Perforce depot, cosmetic cleanup.
// 05-06-03 AWL Introduce callback model for output (e.g. dump routines).
// 04-18-03 AWL Remove formsMatch parameter from RegisterAlias.
// 10-22-02 AWL Another round of tweaks and cleanup.
// 09-12-02 AWL Tweak to clean compile.
// 09-06-02 AWL First version for general review.
// 08-22-02 AWL First draft sent to Perry Caro and Chris Deighan.
// 08-15-02 AWL Started first draft.
//
// =================================================================================================
#endif // AdobePrivate

#include "client-glue/WXMP_Common.hpp"

#if __cplusplus
extern "C" {
#endif

// =================================================================================================

static XMP_Bool WrapErrorNotify ( XMPMeta_ErrorCallbackProc proc, void * context,
							  XMP_ErrorSeverity severity, XMP_Int32 cause, XMP_StringPtr message )
{
	bool ok;
	try {
		ok = (*proc) ( context, severity, cause, message );
	} catch ( ... ) {
		ok = false;
	}
	return ConvertBoolToXMP_Bool( ok );
}

// =================================================================================================

#define zXMPMeta_GetVersionInfo_1(info) \
    WXMPMeta_GetVersionInfo_1 ( info /* no wResult */ )

#if ! AdobePrivate
#define zXMPMeta_Initialize_1() \
    WXMPMeta_Initialize_1 ( &wResult )
#else
#define zXMPMeta_Initialize_1(AllocateProc,DeleteProc) \
    WXMPMeta_Initialize_1 ( AllocateProc, DeleteProc, &wResult )
#endif

#define zXMPMeta_Terminate_1() \
    WXMPMeta_Terminate_1 ( /* no wResult */ )

#define zXMPMeta_CTor_1() \
    WXMPMeta_CTor_1 ( &wResult )

#define zXMPMeta_GetGlobalOptions_1() \
    WXMPMeta_GetGlobalOptions_1 ( &wResult )

#define zXMPMeta_SetGlobalOptions_1(options) \
    WXMPMeta_SetGlobalOptions_1 ( options, &wResult )

#if AdobePrivate
#define zXMPMeta_GetMemProcs_1(AllocateProc,DeleteProc) \
    WXMPMeta_GetMemProcs_1 ( AllocateProc, DeleteProc, &wResult )

#define zXMPMeta_RegisterAssertNotify_1(notifyProc,refCon) \
    WXMPMeta_RegisterAssertNotify_1 ( 0 /* old callback wrapper */, notifyProc, refCon, &wResult )

#define zXMPMeta_UnregisterAssertNotify_1(notifyProc) \
    WXMPMeta_UnregisterAssertNotify_1 ( notifyProc, &wResult )
#endif

#define zXMPMeta_DumpNamespaces_1(outProc,refCon) \
    WXMPMeta_DumpNamespaces_1 ( outProc, refCon, &wResult )

#if AdobePrivate
#define zXMPMeta_DumpPropertyTraits_1(outProc,refCon) \
    WXMPMeta_DumpPropertyTraits_1 ( outProc, refCon, &wResult )
#define zXMPMeta_Use_CPP_DOM_APIs_1(useNewCoreAPIs) \
	WXMPMeta_Use_CPP_DOM_APIs_1( useNewCoreAPIs, &wResult )
#endif
#define zXMPMeta_RegisterNamespace_1(namespaceURI,suggestedPrefix,actualPrefix,SetClientString) \
    WXMPMeta_RegisterNamespace_1 ( namespaceURI, suggestedPrefix, actualPrefix, SetClientString, &wResult )

#define zXMPMeta_GetNamespacePrefix_1(namespaceURI,namespacePrefix,SetClientString) \
    WXMPMeta_GetNamespacePrefix_1 ( namespaceURI, namespacePrefix, SetClientString, &wResult )

#define zXMPMeta_GetNamespaceURI_1(namespacePrefix,namespaceURI,SetClientString) \
    WXMPMeta_GetNamespaceURI_1 ( namespacePrefix, namespaceURI, SetClientString, &wResult )

#define zXMPMeta_DeleteNamespace_1(namespaceURI) \
    WXMPMeta_DeleteNamespace_1 ( namespaceURI, &wResult )

#if AdobePrivate
#define zXMPMeta_RegisterPropertyTraits_1(schemaNS,propName,options) \
    WXMPMeta_RegisterPropertyTraits_1 ( schemaNS, propName, options, &wResult )
#define zXMPMeta_GetIXMPMetadata_1() \
	WXMPMeta_GetIXMPMetadata_1( this->xmpRef, &wResult )
#endif
#define zXMPMeta_GetProperty_1(schemaNS,propName,propValue,options,SetClientString) \
    WXMPMeta_GetProperty_1 ( this->xmpRef, schemaNS, propName, propValue, options, SetClientString, &wResult )

#define zXMPMeta_GetArrayItem_1(schemaNS,arrayName,itemIndex,itemValue,options,SetClientString) \
    WXMPMeta_GetArrayItem_1 ( this->xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, SetClientString, &wResult )

#define zXMPMeta_GetStructField_1(schemaNS,structName,fieldNS,fieldName,fieldValue,options,SetClientString) \
    WXMPMeta_GetStructField_1 ( this->xmpRef, schemaNS, structName, fieldNS, fieldName, fieldValue, options, SetClientString, &wResult )

#define zXMPMeta_GetQualifier_1(schemaNS,propName,qualNS,qualName,qualValue,options,SetClientString) \
    WXMPMeta_GetQualifier_1 ( this->xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, SetClientString, &wResult )

#define zXMPMeta_SetProperty_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetArrayItem_1(schemaNS,arrayName,itemIndex,itemValue,options) \
    WXMPMeta_SetArrayItem_1 ( this->xmpRef, schemaNS, arrayName, itemIndex, itemValue, options, &wResult )

#define zXMPMeta_AppendArrayItem_1(schemaNS,arrayName,arrayOptions,itemValue,options) \
    WXMPMeta_AppendArrayItem_1 ( this->xmpRef, schemaNS, arrayName, arrayOptions, itemValue, options, &wResult )

#define zXMPMeta_SetStructField_1(schemaNS,structName,fieldNS,fieldName,fieldValue,options) \
    WXMPMeta_SetStructField_1 ( this->xmpRef, schemaNS, structName, fieldNS, fieldName, fieldValue, options, &wResult )

#define zXMPMeta_SetQualifier_1(schemaNS,propName,qualNS,qualName,qualValue,options) \
    WXMPMeta_SetQualifier_1 ( this->xmpRef, schemaNS, propName, qualNS, qualName, qualValue, options, &wResult )

#define zXMPMeta_DeleteProperty_1(schemaNS,propName) \
    WXMPMeta_DeleteProperty_1 ( this->xmpRef, schemaNS, propName, &wResult )

#define zXMPMeta_DeleteArrayItem_1(schemaNS,arrayName,itemIndex) \
    WXMPMeta_DeleteArrayItem_1 ( this->xmpRef, schemaNS, arrayName, itemIndex, &wResult )

#define zXMPMeta_DeleteStructField_1(schemaNS,structName,fieldNS,fieldName) \
    WXMPMeta_DeleteStructField_1 ( this->xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult )

#define zXMPMeta_DeleteQualifier_1(schemaNS,propName,qualNS,qualName) \
    WXMPMeta_DeleteQualifier_1 ( this->xmpRef, schemaNS, propName, qualNS, qualName, &wResult )

#define zXMPMeta_DoesPropertyExist_1(schemaNS,propName) \
    WXMPMeta_DoesPropertyExist_1 ( this->xmpRef, schemaNS, propName, &wResult )

#define zXMPMeta_DoesArrayItemExist_1(schemaNS,arrayName,itemIndex) \
    WXMPMeta_DoesArrayItemExist_1 ( this->xmpRef, schemaNS, arrayName, itemIndex, &wResult )

#define zXMPMeta_DoesStructFieldExist_1(schemaNS,structName,fieldNS,fieldName) \
    WXMPMeta_DoesStructFieldExist_1 ( this->xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult )

#define zXMPMeta_DoesQualifierExist_1(schemaNS,propName,qualNS,qualName) \
    WXMPMeta_DoesQualifierExist_1 ( this->xmpRef, schemaNS, propName, qualNS, qualName, &wResult )

#define zXMPMeta_GetLocalizedText_1(schemaNS,altTextName,genericLang,specificLang,clientLang,clientValue,options,SetClientString) \
    WXMPMeta_GetLocalizedText_1 ( this->xmpRef, schemaNS, altTextName, genericLang, specificLang, clientLang, clientValue, options, SetClientString, &wResult )

#define zXMPMeta_SetLocalizedText_1(schemaNS,altTextName,genericLang,specificLang,itemValue,options) \
    WXMPMeta_SetLocalizedText_1 ( this->xmpRef, schemaNS, altTextName, genericLang, specificLang, itemValue, options, &wResult )

#define zXMPMeta_DeleteLocalizedText_1(schemaNS,altTextName,genericLang,specificLang) \
    WXMPMeta_DeleteLocalizedText_1 ( this->xmpRef, schemaNS, altTextName, genericLang, specificLang, &wResult )
#define zXMPMeta_GetProperty_Bool_1(schemaNS,propName,propValue,options) \
    WXMPMeta_GetProperty_Bool_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_GetProperty_Int_1(schemaNS,propName,propValue,options) \
    WXMPMeta_GetProperty_Int_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_GetProperty_Int64_1(schemaNS,propName,propValue,options) \
    WXMPMeta_GetProperty_Int64_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_GetProperty_Float_1(schemaNS,propName,propValue,options) \
    WXMPMeta_GetProperty_Float_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_GetProperty_Date_1(schemaNS,propName,propValue,options) \
    WXMPMeta_GetProperty_Date_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetProperty_Bool_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_Bool_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetProperty_Int_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_Int_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetProperty_Int64_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_Int64_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetProperty_Float_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_Float_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_SetProperty_Date_1(schemaNS,propName,propValue,options) \
    WXMPMeta_SetProperty_Date_1 ( this->xmpRef, schemaNS, propName, propValue, options, &wResult )

#define zXMPMeta_GetObjectName_1(objName,SetClientString) \
    WXMPMeta_GetObjectName_1 ( this->xmpRef, objName, SetClientString, &wResult )

#define zXMPMeta_SetObjectName_1(name) \
    WXMPMeta_SetObjectName_1 ( this->xmpRef, name, &wResult )

#define zXMPMeta_GetObjectOptions_1() \
    WXMPMeta_GetObjectOptions_1 ( this->xmpRef, &wResult )

#define zXMPMeta_SetObjectOptions_1(options) \
    WXMPMeta_SetObjectOptions_1 ( this->xmpRef, options, &wResult )

#define zXMPMeta_Sort_1() \
    WXMPMeta_Sort_1 ( this->xmpRef, &wResult )

#define zXMPMeta_Erase_1() \
    WXMPMeta_Erase_1 ( this->xmpRef, &wResult )

#define zXMPMeta_Clone_1(options) \
    WXMPMeta_Clone_1 ( this->xmpRef, options, &wResult )

#define zXMPMeta_CountArrayItems_1(schemaNS,arrayName) \
    WXMPMeta_CountArrayItems_1 ( this->xmpRef, schemaNS, arrayName, &wResult )

#if AdobePrivate
#define zXMPMeta_MarkStaleProperties_1(options) \
    WXMPMeta_MarkStaleProperties_1 ( this->xmpRef, options, &wResult )
#endif
#define zXMPMeta_DumpObject_1(outProc,refCon) \
    WXMPMeta_DumpObject_1 ( this->xmpRef, outProc, refCon, &wResult )

#define zXMPMeta_ParseFromBuffer_1(buffer,bufferSize,options) \
    WXMPMeta_ParseFromBuffer_1 ( this->xmpRef, buffer, bufferSize, options, &wResult )

#define zXMPMeta_SerializeToBuffer_1(pktString,options,padding,newline,indent,baseIndent,SetClientString) \
    WXMPMeta_SerializeToBuffer_1 ( this->xmpRef, pktString, options, padding, newline, indent, baseIndent, SetClientString, &wResult )

#define zXMPMeta_SetDefaultErrorCallback_1(proc,context,limit) \
	WXMPMeta_SetDefaultErrorCallback_1 ( WrapErrorNotify, proc, context, limit, &wResult )
	
#define zXMPMeta_SetErrorCallback_1(proc,context,limit) \
	WXMPMeta_SetErrorCallback_1 ( this->xmpRef, WrapErrorNotify, proc, context, limit, &wResult )

#define zXMPMeta_ResetErrorCallbackLimit_1(limit) \
	WXMPMeta_ResetErrorCallbackLimit_1 ( this->xmpRef, limit, &wResult )

// =================================================================================================

extern void
XMP_PUBLIC WXMPMeta_GetVersionInfo_1 ( XMP_VersionInfo * info );

#if ! AdobePrivate
extern void
XMP_PUBLIC WXMPMeta_Initialize_1 ( WXMP_Result * wResult );
#else
extern void
XMP_PUBLIC WXMPMeta_Initialize_1 ( XMP_AllocateProc AllocateProc,
                        XMP_DeleteProc   DeleteProc,
                        WXMP_Result *    wResult );
#endif

extern void
XMP_PUBLIC WXMPMeta_Terminate_1();

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_CTor_1 ( WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_IncrementRefCount_1 ( XMPMetaRef xmpRef );

extern void
XMP_PUBLIC WXMPMeta_DecrementRefCount_1 ( XMPMetaRef xmpRef );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_GetGlobalOptions_1 ( WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_SetGlobalOptions_1 ( XMP_OptionBits options,
                              WXMP_Result *  wResult );

#if AdobePrivate
extern void
XMP_PUBLIC WXMPMeta_GetMemProcs_1 ( XMP_AllocateProc * AllocateProc,
                         XMP_DeleteProc *   DeleteProc,
                         WXMP_Result *      wResult );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_RegisterAssertNotify_1 ( void * ignoredOldParam,
                                  XMP_AssertNotifyProc  notifyProc,
                                  void *                refCon,
                                  WXMP_Result *         wResult );

extern void
XMP_PUBLIC WXMPMeta_UnregisterAssertNotify_1 ( XMP_AssertNotifyProc notifyProc,
                                    WXMP_Result *        wResult );
#endif

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_DumpNamespaces_1 ( XMP_TextOutputProc outProc,
                            void *             refCon,
                            WXMP_Result *      wResult );

#if AdobePrivate
extern void
XMP_PUBLIC WXMPMeta_DumpPropertyTraits_1 ( XMP_TextOutputProc outProc,
                                void *             refCon,
                                WXMP_Result *      wResult );
extern void
XMP_PUBLIC WXMPMeta_Use_CPP_DOM_APIs_1(XMP_Bool useNewCoreAPIs,
									  WXMP_Result * wResult );
#endif

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_RegisterNamespace_1 ( XMP_StringPtr namespaceURI,
                               XMP_StringPtr suggestedPrefix,
                               void *        actualPrefix,
                               SetClientStringProc SetClientString,
                               WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_GetNamespacePrefix_1 ( XMP_StringPtr namespaceURI,
                                void *        namespacePrefix,
                                SetClientStringProc SetClientString,
                                WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_GetNamespaceURI_1 ( XMP_StringPtr namespacePrefix,
                             void *        namespaceURI,
                             SetClientStringProc SetClientString,
                             WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_DeleteNamespace_1 ( XMP_StringPtr namespaceURI,
                             WXMP_Result * wResult );

// -------------------------------------------------------------------------------------------------

#if AdobePrivate
extern void
XMP_PUBLIC WXMPMeta_RegisterPropertyTraits_1 ( XMP_StringPtr  schemaNS,
                                    XMP_StringPtr  propName,
                                    XMP_OptionBits options,
                                    WXMP_Result *  wResult );
extern void
XMP_PUBLIC WXMPMeta_GetIXMPMetadata_1(XMPMetaRef	  xmpObjRef,
WXMP_Result *  wResult );

// -------------------------------------------------------------------------------------------------
#endif

extern void
XMP_PUBLIC WXMPMeta_GetProperty_1 ( XMPMetaRef       xmpRef,
                         XMP_StringPtr    schemaNS,
                         XMP_StringPtr    propName,
                         void *           propValue,
                         XMP_OptionBits * options,
                         SetClientStringProc SetClientString,
                         WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetArrayItem_1 ( XMPMetaRef       xmpRef,
                          XMP_StringPtr    schemaNS,
                          XMP_StringPtr    arrayName,
                          XMP_Index        itemIndex,
                          void *           itemValue,
                          XMP_OptionBits * options,
                          SetClientStringProc SetClientString,
                          WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetStructField_1 ( XMPMetaRef       xmpRef,
                            XMP_StringPtr    schemaNS,
                            XMP_StringPtr    structName,
                            XMP_StringPtr    fieldNS,
                            XMP_StringPtr    fieldName,
                            void *           fieldValue,
                            XMP_OptionBits * options,
                            SetClientStringProc SetClientString,
                            WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetQualifier_1 ( XMPMetaRef       xmpRef,
                          XMP_StringPtr    schemaNS,
                          XMP_StringPtr    propName,
                          XMP_StringPtr    qualNS,
                          XMP_StringPtr    qualName,
                          void *           qualValue,
                          XMP_OptionBits * options,
                          SetClientStringProc SetClientString,
                          WXMP_Result *    wResult ) /* const */ ;

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_SetProperty_1 ( XMPMetaRef     xmpRef,
                         XMP_StringPtr  schemaNS,
                         XMP_StringPtr  propName,
                         XMP_StringPtr  propValue,
                         XMP_OptionBits options,
                         WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetArrayItem_1 ( XMPMetaRef     xmpRef,
                          XMP_StringPtr  schemaNS,
                          XMP_StringPtr  arrayName,
                          XMP_Index      itemIndex,
                          XMP_StringPtr  itemValue,
                          XMP_OptionBits options,
                          WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_AppendArrayItem_1 ( XMPMetaRef     xmpRef,
                             XMP_StringPtr  schemaNS,
                             XMP_StringPtr  arrayName,
                             XMP_OptionBits arrayOptions,
                             XMP_StringPtr  itemValue,
                             XMP_OptionBits options,
                             WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetStructField_1 ( XMPMetaRef     xmpRef,
                            XMP_StringPtr  schemaNS,
                            XMP_StringPtr  structName,
                            XMP_StringPtr  fieldNS,
                            XMP_StringPtr  fieldName,
                            XMP_StringPtr  fieldValue,
                            XMP_OptionBits options,
                            WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetQualifier_1 ( XMPMetaRef     xmpRef,
                          XMP_StringPtr  schemaNS,
                          XMP_StringPtr  propName,
                          XMP_StringPtr  qualNS,
                          XMP_StringPtr  qualName,
                          XMP_StringPtr  qualValue,
                          XMP_OptionBits options,
                          WXMP_Result *  wResult );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_DeleteProperty_1 ( XMPMetaRef    xmpRef,
                            XMP_StringPtr schemaNS,
                            XMP_StringPtr propName,
                            WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_DeleteArrayItem_1 ( XMPMetaRef    xmpRef,
                             XMP_StringPtr schemaNS,
                             XMP_StringPtr arrayName,
                             XMP_Index     itemIndex,
                             WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_DeleteStructField_1 ( XMPMetaRef    xmpRef,
                               XMP_StringPtr schemaNS,
                               XMP_StringPtr structName,
                               XMP_StringPtr fieldNS,
                               XMP_StringPtr fieldName,
                               WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_DeleteQualifier_1 ( XMPMetaRef    xmpRef,
                             XMP_StringPtr schemaNS,
                             XMP_StringPtr propName,
                             XMP_StringPtr qualNS,
                             XMP_StringPtr qualName,
                             WXMP_Result * wResult );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_DoesPropertyExist_1 ( XMPMetaRef    xmpRef,
                               XMP_StringPtr schemaNS,
                               XMP_StringPtr propName,
                               WXMP_Result * wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_DoesArrayItemExist_1 ( XMPMetaRef    xmpRef,
                                XMP_StringPtr schemaNS,
                                XMP_StringPtr arrayName,
                                XMP_Index     itemIndex,
                                WXMP_Result * wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_DoesStructFieldExist_1 ( XMPMetaRef    xmpRef,
                                  XMP_StringPtr schemaNS,
                                  XMP_StringPtr structName,
                                  XMP_StringPtr fieldNS,
                                  XMP_StringPtr fieldName,
                                  WXMP_Result * wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_DoesQualifierExist_1 ( XMPMetaRef    xmpRef,
                                XMP_StringPtr schemaNS,
                                XMP_StringPtr propName,
                                XMP_StringPtr qualNS,
                                XMP_StringPtr qualName,
                                WXMP_Result * wResult ) /* const */ ;

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_GetLocalizedText_1 ( XMPMetaRef       xmpRef,
                              XMP_StringPtr    schemaNS,
                              XMP_StringPtr    altTextName,
                              XMP_StringPtr    genericLang,
                              XMP_StringPtr    specificLang,
                              void *           clientLang,
                              void *           clientValue,
                              XMP_OptionBits * options,
                              SetClientStringProc SetClientString,
                              WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_SetLocalizedText_1 ( XMPMetaRef     xmpRef,
                              XMP_StringPtr  schemaNS,
                              XMP_StringPtr  altTextName,
                              XMP_StringPtr  genericLang,
                              XMP_StringPtr  specificLang,
                              XMP_StringPtr  itemValue,
                              XMP_OptionBits options,
                              WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_DeleteLocalizedText_1 ( XMPMetaRef       xmpRef,
                              XMP_StringPtr    schemaNS,
                              XMP_StringPtr    altTextName,
                              XMP_StringPtr    genericLang,
                              XMP_StringPtr    specificLang,
                              WXMP_Result *    wResult );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_GetProperty_Bool_1 ( XMPMetaRef       xmpRef,
                              XMP_StringPtr    schemaNS,
                              XMP_StringPtr    propName,
                              XMP_Bool *       propValue,
                              XMP_OptionBits * options,
                              WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetProperty_Int_1 ( XMPMetaRef       xmpRef,
                             XMP_StringPtr    schemaNS,
                             XMP_StringPtr    propName,
                             XMP_Int32 *      propValue,
                             XMP_OptionBits * options,
                             WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetProperty_Int64_1 ( XMPMetaRef       xmpRef,
                               XMP_StringPtr    schemaNS,
                               XMP_StringPtr    propName,
                               XMP_Int64 *      propValue,
                               XMP_OptionBits * options,
                               WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetProperty_Float_1 ( XMPMetaRef       xmpRef,
                               XMP_StringPtr    schemaNS,
                               XMP_StringPtr    propName,
                               double *         propValue,
                               XMP_OptionBits * options,
                               WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_GetProperty_Date_1 ( XMPMetaRef       xmpRef,
                              XMP_StringPtr    schemaNS,
                              XMP_StringPtr    propName,
                              XMP_DateTime *   propValue,
                              XMP_OptionBits * options,
                              WXMP_Result *    wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_SetProperty_Bool_1 ( XMPMetaRef     xmpRef,
                              XMP_StringPtr  schemaNS,
                              XMP_StringPtr  propName,
                              XMP_Bool       propValue,
                              XMP_OptionBits options,
                              WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetProperty_Int_1 ( XMPMetaRef     xmpRef,
                             XMP_StringPtr  schemaNS,
                             XMP_StringPtr  propName,
                             XMP_Int32      propValue,
                             XMP_OptionBits options,
                             WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetProperty_Int64_1 ( XMPMetaRef     xmpRef,
                               XMP_StringPtr  schemaNS,
                               XMP_StringPtr  propName,
                               XMP_Int64      propValue,
                               XMP_OptionBits options,
                               WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetProperty_Float_1 ( XMPMetaRef     xmpRef,
                               XMP_StringPtr  schemaNS,
                               XMP_StringPtr  propName,
                               double         propValue,
                               XMP_OptionBits options,
                               WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SetProperty_Date_1 ( XMPMetaRef           xmpRef,
                              XMP_StringPtr        schemaNS,
                              XMP_StringPtr        propName,
                              const XMP_DateTime & propValue,
                              XMP_OptionBits       options,
                              WXMP_Result *        wResult );

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_GetObjectName_1 ( XMPMetaRef    xmpRef,
                           void *        objName,
                           SetClientStringProc SetClientString,
                           WXMP_Result * wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_SetObjectName_1 ( XMPMetaRef    xmpRef,
                           XMP_StringPtr name,
                           WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_GetObjectOptions_1 ( XMPMetaRef    xmpRef,
                              WXMP_Result * wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_SetObjectOptions_1 ( XMPMetaRef     xmpRef,
                              XMP_OptionBits options,
                              WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_Sort_1 ( XMPMetaRef    xmpRef,
                  WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_Erase_1 ( XMPMetaRef    xmpRef,
                   WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_Clone_1 ( XMPMetaRef     xmpRef,
                   XMP_OptionBits options,
                   WXMP_Result *  wResult ) /* const */ ;

extern void
XMP_PUBLIC WXMPMeta_CountArrayItems_1 ( XMPMetaRef    xmpRef,
                             XMP_StringPtr schemaNS,
                             XMP_StringPtr arrayName,
                             WXMP_Result * wResult ) /* const */ ;

#if AdobePrivate
extern void
XMP_PUBLIC WXMPMeta_MarkStaleProperties_1 ( XMPMetaRef     xmpRef,
                                 XMP_OptionBits options,
                                 WXMP_Result *  wResult );
#endif

extern void
XMP_PUBLIC WXMPMeta_DumpObject_1 ( XMPMetaRef         xmpRef,
                        XMP_TextOutputProc outProc,
                        void *             refCon,
                        WXMP_Result *      wResult ) /* const */ ;

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_ParseFromBuffer_1 ( XMPMetaRef     xmpRef,
                             XMP_StringPtr  buffer,
                             XMP_StringLen  bufferSize,
                             XMP_OptionBits options,
                             WXMP_Result *  wResult );

extern void
XMP_PUBLIC WXMPMeta_SerializeToBuffer_1 ( XMPMetaRef     xmpRef,
                               void *         pktString,
                               XMP_OptionBits options,
                               XMP_StringLen  padding,
                               XMP_StringPtr  newline,
                               XMP_StringPtr  indent,
                               XMP_Index      baseIndent,
                               SetClientStringProc SetClientString,
                               WXMP_Result *  wResult ) /* const */ ;

// -------------------------------------------------------------------------------------------------

extern void
XMP_PUBLIC WXMPMeta_SetDefaultErrorCallback_1 ( XMPMeta_ErrorCallbackWrapper wrapperProc,
									 XMPMeta_ErrorCallbackProc    clientProc,
									 void *        context,
									 XMP_Uns32     limit,
                   					 WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_SetErrorCallback_1 ( XMPMetaRef    xmpRef,
                              XMPMeta_ErrorCallbackWrapper wrapperProc,
							  XMPMeta_ErrorCallbackProc    clientProc,
							  void *        context,
							  XMP_Uns32     limit,
							  WXMP_Result * wResult );

extern void
XMP_PUBLIC WXMPMeta_ResetErrorCallbackLimit_1 ( XMPMetaRef    xmpRef,
							  		 XMP_Uns32     limit,
							  		 WXMP_Result * wResult );

// =================================================================================================

#if __cplusplus
} /* extern "C" */
#endif

#endif  // __WXMPMeta_hpp__
