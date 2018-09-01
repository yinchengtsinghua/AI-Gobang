

#include "stdafx.h"
#include "renju.h"
#include "NewGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog


CNewGame::CNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGame)
	DDX_Control(pDX, IDC_PLY, m_SetPly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGame, CDialog)
	//{{AFX_MSG_MAP(CNewGame)
	ON_BN_CLICKED(IDC_BLACKSTONE, OnBlackstone)
	ON_BN_CLICKED(IDC_WHITESTONE, OnWhitestone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGame message handlers

void CNewGame::OnOK() 
{
	// TODO: Add extra validation here
	m_nSelectedPly = m_SetPly.GetPos();
	 
	CDialog::OnOK();
}

BOOL CNewGame::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_BLACKSTONE))->SetCheck(TRUE);
	m_nStoneColor = BLACK;
	m_SetPly.SetRange(1, 5);
	m_SetPly.SetPos(3);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CNewGame::OnBlackstone() 
{
	// TODO: Add your control notification handler code here
	m_nStoneColor = BLACK;
	
}

void CNewGame::OnWhitestone() 
{
	// TODO: Add your control notification handler code here
	m_nStoneColor = WHITE;
	
}
