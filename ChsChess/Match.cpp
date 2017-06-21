#include "StdAfx.h"
//#include "vld.h"
#include <iostream>
#include <ctime>
#include <cstdio> 
#include <cstdlib>

#include "Match.h"
#include "Piece.h"
#include "Ju.h"
#include "Ma.h"
#include "Pao.h"
#include "Shi.h"
#include "Shuai.h"
#include "Xiang.h"
#include "Bing.h"
#include "Manual.h"


CMatch::CMatch(void):m_vPieces(33),m_iGoSide(RED)
{
    memset(m_sMatchID, 0, sizeof(m_sMatchID));

    for(size_t i = 0; i < m_vPieces.size(); i++)
    {
        m_vPieces[i] = NULL;
    }
}

CMatch::~CMatch(void)
{
    clean();
}

const CChnChessTable& CMatch::getTable()
{
    return m_vTable;
}

CPiece* CMatch::getPieceByName(int iPieceName)
{
    return m_vPieces[iPieceName];
}

bool CMatch::init()
{
    //先清理
    clean();
    
    createMatchID();

    //初始化比赛日志文件
    char sMatchLogFile[NORMAL_BUF_SIZE + 1] = {0};
    sprintf_s(sMatchLogFile, NORMAL_BUF_SIZE, _T("match%s.txt"), m_sMatchID);
    m_logMatch.openLogFile(sMatchLogFile);

    m_logMatch.logInfo( _T("棋局开始") );

    //初始化棋盘
    m_vTable.init();
    m_logMatch.logInfo( _T("初始化棋盘完成") );

    //初始化棋子
    CPiece* pPiece = NULL;
    bool binitResult = true;

    //红方
    pPiece = new CJu();
    binitResult = binitResult && initPiece(JU_LEFT_RED, RED, 9, 0, pPiece);

    pPiece = new CJu();
    binitResult = binitResult && initPiece(JU_RIGHT_RED, RED, 9, 8, pPiece);

    pPiece = new CMa();
    binitResult = binitResult && initPiece(MA_LEFT_RED, RED, 9, 1, pPiece);

    pPiece = new CMa();
    binitResult = binitResult && initPiece(MA_RIGHT_RED, RED, 9, 7, pPiece);

    pPiece = new CXiang();
    binitResult = binitResult && initPiece(XIANG_LEFT_RED, RED, 9, 2, pPiece);

    pPiece = new CXiang();
    binitResult = binitResult && initPiece(XIANG_RIGHT_RED, RED, 9, 6, pPiece);

    pPiece = new CShi();
    binitResult = binitResult && initPiece(SHI_LEFT_RED, RED, 9, 3, pPiece);

    pPiece = new CShi();
    binitResult = binitResult && initPiece(SHI_RIGHT_RED, RED, 9, 5, pPiece);

    pPiece = new CShuai();
    binitResult = binitResult && initPiece(SHUAI_RED, RED, 9, 4, pPiece);

    pPiece = new CPao();
    binitResult = binitResult && initPiece(PAO_LEFT_RED, RED, 7, 1, pPiece);

    pPiece = new CPao();
    binitResult = binitResult && initPiece(PAO_RIGHT_RED, RED, 7, 7, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(BING_ONE_RED, RED, 6, 0, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(BING_TWO_RED, RED, 6, 2, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(BING_THREE_RED, RED, 6, 4, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(BING_FOUR_RED, RED, 6, 6, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(BING_FIVE_RED, RED, 6, 8, pPiece);

    //黑方
    pPiece = new CJu();
    binitResult = binitResult && initPiece(JU_LEFT_BLACK, BLACK, 0, 0, pPiece);

    pPiece = new CJu();
    binitResult = binitResult && initPiece(JU_RIGHT_BLACK, BLACK, 0, 8, pPiece);

    pPiece = new CMa();
    binitResult = binitResult && initPiece(MA_LEFT_BLACK, BLACK, 0, 1, pPiece);

    pPiece = new CMa();
    binitResult = binitResult && initPiece(MA_RIGHT_BLACK, BLACK, 0, 7, pPiece);

    pPiece = new CXiang();
    binitResult = binitResult && initPiece(XIANG_LEFT_BLACK, BLACK, 0, 2, pPiece);

    pPiece = new CXiang();
    binitResult = binitResult && initPiece(XIANG_RIGHT_BLACK, BLACK, 0, 6, pPiece);

    pPiece = new CShi();
    binitResult = binitResult && initPiece(SHI_LEFT_BLACK, BLACK, 0, 3, pPiece);

    pPiece = new CShi();
    binitResult = binitResult && initPiece(SHI_RIGHT_BLACK, BLACK, 0, 5, pPiece);

    pPiece = new CShuai();
    binitResult = binitResult && initPiece(JIANG_BLACK, BLACK, 0, 4, pPiece);

    pPiece = new CPao();
    binitResult = binitResult && initPiece(PAO_LEFT_BLACK, BLACK, 2, 1, pPiece);

    pPiece = new CPao();
    binitResult = binitResult && initPiece(PAO_RIGHT_BLACK, BLACK, 2, 7, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(ZU_ONE_BLACK, BLACK, 3, 0, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(ZU_TWO_BLACK, BLACK, 3, 2, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(ZU_THREE_BLACK, BLACK, 3, 4, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(ZU_FOUR_BLACK, BLACK, 3, 6, pPiece);

    pPiece = new CBing();
    binitResult = binitResult && initPiece(ZU_FIVE_BLACK, BLACK, 3, 8, pPiece);

    pPiece = NULL;

    if(binitResult)
    {
		m_logMatch.logInfo( _T("初始化棋子完成。") );
        //_vTable.print();
    }
    else
    {
		m_logMatch.logInfo( _T("初始化棋子失败。") );
    }

    return binitResult;
}

bool CMatch::go(int iPieceName, TPosition pos)
{
    m_logMatch.logDebug( _T("进入CMatch::go函数") );
    CPiece* pPiece = m_vPieces[iPieceName];
    if(NULL == pPiece)
    {
        return false;
    }

    //检查是否本方走棋
    if(m_iGoSide != pPiece->getType())
    {
        m_logMatch.logInfo( _T("对方走棋") );
        return false;
    }

    TStepInfo step;
    step.m_Src = pPiece->getPos();
    step.m_Des = pos;
    step.m_iPiece = iPieceName;
    step.m_iDesPiece = m_vTable.getPieceNameByPos(pos);

    if(pPiece->move(pos, this))
    {
        //如果是吃子，把被吃的子的位置移到棋盘外。
        if(NO_PIECE != step.m_iDesPiece)
        {
            m_logMatch.logInfo( _T("将被吃的子的位置移到棋盘外") );
            CPiece* tmpPtrPiece = getPieceByName(step.m_iDesPiece);
            if(NULL != tmpPtrPiece)
            {
                TPosition tmpPos;
                tmpPos.col = -1;
                tmpPos.row = -1;
                tmpPtrPiece->setPos(tmpPos);
            }
        }

        saveToHistory(step);

        step.m_iDesPiece = NO_PIECE; //正常走棋时，要把出棋位置置空
        m_vTable.update(step);

        //m_vTable.print();
        
        int iType = pPiece->getType();
        if(isEnd(iType))
        {
            m_logMatch.logInfo(sEndInfo[iType]);
            //std::cout<<sEndInfo[iType]<<std::endl;
            //clean();
            return true;
        }

        swapGoSide(m_iGoSide);
        return true;
    }
    else
    {
        return false;
    }
    
}

void CMatch::saveToHistory(TStepInfo step)
{
    m_logMatch.logDebug( _T("进入CMatch::saveToHistory函数") );
    m_logMatch.logInfo( _T("保存走棋步骤") );
    m_stackHistory.push(step);
    m_stackManual.push(step);
}

bool CMatch::isEnd(int iType)
{
    m_logMatch.logDebug( _T("进入CMatch::isEnd函数") );

    //如果iType对方的帅不在棋盘上了，则结束
    CPiece* tmpPtrPiece = NULL;
    TPosition tmpPos;
    if(RED == iType)
    {
        tmpPtrPiece = getPieceByName(JIANG_BLACK);
        if(NULL != tmpPtrPiece)
        {
            tmpPos = tmpPtrPiece->getPos();
            if(tmpPos.row != -1)
            {
                return false;
            }
        }
    }
    else if(BLACK == iType)
    {
        tmpPtrPiece = getPieceByName(SHUAI_RED);
        if(NULL != tmpPtrPiece)
        {
            tmpPos = tmpPtrPiece->getPos();
            if(tmpPos.row != -1)
            {
                return false;
            }
        }
    }
    else
    {
        m_logMatch.logError( _T("程序异常") );
    }

    return true;
}

TStepInfo CMatch::goBack()
{
    m_logMatch.logDebug( _T("进入CMatch::goBack函数") );

    if(m_stackHistory.empty())
    {
        TStepInfo step;
        memset(&step, 0, sizeof(step));
        return step;
    }

    //将最近一步棋出栈
    TStepInfo step = m_stackHistory.top();
    m_stackHistory.pop();
    m_stackManual.pop();

    //更新棋子位置属性
    CPiece* tmpPtrPiece = getPieceByName(step.m_iDesPiece);
    if(NULL != tmpPtrPiece)
    {
        tmpPtrPiece->setPos(step.m_Des);
    }
    tmpPtrPiece = getPieceByName(step.m_iPiece);
    tmpPtrPiece->setPos(step.m_Src);
    swapGoSide(m_iGoSide);   //重置走棋方

    //将棋盘上的棋子退回原来位置
    int iPiece = step.m_iDesPiece;
    step.m_iDesPiece = step.m_iPiece;
    step.m_iPiece = iPiece;
    m_vTable.update(step);

    //重新打印棋盘
    //m_vTable.print();
    return step;
}

bool CMatch::initPiece(int iName, int iType, int iRow, int iCol, CPiece* pPiece)
{
    m_logMatch.logDebug( _T("进入CMatch::initPiece函数") );

    if( NULL == pPiece)
    {
        m_logMatch.logInfo( _T("初始化棋子失败") );
        return false;
    }

    pPiece->setName(iName);
    pPiece->setType(iType);
    TPosition pos;
    pos.row = iRow;
    pos.col = iCol;
    pPiece->setPos(pos);
    m_vPieces[iName] = pPiece;

    return true;
}

void CMatch::clean()
{
    m_iGoSide = RED;
    memset(m_sMatchID, 0, sizeof(m_sMatchID));
    //m_logMatch.closeLogFile();//不需要显式关闭，自动析构
    m_vTable.clean();

    for(size_t i = 0; i < m_vPieces.size(); i++)
    {
        if(NULL != m_vPieces[i])
        {
            delete m_vPieces[i];
            m_vPieces[i] = NULL;
        }
    }

    while(!m_stackHistory.empty())
    {
        m_stackHistory.pop();
        m_stackManual.pop();
    }
}

void CMatch::finish()
{
    m_logMatch.logDebug( _T("进入CMatch::finish函数") );
    m_logMatch.logInfo( _T("棋局结束") );

    if(NULL != this)
    {
        delete this;
        //this = NULL;
    }
}

void CMatch::swapGoSide(int iType)
{
    m_logMatch.logDebug( _T("进入CMatch::swapGoSide函数") );

    if(RED == iType)
    {
        m_logMatch.logInfo( _T("轮到黑方走") );
        m_iGoSide = BLACK;
    }
    else if(BLACK == iType)
    {
        m_logMatch.logInfo( _T("轮到红方走") );
        m_iGoSide = RED;
    }
    else
    {
        m_logMatch.logError( _T("程序异常") );
    }
}

//生产本局比赛ID：yyyymmddhhmmss+4位1000~9999随机数
//本函数不能输出日志，创建ID时，日志文件还没有创建
void CMatch::createMatchID()
{
    time_t nowtime = time(0);
    struct tm _tm;
    localtime_s(&_tm, &nowtime);
    strftime(m_sMatchID, NORMAL_BUF_SIZE, _T("%Y%m%d%H%M%S"), &_tm); 

    srand((unsigned)time(NULL));
    int iRandom = (double)rand() / (RAND_MAX + 1) * (9999 - 1000) + 1000;
    sprintf_s(m_sMatchID, NORMAL_BUF_SIZE, _T("%s%4d"), m_sMatchID, iRandom);

}

CLog& CMatch::getLogHandle()
{
    return m_logMatch;
}

int CMatch::getGoSide()
{
    return m_iGoSide;
}

//获取当前一步的打谱
std::string CMatch::getCurrentManual()
{
    return m_stackManual.top();
}




