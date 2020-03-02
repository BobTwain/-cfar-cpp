// NengView.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "NengView.h"
#include "MainFrm.h"
#include "Math.h"
#include "DrawView.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
bool drawfromfiledone = false;
bool b_lianfang = false;
WORD *buf=NULL;
int pointNumb;
// int m_qishi;
int lianfang;	//-1非连放状态，0为32幅连放，1为时间序列连放
int m_xianshu=0;
//int m_cha=0;
int cx,cy;
long step;

//float xiuzheng;
//float m_liangcheng;
float m_beishu;
//int m_qishi1=0;
//int m_jieshu=0;
CString str;
extern CString gbLocation;
extern CString gbLocation1;


extern int gbLineNo; 
extern CString strText;

IMPLEMENT_DYNCREATE(CNengView, CFormView)

CNengView::CNengView()
	: CFormView(CNengView::IDD)
{
	//{{AFX_DATA_INIT(CNengView)
	m_strPath = _T("");
	m_nLineNumb = 0;
	m_yanse = 0;
	m_shezhi = 20;
	m_showangle = _T("");
	m_banjing = _T("");
	m_xian = 0;
	m_dianya = _T("");
	m_n = 1.0;
	yuzhi = 20;
	m_liangcheng = 2;
	m_HeadNumb = 0;
	m_beishu = 1.0;
	lianfang = -1;
	m_azinum = 0;
	fengxiang =  0.0f;
	hangxiang =  0.0f;
	ptemp1=(0,0);
	ptemp2=(0,0);
	ptemp3=(0,0);
	ptemp4=(0,0);
	//}}AFX_DATA_INIT	
	
}

CNengView::~CNengView()
{
	if(buf)
	{
			delete []buf;
			buf = NULL;
	}
}

void CNengView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNengView)
	DDX_Control(pDX, IDC_SLIDER1, m_slider1);
	DDX_Control(pDX, IDC_COMBO1, m_strPointNumb);
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
	DDX_Text(pDX, IDC_EDIT2, m_nLineNumb);
	DDX_Radio(pDX, IDC_RADIO1, m_yanse);
	DDX_Text(pDX, IDC_EDIT3, m_shezhi);
	DDX_Text(pDX, IDC_EDIT4, m_showangle);
	DDX_Text(pDX, IDC_EDIT6, m_banjing);
	DDX_Text(pDX, IDC_EDIT8, m_xian);
	DDX_Text(pDX, IDC_EDIT9, m_dianya);
	DDX_Text(pDX, IDC_EDIT11, m_n);
	DDX_Slider(pDX, IDC_SLIDER1, yuzhi);
	DDX_Radio(pDX, IDC_RADIO3, m_liangcheng);
	DDX_Text(pDX, IDC_EDIT5, m_HeadNumb);
	DDX_Text(pDX, IDC_EDIT7, m_azinum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNengView, CFormView)
	//{{AFX_MSG_MAP(CNengView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MESSAGE_DISPLAYLINE,DisPlayLine)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNengView diagnostics

#ifdef _DEBUG
void CNengView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNengView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNengView message handlers

void CNengView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	static char BASED_CODE szFilter[] = "雷达图像数据(*.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);


	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="暂停"))		//如果是连放时暂停连放状态
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"继续");
	}
		
	
	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		
		lianfang=-1;
		if(GetDlgItemText(IDC_BUTTON5,str),str!="暂停")	
		SetDlgItemText(IDC_BUTTON5,"暂停");

		b_lianfang = false;
		UpdateData(false);

		this->OnButton2();
	}

}

void CNengView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	this->m_pFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	// TODO: Add your specialized code here and/or call the base class

	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1300");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1500");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2048");
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("600");
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(3);
	m_slider1.SetRange(1,50,TRUE);
    m_slider1.SetPos(yuzhi);

    UpdateData(false);
}

