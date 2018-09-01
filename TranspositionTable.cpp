

#include "stdafx.h"
#include "renju.h"
#include "TranspositionTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LONGLONG rand64(void)
{

    return rand() ^ ((LONGLONG)rand() << 15) ^ ((LONGLONG)rand() << 30) ^

        ((LONGLONG)rand() << 45) ^ ((LONGLONG)rand() << 60);

}
LONG rand32(void)
{

    return rand() ^ ((LONG)rand() << 15) ^ ((LONG)rand() << 30);

}

CTranspositionTable::CTranspositionTable()
{
	InitializeHashKey();
}

CTranspositionTable::~CTranspositionTable()
{		
	delete m_pTT[0];
	delete m_pTT[1];
}

void CTranspositionTable::InitializeHashKey()
{
	int i,j,k;
	
	srand( (unsigned)time( NULL ));
	
for (k = 0; k < 2; k++)
	for (i = 0; i < GRID_NUM; i++)
		for (j = 0; j < GRID_NUM; j++)
			{
				m_nHashKey32[k][i][j] = rand32();
				m_ulHashKey64[k][i][j] = rand64();
			}

	m_pTT[0] = new HashItem[1024*1024];
	m_pTT[1] = new HashItem[1024*1024];
}
void CTranspositionTable::CalculateInitHashKey(BYTE CurPosition[GRID_NUM][GRID_NUM])
{
	int i,j,nStoneType;
	m_HashKey32 = 0;
	m_HashKey32 = 0;
	for (i = 0; i < GRID_NUM; i++)
		for (j = 0; j < GRID_NUM; j++)
		{
			nStoneType = CurPosition[i][j];
			if (nStoneType != NOSTONE)
			{
				m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nStoneType][i][j]; 
				m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nStoneType][i][j]; 
			}
		}
}

void CTranspositionTable::Hash_MakeMove(STONEMOVE* move, BYTE CurPosition[GRID_NUM][GRID_NUM])
{
	int type;
	type = CurPosition[move->StonePos.y][move->StonePos.x];
	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[type][move->StonePos.y][move->StonePos.x]; 
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[type][move->StonePos.y][move->StonePos.x]; 
}

void CTranspositionTable::Hash_UnMakeMove(STONEMOVE* move, BYTE CurPosition[GRID_NUM][GRID_NUM])
{
	int type;
	type = CurPosition[move->StonePos.y][move->StonePos.x];
	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[type][move->StonePos.y][move->StonePos.x]; 
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[type][move->StonePos.y][move->StonePos.x]; 
}

int CTranspositionTable::LookUpHashTable(int alpha, int beta, int depth,int TableNo)
{
	int x;
	HashItem * pht;

	x = m_HashKey32 & 0xFFFFF;
	pht = &m_pTT[TableNo][x];

    if (pht->depth >= depth && pht->checksum == m_HashKey64)
	{
		switch (pht->entry_type) 
		{
		case exact: 
			return pht->eval;
		case lower_bound:
			if (pht->eval >= beta)
				return (pht->eval);
			else 
				break;
		case upper_bound:
			if (pht->eval <= alpha)
				return (pht->eval);
			else 
				break;
        }
	}

	return 66666;
}
void CTranspositionTable::EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo)
{
	int x;
	HashItem * pht;

	x = m_HashKey32 & 0xFFFFF;//二十位哈希地址
	pht = &m_pTT[TableNo][x];

	pht->checksum = m_HashKey64;
	pht->entry_type = entry_type;
	pht->eval = eval;
	pht->depth = depth;

}
