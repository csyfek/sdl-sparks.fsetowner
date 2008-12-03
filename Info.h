// Info.h: interface for the CInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFO_H__394E5702_C2B6_11D2_BAA4_0000E829B15A__INCLUDED_)
#define AFX_INFO_H__394E5702_C2B6_11D2_BAA4_0000E829B15A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInfo  
{
public:
	static void SecGetGroups(CStringArray& arGroups);
	CInfo();
	virtual ~CInfo();

};

#endif // !defined(AFX_INFO_H__394E5702_C2B6_11D2_BAA4_0000E829B15A__INCLUDED_)
