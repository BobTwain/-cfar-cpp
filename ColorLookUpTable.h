// ColorLookUpTable.h: interface for the CColorLookUpTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_)
#define AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct CColorNode
{//颜色表中的颜色节点
	float pos;        // 0~1 ,归一化坐标位置
	COLORREF color;
	CColorNode(float p=0.f,COLORREF clr=0):pos(p),color(clr){}
};

  class CColorLookUpTable  
{ 
public:
//	void SetColorTable();
	CColorLookUpTable();
	virtual ~CColorLookUpTable();

	void SetValueRange(float min, float max);

	COLORREF GetColor(float pos)const;

	void DrawColorSpectrumRect(CDC* pDC, const CRect& drawRect);
	
	COLORREF LookUpColor(float v) const; //在颜色表中查询v值的颜色

private:
	CArray <CColorNode,CColorNode&> m_ColorTable; //颜色表(0~1内的位置--->RGB颜色)
	float m_ValueMin, m_ValueMax;       //数值的范围,该范围内的数值和颜色表内的颜色相互对应


};

inline void CColorLookUpTable::SetValueRange(float min, float max)
{
	ASSERT( min < max );
	m_ValueMin = min;
	m_ValueMax = max;
}


#endif // !defined(AFX_COLORLOOKUPTABLE_H__C7B146CA_3A98_4F78_B397_37456D77E223__INCLUDED_)
