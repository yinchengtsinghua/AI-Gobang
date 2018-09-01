//******
//

#include "stdafx.h"
#include "renju.h"
#include "renjuDlg.h"
#include "newgame.h"
#include "MoveGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CRenjuDlg dialog

CRenjuDlg::CRenjuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenjuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRenjuDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenjuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenjuDlg)
	DDX_Control(pDX, IDC_THINKPRG, m_ThinkProgress);
	DDX_Control(pDX, IDC_NODECOUNT, m_OutputInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRenjuDlg, CDialog)
	//{{AFX_MSG_MAP(CRenjuDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_NEWGAME, OnNewgame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenjuDlg message handlers

BOOL CRenjuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	memset(m_RenjuBoard, NOSTONE, GRID_COUNT);//初始化棋盘
	
	CMoveGenerator *pMG;
	CEveluation *pEvel;
	m_nUserStoneColor = BLACK;

	m_pSE = new CNegaScout_TT_HH;
	pMG = new CMoveGenerator;
	pEvel = new CEveluation;
	m_pSE->SetThinkProgress(&m_ThinkProgress);
	m_pSE->SetSearchDepth(3);
	m_pSE->SetMoveGenerator(pMG);
	m_pSE->SetEveluator(pEvel);
	//this->SetWindowTextA("你妹");
	return TRUE;  // returnTRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRenjuDlg::OnPaint() 
{
	CPaintDC dc(this);
	
//画横轴；
	for ( int i=0; i < GRID_NUM; i++ )
	{
		dc.MoveTo( BOARD_POS_X , BOARD_POS_Y + i*BOARD_WIDTH );
		dc.LineTo( BOARD_POS_X + 14*BOARD_WIDTH, BOARD_POS_Y + i*BOARD_WIDTH );      
	}

//画竖轴；
	for ( int j=0; j <GRID_NUM; j++ )
	{
		dc.MoveTo( BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y );
		dc.LineTo( BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y + 14*BOARD_WIDTH );      
	}

//画横坐标数字
	char ch[2];
	ch[0] = 'a';
	ch[1] = 0;

	dc.SetBkMode(TRANSPARENT);
	for ( int  i=0; i < GRID_NUM; i++ )
	{
		dc.TextOut(BOARD_POS_X + i*BOARD_WIDTH - 5, BOARD_POS_Y + 14*BOARD_WIDTH + 20, ch);
		ch[0] += 1;
	}

//画纵坐标数字
	ch[0] = 'O';
	ch[1] = 0;

	for (int i=0; i < GRID_NUM; i++ )
	{
		dc.TextOut(BOARD_POS_X - BOARD_WIDTH  , BOARD_POS_Y + i*BOARD_WIDTH - 10, ch);
		ch[0] -= 1;
	}

//画标记点
    dc.SelectStockObject( BLACK_BRUSH );
    dc.Ellipse(BOARD_POS_X + 3*BOARD_WIDTH - 3,BOARD_POS_Y + 3*BOARD_WIDTH - 3,BOARD_POS_X + 3*BOARD_WIDTH + 3,BOARD_POS_Y + 3*BOARD_WIDTH + 3);
    dc.Ellipse(BOARD_POS_X + 11*BOARD_WIDTH - 3,BOARD_POS_Y + 3*BOARD_WIDTH - 3,BOARD_POS_X + 11*BOARD_WIDTH + 3,BOARD_POS_Y + 3*BOARD_WIDTH + 3);
    dc.Ellipse(BOARD_POS_X + 7*BOARD_WIDTH - 3,BOARD_POS_Y + 7*BOARD_WIDTH - 3,BOARD_POS_X + 7*BOARD_WIDTH + 3,BOARD_POS_Y + 7*BOARD_WIDTH + 3);
    dc.Ellipse(BOARD_POS_X + 3*BOARD_WIDTH - 3,BOARD_POS_Y + 11*BOARD_WIDTH - 3,BOARD_POS_X + 3*BOARD_WIDTH + 3,BOARD_POS_Y + 11*BOARD_WIDTH + 3);
    dc.Ellipse(BOARD_POS_X + 11*BOARD_WIDTH - 3,BOARD_POS_Y + 11*BOARD_WIDTH - 3,BOARD_POS_X + 11*BOARD_WIDTH + 3,BOARD_POS_Y + 11*BOARD_WIDTH + 3);

	//画棋子
	int x;
	int y;
	for ( x=0; x< GRID_NUM; x++ )
	{
		for( y=0; y < GRID_NUM; y++ )
		{
			if ( m_RenjuBoard[y][x] == BLACK )
			{
				dc.SelectStockObject( BLACK_BRUSH );
				dc.Ellipse( BOARD_POS_X + x*BOARD_WIDTH - BOARD_WIDTH/2 + 1, BOARD_POS_Y + y*BOARD_WIDTH  - BOARD_WIDTH/2 + 1,BOARD_POS_X + x*BOARD_WIDTH + BOARD_WIDTH/2 - 1,BOARD_POS_Y + y*BOARD_WIDTH + BOARD_WIDTH/2 - 1 );
			}
			else if ( m_RenjuBoard[y][x] == WHITE )
			{
				dc.SelectStockObject( WHITE_BRUSH );
				dc.Ellipse( BOARD_POS_X + x*BOARD_WIDTH - BOARD_WIDTH/2 + 1, BOARD_POS_Y + y*BOARD_WIDTH  - BOARD_WIDTH/2 + 1,BOARD_POS_X + x*BOARD_WIDTH + BOARD_WIDTH/2 - 1,BOARD_POS_Y + y*BOARD_WIDTH + BOARD_WIDTH/2 - 1 );
			}
		}
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRenjuDlg::OnQueryDragIcon()
{
	return(HCURSOR) m_hIcon;
}

extern int count;
void CRenjuDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//this code does not content in books
	if (m_pSE->GameOver())
		return;
	//this code does not content in books
	
	CDC *pDC;
	pDC = GetDC();
	CRect rect( BOARD_POS_X -5 , BOARD_POS_Y - 5,BOARD_POS_X + 14*BOARD_WIDTH + 5,BOARD_POS_Y + 14*BOARD_WIDTH + 5);
	int i = ( point.x + BOARD_WIDTH/2 - 1 - BOARD_POS_X )/BOARD_WIDTH;
	int j = ( point.y + BOARD_WIDTH/2 - 1 - BOARD_POS_Y )/BOARD_WIDTH;
	if ( IsValidPos(i, j) && m_RenjuBoard[j][i] == (BYTE)NOSTONE )
	{
		
		m_RenjuBoard[j][i] = m_nUserStoneColor;
		switch (m_nUserStoneColor) 
		{
		case BLACK:
			pDC->SelectStockObject( BLACK_BRUSH );
			break;
		case WHITE:
			pDC->SelectStockObject( WHITE_BRUSH );
			break;
		}
		pDC->Ellipse( BOARD_POS_X + i*BOARD_WIDTH - BOARD_WIDTH/2 + 1, BOARD_POS_Y + j*BOARD_WIDTH  - BOARD_WIDTH/2 + 1,BOARD_POS_X + i*BOARD_WIDTH + BOARD_WIDTH/2 - 1,BOARD_POS_Y + j*BOARD_WIDTH + BOARD_WIDTH/2 - 1 );
	    m_ThinkProgress.SetPos(0);
		//m_OutputInfo.SetWindowText("Computer is thinking about how to move,Please wait... ");
		int timecount;
		timecount = GetTickCount();
		count=0;
		if (m_nUserStoneColor == BLACK)
			InvertRenjuBroad();
		m_pSE->SearchAGoodMove(m_RenjuBoard, BLACK);//!m_nUserStoneColor);	
		
		CString mystr;
		mystr.Format("如皋黑客松-清华魔王队 data=%d", m_pSE->money);
		this->SetWindowTextA(mystr);
		

		if (m_nUserStoneColor == BLACK)
			InvertRenjuBroad();
		CString sNodeCount;
		
		//sNodeCount.Format(" Cost %d ms. %d Nodes were eveluated.", GetTickCount() - timecount,count);
		m_OutputInfo.SetWindowText(sNodeCount);

	}
	InvalidateRect(NULL,TRUE);
	UpdateWindow();

	CDialog::OnLButtonDown(nFlags, point);
}

void CRenjuDlg::OnNewgame() 
{
	// TODO: Add your control notification handler code here
	CNewGame NewGame;
	
	if (NewGame.DoModal() == IDOK)
	{	
		m_pSE->SetSearchDepth(NewGame.GetSelectedPly());


		m_nUserStoneColor = NewGame.GetStoneColor();		
		memset(m_RenjuBoard, NOSTONE, GRID_COUNT);//初始化棋盘
		if (m_nUserStoneColor == WHITE)
			m_RenjuBoard[7][7] = BLACK;//Black First
		
		InvalidateRect(NULL,TRUE);
		UpdateWindow();

		//this code does not content in books
		m_pSE->BeginGame();
		//this code does not content in books
	}
	else
		return; 
}

void CRenjuDlg::InvertRenjuBroad()
{
	int x, y;
	for ( x=0; x< GRID_NUM; x++ )
	{
		for( y=0; y < GRID_NUM; y++ )
		{
			switch( m_RenjuBoard[y][x] )
			{
			case WHITE:
				m_RenjuBoard[y][x] = BLACK;
				break;
			case BLACK:
				m_RenjuBoard[y][x] = WHITE;
				break;
			default:
				break;
			}
		}
	}
}