void CNengView::OnButton2() 
{
    UpdateData(TRUE);

	static const double pi = 3.141592654;
    int Index = m_strPointNumb.GetCurSel();//去的当前下拉菜单的下标
	bool biao1=false;
    bool biao2=false;

    long filelength;

    switch(Index)
	{
	   case 0: 
		   {
			pointNumb=1300;
		    break;
		   }
	   case 1:
		   {
			pointNumb=1500;
		    break;
		   }
       case 2:
		   {
			pointNumb=2048;
		    break;
		   }
        case 3:
		   {
			pointNumb=600;
		    break;
		   }
	   default:
		   break;
	}

	FILE *stream;
	
	if( (stream = fopen( m_strPath, "rb" )) != NULL )
	{	
		fseek(stream, 0L, SEEK_END );
		filelength = ftell(stream);//得到文件的大小
	
        fseek(stream, 0L, SEEK_SET );//定位到文件的开头
		if(buf)
		{
			delete []buf;
			buf=NULL;
		}//动态内存释放

		buf = new WORD[filelength/2];
      
		if(buf==NULL)//没有加载文件
		{
			MessageBox("分配内存出错");
		}
        
	    fread(buf, sizeof(WORD), filelength/2, stream);//读出数据流
		fclose(stream); 

	}
	 		 
	else if(b_lianfang)
	{	 
		KillTimer(1);
		MessageBox("当前时间序列不足32幅图像");
		
		m_nMap--;
		CString pathname = m_strPath.Left(m_strPath.ReverseFind('_'));//将文件名付给pathname
		m_strPath.Format("%s_%02d.dat",pathname,m_nMap);
		return;
	}
	
	else
	{	 
		MessageBox("打开文件错误，请选择文件"); 
		return;
	}
//////////////////////////////////////////////////////////////////////////

	m_xianshu=buf[1557];
	m_nLineNumb=m_xianshu;
    UpdateData(false);

    HDC hMYDC;//定义了一个类型为HDC的变量hMYDC
	hMYDC = ::GetDC(m_pFrm->m_pLeftView->m_hWnd);//获得窗口的设备描述表
	CRect rect;
	::GetClientRect(m_pFrm->m_pLeftView->m_hWnd,&rect);//获得画图的区域，并将rect指向它

	CClientDC dc(m_pFrm->m_pLeftView);//开始画图

	cx = rect.right / 2;
	cy = rect.bottom / 2;

	HPEN hYellowPen = CreatePen(PS_SOLID,1,RGB(255,255,0));//创建一个黄色的画柄
    SelectObject(hMYDC, hYellowPen);//将黄色画柄选到hMYDC
	MoveToEx(hMYDC, cx, cy, NULL);//移动到线条的起点
	LineTo(hMYDC, cx, rect.top );//画黄色船首信号线

    if(cx>cy)//图像与边界的最小像素为10（根据对窗口大小的调整绘制不同大小的图像）
	{
		step = 600/((cy-10))+1;//step是调节大小使用的
	}
	else
	{
		step = 600/((cx-90))+1;
	}
	
/////////////////////////////画风向标志////////////////////////////////
	CPen black(PS_SOLID, 3, RGB(0,0,0));	//擦除上幅留下的风向线迹（创建黑色画笔）
	dc.SelectObject(black);
	dc.MoveTo(ptemp1);
	dc.LineTo(ptemp2);

	dc.MoveTo(ptemp3);
	dc.LineTo(ptemp1);

	dc.MoveTo(ptemp4);
	dc.LineTo(ptemp1);

	hangxiang = (float)GetValue(1,6,4)*180*pow(2,-30);
	fengxiang = (float)GetValue(2,26,2)*180*pow(2,-14);

	float w_angle;	//风向相对艏向的偏移角度
	w_angle = 360-hangxiang+fengxiang;
	if(w_angle-360 > 0.0005)
		w_angle-=360;
	CPoint point1,point2,point3,point4,ptemp;

	point1.x = cx + (600+10)/step*sin(pi*w_angle/180);
	point1.y = cy - (600+10)/step*cos(pi*w_angle/180);

	point2.x = cx + (600+70)/step*sin(pi*w_angle/180);
	point2.y = cy - (600+70)/step*cos(pi*w_angle/180);
	
//////////////////////////////////////////////////////////////////////////
	double Angle = 30*pi/180;	//20度
//	double	proportion = 0.6;
	double	Sin   = sin(Angle),   Cos  = cos(Angle);
	double	Sin2  = sin(-Angle),  Cos2 = cos(-Angle);
	
	ptemp.x = cx + (600+40)/step*sin(pi*w_angle/180);
	ptemp.y = cy - (600+40)/step*cos(pi*w_angle/180);

	int	nTempX	 = ptemp.x-point1.x;
	int nTempY	 = ptemp.y-point1.y;

	point3.x = (int)(nTempX*Cos - nTempY*Sin) + point1.x;//弧的中止点
	point3.y = (int)(nTempX*Sin + nTempY*Cos) + point1.y;
	point4.x = (int)(nTempX*Cos2 - nTempY*Sin2) + point1.x;//弧的中止点
	point4.y = (int)(nTempX*Sin2 + nTempY*Cos2) + point1.y;

//////////////////////////////////////////////////////////////////////////

	CPen pencolor(PS_SOLID, 3, RGB(0,255,255));
	dc.SelectObject(pencolor);

	dc.MoveTo(point1);
	dc.LineTo(point2);

	dc.MoveTo(point3);
	dc.LineTo(point1);

	dc.MoveTo(point4);
	dc.LineTo(point1);
	
	ptemp1 = point1;
	ptemp2 = point2;
	ptemp3 = point3;
	ptemp4 = point4;

//////////////////////////////////////////////////////////////////////////

	this->ZitiInfo();		//显示图像界面的导航信息
	this->SiglCount();		// 计算方位数和船首信号中的触发线数

////////////////////////////显示色标/////////////////////////////////////////////

	m_rect_color.left = (cx-600/step)/3+5;
	m_rect_color.right =m_rect_color.left+20;
	m_rect_color.top = cy-400/step;
	m_rect_color.bottom =cy+ 400/step;

	if(m_yanse==2)				//伪彩时显示色标
	{	
		float ff= 2.5/50*yuzhi;
		float fffvalue = (float)0.18;

		CDC *pDC=CDC::FromHandle(hMYDC);		
		m_colortable.SetValueRange(fffvalue,ff);
		this->m_colortable.DrawColorSpectrumRect(pDC,m_rect_color);
		ReleaseDC(pDC);
	}
	else
	{
		CRect m_rect(m_rect_color);
		m_rect.left=m_rect_color.left-25;//25为色标值的宽度
		m_rect.right=m_rect_color.right;
		m_rect.top=m_rect_color.top-10;
		m_rect.bottom=m_rect_color.bottom+10;
		
		CBrush brush(RGB(0,0,0));
		dc.FillRect(m_rect,&brush);
	}
//////////////////////////////////////////////////////////////////////////

	this->CRadarDraw();		//draw the radar image

//////////////////////////////////////////////////////////////////////////
	
   UpdateData(false);
   drawfromfiledone = true;
   
}

