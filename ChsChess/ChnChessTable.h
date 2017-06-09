#pragma once

#include <stack>

static const unsigned int MAX_COL = 9;
static const unsigned int MAX_ROW = 10;

//坐标
struct TPosition
{
    int row;
    int col;
};

//记录一步棋的信息
struct TStepInfo
{
    int m_iPiece;             //棋子
    int m_iDesPiece;          //目标位置棋子
    TPosition m_Src;         //初始位置
    TPosition m_Des;         //目标位置
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

static const char* sPiecies[33] = { "N", "-車-", "-車-", "-馬-", "-馬-", "-炮-", "-炮-", 
                                   "-相-", "-相-", "-仕-", "-仕-", "-帅-", 
                                   "-兵-", "-兵-", "-兵-", "-兵-", "-兵-",
                                   "-車-", "-車-", "-馬-", "-馬-", "-砲-", "-砲-", 
                                   "-象-", "-象-", "-士-", "-士-", "-将-", 
                                   "-卒-", "-卒-", "-卒-", "-卒-", "-卒-"};

void printPiece(int iPieceNum);

class CChnChessTable
{
public:
    CChnChessTable(void);
    virtual ~CChnChessTable(void);

    //初始化棋盘
    void init();

    //清空棋盘
    void clean();

    //将棋盘当前状态输出到屏幕
    void print();

    //接受棋子的通知，调整棋子的位置
    void update(TStepInfo step);

    //根据棋盘位置获得所在棋子名
    int getPieceNameByPos(TPosition pos);
    
private:
    //棋盘
    int iArrChnChessTable[MAX_ROW][MAX_COL];
    
};
