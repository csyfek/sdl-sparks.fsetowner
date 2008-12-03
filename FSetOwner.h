// FSetOwner.h : main header file for the FSETOWNER application
//

#if !defined(AFX_FSETOWNER_H__4AA9FA85_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_)
#define AFX_FSETOWNER_H__4AA9FA85_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFSetOwnerApp:
// See FSetOwner.cpp for the implementation of this class
//

class CFSetOwnerApp : public CWinApp
{
public:
	CFSetOwnerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFSetOwnerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFSetOwnerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSETOWNER_H__4AA9FA85_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_)