void CNengView::OnRadio1() 
{

	m_yanse=0;
}

void CNengView::OnRadio2() 
{

	m_yanse=1;
}

void CNengView::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	m_yanse=2;
}

void CNengView::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_shezhi=m_slider1.GetPos();
    yuzhi=m_shezhi;
	m_n=2.5/50*m_shezhi;
    UpdateData(false);
	*pResult = 0;
}

void CNengView::DisPlayLine(LPARAM lp, WPARAM wp)
{
	m_showangle = gbLocation;
    m_banjing= gbLocation1;
	m_xian=gbLineNo;
	m_dianya=strText;
	UpdateData(FALSE);

}


void CNengView::OnButton3() 
{
	// TODO: Add your control notification handler code here


 	UpdateData(TRUE);


	static char BASED_CODE szFilter[] = "雷达图像数据(*.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*_01.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="暂停"))
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"继续");
	}

	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
	    m_nMap=1;
		lianfang=0;

		SetDlgItemText(IDC_BUTTON5,"暂停");
		b_lianfang = true;
		UpdateData(false);
	    SetTimer(1, 100, 0);

	}

}

void CNengView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(lianfang==0)
	{

		if(m_nMap>32)
		{
		  KillTimer(1);
		  lianfang =-1;
//		  m_nMap=1;
		  b_lianfang = false;
		  return;
		}
		CString filename1 = m_strPath.Left(m_strPath.ReverseFind('_'));
		CString filename2;
		filename2.Format("%s_%02d.dat",filename1,m_nMap);
		m_strPath =filename2;
		
		UpdateData(false);
		this->OnButton2();

		m_nMap++;
	}

	else if(lianfang==1)
	{
		WIN32_FIND_DATA filedata;
		
		CString filepath1 = m_strPath.Left(m_strPath.ReverseFind('\\'));
		CString filepath2;
		filepath2.Format("%s\\*_01.dat",filepath1);
	
		HANDLE hfind=FindFirstFile(filepath2,&filedata);
		
		CString filepath; 
			
		filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		
		while (m_strPath!=filepath)
		{
			FindNextFile(hfind,&filedata);
			filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		}
		
		UpdateData(false);
		this->OnButton2();
		
		if(FindNextFile(hfind,&filedata)!=0)
		{
		filepath.Format("%s\\%s",filepath1,filedata.cFileName);
		m_strPath=filepath;
		}
		else 
		{
			KillTimer(1);
			lianfang=-1;
			FindClose(hfind);
			b_lianfang = false;
		}		
	}
	
	CFormView::OnTimer(nIDEvent);
}

