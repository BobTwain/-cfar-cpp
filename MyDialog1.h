#if !defined(AFX_MYDIALOG1_H__485F8527_B04A_405E_88FD_E57320AA1170__INCLUDED_)
#define AFX_MYDIALOG1_H__485F8527_B04A_405E_88FD_E57320AA1170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDialog1 dialog

class CMyDialog1 : public CDialog
{
// Construction
public:
	CMyDialog1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDialog1)
	enum { IDD = IDD_DIALOG2 };
	CString	m_fuxiao;
	CString	m_zhengda;
	CString	m_zhengfupingjun;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialog1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDialog1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG1_H__485F8527_B04A_405E_88FD_E57320AA1170__INCLUDED_)
