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
****


// Eveluation.cpp: implementation of the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "renju.h"
#include "Eveluation.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int PosValue[GRID_NUM][GRID_NUM]=
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};





//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEveluation::CEveluation()
{
}

CEveluation::~CEveluation()
{
}

int count=0;
int CEveluation::Eveluate(BYTE position[][GRID_NUM], BOOL bIsBlackTurn)
{
	int i, j, k;
	BYTE nStoneType;
	count++;
	memset (TypeRecord,TOBEANALSIS, GRID_COUNT*4*4);
	memset (TypeCount,0, 40*4);
	for (i=0; i<GRID_NUM; i++)
		for (j=0; j<GRID_NUM; j++)
		{
			 if (position[i][j] != NOSTONE) 
			 {
				if (TypeRecord[i][j][0] == TOBEANALSIS)
					AnalysisHorizon(position, i, j);
				if (TypeRecord[i][j][1] == TOBEANALSIS)
					AnalysisVertical(position, i, j);
				if (TypeRecord[i][j][2] == TOBEANALSIS)
					AnalysisLeft(position, i, j);
				if (TypeRecord[i][j][3] == TOBEANALSIS)
					AnalysisRight(position, i, j);
			 
			 }
			
		}

	for (i=0; i<GRID_NUM; i++)
		for (j=0; j<GRID_NUM; j++)
			for (k=0; k<4; k++)
		{
			nStoneType = position[i][j];
			if (nStoneType != NOSTONE)
			{
			 switch (TypeRecord[i][j][k]) 
			 {
			 case FIVE:
				 TypeCount[nStoneType][FIVE] ++;
				 break;
			 case FOUR:
				 TypeCount[nStoneType][FOUR] ++;
				 break;
			 case SFOUR:
				 TypeCount[nStoneType][SFOUR] ++;
				 break;
			 case THREE:
				 TypeCount[nStoneType][THREE] ++;
				 break;
			 case STHREE:
				 TypeCount[nStoneType][STHREE] ++;
				 break;
			 case TWO:
				 TypeCount[nStoneType][TWO] ++;
				 break;
			 case STWO:
				 TypeCount[nStoneType][STWO] ++;
				 break;
			 default:
				 break;

			 }
			}
			
		}

	if (bIsBlackTurn)
	{
		if (TypeCount[BLACK][FIVE])
			return -9999;
		if (TypeCount[WHITE][FIVE])
			return 9999;
	}
	else
	{
		if (TypeCount[BLACK][FIVE])
			return 9999;
		if (TypeCount[WHITE][FIVE])
			return -9999;
	}
	if (TypeCount[WHITE][SFOUR] > 1)
		TypeCount[WHITE][FOUR]++;

	if (TypeCount[BLACK][SFOUR] > 1)
		TypeCount[BLACK][FOUR]++;


	int WValue=0,BValue=0;
	if (bIsBlackTurn)
	{

		if (TypeCount[WHITE][FOUR])//°×Ê¤
		{
			return 9990;
		}

		if (TypeCount[WHITE][SFOUR])//°×Ê¤
		{
			return 9980;
		}

		if (TypeCount[BLACK][FOUR] )//ºÚÊ¤
		{
			return -9970;
		}


		if (TypeCount[BLACK][SFOUR] && TypeCount[BLACK][THREE])//ºÚÊ¤
		{
			return -9960;
		}

		if (TypeCount[WHITE][THREE] && TypeCount[BLACK][SFOUR] == 0)
		{
			return 9950;
		}

		if (TypeCount[BLACK][THREE] > 1 && 
			TypeCount[WHITE][SFOUR] == 0 &&
			TypeCount[WHITE][THREE] == 0 &&
			TypeCount[WHITE][STHREE] == 0)
		{
			return -9940;
		}


		if (TypeCount[WHITE][THREE] > 1)
			WValue += 2000;
		else{
			if (TypeCount[WHITE][THREE])
				WValue += 200;
		}

		if (TypeCount[BLACK][THREE] > 1)
			BValue += 500;
		else{
			if (TypeCount[BLACK][THREE])
				BValue += 100;
		}


		if (TypeCount[WHITE][STHREE])
			WValue += TypeCount[WHITE][STHREE]*10;

		if (TypeCount[BLACK][STHREE])
			BValue += TypeCount[BLACK][STHREE]*10;

		if (TypeCount[WHITE][TWO])
			WValue += TypeCount[WHITE][TWO]*4;

		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][TWO]*4;

		if (TypeCount[WHITE][STWO])
			WValue += TypeCount[WHITE][STWO];

		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][STWO];

	
	}
	else
	{
		if (TypeCount[BLACK][FOUR])
		{
			return 9990;
		}
		
		if (TypeCount[BLACK][SFOUR])
		{
			return 9980;
		}

		if (TypeCount[WHITE][FOUR])
		{
			return -9970;
		}

		if (TypeCount[WHITE][SFOUR] && TypeCount[WHITE][THREE])
		{
			return -9960;
		}

		if (TypeCount[BLACK][THREE] && TypeCount[WHITE][SFOUR] == 0)
		{
			return 9950;
		}

		if (TypeCount[WHITE][THREE] > 1 && 
			TypeCount[BLACK][SFOUR] == 0 &&
			TypeCount[BLACK][THREE] == 0 &&
			TypeCount[BLACK][STHREE] == 0)
		{
			return -9940;
		}

		if (TypeCount[BLACK][THREE] > 1)
			BValue += 2000;
		else{
			if (TypeCount[BLACK][THREE])
				BValue += 200;
		}

		if (TypeCount[WHITE][THREE] > 1)
			WValue += 500;
		else{
			if (TypeCount[WHITE][THREE])
				WValue += 100;
		}

		

		if (TypeCount[WHITE][STHREE])
			WValue += TypeCount[WHITE][STHREE]*10;

		if (TypeCount[BLACK][STHREE])
			BValue += TypeCount[BLACK][STHREE]*10;

		if (TypeCount[WHITE][TWO])
			WValue += TypeCount[WHITE][TWO]*4;

		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][TWO]*4;

		if (TypeCount[WHITE][STWO])
			WValue += TypeCount[WHITE][STWO];

		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][STWO];

	}

	for (i=0; i<GRID_NUM; i++)
		for (j=0; j<GRID_NUM; j++)
		{
			nStoneType = position[i][j];
			if (nStoneType != NOSTONE)
			{
		if (nStoneType == BLACK)
			 BValue += PosValue[i][j];
		else
			 WValue += PosValue[i][j];
				
			
			}
		}
		

	if (!bIsBlackTurn)
		return BValue - WValue;
	else
		return WValue - BValue;

}


