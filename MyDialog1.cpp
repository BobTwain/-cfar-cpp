// MyDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "draw.h"
#include "MyDialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//extern int m_qishi1;
//extern int m_jieshu;
extern WORD *buf;
extern int pointNumb;
extern int m_xianshu;
//extern int m_qishi;
/////////////////////////////////////////////////////////////////////////////
// CMyDialog1 dialog


CMyDialog1::CMyDialog1(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDialog1)
	m_fuxiao = _T("");
	m_zhengda = _T("");
	m_zhengfupingjun = _T("");
	//}}AFX_DATA_INIT
}


void CMyDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialog1)
	DDX_Text(pDX, IDC_EDIT1, m_fuxiao);
	DDX_Text(pDX, IDC_EDIT2, m_zhengda);
	DDX_Text(pDX, IDC_EDIT3, m_zhengfupingjun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialog1, CDialog)
	//{{AFX_MSG_MAP(CMyDialog1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialog1 message handlers

BOOL CMyDialog1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CListCtrl* pmyListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	DWORD dwStyle = GetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE); 
    SetWindowLong( pmyListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);
	
	//设置listctrl可以整行选择和网格条纹
	DWORD styles = pmyListCtrl->GetExtendedStyle();
	pmyListCtrl->SetExtendedStyle(styles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	
	//给listctrl设置2个标题栏
	TCHAR rgtsz[2][20] = {_T("方位线标号"),_T("触发线数")};
	LV_COLUMN lvcolumn;
	CRect rect;

	pmyListCtrl->GetWindowRect(&rect);
	for(int t=0;t<2;t++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT 
			| LVCF_WIDTH | LVCF_ORDER;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[t];
		lvcolumn.iSubItem = t;
		lvcolumn.iOrder = t;
		lvcolumn.cx = rect.Width()/2;

		pmyListCtrl->InsertColumn(t, &lvcolumn);
	}

	CString strText,strText1;

	int aziNum=0,triNum=0,sum=0;
	unsigned short AziVolNow,AziVolNext;

	for (int k=0;k<m_xianshu-1;k++)
	{
		AziVolNow =	buf[k*pointNumb+5158]&0x8000;
		AziVolNext = buf[(k+1)*pointNumb+5158]&0x8000;	
		triNum ++ ;
		
		if (AziVolNow==0 && AziVolNext==0x8000)
		{
			strText.Format(TEXT("方位信号%d"), aziNum);
			pmyListCtrl->InsertItem(aziNum,strText);

			strText1.Format(TEXT("%d"), triNum);
			pmyListCtrl->SetItemText(aziNum, 1, strText1);

			sum+=triNum;
			triNum=0;
			aziNum++;
		}
	}
		strText.Format(TEXT("方位信号%d"), aziNum);
		pmyListCtrl->InsertItem(aziNum,strText);

		strText1.Format(TEXT("%d"), triNum+1);
		pmyListCtrl->SetItemText(aziNum, 1, strText1);

		
		
		strText.Format(TEXT("触发线数总计"));
		pmyListCtrl->InsertItem(aziNum+1,strText);

		strText1.Format(TEXT("%d"), sum+triNum+1);
		pmyListCtrl->SetItemText(aziNum+1, 1, strText1);


	// TODO: Add extra initialization here

	unsigned int f; 
	float zhi;

	int zhengdianshu=0;

	bool biao=true,biao1=true,biao2=false,biao3=false;
	float zhenghe=0.00;
	float zhengzuida=0.00,zhengzuixiao=0.00,zhengpingjun=0.00;

	for(int i=0;i<m_xianshu;i++)
	{
		for (int j=0;j<600;j++)
		{
			f=buf[i*pointNumb+j+5158]&0x3FFF;
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
				{	
					zhengzuida=zhi;
				}
				if(zhi<zhengzuixiao)
					zhengzuixiao=zhi;
			}
		}
	}

	float zhengping=zhenghe/zhengdianshu;

	m_zhengda.Format("%.3f",zhengzuida);
	m_fuxiao.Format("%.3f",zhengzuixiao);
	m_zhengfupingjun.Format("正：%.3f",zhengping);
 

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
