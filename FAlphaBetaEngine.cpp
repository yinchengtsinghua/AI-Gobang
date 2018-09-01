// FAlphaBetaEngine.cpp: implementation of the CFAlphaBetaEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "renju.h"
#include "FAlphaBetaEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFAlphaBetaEngine::CFAlphaBetaEngine()
{
}

CFAlphaBetaEngine::~CFAlphaBetaEngine()
{
}

CFAlphaBetaEngine::SearchAGoodMove(BYTE position[10][9])
{
	memcpy(CurPosition, position, 90);
	m_nMaxDepth = m_nSearchDepth;
	FAlphaBeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 90);
	return 0;
}


int CFAlphaBetaEngine::FAlphaBeta(int depth, int alpha, int beta)
{
	int current = -20000 ;
	int score;
	int Count,i;
	BYTE type;
	
	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;

	if (depth <= 0)	//叶子节点取估值
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth-depth)%2);
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, (m_nMaxDepth-depth)%2);

	for (i=0;i<Count;i++) 
	{
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -FAlphaBeta(depth - 1, -beta, -alpha);
		UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 
				
		if (score > current)
		{
			current = score;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			if (score > alpha)
				alpha = score;
			if (score >= beta) //beta剪枝
				break;
		}

	}

	return current;
}