void CNengView::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	if(lianfang!= -1  && (GetDlgItemText(IDC_BUTTON5,str),str=="暂停"))		//连放->停止
		
	{ 
			KillTimer(1);

			SetDlgItemText(IDC_BUTTON5,"继续");
			b_lianfang = false;
	}

	else if (lianfang!= -1  && (GetDlgItemText(IDC_BUTTON5,str),str=="继续"))	//停止->继续
	{	
		SetTimer(1,100,0);
		SetDlgItemText(IDC_BUTTON5,"暂停");
		b_lianfang = true;
	}
	UpdateData(FALSE);
}

void CNengView::OnButton6() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);


	static char BASED_CODE szFilter[] = "雷达图像数据(*_01.dat)|*.dat|ALL Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,_T("*_01.dat"),OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(lianfang!= -1 && (GetDlgItemText(IDC_BUTTON5,str),str=="暂停"))
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON5,"继续");
	}

	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		lianfang=1;

		SetDlgItemText(IDC_BUTTON5,"暂停");
		b_lianfang = true;
		UpdateData(false);

	    SetTimer(1, 100, 0);
	}

}


void CNengView::OnRadio3() 
{
	// TODO: Add your control notification handler code here

	m_liangcheng = 0;
	m_beishu = 3.0;

}

void CNengView::OnRadio4() 
{
	// TODO: Add your control notification handler code here

	m_liangcheng = 1;
	m_beishu = 1.5;

}

void CNengView::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	m_liangcheng = 2;
	m_beishu = 1.0;
}



void CNengView::SiglCount()
{
	unsigned short H_voltage=0;
	unsigned short aziVolNow,aziVolNext;
	m_HeadNumb=0;
	m_azinum=0;
	
	for(int i=0;i<m_xianshu;i++)
	{
		H_voltage=buf[i*pointNumb+5158]&0x4000;
		
		if (H_voltage==0x4000)
			m_HeadNumb++;
		
		else 
			break;
	} 

	for (int k=0;k<m_xianshu-1;k++)
	{
		aziVolNow =	buf[k*pointNumb+5158]&0x8000;
		aziVolNext = buf[(k+1)*pointNumb+5158]&0x8000;	
		
		if (aziVolNow==0 && aziVolNext==0x8000)
			m_azinum++;
		else 
			continue;
	}
		
}

void CNengView::CRadarDraw()
{
	
	static const double pi = 3.141592654;

	int n=0;
	unsigned short f=0;

	long i,j;
	int color;
	float angle=0.0;

    float zhi1=0.0;////电压值
	float ff= 2.5/50*yuzhi;
	float fffvalue = (float)0.18;

    HDC hMYDC;
	hMYDC = ::GetDC(m_pFrm->m_pLeftView->m_hWnd);
    

if (m_beishu==1.0||m_beishu==1.5)	//draw the radar image in 1.5 or 2.4 sea miles
{

	for(i=0;i<m_xianshu;i++)
	{
		
		angle+=(360.0/m_xianshu); //将360度用总线数平分
		for(j=0;j<600/m_beishu;j++)
		{ 
			
			int cx1=int(cx+(j)*(m_beishu/step)*sin(pi*angle/180.0));
			int cy1=int(cy-(j)*(m_beishu/step)*cos(pi*angle/180.0));
			f=buf[i*pointNumb+j+5158]&0x3fff;//读出所画线的点数					
			zhi1=(float)f*2.5/8191.0;//读出该点的电压值
			if(m_yanse==0)//选择彩色时
			{	
				if(zhi1>ff)//电压值高于设置时
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));//将高于设置电压点设置为黄色
				}
				else 
				{									
					color=zhi1*255/ff;//电压低于设置时
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));//
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,255));//将低于点设置为蓝色
					
				}
				
			}
			else if(m_yanse==1)//选择黑白时
			{ 
				if(zhi1>ff)//高于设置的
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));//讲高于设置点电压得点画成白色
				}
				else 
				{
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}
			}
			
			else//当选择为伪彩时
			{										
			
				if(zhi1>ff)
				{
					zhi1=ff;
				}  // 增加一判断避免绘彩图时出错
				
				if(zhi1>=fffvalue)
				{	
					m_clrMapColor=m_colortable.LookUpColor((float)zhi1);
					SetPixel(hMYDC,cx1, cy1,m_clrMapColor);
				}
				else
				{
					SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));//画成黑色
				}	
			}
		}
		
	}	

}  

