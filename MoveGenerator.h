
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERATOR_H__54A88FC2_CAFC_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_MOVEGENERATOR_H__54A88FC2_CAFC_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();
	int CreatePossibleMove(BYTE position[GRID_NUM][GRID_NUM], int nPly,int nSide);

	STONEMOVE m_MoveList[10][225];
protected:
	int AddMove(int nFromX,int nToX,int nPly);
	int m_nMoveCount;
};

#endif // !defined(AFX_MOVEGENERATOR_H__54A88FC2_CAFC_11D5_AEC7_5254AB2E22C7__INCLUDED_)
