//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of Renju which is an example of <Game Programing guide>.
// You may use, compile or redistribute it as part of your application 
// for free. 
// You cannot redistribute sources without the official agreement of the author. 
// If distribution of you application which contents code below was occured, place 
// e-mail <hidebug@hotmail.com> on it is to be appreciated.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 

//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "renju.h"
#include "MoveGenerator.h"
#include "HistoryHeuristic.h"
#include "Eveluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static BYTE THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveGenerator::CMoveGenerator()
{
	
}

CMoveGenerator::~CMoveGenerator()
{
	
}
int CMoveGenerator::AddMove(int nToX, int nToY,int nPly)
{
	m_MoveList[nPly][m_nMoveCount].StonePos.x = nToX;
	m_MoveList[nPly][m_nMoveCount].StonePos.y = nToY;
	m_nMoveCount++;
	m_MoveList[nPly][m_nMoveCount].Score = PosValue[nToY][nToX];
	return m_nMoveCount;
}

int CMoveGenerator::CreatePossibleMove(BYTE position[GRID_NUM][GRID_NUM], int nPly, int nSide)
{
	int		i,j;
	m_nMoveCount = 0;
	for (i = 0; i < GRID_NUM; i++)
		for (j = 0; j < GRID_NUM; j++)
		{
			if (position[i][j] == (BYTE)NOSTONE)
			{
				AddMove(j, i, nPly);
			}
		}

	CHistoryHeuristic::MergeSort(m_MoveList[nPly], m_nMoveCount, 0);
	return m_nMoveCount;
}
