// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Draw.h"

#include "MainFrm.h"
#include"DrawView.h"

#include"NengView.h"

extern bool drawfromfiledone;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_NAVINFO, OnNavinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


    CMainFrame::GetPointer();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.x = 0;/////初始位置
	cs.y = 0;
    cs.style = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME
		| WS_SYSMENU | WS_MINIMIZEBOX |  WS_MAXIMIZE;
	cs.cx=GetSystemMetrics(SM_CXMAXIMIZED);
	cs.cy=GetSystemMetrics(SM_CYMAXIMIZED);

	cs.lpszName = "雷达图像600个点显示软件Ver1.06";
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
 	
	BOOL bCreateSpltr = m_window1.CreateStatic(this,1,2);

	m_window1.SetColumnInfo(0,cx*3/4,100);
	m_window1.SetColumnInfo(1,cx*1/4,100);

	m_window1.CreateView(0,0,RUNTIME_CLASS(CDrawView), CSize(cx*3/4,cy), pContext);
	m_window1.CreateView(0,1,RUNTIME_CLASS(CNengView), CSize(cx*1/4,cy), pContext);

    return (bCreateSpltr);
}

void CMainFrame::GetPointer()
{
	CWnd *pWnd = NULL;
	
	pWnd = this->m_window1.GetPane(0,0);
	this->m_pLeftView = DYNAMIC_DOWNCAST(CDrawView,pWnd);
	
	pWnd = this->m_window1.GetPane(0,1);
	this->m_pRightView = DYNAMIC_DOWNCAST(CNengView, pWnd);
}

void CMainFrame::OnNavinfo() 
{
	// TODO: Add your command handler code here
	if (drawfromfiledone)
	{	
		CNavDialog	navdlg;//构造CNavDialog类的对象
		navdlg.DoModal();//让对话框显示
	}
	else
		MessageBox("请先选择图像文件");
}
