
// ChsChessDlg.cpp : ʵ���ļ�
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


// CChsChessDlg �Ի���

//��ť�����ԣ����أ�
#define BUTTON_WIDTH     80
#define BUTTON_HEIGHT    25
#define BUTTON_LEFT      (554 + (200 - 80)/2)
#define BUTTON_TOP       300
#define BUTTON_INTERVAL  20

//�������ԣ����أ�
#define TABLE_WIDTH  554
#define TABLE_HEIGHT 620

//���ࣨ���أ�
#define PIECE_INTERVAL 5

//�������Ͻǵ�һ�����ӵľ���top-leftλ��
#define FIRST_PIECE_CX 23
#define FIRST_PIECE_CY 30

//���������γߴ磨���أ�
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
//CChsChessDlg ��Ϣ��������������
/////////////////////////////////////////////////////////////////////////////

BOOL CChsChessDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);         // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��

    // ���ô��ڵ�λ��,�߶Ȱ����˱������ĸ߶�
    SetWindowPos(&wndTop, 0, 0, TABLE_WIDTH + 200, TABLE_HEIGHT + 30, SWP_SHOWWINDOW);

    //��ʼ���������
    initUI();

    //��ʼ�����̡�����
    initChessData();

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CChsChessDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }

    //��������
    updateTable();
    showMatchView();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
        if(m_bClickedFlag)//֮ǰѡ��������
        {
            CChnChessTable tbl = m_pMatch->getTable();
            int iTmpPieceName = tbl.getPieceNameByPos(tmpPos);
            if(NO_PIECE != iTmpPieceName)
            {
                CPiece* pPiece = m_pMatch->getPieceByName(iTmpPieceName);

                //����Ƿ�����һ�������˱�����һ������
                if(pPiece->getType() == m_pMatch->getGoSide())
                {
                    //�洢����ѡ�е�����
                    m_iSelectedPieceName = iTmpPieceName;
                    m_bClickedFlag = true;

                    //�ػ�����
                    drawBlankTable();
                    drawPieces();
                    m_ptSrcOfActPiece = ptTablePosRect;
                    drawSrcOfActPieceFlag();
                    showMatchView();
                    return;
                }
            }

            //ִ������
            if(m_pMatch->go(m_iSelectedPieceName, tmpPos))
            {
                //�ػ�����
                m_bClickedFlag = false;
                m_ptDesOfActPiece = ptTablePosRect;
                updateTable();
                showMatchView();

                if(m_pMatch->isEnd(m_pMatch->getGoSide()))
                {
                    ::MessageBox(m_hWnd, sEndInfo[m_pMatch->getGoSide()], _T("��Ϸ����"), MB_OK);
                    m_pMatch->finish();
                    m_pMatch = NULL;
                    initMatchView();
                    showMatchView();
                    return;
                }
            }
            else
            {
                //ɶ��Ҳ����
            }
        }
        else  //֮ǰû��ѡ������
        {
            CChnChessTable tbl = m_pMatch->getTable();
            int iTmpPieceName = tbl.getPieceNameByPos(tmpPos);
            if(NO_PIECE != iTmpPieceName)
            {
                CPiece* pPiece = m_pMatch->getPieceByName(iTmpPieceName);
                //����Ƿ�����һ�������˱�������
                if(pPiece->getType() != m_pMatch->getGoSide())
                {
                    return;
                }

                //�ػ�����
                drawBlankTable();
                drawPieces();
                m_ptSrcOfActPiece = ptTablePosRect;
                drawSrcOfActPieceFlag();
                showMatchView();

                //�洢����ѡ�е�����
                m_iSelectedPieceName = iTmpPieceName;
                m_bClickedFlag = true;
            }

        }
    }

    CDialog::OnLButtonUp(nFlags, point);
}

//���������
BOOL CChsChessDlg::DestroyWindow()
{
    //�������ӡ�����ͼƬ
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

    //�������
    if(NULL != m_pMatch)
    {
        delete m_pMatch;
        m_pMatch = NULL;
    }

    return CDialog::DestroyWindow();
}

