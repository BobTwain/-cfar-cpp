// DrawView.cpp : implementation of the CDrawView class
//

#include "stdafx.h"
#include "Draw.h"
#include "MainFrm.h"
#include "DrawDoc.h"
#include "DrawView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawView
extern bool drawfromfiledone;
extern bool b_lianfang;
//extern float xiuzheng;
extern float m_beishu;
extern WORD *buf;
extern int pointNumb;
extern int m_xianshu;
CString gbLocation;
CString gbLocation1;
CString strText;

int gbLineNo = 0; 
//extern int m_qishi;
extern long step;
extern int cx,cy;
IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	//{{AFX_MSG_MAP(CDrawView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView construction/destruction

CDrawView::CDrawView()
{
	// TODO: add construction code here

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView drawing

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); //将pDoc定义为指向CObject的指针
	CRect rc;
	GetClientRect(&rc);
	int	cx = rc.right / 2;
	int cy = rc.bottom / 2;
	if(drawfromfiledone)
	{
	

		CBrush brush1;   // Must initialize!
		brush1.CreateSolidBrush(RGB(0,0,0));   // Black brush.
		CBrush * pTempBrush = NULL;
		CBrush OrigBrush;
		pTempBrush = (CBrush*)pDC->SelectObject(&brush1);// Save original brush.
		pDC->Rectangle(0, 0, rc.Width(), rc.Height());///////////////wln 12.25 21.02 避免每次都重画黑背景
		OrigBrush.FromHandle((HBRUSH)pTempBrush);
		pDC->SelectObject(&OrigBrush);
		
		this->m_pFrm->m_pRightView->OnButton2();
		
	}
	else
	{
     
		CBrush brush1;   // Must initialize!
		brush1.CreateSolidBrush(RGB(0,0,0));   // Black brush.
		CBrush* pTempBrush = NULL;
		CBrush OrigBrush;
 	    pTempBrush = (CBrush*)pDC->SelectObject(&brush1);// Save original brush.
		pDC->Rectangle(0, 0, rc.Width(), rc.Height());///////////////wln 12.25 21.02 避免每次都重画黑背景
     	OrigBrush.FromHandle((HBRUSH)pTempBrush);
	   	pDC->SelectObject(&OrigBrush);
	}
 }

/////////////////////////////////////////////////////////////////////////////
// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawView message handlers

void CDrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	m_pFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	// TODO: Add your specialized code here and/or call the base class
	
}



void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	    static const double pi = 3.141592654;
  
		if(drawfromfiledone)		//画完雷达图后响应消息
		{
			CRect Rect;
			GetClientRect(&Rect);
			CClientDC cclientDC(this);
			OnPrepareDC(&cclientDC);  
			cclientDC.DPtoLP(&point);
			int cx = Rect.right / 2;
			int cy = Rect.bottom / 2;
			float u = point.x-cx;
			float v = cy-point.y;
			float radius = sqrt(pow(u,2)+pow(v,2));
			unsigned int f;
			float zhi=0.0;
			int i=0;
			if(radius<=600.0/step)
			{
				double pai = 3.141592654;
				float angle = 0;
				if((fabs(u)>0.000005)||(fabs(v)>0.000005))
				{
					angle = (float)(90 - atan2(v,u)*180.0/pai);
					if(angle<0)
					{
						angle = 360+angle;
					}
				}
				gbLineNo = (int)(angle/(360.0/m_xianshu));
                i=(int)((point.x-cx)/sin(pi*angle/180.0)*step/m_beishu);
				angle = angle*10;

				radius=radius*(2.43/m_beishu)/(600.0/step);

				gbLocation.Empty();
				gbLocation.Format("%.1f°", angle/10.0);
				this->m_pFrm->m_pRightView->m_showangle.Empty();
		
				gbLocation1.Empty();
                this->m_pFrm->m_pRightView->m_banjing.Empty();
                gbLocation1.Format("%.3f", radius);
            
	            f=buf[gbLineNo*pointNumb+i+5158]&0x3FFF;
		    
				
                zhi=(float)f*2.5/8191.0;
			
				strText.Format("%.3f",zhi);
				::SendMessage(m_pFrm->m_pRightView->m_hWnd,MESSAGE_DISPLAYLINE,0,0);
	
			
			
            }
			
		}
	CView::OnMouseMove(nFlags, point);
}

void CDrawView::Diaplay1()
{
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	int	cx = rc.right / 2;
	int cy = rc.bottom / 2;
	CPen pen(PS_SOLID,1,RGB(0,255,0));
	dc.SelectObject(&pen);
    CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
/*	
	dc.Ellipse(cx-48,cy-48,cx+48,cy+48);
	dc.Ellipse(cx-96,cy-96,cx+96,cy+96);
	dc.Ellipse(cx-144,cy-144,cx+144,cy+144);
	dc.Ellipse(cx-192,cy-192,cx+192,cy+192);
	dc.Ellipse(cx-240,cy-240,cx+240,cy+240);
	dc.Ellipse(cx-288,cy-288,cx+288,cy+288);
*/
	int r=600/(6*step);//将一条线六等分，画六条绿色的园

	dc.Ellipse(cx-r,cy-r,cx+r,cy+r);

	dc.Ellipse(cx-2*r,cy-2*r,cx+2*r,cy+2*r);
 
	dc.Ellipse(cx-3*r,cy-3*r,cx+3*r,cy+3*r);
   
	dc.Ellipse(cx-4*r,cy-4*r,cx+4*r,cy+4*r);
  
	dc.Ellipse(cx-5*r,cy-5*r,cx+5*r,cy+5*r);

	dc.Ellipse(cx-6*r,cy-6*r,cx+6*r,cy+6*r);
}

void CDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(drawfromfiledone&&(!b_lianfang))		//画完雷达图像并且非连放时响应消息
	{
		dlg1.DoModal();
		CView::OnLButtonDown(nFlags, point);
	}
}

void CDrawView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(drawfromfiledone&&(!b_lianfang))
	{
		dlg2.DoModal();
		CView::OnRButtonDown(nFlags, point);
	}
}
