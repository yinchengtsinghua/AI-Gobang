
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYHEURISTIC_H__5870AB20_E3F1_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_HISTORYHEURISTIC_H__5870AB20_E3F1_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHistoryHeuristic  
{
public:
	CHistoryHeuristic();
	virtual ~CHistoryHeuristic();
	
	void ResetHistoryTable();
	int GetHistoryScore(STONEMOVE *move);
	void EnterHistoryScore(STONEMOVE *move,int depth);
	static void MergeSort(STONEMOVE *source, int n, BOOL direction);
protected:
	static void Merge(STONEMOVE *source, STONEMOVE *target, int l,int m, int r);
	static void MergePass(STONEMOVE *source, STONEMOVE *target, const  int s, const  int n, const BOOL direction);
	static void Merge_A(STONEMOVE *source, STONEMOVE *target, int l,int m, int r);
	static STONEMOVE m_TargetBuff[225]; 
	int m_HistoryTable[GRID_NUM][GRID_NUM];

};

#endif // !defined(AFX_HISTORYHEURISTIC_H__5870AB20_E3F1_11D5_AEC7_5254AB2E22C7__INCLUDED_)
