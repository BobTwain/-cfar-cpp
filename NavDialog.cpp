// NavDialog.cpp : implementation file
//

#include "stdafx.h"
#include "draw.h"
#include "NavDialog.h"

#include "NengView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern WORD *buf;

/////////////////////////////////////////////////////////////////////////////
// CNavDialog dialog


CNavDialog::CNavDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNavDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNavDialog)
	m_shouxiang = _T("");
	m_zongyao = _T("");
	m_hengyao = _T("");
	m_zitaiflag = _T("");
	m_shujuflag = _T("");
	m_group1now = 1;
	m_group1total = 0;
	m_group2total = 0;
	m_jingdu = _T("");
	m_jingduflag = _T("");
	m_weidu = _T("");
	m_haishen = _T("");
	m_hangsu = _T("");
	m_disu = _T("");
	m_dongsu = _T("");
	m_beisu = _T("");
	m_fengxiang = _T("");
	m_fengsu = _T("");
	m_weiduflag = _T("");
	m_haishenflag = _T("");
	m_hangsuflag = _T("");
	m_disuflag = _T("");
	m_dongsuflag = _T("");
	m_beisuflag = _T("");
	m_fengxiangflag = _T("");
	m_fengsuflag = _T("");
	m_group2now = 1;
	m_shouxiangmax = 0.0f;
	m_shouxiangmin = 0.0f;
	m_zongyaomax = 0.0f;
	m_hengyaomax = 0.0f;
	m_zongyaomin = 0.0f;
	m_hengyaomin = 0.0f;
	m_zushu1 = 0;
	m_zushu2 = 0;
	m_zushu3 = 0;
	//}}AFX_DATA_INIT
}


void CNavDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavDialog)
	DDX_Text(pDX, IDC_EDIT2, m_shouxiang);
	DDX_Text(pDX, IDC_EDIT13, m_zongyao);
	DDX_Text(pDX, IDC_EDIT14, m_hengyao);
	DDX_Text(pDX, IDC_EDIT3, m_zitaiflag);
	DDX_Text(pDX, IDC_EDIT4, m_shujuflag);
	DDX_Text(pDX, IDC_EDIT15, m_group1now);
	DDX_Text(pDX, IDC_EDIT1, m_group1total);
	DDX_Text(pDX, IDC_EDIT16, m_group2total);

	DDX_Text(pDX, IDC_EDIT6, m_jingdu);
	DDX_Text(pDX, IDC_EDIT23, m_jingduflag);
	DDX_Text(pDX, IDC_EDIT7, m_weidu);
	DDX_Text(pDX, IDC_EDIT8, m_haishen);
	DDX_Text(pDX, IDC_EDIT17, m_hangsu);
	DDX_Text(pDX, IDC_EDIT18, m_disu);
	DDX_Text(pDX, IDC_EDIT19, m_dongsu);
	DDX_Text(pDX, IDC_EDIT20, m_beisu);
	DDX_Text(pDX, IDC_EDIT21, m_fengxiang);
	DDX_Text(pDX, IDC_EDIT22, m_fengsu);
	DDX_Text(pDX, IDC_EDIT24, m_weiduflag);
	DDX_Text(pDX, IDC_EDIT25, m_haishenflag);
	DDX_Text(pDX, IDC_EDIT26, m_hangsuflag);
	DDX_Text(pDX, IDC_EDIT27, m_disuflag);
	DDX_Text(pDX, IDC_EDIT28, m_dongsuflag);
	DDX_Text(pDX, IDC_EDIT29, m_beisuflag);
	DDX_Text(pDX, IDC_EDIT30, m_fengxiangflag);
	DDX_Text(pDX, IDC_EDIT31, m_fengsuflag);
	DDX_Text(pDX, IDC_EDIT32, m_group2now);
	DDX_Text(pDX, IDC_EDIT33, m_shouxiangmax);
	DDX_Text(pDX, IDC_EDIT34, m_shouxiangmin);
	DDX_Text(pDX, IDC_EDIT35, m_zongyaomax);
	DDX_Text(pDX, IDC_EDIT37, m_hengyaomax);
	DDX_Text(pDX, IDC_EDIT36, m_zongyaomin);
	DDX_Text(pDX, IDC_EDIT38, m_hengyaomin);
	DDX_Text(pDX, IDC_EDIT39, m_zushu1);
	DDX_Text(pDX, IDC_EDIT40, m_zushu2);
	DDX_Text(pDX, IDC_EDIT41, m_zushu3);

	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_EDIT42, m_group1total);
	DDX_Text(pDX, IDC_EDIT46, m_group1total);
	DDX_Text(pDX, IDC_EDIT50, m_group1total);

	DDX_Text(pDX, IDC_EDIT43, m_zushu1);
	DDX_Text(pDX, IDC_EDIT47, m_zushu1);
	DDX_Text(pDX, IDC_EDIT44, m_zushu2);
	DDX_Text(pDX, IDC_EDIT48, m_zushu2);
	DDX_Text(pDX, IDC_EDIT45, m_zushu3);
	DDX_Text(pDX, IDC_EDIT49, m_zushu3);
}


