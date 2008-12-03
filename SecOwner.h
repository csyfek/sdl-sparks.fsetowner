// SecOwner.h: interface for the CSecOwner class.
//
// (c) 2000 Andreas Saurwein, Secowner@uniwares.net
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECOWNER_H__6BAF2374_CB27_11D2_87C0_00105A01CDEB__INCLUDED_)
#define AFX_SECOWNER_H__6BAF2374_CB27_11D2_87C0_00105A01CDEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSecOwner  
{
public:
	void ErrorMessage(DWORD err);
	BOOL AssertRestore(void);
	BOOL SetFileOwnerSID(LPBYTE UserSID, LPSTR pFileName);
	BOOL SetFileOwner(LPSTR UserName, LPSTR pFileName);
	CSecOwner();
	virtual ~CSecOwner();

};

#endif // !defined(AFX_SECOWNER_H__6BAF2374_CB27_11D2_87C0_00105A01CDEB__INCLUDED_)
