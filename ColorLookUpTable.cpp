// ColorLookUpTable.cpp: implementation of the CColorLookUpTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "draw.h"
#include "ColorLookUpTable.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorLookUpTable::CColorLookUpTable()
{
	m_ValueMin = m_ValueMax = 0;

	m_ColorTable.Add( CColorNode(0.1f,RGB(0, 0, 128)) );
	m_ColorTable.Add( CColorNode(0.2f,RGB(0, 0, 160)) );
	m_ColorTable.Add( CColorNode(0.3f,RGB(0, 0, 254)) );
	m_ColorTable.Add( CColorNode(0.4f,RGB(0, 128, 255)) );
	m_ColorTable.Add( CColorNode(0.5f,RGB(0, 255, 255)) );
	m_ColorTable.Add( CColorNode(0.6f,RGB(0, 255, 1)) );
	m_ColorTable.Add( CColorNode(0.7f,RGB(0, 129, 0)) );
	m_ColorTable.Add( CColorNode(0.8f,RGB(255, 255, 0)) );// 黄
	m_ColorTable.Add( CColorNode(0.9f,RGB(255, 127, 0)) );// 橙
	m_ColorTable.Add( CColorNode(1.0f,RGB(255, 0, 0)) );	


/*

	m_ColorTable.Add( CColorNode(0.1f,RGB(  0,   0, 160)) );
	m_ColorTable.Add( CColorNode(0.2f,RGB(  0,   0, 255)) );
	m_ColorTable.Add( CColorNode(0.3f,RGB(  0, 128, 255)) );
	m_ColorTable.Add( CColorNode(0.4f,RGB(  0, 255, 255)) );
	m_ColorTable.Add( CColorNode(0.5f,RGB(  0, 128,   0)) );
	m_ColorTable.Add( CColorNode(0.6f,RGB(128, 255,   0)) );
	m_ColorTable.Add( CColorNode(0.7f,RGB(255, 255,   0)) );
	m_ColorTable.Add( CColorNode(0.8f,RGB(255, 128,   0)) );
	m_ColorTable.Add( CColorNode(0.9f,RGB(128,   0,   0)) );
	m_ColorTable.Add( CColorNode(1.0f,RGB(255,   0,   0)) );
*/	
}

CColorLookUpTable::~CColorLookUpTable()
{

}

//根据pos的位置找出在ColorTable中对应的颜色,
//pos为0～1的值
COLORREF CColorLookUpTable::GetColor(float pos) const
{
	ASSERT( pos>=0.f && pos<=1.0f );
	
	int count=m_ColorTable.GetSize();

	if(pos<=m_ColorTable.GetAt(0).pos)
		return m_ColorTable.GetAt(0).color;
		
	float ps = 0;
	
	for(int i=0; i<count; i++)
	{
		ps = m_ColorTable[i].pos;

		if( pos <= ps)
		{
			return m_ColorTable[i].color;
		}
		else if( pos > ps )
		{
			continue;
		}
	}

	return m_ColorTable.GetAt(count-1).color;
}


 //在颜色表中查询v值的颜色
COLORREF CColorLookUpTable::LookUpColor(float v) const
{
	ASSERT( v>=m_ValueMin && v<=m_ValueMax );

	return GetColor( (v-m_ValueMin)/(m_ValueMax-m_ValueMin) );
}

void CColorLookUpTable::DrawColorSpectrumRect(CDC* pDC, const CRect& drawRect)
{//绘制颜色表的颜色谱,直接用画刷刷
	int nSize = m_ColorTable.GetSize();
	CRect rect(drawRect);
	
	for(int i=0; i<nSize; i++)//i从1开始
	{
		rect.top = drawRect.bottom-int(drawRect.Height()*(i+1)/nSize);
		
		COLORREF color = m_ColorTable.GetAt(i).color;
	    CBrush brush(color);
		CPen pen(PS_SOLID,1,color);
		pDC->SelectObject(&brush);
		pDC->SelectObject(&pen);
		pDC->Rectangle(rect);

		rect.bottom = rect.top;
	}

	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,255));
	
	int x = drawRect.left-25;//色标值从左侧此处开始
//	int x = 10;
	int y = drawRect.bottom+10;

//	if(nSize<11)
//	{
		float ii = 0;
		for( i=0; i<6; i++)//i从1开始
		{
			CString strTex;
			strTex.Format("%.1f",ii+i*0.2*m_ValueMax);
			
			y = drawRect.bottom-i*2*drawRect.Height()/nSize-10;
			pDC->TextOut(x,y,strTex);
		}
//	}
/*	else
	{
		x = drawRect.left-30;
		pDC->TextOut(x,y,"回波强度");

		x = drawRect.right+2;
		CString strTex;
		int ii = 0;
		for( i=0; i<5; i++)//i从1开始
		{
			strTex.Format("%d",ii+i*25);	
			y = drawRect.bottom-i*drawRect.Height()/4-10;
			pDC->TextOut(x,y,strTex);
		}
	
		strTex = "(%)";
		y = y-20;
		pDC->TextOut(x,y,strTex);
	}
*/
}

/*

void CColorLookUpTable::SetColorTable()
{//雷达图像显示色标，设置雷达图像色标的颜色
	m_ColorTable.RemoveAll();

	float poss[14];
	float intel = (float)(1/13.0);
	for(int i=0;i<14;i++)
	{
		poss[i] = i*intel;
	}
	m_ColorTable.Add( CColorNode(poss[0],RGB(2, 2, 2)) );
	m_ColorTable.Add( CColorNode(poss[1],RGB(2, 2, 254)) );
	m_ColorTable.Add( CColorNode(poss[2],RGB(2, 130, 254)) );
	m_ColorTable.Add( CColorNode(poss[3],RGB(2, 254, 254)) );
	m_ColorTable.Add( CColorNode(poss[4],RGB(2, 254, 134)) );
	m_ColorTable.Add( CColorNode(poss[5],RGB(2, 254, 2)) );
	m_ColorTable.Add( CColorNode(poss[6],RGB(134, 254, 134)) );
	m_ColorTable.Add( CColorNode(poss[7],RGB(254, 130, 2)) );	
	m_ColorTable.Add( CColorNode(poss[8],RGB(254, 2, 2)) );
	m_ColorTable.Add( CColorNode(poss[9],RGB(134, 2, 2)) );
	m_ColorTable.Add( CColorNode(poss[10],RGB(134, 2, 134)) );
	m_ColorTable.Add( CColorNode(poss[11],RGB(254, 2, 254)) );
	m_ColorTable.Add( CColorNode(poss[12],RGB(254, 254, 2)) );
	m_ColorTable.Add( CColorNode(poss[13],RGB(254, 254, 254)) );

}

*/


