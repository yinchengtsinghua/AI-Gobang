//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of Renju which is an example of <Game Programing guide>.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEGASCOUT_TT_HH_H__42GRID_NUM8561_E8BC_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_NEGASCOUT_TT_HH_H__42GRID_NUM8561_E8BC_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"
#include "TranspositionTable.h"
#include "HistoryHeuristic.h"

class CNegaScout_TT_HH : 
	public CTranspositionTable, 
	public CHistoryHeuristic, 
	public CSearchEngine  
{
public:
	CNegaScout_TT_HH();
	virtual ~CNegaScout_TT_HH();
	

	virtual int  SearchAGoodMove(BYTE position[GRID_NUM][GRID_NUM],int Type);

protected:
	int NegaScout(int depth, int alpha, int beta);
	
};

#endif // !defined(AFX_NEGASCOUT_TT_HH_H__42GRID_NUM8561_E8BC_11D5_AEC7_5254AB2E22C7__INCLUDED_)
