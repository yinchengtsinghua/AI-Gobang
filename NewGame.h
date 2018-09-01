//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of Renju which is an example of <Game Programing guide>.


#if !defined(AFX_NEWGAME_H__B0962A80_D557_11D5_AEC7_5254AB2E22C7__INCLUDED_)
#define AFX_NEWGAME_H__B0962A80_D557_11D5_AEC7_5254AB2E22C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog

class CNewGame : public CDialog
{
// Construction
public:

	CNewGame(CWnd* pParent = NULL);   // standard constructor
	int GetSelectedPly(){return m_nSelectedPly;};
	int GetStoneColor(){return m_nStoneColor;};

// Dialog Data
	//{{AFX_DATA(CNewGame)
	enum { IDD = IDD_NEWGAME };
	CSpinButtonCtrl	m_SetPly;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nSelectedPly;
	int m_nStoneColor;
	// Generated message map functions
	//{{AFX_MSG(CNewGame)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBlackstone();
	afx_msg void OnWhitestone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGAME_H__B0962A80_D557_11D5_AEC7_5254AB2E22C7__INCLUDED_)
