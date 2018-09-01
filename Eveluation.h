//*******************************************************************************

// Eveluation.h: interface for the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVELUATION_H__2AF7A221_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_EVELUATION_H__2AF7A221_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define  STWO      1   //眠二
#define  STHREE    2   //眠三
#define  SFOUR     3   //冲四
#define  TWO       4   //活二
#define  THREE     5   //活三
#define  FOUR      6   //活四
#define  FIVE      7   //五连
#define  DFOUR     8   //双四
#define  FOURT     9   //四三
#define  DTHREE   10   //三三
#define  NOTYPE   11   //未定义
#define  ANALSISED 255  //已分析过的
#define  TOBEANALSIS 0  //已分析过的

extern int PosValue[15][15];

class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();
	
	virtual int Eveluate(BYTE position[][GRID_NUM], BOOL bIsRedTurn);

protected:

	int AnalysisHorizon(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisVertical(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLeft(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisRight(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLine(BYTE *position, int GridNum, int StonePos);
	BYTE m_LineRecord[30];
	int TypeRecord[GRID_NUM][GRID_NUM][4];
	int TypeCount[2][20];

};

#endif // !defined(AFX_EVELUATION_H__2AF7A221_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_)
