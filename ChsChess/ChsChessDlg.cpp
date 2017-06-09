
// ChsChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChsChess.h"
#include "ChsChessDlg.h"
#include "Match.h"
#include "Piece.h"
#include "ChnChessTable.h"


#ifdef _DEBUG
    #define new DEBUG_NEW
#endif


// CChsChessDlg 对话框

//按钮的属性（像素）
#define BUTTON_WIDTH     80
#define BUTTON_HEIGHT    25
#define BUTTON_LEFT      (554 + (200 - 80)/2)
#define BUTTON_TOP       300
#define BUTTON_INTERVAL  20

//棋盘属性（像素）
#define TABLE_WIDTH  554
#define TABLE_HEIGHT 620

//棋间距（像素）
#define PIECE_INTERVAL 5

//棋盘左上角第一个棋子的矩形top-left位置
#define FIRST_PIECE_CX 23
#define FIRST_PIECE_CY 30

//棋子正方形尺寸（像素）
#define PIECE_SIZE     52

CChsChessDlg::CChsChessDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CChsChessDlg::IDD, pParent),
      m_pMatch(NULL),
      m_CachedTable(NULL),
      m_iSelectedPieceName(NO_PIECE)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bClickedFlag = false;

    for(int i = 0; i < 1+32+3; i++)
    {
        m_PieceImageList[i] = NULL;
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            (m_PointRectMap[i][j]).SetPoint(0, 0);
        }
    }

    m_ptSrcOfActPiece.SetPoint(0, 0);
    m_ptDesOfActPiece.SetPoint(0, 0);

}

void CChsChessDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChsChessDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CANCEL, &CChsChessDlg::OnBnClickedCancel)
    ON_WM_LBUTTONUP()
    ON_BN_CLICKED(IDC_BUTTON_START, &CChsChessDlg::OnBnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_DRAW, &CChsChessDlg::OnBnClickedButtonDraw)
    ON_BN_CLICKED(IDC_BUTTON_FAIL, &CChsChessDlg::OnBnClickedButtonFail)
    ON_BN_CLICKED(IDC_BUTTON_BACK, &CChsChessDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//CChsChessDlg 消息处理函数定义如下
/////////////////////////////////////////////////////////////////////////////

BOOL CChsChessDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // 设置窗口的位置,高度包含了标题栏的高度
    SetWindowPos(&wndTop, 0, 0, TABLE_WIDTH + 200, TABLE_HEIGHT + 30, SWP_SHOWWINDOW);

    //初始化软件界面
    initUI();

    //初始化棋盘、棋子
    initChessData();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CChsChessDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }

    //更新棋盘
    updateTable();
    showMatchView();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChsChessDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CChsChessDlg::OnOK()
{
    TRACE("CChsChessDlg::OnOK()\n");
}

void CChsChessDlg::OnCancel()
{
    TRACE("CChsChessDlg::OnCancel()\n");
}

void CChsChessDlg::OnBnClickedCancel()
{
    TRACE("CChsChessDlg::OnBnClickedCancel()\n");
    CDialog::OnCancel();
}

void CChsChessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
    if(NULL == m_pMatch)
    {
        return;
    }

    //CClientDC dc(this);
    //Gdiplus::Graphics graphics(dc);

    CPoint ptTablePosRect;
    TPosition tmpPos;
    if(getTablePos(point, tmpPos, ptTablePosRect))
    {
        if(m_bClickedFlag)//之前选中了棋子
        {
            CChnChessTable tbl = m_pMatch->getTable();
            int iTmpPieceName = tbl.getPieceNameByPos(tmpPos);
            if(NO_PIECE != iTmpPieceName)
            {
                CPiece* pPiece = m_pMatch->getPieceByName(iTmpPieceName);

                //检查是否走棋一方单击了本方另一个棋子
                if(pPiece->getType() == m_pMatch->getGoSide())
                {
                    //存储本次选中的棋子
                    m_iSelectedPieceName = iTmpPieceName;
                    m_bClickedFlag = true;

                    //重绘棋盘
                    drawBlankTable();
                    drawPieces();
                    m_ptSrcOfActPiece = ptTablePosRect;
                    drawSrcOfActPieceFlag();
                    showMatchView();
                    return;
                }
            }

            //执行走棋
            if(m_pMatch->go(m_iSelectedPieceName, tmpPos))
            {
                //重绘棋盘
                m_bClickedFlag = false;
                m_ptDesOfActPiece = ptTablePosRect;
                updateTable();
                showMatchView();

                if(m_pMatch->isEnd(m_pMatch->getGoSide()))
                {
                    ::MessageBox(m_hWnd, sEndInfo[m_pMatch->getGoSide()], _T("游戏结束"), MB_OK);
                    m_pMatch->finish();
                    m_pMatch = NULL;
                    initMatchView();
                    showMatchView();
                    return;
                }
            }
            else
            {
                //啥事也不干
            }
        }
        else  //之前没有选中棋子
        {
            CChnChessTable tbl = m_pMatch->getTable();
            int iTmpPieceName = tbl.getPieceNameByPos(tmpPos);
            if(NO_PIECE != iTmpPieceName)
            {
                CPiece* pPiece = m_pMatch->getPieceByName(iTmpPieceName);
                //检查是否走棋一方单击了本方棋子
                if(pPiece->getType() != m_pMatch->getGoSide())
                {
                    return;
                }

                //重绘棋盘
                drawBlankTable();
                drawPieces();
                m_ptSrcOfActPiece = ptTablePosRect;
                drawSrcOfActPieceFlag();
                showMatchView();

                //存储本次选中的棋子
                m_iSelectedPieceName = iTmpPieceName;
                m_bClickedFlag = true;
            }

        }
    }

    CDialog::OnLButtonUp(nFlags, point);
}

//完成清理工作
BOOL CChsChessDlg::DestroyWindow()
{
    //清理棋子、棋盘图片
    if(NULL != m_CachedTable)
    {
        delete m_CachedTable;
        m_CachedTable = NULL;
    }
    if(NULL != m_PieceImageList)
    {
        for(int i = 1; i < 1+32+3; i++)
        {
            delete m_PieceImageList[i];
            m_PieceImageList[i] = NULL;
        }
    }

    //结束棋局
    if(NULL != m_pMatch)
    {
        delete m_pMatch;
        m_pMatch = NULL;
    }

    return CDialog::DestroyWindow();
}

void CChsChessDlg::OnBnClickedButtonStart()
{
    //创建棋局
    if(NULL == m_pMatch)
    {
        m_pMatch = new CMatch();
        if(NULL == m_pMatch)
        {
            TRACE(_T("创建棋局失败！"));
        }
    }

    if(m_pMatch->init())
    {
        drawBlankTable();
        drawPieces();
        showMatchView();
    }
    else
    {
        //初始化棋局失败
        TRACE(_T("初始化棋局失败！"));
    }

}

/////////////////////////////////////////////////////////////////////////////
//自定义函数定义如下
/////////////////////////////////////////////////////////////////////////////

// 根据给定的点找到对应棋盘上的位置、及其映射的矩形top-left位置
bool CChsChessDlg::getTablePos(const CPoint& ptClk, TPosition& pos, CPoint& ptTablePosRect)
{
    CSize size(PIECE_SIZE, PIECE_SIZE);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            CRect rt(m_PointRectMap[i][j], size);
            if(FALSE != rt.PtInRect(ptClk))
            {
                ptTablePosRect = m_PointRectMap[i][j];
                pos.row = i;
                pos.col = j;
                return true;
            }
        }
    }
    return false;
}

