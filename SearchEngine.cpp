//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of Renju which is an example of <Game Programing guide>.
// You may use, compile or redistribute it as part of your application 
// for free. 
// You cannot redistribute sources without the official agreement of the author. 
// If distribution of you application which contents code below was occured, place 
// e-mail <hidebug@hotmail.com> on it is to be appreciated.
/

#include "stdafx.h"
#include "renju.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSearchEngine::CSearchEngine()
{
}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;
	delete m_pEval;
}

BYTE CSearchEngine::MakeMove(STONEMOVE* move, int type)
{
	CurPosition[move->StonePos.y][move->StonePos.x] = type;
	return 0;
}

void CSearchEngine::UnMakeMove(STONEMOVE* move)
{
	CurPosition[move->StonePos.y][move->StonePos.x] = NOSTONE;
}


int CSearchEngine::IsGameOver(BYTE position[][GRID_NUM], int nDepth)
{
	int score, i;
	i = (m_nMaxDepth - nDepth ) % 2;
	score = m_pEval->Eveluate(position, i);
	
	if (abs(score) > 8000)
		return score; 
	return 0;
}