BEGIN_MESSAGE_MAP(CNavDialog, CDialog)
	//{{AFX_MSG_MAP(CNavDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBack1)
	ON_BN_CLICKED(IDC_BUTTON2, OnNext1)
	ON_BN_CLICKED(IDC_BUTTON7, OnBack2)
	ON_BN_CLICKED(IDC_BUTTON8, OnNext2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavDialog message handlers

BOOL CNavDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_group1total = buf[5];
	m_group2total = buf[1506];

	m_zushu1=m_group1total/4;
	m_zushu2=2*m_zushu1;
	m_zushu3=3*m_zushu1;

	flag1=GetValue(1,4,2);
	flag2=GetValue(2,4,2);

//////////////////导航信息1/////////////////////////////////////////

	m_shouxiang.Format("%.2f°",(float)GetValue(1,6,4)*180*pow(2,-30));
	m_zongyao.Format("%+.3f°",(float)GetValue(1,10,4)*90*pow(2,-30));
	m_hengyao.Format("%+.3f°",(float)GetValue(1,14,4)*90*pow(2,-30));

	m_zitaiflag = (flag1 & 0x01 ? "姿态信息无效":"姿态信息有效");
	m_shujuflag = (flag1 & 0x02 ? "A区数据":"B区数据");

/////////////////导航信息2/////////////////////////////////////////
	
	m_jingdu.Format("%+.2f°",(float)GetValue(2,6,4)*90*pow(2,-30));
	m_jingduflag = (flag2 & 0x01 ? "无效":"有效"); 
	
	m_weidu.Format("%+.2f°",(float)GetValue(2,10,4)*90*pow(2,-30));
	m_weiduflag = (flag2 & 0x02 ? "无效":"有效"); 
	
	m_haishen.Format("%.2fm",(float)GetValue(2,14,4)*0.01);
	m_haishenflag = (flag2 & 0x04 ? "无效":"有效");
	
	m_hangsu.Format("%+.2f节",(float)GetValue(2,18,2)*0.01);
	m_hangsuflag = (flag2 & 0x08 ? "无效":"有效");
	
	m_disu.Format("%.2f节",(float)GetValue(2,20,2)*0.01);
	m_disuflag = (flag2 & 0x10 ? "无效":"有效");

	m_dongsu.Format("%+.2f节",(float)GetValue(2,22,2)*0.01);
	m_dongsuflag = (flag2 & 0x20 ? "无效":"有效");

	m_beisu.Format("%+.2f节",(float)GetValue(2,24,2)*0.01);
	m_beisuflag = (flag2 & 0x40 ? "无效":"有效");
		
	m_fengxiang.Format("%.2f°",(float)GetValue(2,26,2)*180*pow(2,-14));
	m_fengxiangflag = (flag2 & 0x80 ? "无效":"有效");

	m_fengsu.Format("%.2fm/s",(float)GetValue(2,28,2)*0.01);
	m_fengsuflag = (flag2 & 0x100 ? "无效":"有效");

//////////////////////////////////////////////////////////////////////////
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CNavDialog::GetValue(short flag,short position,short length)
{
	int value1=0;
	short value2=0;
	DWORD a[2]={0,0};

	if(flag==1)				//flag==1,导航信息1;
	{	
		int i=6+(m_group1now-1)*9+position/2;//buf为word数组，将position除2;
												
		switch(length)
		{
		case 2:
			
			value2=WORD((buf[i]<<8) | (buf[i]>>8));
				return value2;
			break;			//交换2字节的顺序
			
		case 4:
			
			a[0]=WORD(buf[i]<<8) | (buf[i]>>8);
			a[1]=WORD(buf[i+1]<<8) | (buf[i+1]>>8);
			value1=(a[0]<<16) | a[1];		//组合为4字节形式
				return value1;
			break;		
			
		default:
			return 0;
			break;
		}
	}
	else				//flag==2,导航信息2;
	{
		int i=1507+(m_group2now-1)*15+position/2;
		
		switch(length)
		{
		case 2:
			
			value2=WORD((buf[i]<<8) | (buf[i]>>8));
				return value2;
			break;			//交换2字节的顺序
			
		case 4:
			
			a[0]=WORD(buf[i]<<8) | (buf[i]>>8);
			a[1]=WORD(buf[i+1]<<8) | (buf[i+1]>>8);
			value1=(a[0]<<16) | a[1];		//组合为4字节形式
				return value1;
			break;		
			
		default:
			return 0;
			break;
		}
	}
}


void CNavDialog::OnBack1() 
{
	// TODO: Add your control notification handler code here
	
	m_group1now--;
	
	if(m_group1now<1)
		m_group1now=m_group1total;
	OnInitDialog();
}

void CNavDialog::OnNext1() 
{
	// TODO: Add your control notification handler code here
	
	m_group1now++;
	
	if(m_group1now>m_group1total)
		m_group1now=1;
	OnInitDialog();

}

void CNavDialog::OnBack2() 
{
	// TODO: Add your control notification handler code here
	m_group2now--;

	if (m_group2now<1)
		m_group2now = m_group2total;
	OnInitDialog();
}

void CNavDialog::OnNext2() 
{
	// TODO: Add your control notification handler code here
	m_group2now ++;

	if(m_group2now > m_group2total)
		m_group2now = 1;
	OnInitDialog();
}

HBRUSH CNavDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT3:
		if(flag1&0x01)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT23:
		if(flag2&0x01)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT24:
		if(flag2&0x02)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT25:
		if(flag2&0x04)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT26:
		if(flag2&0x08)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT27:
		if(flag2&0x10)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT28:
		if(flag2&0x20)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT29:
		if(flag2&0x40)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT30:
		if(flag2&0x80)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	case IDC_EDIT31:
		if(flag2&0x100)
			pDC->SetTextColor(RGB(255,0,0));

		break;
	default:
        
		break;
	}	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CNavDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	InitCount();
	Paint1();
	Paint2();
	Paint3();
	UpdateData(false);	
	// Do not call CDialog::OnPaint() for painting messages
}

