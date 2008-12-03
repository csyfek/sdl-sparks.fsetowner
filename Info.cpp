// Info.cpp: implementation of the CInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fsetowner.h"
#include "Info.h"
#include <winnetwk.h>
#include <lmaccess.h>
#include <lmerr.h>
#include <lmapibuf.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInfo::CInfo()
{

}

CInfo::~CInfo()
{

}

void CInfo::SecGetGroups(CStringArray& arGroups)
{
	DWORD	dwGlobalEntries=0; 
	DWORD	dwRet;
	DWORD	i;
	LPBYTE  pdcname;

	//
	// get the global groups from this computer
	//
	//PNET_DISPLAY_GROUP	pGroup;
	dwRet = NetGetAnyDCName(NULL,    NULL,  &pdcname);
	if(dwRet != NERR_Success)
		pdcname = NULL;

	PNET_DISPLAY_USER	pUser;
	dwRet = NetQueryDisplayInformation((LPCWSTR)pdcname,				// pointer to server to get information from
										1,					// level of information to retrieve
										0,					// index of first entry to get information for
										128,				// number of entries to get information for
										16384,				// preferred maximum size, in bytes, of returned buffer
										&dwGlobalEntries,	// receives number of entries for which information is returned
										//(PVOID *)&pGroup);	// receives pointer to system-allocated buffer
										(PVOID *)&pUser);	// receives pointer to system-allocated buffer
									   

	if(dwRet != NERR_Success)
	{
		return;
	}
	for(i = 0; i < dwGlobalEntries; i++)
		arGroups.Add(pUser[i].usri1_name);

	NetApiBufferFree(pdcname);
	NetApiBufferFree(pUser);
}
