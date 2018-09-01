

// TranspositionTable.h: interface for the CTranspositionTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPOSITIONTABLE_H__716F8220_CEEA_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_TRANSPOSITIONTABLE_H__716F8220_CEEA_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum ENTRY_TYPE{ exact , lower_bound, upper_bound}; 

typedef struct HASHITEM{
    LONGLONG checksum;	// or long long might be even better
	ENTRY_TYPE  entry_type;
    short depth;
    short eval;
}HashItem;

class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();

	void CalculateInitHashKey(BYTE CurPosition[GRID_NUM][GRID_NUM]);
	void Hash_MakeMove(STONEMOVE* move,BYTE CurPosition[GRID_NUM][GRID_NUM]);
	void Hash_UnMakeMove(STONEMOVE* move,BYTE CurPosition[GRID_NUM][GRID_NUM]);

	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);

	UINT m_nHashKey32[2][GRID_NUM][GRID_NUM];
	ULONGLONG m_ulHashKey64[2][GRID_NUM][GRID_NUM];
	HashItem *m_pTT[2];
	void InitializeHashKey();
	UINT m_HashKey32;
	LONGLONG m_HashKey64;
};

#endif // !defined(AFX_TRANSPOSITIONTABLE_H__716F8220_CEEA_11D5_AEC7_5254AB2E22C7__INCLUDED_)