void CChsChessDlg::OnBnClickedButtonStart()
{
    //�������
    if(NULL == m_pMatch)
    {
        m_pMatch = new CMatch();
        if(NULL == m_pMatch)
        {
            TRACE(_T("�������ʧ�ܣ�"));
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
        //��ʼ�����ʧ��
        TRACE(_T("��ʼ�����ʧ�ܣ�"));
    }

}

/////////////////////////////////////////////////////////////////////////////
//�Զ��庯����������
/////////////////////////////////////////////////////////////////////////////

// ���ݸ����ĵ��ҵ���Ӧ�����ϵ�λ�á�����ӳ��ľ���top-leftλ��
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

//��ʼ���������
void CChsChessDlg::initUI(void)
{
    //���ð�ť��λ��
    CButton* pButton = NULL;
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_START);
    pButton->SetWindowTextA(_T("��ʼ"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, BUTTON_TOP, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_DRAW);
    pButton->SetWindowTextA(_T("����"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_FAIL);
    pButton->SetWindowTextA(_T("����"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 2, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_BACK);
    pButton->SetWindowTextA(_T("����"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 3, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_BUTTON_STEP);
    pButton->SetWindowTextA(_T("����"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 4, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    pButton = (CButton*)GetDlgItem(IDC_CANCEL);
    pButton->SetWindowTextA(_T("�˳�"));
    pButton->SetWindowPos(&wndTop, BUTTON_LEFT, 
        BUTTON_TOP + (BUTTON_HEIGHT + BUTTON_INTERVAL) * 5, BUTTON_WIDTH, BUTTON_HEIGHT, SWP_SHOWWINDOW);
    CenterWindow();
}

void CChsChessDlg::initChessData(void)
{
    //��ʼ������λ�����Ӧ���Ӿ�������ӳ���
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

    //��ʼ������ͼƬ
    m_PieceImageList[JU_RIGHT_RED] = m_PieceImageList[JU_LEFT_RED] = ::new Gdiplus::Image(L"res\\�쳵.png");
    m_PieceImageList[MA_RIGHT_RED] = m_PieceImageList[MA_LEFT_RED] = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[PAO_RIGHT_RED] = m_PieceImageList[PAO_LEFT_RED] = ::new Gdiplus::Image(L"res\\��h.png");
    m_PieceImageList[XIANG_RIGHT_RED] = m_PieceImageList[XIANG_LEFT_RED] = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[SHI_RIGHT_RED] = m_PieceImageList[SHI_LEFT_RED] = ::new Gdiplus::Image(L"res\\����.png");

    m_PieceImageList[JU_RIGHT_BLACK] = m_PieceImageList[JU_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\�ڳ�.png");
    m_PieceImageList[MA_RIGHT_BLACK] = m_PieceImageList[MA_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[PAO_RIGHT_BLACK] = m_PieceImageList[PAO_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[XIANG_RIGHT_BLACK] = m_PieceImageList[XIANG_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[SHI_RIGHT_BLACK] = m_PieceImageList[SHI_LEFT_BLACK] = ::new Gdiplus::Image(L"res\\��ʿ.png");

    m_PieceImageList[SHUAI_RED]  = ::new Gdiplus::Image(L"res\\��˧.png");
    m_PieceImageList[JIANG_BLACK]  = ::new Gdiplus::Image(L"res\\�ڽ�.png");

    m_PieceImageList[BING_ONE_RED] = m_PieceImageList[BING_TWO_RED] = m_PieceImageList[BING_THREE_RED]
        = m_PieceImageList[BING_FOUR_RED] = m_PieceImageList[BING_FIVE_RED] = ::new Gdiplus::Image(L"res\\���.png");

    m_PieceImageList[ZU_ONE_BLACK] = m_PieceImageList[ZU_TWO_BLACK] = m_PieceImageList[ZU_THREE_BLACK]
        = m_PieceImageList[ZU_FOUR_BLACK] = m_PieceImageList[ZU_FIVE_BLACK] = ::new Gdiplus::Image(L"res\\����.png");

    m_PieceImageList[TABLE]  = ::new Gdiplus::Image(L"res\\����.png");
    m_PieceImageList[POS_SRC]  = ::new Gdiplus::Image(L"res\\��ʼλ.png");
    m_PieceImageList[POS_DES]  = ::new Gdiplus::Image(L"res\\Ŀ��λ.png");

    m_CachedTable = ::new Gdiplus::Image(L"res\\����.png");

}

//�������ӳ�ʼλ��
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

//������������
void CChsChessDlg::updateTable(void)
{
    drawBlankTable();
    drawPieces();
    drawActPieceFlag();
}

// ��������
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

//�������л��õ�������ʾ����
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

    ::MessageBox(m_hWnd, sEndInfo[0], _T("��Ϸ����"), MB_OK);
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

    ::MessageBox(m_hWnd, sEndInfo[ RED == m_pMatch->getGoSide() ? BLACK : RED ], _T("��Ϸ����"), MB_OK);
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
