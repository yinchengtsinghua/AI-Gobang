
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__2AF7A220_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_SEARCHENGINE_H__2AF7A220_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveGenerator.h"
#include "Eveluation.h"

class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
	
	virtual int  SearchAGoodMove(BYTE position[][GRID_NUM], int Type)=0;
	
	virtual int SetSearchDepth(int nDepth){m_nSearchDepth = nDepth; return 0;};
	
	virtual int SetEveluator(CEveluation *pEval) { m_pEval = pEval; return 0; };

	virtual int SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG; return 0;};
	void SetThinkProgress(CProgressCtrl	*pThinkProgress)
	{m_pThinkProgress = pThinkProgress; };
	BOOL GameOver(){return m_bGameOver;};
	void BeginGame(){m_bGameOver = FALSE;};
	int money;
protected:
	CProgressCtrl	*m_pThinkProgress;
	virtual BYTE MakeMove(STONEMOVE* move,int type);
	virtual void UnMakeMove(STONEMOVE* move);
	virtual int IsGameOver(BYTE position[GRID_NUM][GRID_NUM], int nDepth);
	BYTE CurPosition[GRID_NUM][GRID_NUM];
	STONEMOVE m_cmBestMove;
	CMoveGenerator *m_pMG;
	CEveluation *m_pEval;
	int m_nSearchDepth;
	int m_nMaxDepth;
	BOOL m_bGameOver;
};

#endif // !defined(AFX_SEARCHENGINE_H__2AF7A220_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_)
