
// ChsChessDlg.h : 头文件
//

#pragma once

class CMatch;
struct TPosition;

// CChsChessDlg 对话框
class CChsChessDlg : public CDialog
{
// 构造
public:
    CChsChessDlg(CWnd* pParent = NULL); // 标准构造函数

    // 对话框数据
    enum { IDD = IDD_CHSCHESS_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


// 实现
protected:
    /////////////////////////////////////////////////////////////////
    //成员变量
    /////////////////////////////////////////////////////////////////
    HICON m_hIcon;

    //点中棋子标志（初始false,第一次选中:true，第二次走棋:false）
    bool m_bClickedFlag;

    //棋盘位置与对应棋子矩形坐标映射表
    CPoint m_PointRectMap[10][9];

    //棋子与棋子图片映射关系表（包含棋盘、走棋位置提示标志，放在列表最后面）
    Gdiplus::Image* m_PieceImageList[1+32+3]; 

    //双缓存
    Gdiplus::Image* m_CachedTable;

    //一场棋局
    CMatch* m_pMatch;

    //记录选中的棋子
    int m_iSelectedPieceName;

    //记录走棋标识坐标(矩形top-left位置)
    CPoint m_ptSrcOfActPiece;
    CPoint m_ptDesOfActPiece;

    //清空打谱信息
    void clearManual(void);

    /////////////////////////////////////////////////////////////////
    //成员函数
    /////////////////////////////////////////////////////////////////
    // 生成的消息映射函数
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()
    virtual void OnOK();
    virtual void OnCancel();


public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedButtonStart();
    afx_msg void OnBnClickedButtonDraw();
    afx_msg void OnBnClickedButtonFail();
    afx_msg void OnBnClickedButtonBack();

    virtual BOOL OnInitDialog();
    virtual BOOL DestroyWindow();

    //画空棋盘
    void drawBlankTable(void);

    // 根据给定的点找到对应棋盘上的位置映射的矩形top-left位置
    bool getTablePos(const CPoint& ptClk, TPosition& pos, CPoint& ptTablePosRect);

    //初始化软件界面
    void initUI(void);

    //初始化棋盘、棋子相关数据
    void initChessData(void);

    //初始化棋局界面
    void initMatchView(void);

    //将缓存中画好的棋盘显示出来
    void showMatchView(void);

    //根据棋子在棋盘上的位置逐个画到棋盘上
    void drawPieces(void);

    //走棋后更新棋盘
    void updateTable(void);

    //画当前移动棋子的矩形亮框
    void drawActPieceFlag(void);
    void drawSrcOfActPieceFlag(void);
    void drawDesOfActPieceFlag(void);

};






