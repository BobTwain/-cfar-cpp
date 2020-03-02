#if !defined(AFX_NENGVIEW_H__E38CC967_9655_4E4B_9300_818BCDEF5899__INCLUDED_)
#define AFX_NENGVIEW_H__E38CC967_9655_4E4B_9300_818BCDEF5899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NengView.h : header file
#include "MyDialog.h"
#define	MESSAGE_DISPLAYLINE		WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CNengView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#include "ColorLookUpTable.h"  

class CMainFrame;

class CNengView : public CFormView
{
protected:
	CNengView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNengView)

// Form Data
public:
	//{{AFX_DATA(CNengView)
	enum { IDD = IDD_FORMVIEW };
	CSliderCtrl	m_slider1;
	CComboBox	m_strPointNumb;
	CString	m_strPath;
	long	m_nLineNumb;
	int		m_yanse;
	int		m_shezhi;
	CString	m_showangle;
	CString	m_banjing;
	int		m_xian;
	CString	m_dianya;
	float	m_n;
	int		yuzhi;
	int		m_liangcheng;
	int		m_HeadNumb;
	short	m_azinum;
	//}}AFX_DATA

// Attributes
public:
     void DisPlayLine(LPARAM lp, WPARAM wp);
     afx_msg void OnButton2();
	CColorLookUpTable m_colortable;

// Operations
public:
	void CRadarDraw();
	void SiglCount();
	int m_nMap;
	int m_nTimer;
	COLORREF m_clrMapColor;
	CRect m_rect_color;


	CMainFrame *m_pFrm;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNengView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNengView();
	GetValue(short flag,short position,short length);
	void ZitiInfo();	//显示图像界面的文件名及导航信息
	CString m_hangxiang;
	CString m_hangsu;
	CString m_fengxiang;
	CString m_fengsu;
	CString m_haishen;
	CString m_dongsu;
	CString m_beisu;
	CString m_disu;
	CString m_zongyao;
	CString m_hengyao;
//private:
//	CColorLookUpTable m_ColorTable;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CNengView)
	afx_msg void OnButton1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnRadio5();
	afx_msg void OnRadio7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CPoint ptemp1,ptemp2,ptemp3,ptemp4;
	float hangxiang;
	float fengxiang;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NENGVIEW_H__E38CC967_9655_4E4B_9300_818BCDEF5899__INCLUDED_)