if (m_beishu==3.0)				//显示0.75海里雷达图像
{
	for(i=0;i<m_xianshu;i++)
	{
		
		angle+=(360.0/m_xianshu);
		for(int k=0;k<600/step;k++)		//j==200点
		{ 
			
			int j=k*step/m_beishu;
			int	cx1=int(cx+k*sin(pi*angle/180.0));
			int	cy1=int(cy-k*cos(pi*angle/180.0));
			
			
			f=buf[i*pointNumb+j+5158]&0x3fff;					
			zhi1=(float)f*2.5/8191.0;		//200点的对应电压值,8191是干啥的
			if(m_yanse==0)
			{	
				if(zhi1>ff)
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));
				}
				else 
				{									
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,0));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,255));
					
				}
				
			}
			else if(m_yanse==1)
			{ 
				if(zhi1>ff)
				{
					color=255;
					SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
				}
				else 
				{
					color=zhi1*255/ff;
					if(color>100) 
					{
						SetPixel(hMYDC,cx1,cy1,RGB(color,color,color));
					}
					else  
						SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}
			}
			else
			{										
				
				if(zhi1>ff)
				{
					zhi1=ff;
				}  
				
				if(zhi1>=fffvalue)
				{	
					m_clrMapColor=m_colortable.LookUpColor((float)zhi1);
					SetPixel(hMYDC,cx1, cy1,m_clrMapColor);
				}
				else
				{
					SetPixel(hMYDC,cx1,cy1,RGB(0,0,0));
				}	
			}
			
		}
		
	}	

}
 
   m_pFrm->m_pLeftView->Diaplay1();

}

CNengView::GetValue(short flag, short position, short length)
{					//flag-导航信息组数标志，position-信息在相应导航组的偏移
					//length为信息的长度
	int value1=0;
	short value2=0;
	DWORD a[2]={0,0};

	if(flag==1)				//flag==1,导航信息1;
	{	
		int i=6+position/2;//buf为word数组，故将position除2;
		
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
		int i=1507+position/2;
		
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




void CNengView::ZitiInfo()
{
////////////////show the current filename/navInfomation on the LeftView //////////////
	
	CString filename1 = m_strPath.Right(strlen(m_strPath) - m_strPath.ReverseFind('\\')-1);
	CString filename2 = filename1.Left(filename1.ReverseFind('.'));

	CRect rect;
	::GetClientRect(m_pFrm->m_pLeftView->m_hWnd,&rect);
	
	CClientDC dc(m_pFrm->m_pLeftView);
	CFont font;
	font.CreatePointFont(320/step,"楷体_GB2312",NULL);
	CFont * pOldFont = dc.SelectObject(&font);
	
//	dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(RGB(0,0,0));
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(20,20,filename2);

//  注：以下导航信息后留空格是覆盖刷新上附图所留的信息

	m_hangsu.Format("航速:%+.2f节   ",(float)GetValue(2,18,2)*0.01);
	dc.TextOut(rect.right-185,10,m_hangsu);	
	m_hangxiang.Format("航向:%.2f°   ",(float)GetValue(1,6,4)*180*pow(2,-30));
	dc.TextOut(rect.right-200,35,m_hangxiang);
	m_fengsu.Format("风速:%.2fm/s   ",(float)GetValue(2,28,2)*0.01);
	dc.TextOut(rect.right-185,60,m_fengsu);
	m_fengxiang.Format("风向:%.2f°   ",(float)GetValue(2,26,2)*180*pow(2,-14));
	dc.TextOut(rect.right-160,85,m_fengxiang);
//纵横摇一个空格，其它3空格
	m_zongyao.Format("纵摇:%+.2f° ",(float)GetValue(1,10,4)*90*pow(2,-30));
	dc.TextOut(10,rect.bottom-110,m_zongyao);
	m_hengyao.Format("横摇:%+.2f° ",(float)GetValue(1,14,4)*90*pow(2,-30));
	dc.TextOut(40,rect.bottom-80,m_hengyao);
	m_haishen.Format("海深:%.2fm   ",(float)GetValue(2,14,4)*0.01);
	dc.TextOut(25,rect.bottom-50,m_haishen);
//两个空格
	m_dongsu.Format("东速:%+.2f节  ",(float)GetValue(2,22,2)*0.01);
		dc.TextOut(rect.right-150,rect.bottom-110,m_dongsu);
	m_beisu.Format("北速:%+.2f节  ",(float)GetValue(2,24,2)*0.01);
		dc.TextOut(rect.right-170,rect.bottom-80,m_beisu);
	m_disu.Format("地速:%.2f节  ",(float)GetValue(2,20,2)*0.01);
		dc.TextOut(rect.right-160,rect.bottom-50,m_disu);
	
	dc.SelectObject(pOldFont);

/////////////////////////////////////////////////////////////////////////////////
}