void CNavDialog::InitCount()
{
	for (int i=0;i<m_group1total;i++)
	{
		data.a[0]=HIBYTE(buf[10+i*9]);
		data.a[1]=LOBYTE(buf[10+i*9]);
		data.a[2]=HIBYTE(buf[9+i*9]);
		data.a[3]=LOBYTE(buf[9+i*9]);
		shouxiang[i]=(float)data.shouxiang*180*pow(2,-30);
		
		data.a[0]=HIBYTE(buf[12+i*9]);
		data.a[1]=LOBYTE(buf[12+i*9]);
		data.a[2]=HIBYTE(buf[11+i*9]);
		data.a[3]=LOBYTE(buf[11+i*9]);
		zongyao[i]=(float)data.zongyao*90*pow(2,-30);
		
		data.a[0]=HIBYTE(buf[14+i*9]);
		data.a[1]=LOBYTE(buf[14+i*9]);
		data.a[2]=HIBYTE(buf[13+i*9]);
		data.a[3]=LOBYTE(buf[13+i*9]);
		hengyao[i]=(float)data.hengyao*90*pow(2,-30);
	}
	
	int f_temp=0;

	m_shouxiangmax=m_shouxiangmin=shouxiang[0];
	m_zongyaomax=m_zongyaomin=zongyao[0];
	m_hengyaomax=m_hengyaomin=hengyao[0];

	for (i=1;i<m_group1total;i++)
	{
		m_shouxiangmax=(m_shouxiangmax>shouxiang[i]?m_shouxiangmax:shouxiang[i]);
		m_shouxiangmin=(m_shouxiangmin<shouxiang[i]?m_shouxiangmin:shouxiang[i]);

		m_zongyaomax=(m_zongyaomax>zongyao[i]?m_zongyaomax:zongyao[i]);
		m_zongyaomin=(m_zongyaomin<zongyao[i]?m_zongyaomin:zongyao[i]);

		m_hengyaomax=(m_hengyaomax>hengyao[i]?m_hengyaomax:hengyao[i]);
		m_hengyaomin=(m_hengyaomin<hengyao[i]?m_hengyaomin:hengyao[i]);
	}
	
}

void CNavDialog::Paint1()
{
	CWnd* pWnd1 = GetDlgItem(IDC_SHOUXIANGJIAO);
	pWnd1->GetClientRect(&rect);

	CPaintDC dc(pWnd1);
	
	// 创建画笔对象
	CPen pPenRed,pPenGreen;	

	pPenRed.CreatePen(PS_SOLID,1,RGB(255,0,0));	
	pPenGreen.CreatePen(PS_SOLID,1,RGB(0,130,0));	

	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(&rect);//绘制背景（着色）	

	// 画背景行列 选择绿色画笔		
	dc.SelectObject(pPenGreen); 

	int i,j,l;
	float iTemp=(rect.bottom-rect.top)/8.0;		//iTemp,jTemp必须为float型
	for (i=1;i<8;i++)
	{
		dc.MoveTo(rect.left,rect.bottom-i*iTemp);
		dc.LineTo(rect.right,rect.bottom-i*iTemp);
	}

	float jTemp = (rect.right-rect.left)/15.0;
	for (j=1;j<=14;j++)
	{
		dc.MoveTo(rect.right-j*jTemp,rect.bottom);
		dc.LineTo(rect.right-j*jTemp,rect.top);
	}
	//画曲线图
	dc.SelectObject(pPenRed);
	float x1=rect.right-rect.left;
	short x2=m_group1total;
	float Xscale=x1/x2;//横坐标百分比

	//绘制曲线
	for(l=0;l<(m_group1total-1);l++) 
	{
		point1.x=Xscale*l+rect.left;
		point1.y=rect.bottom-rect.Height()*(shouxiang[l]-m_shouxiangmin)/(m_shouxiangmax-m_shouxiangmin);
		
		point2.x=Xscale*(l+1)+rect.left;
		point2.y=rect.bottom-rect.Height()*(shouxiang[l+1]-m_shouxiangmin)/(m_shouxiangmax-m_shouxiangmin);
		dc.MoveTo(point1);
		dc.LineTo(point2);	
	}
}

