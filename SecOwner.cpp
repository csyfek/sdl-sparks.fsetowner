// SecOwner.cpp: implementation of the CSecOwner class.
//
// (c) 2000 Andreas Saurwein, Secowner@uniwares.net
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SecOwner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define SD_SIZE (65536 + SECURITY_DESCRIPTOR_MIN_LENGTH)
#define FULLCOPY	0

CSecOwner::CSecOwner()
{

}

CSecOwner::~CSecOwner()
{

}

BOOL CSecOwner::SetFileOwner(LPSTR UserName, LPSTR pFileName)
{
    // SID variables
	
	char          psnuType[2048];
	char          lpszDomain[2048];
	DWORD         dwDomainLength = 250;
	char          UserSID[1024];
	DWORD         dwSIDBufSize=1024;
	
	if (!LookupAccountName((LPSTR) NULL,
		UserName,
		UserSID,
		&dwSIDBufSize,
		&lpszDomain[0],
		&dwDomainLength,
		(PSID_NAME_USE)psnuType))
	{
		return FALSE;
	}
	
	if ( ! AssertRestore() ) 
	{
		return FALSE;
	}

	return SetFileOwnerSID((LPBYTE)&UserSID[0], pFileName);
}

BOOL CSecOwner::SetFileOwnerSID(LPBYTE UserSID, LPSTR pFileName)
{
	// File SD variables
	
	UCHAR          ucSDbuf[SD_SIZE];
	PSECURITY_DESCRIPTOR pFileSD=(PSECURITY_DESCRIPTOR)ucSDbuf;
	DWORD          dwSDLengthNeeded;
	
	// New SD variables
	
	UCHAR                NewSD[SECURITY_DESCRIPTOR_MIN_LENGTH];
	PSECURITY_DESCRIPTOR psdNewSD=(PSECURITY_DESCRIPTOR)NewSD;
	
	// STEP 1: Get security descriptor (SD) for file
	
	if(!GetFileSecurity(pFileName,
		(SECURITY_INFORMATION)(OWNER_SECURITY_INFORMATION),
		pFileSD,
		SD_SIZE,
		(LPDWORD)&dwSDLengthNeeded))
	{
		ErrorMessage(GetLastError());
		return(FALSE);
	}
	
	// STEP 2: Initialize new SD
	
	if(!InitializeSecurityDescriptor(psdNewSD,SECURITY_DESCRIPTOR_REVISION))
	{
		ErrorMessage(GetLastError());
		return(FALSE);
	}
	
	// STEP 3: Get DACL from SD
	
	if(!SetSecurityDescriptorOwner(psdNewSD,UserSID,0))
	{
		ErrorMessage(GetLastError());
		return(FALSE);
	}
	
	// STEP 4: Set the SD to the File
	
	if (!SetFileSecurity(pFileName, OWNER_SECURITY_INFORMATION,psdNewSD))
	{
		ErrorMessage(GetLastError());
		return(FALSE);
	}
	
	return TRUE; 
}

BOOL CSecOwner::AssertRestore()
{
	HANDLE hToken; 
	LUID RestoreValue; 
	TOKEN_PRIVILEGES tkp; 

	/* Retrieve a handle of the access token.           */ 

	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, 
		&hToken)) 
	{ 
		ErrorMessage(GetLastError());
		return FALSE; 
	} 

	/* 
	* Enable the SE_RESTORE_NAME privilege or 
	* disable all privileges, depending on the fEnable 
	* flag. 
	*/ 

	if (!LookupPrivilegeValue((LPSTR) NULL, 
		SE_RESTORE_NAME, 
		&RestoreValue)) 
	{ 
		ErrorMessage(GetLastError());
		return FALSE; 
	} 

	tkp.PrivilegeCount = 1; 
	tkp.Privileges[0].Luid = RestoreValue; 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	AdjustTokenPrivileges(hToken, 
		FALSE, 
		&tkp, 
		sizeof(TOKEN_PRIVILEGES), 
		(PTOKEN_PRIVILEGES) NULL, 
		(PDWORD) NULL); 

		/* 
		* The return value of AdjustTokenPrivileges cannot 
		* be tested. 
	*/ 

	if (GetLastError() != ERROR_SUCCESS)
	{
		ErrorMessage(GetLastError());
		return FALSE; 
	} 

	return TRUE; 
	
}

void CSecOwner::ErrorMessage(DWORD err)
{
	LPVOID lpMsgBuf;
	FormatMessage(  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM |     
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					err,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
	// ...// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}
