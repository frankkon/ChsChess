#pragma once

#include <stack>

static const unsigned int MAX_COL = 9;
static const unsigned int MAX_ROW = 10;

//����
struct TPosition
{
    int row;
    int col;
};

//��¼һ�������Ϣ
struct TStepInfo
{
    int m_iPiece;             //����
    int m_iDesPiece;          //Ŀ��λ������
    TPosition m_Src;         //��ʼλ��
    TPosition m_Des;         //Ŀ��λ��
};

enum TChnChessPiece
{
    NO_PIECE, JU_RIGHT_RED, JU_LEFT_RED, MA_RIGHT_RED, MA_LEFT_RED, PAO_RIGHT_RED, PAO_LEFT_RED,
    XIANG_RIGHT_RED, XIANG_LEFT_RED, SHI_RIGHT_RED, SHI_LEFT_RED, SHUAI_RED, 
    BING_ONE_RED, BING_TWO_RED, BING_THREE_RED, BING_FOUR_RED, BING_FIVE_RED,
    JU_LEFT_BLACK, JU_RIGHT_BLACK, MA_LEFT_BLACK, MA_RIGHT_BLACK, PAO_LEFT_BLACK, PAO_RIGHT_BLACK,
    XIANG_LEFT_BLACK, XIANG_RIGHT_BLACK, SHI_LEFT_BLACK, SHI_RIGHT_BLACK, JIANG_BLACK, 
    ZU_ONE_BLACK, ZU_TWO_BLACK, ZU_THREE_BLACK, ZU_FOUR_BLACK, ZU_FIVE_BLACK,
    TABLE, POS_SRC, POS_DES
};

static const char* sPiecies[33] = { "N", "-܇-", "-܇-", "-�R-", "-�R-", "-��-", "-��-", 
                                   "-��-", "-��-", "-��-", "-��-", "-˧-", 
                                   "-��-", "-��-", "-��-", "-��-", "-��-",
                                   "-܇-", "-܇-", "-�R-", "-�R-", "-�h-", "-�h-", 
                                   "-��-", "-��-", "-ʿ-", "-ʿ-", "-��-", 
                                   "-��-", "-��-", "-��-", "-��-", "-��-"};

void printPiece(int iPieceNum);

class CChnChessTable
{
public:
    CChnChessTable(void);
    virtual ~CChnChessTable(void);

    //��ʼ������
    void init();

    //�������
    void clean();

    //�����̵�ǰ״̬�������Ļ
    void print();

    //�������ӵ�֪ͨ���������ӵ�λ��
    void update(TStepInfo step);

    //��������λ�û������������
    int getPieceNameByPos(TPosition pos);
    
private:
    //����
    int iArrChnChessTable[MAX_ROW][MAX_COL];
    
};
