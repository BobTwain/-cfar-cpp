#if !defined(AFX_NAVDIALOG_H__861453B5_D48C_4674_A9EA_A62AB76C73F4__INCLUDED_)
#define AFX_NAVDIALOG_H__861453B5_D48C_4674_A9EA_A62AB76C73F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavDialog dialog


class CNavDialog : public CDialog
{
// Construction
	
	union FourUnion
	{
		int shouxiang;
		int zongyao;
		int hengyao;
		char a[4];
	}data;

public:
	CNavDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNavDialog)
	enum { IDD = IDD_NAVDIALOG };
	CString	m_shouxiang;
	CString	m_zongyao;
	CString	m_hengyao;
	CString	m_zitaiflag;
	CString	m_shujuflag;
	short	m_group1now;		//导航信息1当前组数
	short	m_group1total;
	short	m_group2total;
	CString	m_jingdu;
	CString	m_jingduflag;
	CString	m_weidu;
	CString	m_haishen;
	CString	m_hangsu;
	CString	m_disu;
	CString	m_dongsu;
	CString	m_beisu;
	CString	m_fengxiang;
	CString	m_fengsu;
	CString	m_weiduflag;
	CString	m_haishenflag;
	CString	m_hangsuflag;
	CString	m_disuflag;
	CString	m_dongsuflag;
	CString	m_beisuflag;
	CString	m_fengxiangflag;
	CString	m_fengsuflag;
	short	m_group2now;
	float	m_shouxiangmax;
	float	m_shouxiangmin;
	float	m_zongyaomax;
	float	m_hengyaomax;
	float	m_zongyaomin;
	float	m_hengyaomin;
	short	m_zushu1;
	short	m_zushu2;
	short	m_zushu3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	float hengyao[150];
	float zongyao[150];
	float shouxiang[150];

	CRect rect;
	CPoint point1,point2;

	GetValue(short flag,short position,short length);
	// Generated message map functions
	//{{AFX_MSG(CNavDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnBack1();
	afx_msg void OnNext1();
	afx_msg void OnBack2();
	afx_msg void OnNext2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Paint3();
	void Paint2();
	void Paint1();
	void InitCount();

	short flag1;
	short flag2;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVDIALOG_H__861453B5_D48C_4674_A9EA_A62AB76C73F4__INCLUDED_)
