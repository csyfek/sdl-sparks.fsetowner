// FSetOwnerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FSetOwner.h"
#include "FSetOwnerDlg.h"
#include "Info.h"
#include "SecOwner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFSetOwnerDlg dialog

CFSetOwnerDlg::CFSetOwnerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFSetOwnerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFSetOwnerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFSetOwnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFSetOwnerDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Users);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFSetOwnerDlg, CDialog)
	//{{AFX_MSG_MAP(CFSetOwnerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnSet)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFSetOwnerDlg message handlers

BOOL CFSetOwnerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_Tree.Initialize();

	CStringArray ar;
	CInfo::SecGetGroups(ar);
	for(int i = 0; i < ar.GetSize(); m_Users.AddString(ar[i++]))
		;
	m_Users.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFSetOwnerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFSetOwnerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFSetOwnerDlg::OnSet() 
{
	CString cs = m_Tree.GetFullPath(m_Tree.GetSelectedItem());
	CString usr;

	m_Users.GetLBText(m_Users.GetCurSel(), usr);

	CSecOwner sec;

	sec.SetFileOwner(LPSTR(LPCSTR(usr)), LPSTR(LPCSTR(cs)));
}

void CFSetOwnerDlg::OnSize(UINT nType, int cx, int cy) 
{
	if(GetDlgItem(IDC_TREE1) != NULL && ::IsWindow(GetDlgItem(IDC_TREE1)->m_hWnd))
	{
		CRect rc, rc1, rc2, rc3, rc4, rc5;

		GetWindowRect(rc);

		GetDlgItem(IDC_TREE1)->GetWindowRect(rc1);
		GetDlgItem(IDC_TITLE)->GetWindowRect(rc2);
		GetDlgItem(IDC_COMBO1)->GetWindowRect(rc3);
		GetDlgItem(IDOK)->GetWindowRect(rc4);
		GetDlgItem(IDCANCEL)->GetWindowRect(rc5);

		ScreenToClient(rc1);
		ScreenToClient(rc2);
		ScreenToClient(rc3);
		ScreenToClient(rc4);
		ScreenToClient(rc5);

		rc1.right  = cx - 8;
		rc1.bottom = cy - 8 - rc3.Height() - 8;
		if(rc1.Height() < 32)
			return;
		GetDlgItem(IDC_TREE1)->SetWindowPos(NULL, NULL, NULL, rc1.Width(), rc1.Height(), SWP_NOMOVE|SWP_NOZORDER);

		rc2.top = cy - 8 - rc3.Height();
		rc3.top = cy - 8 - rc3.Height();
		rc4.top = cy - 8 - rc3.Height();
		rc5.top = cy - 8 - rc3.Height();
		rc5.left = cx - 8 - rc5.Width();
		if(rc5.left < rc4.left + rc4.Width() + 6)
			rc5.left = rc4.left + rc4.Width() + 6;

		GetDlgItem(IDC_TITLE)->SetWindowPos	(NULL, rc2.left, rc2.top, rc2.Width(), rc2.Height(), SWP_NOSIZE|SWP_NOZORDER);
		GetDlgItem(IDC_COMBO1)->SetWindowPos(NULL, rc3.left, rc3.top, rc3.Width(), rc3.Height(), SWP_NOSIZE|SWP_NOZORDER);
		GetDlgItem(IDOK)->SetWindowPos		(NULL, rc4.left, rc4.top, rc4.Width(), rc4.Height(), SWP_NOSIZE|SWP_NOZORDER);
		GetDlgItem(IDCANCEL)->SetWindowPos	(NULL, rc5.left, rc5.top, rc5.Width(), rc5.Height(), SWP_NOSIZE|SWP_NOZORDER);

	}
	CDialog::OnSize(nType, cx, cy);
}
