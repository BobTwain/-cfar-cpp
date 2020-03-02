// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "draw.h"
#include "MyDialog.h"
#include "DrawView.h"
#include "NengView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int gbLineNo;
extern WORD *buf;
//extern int m_qishi;
extern int pointNumb;
//extern int m_cha;
extern int cx,cy;
extern int m_xianshu;
extern float m_beishu;
extern long step;
/////////////////////////////////////////////////////////////////////////////
// CMyDialog dialog


CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDialog)
	m_zhengfuping = _T("");
	m_zhengzuida = _T("");
	m_zhengzuixiao = _T("");
	//}}AFX_DATA_INIT
}


void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialog)
	DDX_Text(pDX, IDC_EDIT4, m_zhengfuping);
	DDX_Text(pDX, IDC_EDIT5, m_zhengzuida);
	DDX_Text(pDX, IDC_EDIT6, m_zhengzuixiao);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	//{{AFX_MSG_MAP(CMyDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialog message handlers

BOOL CMyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	static const double pi = 3.141592654;
	// TODO: Add extra initialization here
	CListCtrl* pmyListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	DWORD dwStyle = GetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE); 
    SetWindowLong( pmyListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);
	
	//设置listctrl可以整行选择和网格条纹
	DWORD styles = pmyListCtrl->GetExtendedStyle();
	pmyListCtrl->SetExtendedStyle(styles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	
	//给listctrl设置3个标题栏
	TCHAR rgtsz[4][10] = {_T("标号"),_T("十六进制"),_T("电压值"),_T("海里")};
	LV_COLUMN lvcolumn;
	CRect rect;
    int i=0;
	pmyListCtrl->GetWindowRect(&rect);
	for(i=0;i<4;i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT 
			| LVCF_WIDTH | LVCF_ORDER;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		lvcolumn.cx = rect.Width()/4;

		pmyListCtrl->InsertColumn(i, &lvcolumn);
	}
	CString strText,strText1,strText2,strText3;
	unsigned int f;
	float zhi;
	int zhengdianshu=0,fudianshu=0;
	bool biao=true,biao1=true,biao2=false,biao3=false;
	float zhenghe=0.00,fuhe=0.00;
	float zhengzuida=0.00,zhengzuixiao=0.00,fuzuida=0.00,fuzuixiao=0.00,zhengpingjun=0.00,fupingjun=0.00;
	for (i=0;i<600/m_beishu;i++)
	{		
		f=buf[gbLineNo*pointNumb+i+5158]&0x3FFF;
   
        zhi=(float)f*2.5/8191.0;
   
		if((zhi>0)&&biao)
		{
				
				zhengzuida=zhi;
				zhengzuixiao=zhi;
				biao=false;
				biao2=true;
		}

	

		if((zhi>0)&&biao2)
		{
			zhengdianshu++;
			zhenghe+=zhi;
			if(zhi>zhengzuida)
				zhengzuida=zhi;
			if(zhi<zhengzuixiao)
				zhengzuixiao=zhi;
		}	
		
		strText.Format(TEXT("点数 %d"), i);
//		pmyListCtrl->InsertItem(LVIF_TEXT|LVIF_STATE, i, strText, 
//			zhi<=0.3 ? LVIS_SELECTED : 0, LVIS_SELECTED,0, 0);

		pmyListCtrl->InsertItem(i,strText);

		strText1.Format("%x",buf[gbLineNo*pointNumb+i+5158]);
		pmyListCtrl->SetItemText(i, 1, strText1);
		strText2.Format("%.3f",zhi);
		pmyListCtrl->SetItemText(i, 2, strText2);
		float angle=0.0;
		angle=(float)(gbLineNo*360.0/m_xianshu);
		int cx1=int(cx+(i)*(m_beishu/step)*sin(pi*angle/180.0));
		int cy1=int(cy-(i)*(m_beishu/step)*cos(pi*angle/180.0));
		float u = cx1-cx;
		float v = cy-cy1;
		float radius = sqrt(pow(u,2)+pow(v,2));

		radius=radius*(2.43/m_beishu)/(600.0/step);

		strText3.Format("%.3f",radius);
		pmyListCtrl->SetItemText(i, 3, strText3);
	}

	float zhengping=zhenghe/zhengdianshu;
	m_zhengzuida.Format("%.3f",zhengzuida);
	m_zhengzuixiao.Format("%.3f",zhengzuixiao);
//	m_zhengfudian.Format("正：%d",zhengdianshu);

	m_zhengfuping.Format("正：%.3f",zhengping);
		
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
		// EXCEPTION: OCX Property Pages should return FALSE
}