int CEveluation::AnalysisHorizon(BYTE position[][GRID_NUM], int i, int j)
{
	
	AnalysisLine(position[i], 15, j);
	for (int s = 0; s < 15; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[i][s][0] =  m_LineRecord[s];
			
	}
	return TypeRecord[i][j][0];

}


int CEveluation::AnalysisVertical(BYTE position[][GRID_NUM], int i, int j)
{
	BYTE tempArray[GRID_NUM];
	
	for (int k = 0; k < GRID_NUM; k++)
		tempArray[k] = position[k][j];
	AnalysisLine(tempArray, GRID_NUM, i);
	for (int s = 0; s < GRID_NUM; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[s][j][1] =  m_LineRecord[s];
			
	}
	return TypeRecord[i][j][1];
}

int CEveluation::AnalysisLeft(BYTE position[][GRID_NUM], int i, int j)
{
	BYTE tempArray[GRID_NUM];
	int x,y;
	if (i < j)
	{
		y = 0;
		x = j - i;
	}else
	{
		x = 0;
		y = i - j;
	}
	int k = 0;
	for ( k = 0; k < GRID_NUM; k++)
	{
		if (x + k > 14 || y + k > 14)
			break;
		tempArray[k] = position[y+k][x+k];
	}
	AnalysisLine(tempArray, k, j-x);
	for (int s = 0; s < k; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[y+s][x+s][2] =  m_LineRecord[s];
			
	}
	return TypeRecord[i][j][2];

}

