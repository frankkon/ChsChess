
// ChsChessDlg.h : ͷ�ļ�
//

#pragma once

class CMatch;
struct TPosition;

// CChsChessDlg �Ի���
class CChsChessDlg : public CDialog
{
// ����
public:
    CChsChessDlg(CWnd* pParent = NULL); // ��׼���캯��

    // �Ի�������
    enum { IDD = IDD_CHSCHESS_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


// ʵ��
protected:
    /////////////////////////////////////////////////////////////////
    //��Ա����
    /////////////////////////////////////////////////////////////////
    HICON m_hIcon;

    //�������ӱ�־����ʼfalse,��һ��ѡ��:true���ڶ�������:false��
    bool m_bClickedFlag;

    //����λ�����Ӧ���Ӿ�������ӳ���
    CPoint m_PointRectMap[10][9];

    //����������ͼƬӳ���ϵ���������̡�����λ����ʾ��־�������б�����棩
    Gdiplus::Image* m_PieceImageList[1+32+3]; 

    //һ�����
    CMatch* m_pMatch;

    //��¼ѡ�е�����
    int m_iSelectedPieceName;

    //��¼�����ʶ����(����top-leftλ��)
    CPoint m_ptSrcOfActPiece;
    CPoint m_ptDesOfActPiece;

    /////////////////////////////////////////////////////////////////
    //��Ա����
    /////////////////////////////////////////////////////////////////
    // ���ɵ���Ϣӳ�亯��
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedButtonStart();

    virtual BOOL DestroyWindow();

    //������
    void drawTable(void);

    // ���ݸ����ĵ��ҵ���Ӧ�����ϵ�λ��ӳ��ľ���top-leftλ��
    bool getTablePos(const CPoint& ptClk, TPosition& pos, CPoint& ptTablePosRect);

    //��ʼ���������
    void initUI(void);

    //��ʼ�����̡������������
    void initChessData(void);

    //���������������ϵ�λ���������������
    void drawPieces(void);


};
