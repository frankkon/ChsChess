#pragma once

#include <string>
#include <stack>

struct TStepInfo;

//�������
static std::string sRedPingWords[9] = { _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("һ") };
static std::string sRedJinTuiWords[10] = { _T(""), _T("һ"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") };

//�������
static std::string sBlackPingWords[9] = { _T("1"), _T("2"), _T("3"), _T("4"), _T("5"), _T("6"), _T("7"), _T("8"), _T("9")};
static std::string sBlackJinTuiWords[10] = { _T(""), _T("1"), _T("2"), _T("3"), _T("4"), _T("5"), _T("6"), _T("7"), _T("8"), _T("9")};

static std::string sPieceForManual[33] = { _T("N"), _T("܇"), _T("܇"), _T("�R"), _T("�R"), _T("��"), _T("��"), 
                                   _T("��"), _T("��"), _T("��"), _T("��"), _T("˧"), 
                                   _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
                                   _T("܇"), _T("܇"), _T("�R"), _T("�R"), _T("�h"), _T("�h"), 
                                   _T("��"), _T("��"), _T("ʿ"), _T("ʿ"), _T("��"), 
                                   _T("��"), _T("��"), _T("��"), _T("��"), _T("��") };

enum TGoType{ JIN, TUI, PING };
static const char* sGoType[3] = { _T("��"),  _T("��"), _T("ƽ") };

class CManual
{
public:
    CManual(void);
    ~CManual(void);

    void push(TStepInfo step);
    void pop();
    std::string top();

private:
    //��¼����
    std::stack<std::string> m_stackManual;

    std::string translateStepToManual(TStepInfo step);
    std::string translateRedPiece(TStepInfo step);
    std::string translateBlackPiece(TStepInfo step);

};
