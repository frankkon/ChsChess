#pragma once

#include <vector>
#include <stack>
#include <string>

#include "Log.h"
#include "ChnChessTable.h"
#include "Manual.h"

class CPiece;

#define NORMAL_BUF_SIZE       128

static const char* sEndInfo[3] = { _T("和棋！啦啦啦！"), _T("红方胜！耶耶耶！"), _T("黑方胜！哦哦哦！") };

//class CManual;

class CMatch
{
public:
    CMatch(void);
    ~CMatch(void);

    //返回棋盘
    const CChnChessTable& getTable();

    //根据棋子名称获得棋子对象
    CPiece* getPieceByName(int iPieceName);

    //初始化棋局
    bool init();

    //走棋
    bool go(int iPieceName, TPosition pos);

    //保存走棋步骤
    void saveToHistory(TStepInfo step);

    //判负
    bool isEnd(int iType);

    //悔棋
    TStepInfo goBack();

    //结束一局比赛
    void finish();

    //获取日志句柄
    CLog& getLogHandle();

    //获取走棋方信息
    int getGoSide();

    //获取当前一步的打谱
    std::string getCurrentManual();


private:
    //棋盘
    CChnChessTable m_vTable;

    //棋子列表
    std::vector< CPiece* > m_vPieces;

    //走棋历史
    std::stack<TStepInfo> m_stackHistory;

    //记录棋谱
    CManual m_stackManual;

    //走棋方标识
    int m_iGoSide;

    //本局比赛日志
    CLog m_logMatch;
    
    //一局比赛的ID
    char m_sMatchID[NORMAL_BUF_SIZE + 1];

    bool initPiece(int iName, int iType, int iRow, int iCol, CPiece* pPiece);
    void clean();

    //设置走棋方
    void swapGoSide(int iType);

    //生产一局比赛的ID
    void createMatchID();

};  