int CEveluation::AnalysisRight(BYTE position[][GRID_NUM], int i, int j)
{
	BYTE tempArray[GRID_NUM];
	int x,y, realnum;

	if (14 - i < j)
	{
		y = 14;
		x = j - 14 + i;
		realnum = 14 - i; 
	}else
	{
		x = 0;
		y =  i + j;
		realnum = j; 
	}
	int k = 0;
	for ( k = 0; k < GRID_NUM; k++)
	{
		if (x + k > 14 || y - k < 0)
			break;
		tempArray[k] = position[y-k][x+k];
	}
	AnalysisLine(tempArray, k, j-x);
	for (int s = 0; s < k; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[y-s][x+s][3] =  m_LineRecord[s];
			
	}
	return TypeRecord[i][j][3];
}


int CEveluation::AnalysisLine(BYTE *position, int GridNum, int StonePos)
{
	BYTE StoneType;
	BYTE AnalyLine[30];
	int nAnalyPos;
	int LeftEdge, RightEdge;
	int LeftRange, RightRange;
	
	if (GridNum < 5)
	{
		memset(m_LineRecord, ANALSISED, GridNum);
		return 0;
	}

	nAnalyPos = StonePos;
	memset(m_LineRecord, TOBEANALSIS, 30);
	memset(AnalyLine, 0x0F,30);	
	memcpy(&AnalyLine, position, GridNum);

	GridNum--;

	StoneType = AnalyLine[nAnalyPos];
	LeftEdge = nAnalyPos;
	RightEdge = nAnalyPos;
	
	while(LeftEdge > 0)
	{
		if (AnalyLine[LeftEdge-1] != StoneType)
			break;
		LeftEdge--;
	}

	while(RightEdge < GridNum)
	{
		if (AnalyLine[RightEdge+1] != StoneType)
			break;
		RightEdge++;
	}

	LeftRange = LeftEdge;
	RightRange = RightEdge;

	while(LeftRange > 0)
	{
		if (AnalyLine[LeftRange -1] == !StoneType)
			break;
		LeftRange--;
	}

	while(RightRange < GridNum)
	{
		if (AnalyLine[RightRange+1] == !StoneType)
			break;
		RightRange++;
	}

	if (RightRange - LeftRange < 4)
	{
		for (int k = LeftRange ; k <= RightRange; k++ )
			m_LineRecord[k] = ANALSISED;
		return FALSE;
	}

	for (int k = LeftEdge; k <= RightEdge; k++ )
		m_LineRecord[k] = ANALSISED;

	if (RightEdge - LeftEdge > 3)//ÎåÁ¬
	{
		m_LineRecord[nAnalyPos] = FIVE;
		return FIVE;
	}


	if (RightEdge - LeftEdge == 3)//4Á¬
	{
		BOOL Leftfour = FALSE; 
		if (LeftEdge > 0 )
		{
			if (AnalyLine[LeftEdge-1] == NOSTONE)
				Leftfour = TRUE;
		}
	
		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge+1] == NOSTONE)
			{
				if (Leftfour == TRUE)
					m_LineRecord[nAnalyPos] = FOUR;
				else
					m_LineRecord[nAnalyPos] = SFOUR;
			}
			else
			{
				if (Leftfour == TRUE)
					m_LineRecord[nAnalyPos] = SFOUR;
			}

		}else
		{
			if (Leftfour = TRUE)
				m_LineRecord[nAnalyPos] = SFOUR;
		}

		return m_LineRecord[nAnalyPos];
	}



	if (RightEdge - LeftEdge == 2)//3Á¬
	{
		BOOL LeftThree = FALSE; 
		if (LeftEdge > 0 )
		{

			if (AnalyLine[LeftEdge-1] == NOSTONE)
			{
				if (LeftEdge > 1 && AnalyLine[LeftEdge-2] == AnalyLine[LeftEdge])
				{
					m_LineRecord[LeftEdge] = SFOUR;
					m_LineRecord[LeftEdge-2] = ANALSISED;
				}
				else
					LeftThree = TRUE;
			}else
			{
				if (RightEdge == GridNum || AnalyLine[RightEdge+1] != NOSTONE)
					return FALSE;
			}
		}

		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge+1] == NOSTONE)
			{
				if (RightEdge <GridNum -1 && AnalyLine[RightEdge+2] == AnalyLine[RightEdge])
				{
						m_LineRecord[RightEdge] = SFOUR;
						m_LineRecord[RightEdge+2] = ANALSISED;

				}
				else
				{
				if (LeftThree == TRUE)
					m_LineRecord[RightEdge] = THREE;
				else
					m_LineRecord[RightEdge] = STHREE;
				}
			}
			else
			{
				if (m_LineRecord[LeftEdge] == SFOUR)
						return m_LineRecord[LeftEdge];
				if (LeftThree == TRUE)
					m_LineRecord[nAnalyPos] = STHREE;
			}

		}
		else
		{
			if (m_LineRecord[LeftEdge] == SFOUR)
					return m_LineRecord[LeftEdge];
			if (LeftThree == TRUE)
				m_LineRecord[nAnalyPos] = STHREE;
		
		}
		return m_LineRecord[nAnalyPos];
	}

	if (RightEdge - LeftEdge == 1)//2Á¬
	{
		BOOL Lefttwo = FALSE; 
		BOOL Leftthree = FALSE; 
		if (LeftEdge > 2 )
		{
			if (AnalyLine[LeftEdge-1] == NOSTONE)
			{
				if (LeftEdge-1 > 1 && AnalyLine[LeftEdge-2] == AnalyLine[LeftEdge])
				{
					if (AnalyLine[LeftEdge-3] == AnalyLine[LeftEdge])
					{
						m_LineRecord[LeftEdge-3] = ANALSISED;
						m_LineRecord[LeftEdge-2] = ANALSISED;
						m_LineRecord[LeftEdge] = SFOUR;
					}
					else 
						if (AnalyLine[LeftEdge-3] == NOSTONE)
						{
							m_LineRecord[LeftEdge-2] = ANALSISED;
							m_LineRecord[LeftEdge] = STHREE;
						}
				}
				else
				Lefttwo = TRUE;
			}
		}
		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge+1] == NOSTONE)
			{
				if (RightEdge+1 < GridNum-1 && AnalyLine[RightEdge+2] == AnalyLine[RightEdge])
				{
					if (AnalyLine[RightEdge+3] == AnalyLine[RightEdge])
					{
							m_LineRecord[RightEdge+3] = ANALSISED;
							m_LineRecord[RightEdge+2] = ANALSISED;
							m_LineRecord[RightEdge] = SFOUR;
					}
					else 
						if (AnalyLine[RightEdge+3] == NOSTONE)
						{
							m_LineRecord[RightEdge+2] = ANALSISED;
							if (Lefttwo == TRUE)
								m_LineRecord[RightEdge] = THREE;
							else
								m_LineRecord[RightEdge] = STHREE;
						}

				}
				else
				{
					if (m_LineRecord[LeftEdge] == SFOUR)
						return m_LineRecord[LeftEdge];
					if (m_LineRecord[LeftEdge] == STHREE)
					{
						m_LineRecord[LeftEdge] = THREE;
						return m_LineRecord[LeftEdge];
					}

					if (Lefttwo == TRUE)
					m_LineRecord[nAnalyPos] = TWO;
				else
					m_LineRecord[nAnalyPos] = STWO;
				}
			}
			else
			{
					if (m_LineRecord[LeftEdge] == SFOUR)
						return m_LineRecord[LeftEdge];
				if (Lefttwo == TRUE)
					m_LineRecord[nAnalyPos] = STWO;
			}

		}
		return m_LineRecord[nAnalyPos];
	}

	return 0;

}
