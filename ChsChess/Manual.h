#pragma once

#include <string>
#include <stack>

struct TStepInfo;

//红棋打谱
static std::string sRedPingWords[9] = { _T("九"), _T("八"), _T("七"), _T("六"), _T("五"), _T("四"), _T("三"), _T("二"), _T("一") };
static std::string sRedJinTuiWords[10] = { _T(""), _T("一"), _T("二"), _T("三"), _T("四"), _T("五"), _T("六"), _T("七"), _T("八"), _T("九") };

//黑棋打谱
static std::string sBlackPingWords[9] = { _T("1"), _T("2"), _T("3"), _T("4"), _T("5"), _T("6"), _T("7"), _T("8"), _T("9")};
static std::string sBlackJinTuiWords[10] = { _T(""), _T("1"), _T("2"), _T("3"), _T("4"), _T("5"), _T("6"), _T("7"), _T("8"), _T("9")};

static std::string sPieceForManual[33] = { _T("N"), _T("車"), _T("車"), _T("馬"), _T("馬"), _T("炮"), _T("炮"), 
                                   _T("相"), _T("相"), _T("仕"), _T("仕"), _T("帅"), 
                                   _T("兵"), _T("兵"), _T("兵"), _T("兵"), _T("兵"),
                                   _T("車"), _T("車"), _T("馬"), _T("馬"), _T("砲"), _T("砲"), 
                                   _T("象"), _T("象"), _T("士"), _T("士"), _T("将"), 
                                   _T("卒"), _T("卒"), _T("卒"), _T("卒"), _T("卒") };

enum TGoType{ JIN, TUI, PING };
static const char* sGoType[3] = { _T("进"),  _T("退"), _T("平") };

class CManual
{
public:
    CManual(void);
    ~CManual(void);

    void push(TStepInfo step);
    void pop();
    std::string top();

private:
    //记录棋谱
    std::stack<std::string> m_stackManual;

    std::string translateStepToManual(TStepInfo step);
    std::string translateRedPiece(TStepInfo step);
    std::string translateBlackPiece(TStepInfo step);

};
