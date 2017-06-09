#pragma once

#include <vector>
#include <stack>

#include "Log.h"
#include "ChnChessTable.h"

class CPiece;

#define NORMAL_BUF_SIZE       128

static const char* sEndInfo[3] = {"���壡��������", "�췽ʤ��ҮҮҮ��", "�ڷ�ʤ��ŶŶŶ��"};

class CMatch
{
public:
    CMatch(void);
    ~CMatch(void);

    //��������
    const CChnChessTable& getTable();

    //�����������ƻ�����Ӷ���
    CPiece* getPieceByName(int iPieceName);

    //��ʼ�����
    bool init();

    //����
    bool go(int iPieceName, TPosition pos);

    //�������岽��
    void saveToHistory(TStepInfo step);

    //�и�
    bool isEnd(int iType);

    //����
    TStepInfo goBack();

    //����һ�ֱ���
    void finish();

    //��ȡ��־���
    CLog& getLogHandle();

    //��ȡ���巽��Ϣ
    int getGoSide();

private:
    //����
    CChnChessTable m_vTable;

    //�����б�
    std::vector< CPiece* > m_vPieces;

    //������ʷ
    std::stack<TStepInfo> m_stackHistory;

    //���巽��ʶ
    int m_iGoSide;

    //���ֱ�����־
    CLog m_logMatch;
    
    //һ�ֱ�����ID
    char m_sMatchID[NORMAL_BUF_SIZE + 1];

    bool initPiece(int iName, int iType, int iRow, int iCol, CPiece* pPiece);
    void clean();

    //�������巽
    void swapGoSide(int iType);

    //����һ�ֱ�����ID
    void createMatchID();

};  
