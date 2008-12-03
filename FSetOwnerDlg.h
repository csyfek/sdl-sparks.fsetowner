// FSetOwnerDlg.h : header file
//

#if !defined(AFX_FSETOWNERDLG_H__4AA9FA87_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_)
#define AFX_FSETOWNERDLG_H__4AA9FA87_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFSetOwnerDlg dialog
#include "Dirtreectrl.h"

class CFSetOwnerDlg : public CDialog
{
// Construction
public:
	CFSetOwnerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFSetOwnerDlg)
	enum { IDD = IDD_FSETOWNER_DIALOG };
	CComboBox	m_Users;
	CDirTreeCtrl	m_Tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFSetOwnerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFSetOwnerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSet();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSETOWNERDLG_H__4AA9FA87_CA6F_11D2_87C0_00105A01CDEB__INCLUDED_)