void CNavDialog::Paint2()
{
	CWnd* pWnd1 = GetDlgItem(IDC_ZONGYAOJIAO);
	pWnd1->GetClientRect(&rect);

	CPaintDC dc(pWnd1);
	
	// 创建画笔对象
	CPen pPenRed,pPenGreen;	

	pPenRed.CreatePen(PS_SOLID,1,RGB(255,0,0));	
	pPenGreen.CreatePen(PS_SOLID,1,RGB(0,130,0));	

	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(&rect);//绘制背景（着色）	

	// 画背景行列 选择绿色画笔		
	dc.SelectObject(pPenGreen); 

	int i,j,l;
	float iTemp=(rect.bottom-rect.top)/8.0;
	for (i=1;i<8;i++)
	{
		dc.MoveTo(rect.left,rect.bottom-i*iTemp);
		dc.LineTo(rect.right,rect.bottom-i*iTemp);
	}

	float jTemp = (rect.right-rect.left)/15.0;
	for (j=1;j<=14;j++)
	{
		dc.MoveTo(rect.right-j*jTemp,rect.bottom);
		dc.LineTo(rect.right-j*jTemp,rect.top);
	}
	//画曲线图
	dc.SelectObject(pPenRed);
	float x1=rect.right-rect.left;
	short x2=m_group1total;
	float Xscale=x1/x2;//横坐标百分比

	//绘制曲线
	for(l=0;l<(m_group1total-1);l++) 
	{
		point1.x=Xscale*l+rect.left;
		point1.y=rect.bottom-rect.Height()*(zongyao[l]-m_zongyaomin)/(m_zongyaomax-m_zongyaomin);
		
		point2.x=Xscale*(l+1)+rect.left;
		point2.y=rect.bottom-rect.Height()*(zongyao[l+1]-m_zongyaomin)/(m_zongyaomax-m_zongyaomin);
		dc.MoveTo(point1);
		dc.LineTo(point2);	
	}

}

void CNavDialog::Paint3()
{
	CWnd* pWnd1 = GetDlgItem(IDC_HENGYAOJIAO);
	pWnd1->GetClientRect(&rect);

	CPaintDC dc(pWnd1);
	
	// 创建画笔对象
	CPen pPenRed,pPenGreen;	

	pPenRed.CreatePen(PS_SOLID,1,RGB(255,0,0));	
	pPenGreen.CreatePen(PS_SOLID,1,RGB(0,130,0));	

	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(&rect);//绘制背景（着色）	

	// 画背景行列 选择绿色画笔		
	dc.SelectObject(pPenGreen); 

	int i,j,l;
	float iTemp=(rect.bottom-rect.top)/8.0;
	for (i=1;i<8;i++)
	{
		dc.MoveTo(rect.left,rect.bottom-i*iTemp);
		dc.LineTo(rect.right,rect.bottom-i*iTemp);
	}

	float jTemp = (rect.right-rect.left)/15.0;
	for (j=1;j<=14;j++)
	{
		dc.MoveTo(rect.right-j*jTemp,rect.bottom);
		dc.LineTo(rect.right-j*jTemp,rect.top);
	}
	//画曲线图
	dc.SelectObject(pPenRed);
	float x1=rect.right-rect.left;
	short x2=m_group1total;
	float Xscale=x1/x2;//横坐标百分比

	//绘制曲线
	for(l=0;l<(m_group1total-1);l++) 
	{
		point1.x=Xscale*l+rect.left;
		point1.y=rect.bottom-rect.Height()*(hengyao[l]-m_hengyaomin)/(m_hengyaomax-m_hengyaomin);
		point2.x=Xscale*(l+1)+rect.left;
		point2.y=rect.bottom-rect.Height()*(hengyao[l+1]-m_hengyaomin)/(m_hengyaomax-m_hengyaomin);
		dc.MoveTo(point1);
		dc.LineTo(point2);	
	}
}