//初始化软件界面
void CChsChessDlg::initUI(void)
{
    //设置按钮的位置
    CButton* pButton = NULL;
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_START);
    pButton->SetWindowTextA(_T("开始"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, BUTTON_TOP, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_DRAW);
    pButton->SetWindowTextA(_T("和棋"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_FAIL);
    pButton->SetWindowTextA(_T("认输"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 2, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_BACK);
    pButton->SetWindowTextA(_T("悔棋"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 3, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_STEP);
    pButton->SetWindowTextA(_T("打谱"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 4, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_CANCEL);
    pButton->SetWindowTextA(_T("退出"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 5, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    CenterWindow();
}

void CChsChessDlg::initChessData(void)
{
    //初始化棋盘位置与对应棋子矩形坐标映射表
    CPoint pt;
    for(int i = 0; i < 10; i++)
    {
        pt.y = FIRST_PIECE_CY + (PIECE_SIZE + PIECE_INTERVAL) * i;
        for(int j = 0; j < 9; j++)
        {
            pt.x = FIRST_PIECE_CX + (PIECE_SIZE + PIECE_INTERVAL) * j;
            m_PointRectMap[i][j] = pt;
        }
    }

    //初始化棋子图片
    m_PieceImageList[JU_RIGHT_RED] = m_PieceImageList[JU_LEFT_RED] = ::new Gdiplus::Image(L"res\\红车.png");
    m_PieceImageList[MA_RIGHT_RED] = m_PieceImageList[MA_LEFT_RED] = ::new Gdiplus::Image(L"res\\红马.png");
    m_PieceImageList[PAO_RIGHT_RED] = m_PieceImageList[PAO_LEFT_RED] = ::new Gdiplus::Image(L"res\\红砲.png");
    m_PieceImageList[XIANG_RIGHT_RED] = m_PieceImageList[XIANG_LEFT_RED] = ::new Gdiplus::Image(L"res\\红相.png");
    m_PieceImageList[SHI_RIGHT_RED] = m_PieceImageList[SHI_LEFT_RED] = ::new Gdiplus::Image(L"res\\红仕.png");

    m_PieceImageList[JU_RIGHT_BLACK] = m_PieceImageList[JU_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\黑车.png");
    m_PieceImageList[MA_RIGHT_BLACK] = m_PieceImageList[MA_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\黑马.png");
    m_PieceImageList[PAO_RIGHT_BLACK] = m_PieceImageList[PAO_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\黑炮.png");
    m_PieceImageList[XIANG_RIGHT_BLACK] = m_PieceImageList[XIANG_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\黑象.png");
    m_PieceImageList[SHI_RIGHT_BLACK] = m_PieceImageList[SHI_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\黑士.png");

    m_PieceImageList[SHUAI_RED]  = ::new Gdiplus::Image(L"res\\红帅.png");
    m_PieceImageList[JIANG_BLACK]  = ::new Gdiplus::Image(L"res\\黑将.png");

    m_PieceImageList[BING_ONE_RED] = m_PieceImageList[BING_TWO_RED] = m_PieceImageList[BING_THREE_RED]
        = m_PieceImageList[BING_FOUR_RED] = m_PieceImageList[BING_FIVE_RED] = ::new Gdiplus::Image(L"res\\红兵.png");

    m_PieceImageList[ZU_ONE_BLACK] = m_PieceImageList[ZU_TWO_BLACK] = m_PieceImageList[ZU_THREE_BLACK]
        = m_PieceImageList[ZU_FOUR_BLACK] = m_PieceImageList[ZU_FIVE_BLACK] = ::new Gdiplus::Image(L"res\\黑卒.png");

    m_PieceImageList[TABLE]  = ::new Gdiplus::Image(L"res\\棋盘.png");
    m_PieceImageList[POS_SRC]  = ::new Gdiplus::Image(L"res\\初始位.png");
    m_PieceImageList[POS_DES]  = ::new Gdiplus::Image(L"res\\目标位.png");

    m_CachedTable = ::new Gdiplus::Image(L"res\\棋盘.png");

}

//设置棋子初始位置
void CChsChessDlg::drawPieces(void)
{
    if(NULL == m_pMatch)
    {
        return;
    }

    //CClientDC dc(this);
    //Gdiplus::Graphics graphics(dc);
    Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromImage(m_CachedTable); 


    CPiece* pPiece = NULL;
    TPosition pos;
    for(int i = JU_RIGHT_RED; i <= ZU_FIVE_BLACK; i++)
    {
        pPiece = m_pMatch->getPieceByName(i);
        pos = pPiece->getPos();
        graphics->DrawImage(m_PieceImageList[i], 
            m_PointRectMap[pos.row][pos.col].x, m_PointRectMap[pos.row][pos.col].y);
    }
    delete graphics;

}

//走棋后更新棋盘
void CChsChessDlg::updateTable(void)
{
    drawBlankTable();
    drawPieces();
    drawActPieceFlag();
}

// 画空棋盘
void CChsChessDlg::drawBlankTable(void)
{
    //CClientDC dc(this);
    //Gdiplus::Graphics graphics(dc);
    Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromImage(m_CachedTable); 
    graphics->DrawImage(m_PieceImageList[TABLE], 0, 0);
    delete graphics;
}

void CChsChessDlg::drawActPieceFlag(void)
{
    drawSrcOfActPieceFlag();
    drawDesOfActPieceFlag();
}

void CChsChessDlg::drawSrcOfActPieceFlag(void)
{
    if(0 == m_ptSrcOfActPiece.x && 0 == m_ptSrcOfActPiece.y)
    {
        return;
    }

    //CClientDC dc(this);
    //Gdiplus::Graphics graphics(dc);
    Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromImage(m_CachedTable); 
    graphics->DrawImage(m_PieceImageList[POS_SRC], m_ptSrcOfActPiece.x, m_ptSrcOfActPiece.y);
    delete graphics;
}

void CChsChessDlg::drawDesOfActPieceFlag(void)
{
    if(0 == m_ptDesOfActPiece.x && 0 == m_ptDesOfActPiece.y)
    {
        return;
    }

    //CClientDC dc(this);
    //Gdiplus::Graphics graphics(dc);
    Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromImage(m_CachedTable); 
    graphics->DrawImage(m_PieceImageList[POS_DES], m_ptDesOfActPiece.x, m_ptDesOfActPiece.y);
    delete graphics;
}

void CChsChessDlg::initMatchView(void)
{
    m_bClickedFlag = false;
    m_iSelectedPieceName = NO_PIECE;
    m_ptSrcOfActPiece.SetPoint(0, 0);
    m_ptDesOfActPiece.SetPoint(0, 0);

    drawBlankTable();
    drawPieces();
}

//将缓存中画好的棋盘显示出来
void CChsChessDlg::showMatchView(void)
{
    CClientDC dc(this);
    Gdiplus::Graphics graphics(dc);
    graphics.DrawImage(m_CachedTable, 0, 0);
}



void CChsChessDlg::OnBnClickedButtonDraw()
{
    if(NULL == m_pMatch)
    {
        return;
    }

    ::MessageBox(m_hWnd, sEndInfo[0], _T("游戏结束"), MB_OK);
    m_pMatch->finish();
    m_pMatch = NULL;
    initMatchView();
    showMatchView();
}

void CChsChessDlg::OnBnClickedButtonFail()
{
    if(NULL == m_pMatch)
    {
        return;
    }

    ::MessageBox(m_hWnd, sEndInfo[ RED == m_pMatch->getGoSide() ? BLACK : RED ], _T("游戏结束"), MB_OK);
    m_pMatch->finish();
    m_pMatch = NULL;
    initMatchView();
    showMatchView();
}

void CChsChessDlg::OnBnClickedButtonBack()
{
    if(NULL == m_pMatch)
    {
        return;
    }

    TStepInfo step = m_pMatch->goBack();

    if(0 != step.m_iDesPiece)
    {
        drawBlankTable();
        drawPieces();

        Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromImage(m_CachedTable); 
        int cx = m_PointRectMap[step.m_Src.row][step.m_Src.col].x;
        int cy = m_PointRectMap[step.m_Src.row][step.m_Src.col].y;
        graphics->DrawImage(m_PieceImageList[POS_SRC], cx, cy);
        cx = m_PointRectMap[step.m_Des.row][step.m_Des.col].x;
        cy = m_PointRectMap[step.m_Des.row][step.m_Des.col].y;
        graphics->DrawImage(m_PieceImageList[POS_DES], cx, cy);
        delete graphics;

        showMatchView();
    }

}
