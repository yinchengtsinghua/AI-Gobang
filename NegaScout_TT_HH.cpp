

#include "stdafx.h"
#include "renju.h"
#include "NegaScout_TT_HH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegaScout_TT_HH::CNegaScout_TT_HH()
{
	ResetHistoryTable();	
	m_pThinkProgress = NULL;
	m_bGameOver = FALSE;
	money = 30;
}

CNegaScout_TT_HH::~CNegaScout_TT_HH()
{
	
}



int  CNegaScout_TT_HH::SearchAGoodMove(BYTE position[GRID_NUM][GRID_NUM], int Type)
{
	int Score;
	memcpy(CurPosition, position, GRID_COUNT);
	m_nMaxDepth = m_nSearchDepth;
	CalculateInitHashKey(CurPosition);
	ResetHistoryTable();
	Score = NegaScout(m_nMaxDepth, -20000, 20000);

	if (CurPosition[m_cmBestMove.StonePos.y][m_cmBestMove.StonePos.x] != NOSTONE)
	{
		if (Score < 0)
		{
			money += 1;
			MessageBox(NULL, "游戏你赢了", "五子棋", MB_OK);
		}
		else
		{
			money -= 1;
			MessageBox(NULL, "游戏你输了 ", "五子棋", MB_OK);
		}
			

		//this code does not content in books
		m_bGameOver = TRUE;
		//this code does not content in books

	}
	MakeMove(&m_cmBestMove, Type);
	memcpy(position, CurPosition, GRID_COUNT);
	return  money;
}
int CNegaScout_TT_HH::NegaScout(int depth, int alpha, int beta)
{
	int Count,i;
	BYTE type;
	int a,b,t;
	int side;
	int score;

	if (depth>0)
	{
		i = IsGameOver(CurPosition, depth);
		if (i != 0)
			return i;
	}
	side = (m_nMaxDepth-depth)%2;
	
	score = LookUpHashTable(alpha, beta, depth, side); 
	if (score != 66666) 
		return score;
	
	if (depth <= 0)	//叶子节点取估值
	{
		score = m_pEval->Eveluate(CurPosition, side );
		EnterHashTable(exact, score, depth, side );
		return score;
	}

	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, side);
	if (depth == m_nMaxDepth)
	{
		m_pThinkProgress ->SetRange(0, Count);
		m_pThinkProgress ->SetStep(1);
	}
	
	for (i=0;i<Count;i++) 
	{
		m_pMG->m_MoveList[depth][i].Score = 
			GetHistoryScore(&m_pMG->m_MoveList[depth][i]);
	}
	MergeSort(m_pMG->m_MoveList[depth], Count, 0);
	
	int bestmove=-1;
	
    a = alpha;
    b = beta;
    int eval_is_exact = 0;
    for ( i = 0; i < Count; i++ ) 
	{
		if (depth == m_nMaxDepth)
			m_pThinkProgress ->StepIt();
		type = MakeMove(&m_pMG->m_MoveList[depth][i], side);
		Hash_MakeMove(&m_pMG->m_MoveList[depth][i], CurPosition);
		
		t = -NegaScout(depth-1 , -b, -a );
		
		if (t > a && t < beta && i > 0) 
		{
			a = -NegaScout (depth-1, -beta, -t );     /* re-search */
			eval_is_exact = 1;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			bestmove = i;
		}
		Hash_UnMakeMove(&m_pMG->m_MoveList[depth][i], CurPosition); 
		UnMakeMove(&m_pMG->m_MoveList[depth][i]); 
		if (a < t)
		{
			eval_is_exact = 1;
			a=t;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
		}
		if ( a >= beta ) 
		{
			EnterHashTable(lower_bound, a, depth,side);
			EnterHistoryScore(&m_pMG->m_MoveList[depth][i], depth);
			return a;
		}
		b = a + 1;                      /* set new null window */
	}
	if (bestmove != -1)
	EnterHistoryScore(&m_pMG->m_MoveList[depth][bestmove], depth);
	if (eval_is_exact) 
		EnterHashTable(exact, a, depth,side);
	else 
		EnterHashTable(upper_bound, a, depth,side);
	return a;
}