#include "StdAfx.h"
#include "Manual.h"
#include "ChnChessTable.h"

CManual::CManual(void)
{
}

CManual::~CManual(void)
{
}

void CManual::push(TStepInfo step)
{
    m_stackManual.push(translateStepToManual(step));
}

void CManual::pop()
{
    m_stackManual.pop();
}

std::string CManual::top()
{
    return m_stackManual.top();
}

std::string CManual::translateStepToManual(TStepInfo step)
{
    if(JU_RIGHT_RED <= step.m_iPiece && step.m_iPiece <= BING_FIVE_RED)
    {
        return translateRedPiece(step);
    }
    else if(JU_LEFT_BLACK <= step.m_iPiece && step.m_iPiece <= ZU_FIVE_BLACK)
    {
        return translateBlackPiece(step);
    }
    else
    {
        //逆天了！
        std::string sManual;
        return sManual;
    }
}

std::string CManual::translateRedPiece(TStepInfo step)
{
    switch (step.m_iPiece)
    {
    case JU_RIGHT_RED: case JU_LEFT_RED: 
    case PAO_RIGHT_RED: case PAO_LEFT_RED: case SHUAI_RED:
    case BING_ONE_RED: case BING_TWO_RED: case BING_THREE_RED: case BING_FOUR_RED: case BING_FIVE_RED :
        if(step.m_Src.row == step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sRedPingWords[step.m_Src.col] + sGoType[PING] + sRedPingWords[step.m_Des.col];
        }
        else if(step.m_Src.row < step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sRedPingWords[step.m_Src.col] + sGoType[TUI] + sRedJinTuiWords[step.m_Des.row - step.m_Src.row];
        }
        else
        {
            return sPieceForManual[step.m_iPiece] + sRedPingWords[step.m_Src.col] + sGoType[JIN] + sRedJinTuiWords[step.m_Src.row - step.m_Des.row];
        }
    case MA_RIGHT_RED: case MA_LEFT_RED: case XIANG_RIGHT_RED: 
    case XIANG_LEFT_RED: case SHI_RIGHT_RED: case SHI_LEFT_RED :
        if(step.m_Src.row == step.m_Des.row)
        {
            //逆天了
            std::string sManual;
            return sManual;
        }
        else if(step.m_Src.row < step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sRedPingWords[step.m_Src.col] + sGoType[TUI] + sRedPingWords[step.m_Des.col];
        }
        else
        {
            return sPieceForManual[step.m_iPiece] + sRedPingWords[step.m_Src.col] + sGoType[JIN] + sRedPingWords[step.m_Des.col];
        }
    default :
        //逆天了
        std::string sManual;
        return sManual;
    }
}

std::string CManual::translateBlackPiece(TStepInfo step)
{
    switch (step.m_iPiece)
    {
    case JU_LEFT_BLACK : case JU_RIGHT_BLACK: 
    case PAO_LEFT_BLACK: case PAO_RIGHT_BLACK: case JIANG_BLACK:
    case ZU_ONE_BLACK: case ZU_TWO_BLACK: case ZU_THREE_BLACK: case ZU_FOUR_BLACK: case ZU_FIVE_BLACK :
        if(step.m_Src.row == step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sBlackPingWords[step.m_Src.col] + sGoType[PING] + sBlackPingWords[step.m_Des.col];
        }
        else if(step.m_Src.row < step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sBlackPingWords[step.m_Src.col] + sGoType[JIN] + sBlackJinTuiWords[step.m_Des.row - step.m_Src.row];
        }
        else
        {
            return sPieceForManual[step.m_iPiece] + sBlackPingWords[step.m_Src.col] + sGoType[TUI] + sBlackJinTuiWords[step.m_Src.row - step.m_Des.row];
        }
    case MA_LEFT_BLACK: case MA_RIGHT_BLACK: 
    case XIANG_LEFT_BLACK: case XIANG_RIGHT_BLACK: 
    case SHI_LEFT_BLACK: case SHI_RIGHT_BLACK :
        if(step.m_Src.row == step.m_Des.row)
        {
            //逆天了
            std::string sManual;
            return sManual;
        }
        else if(step.m_Src.row < step.m_Des.row)
        {
            return sPieceForManual[step.m_iPiece] + sBlackPingWords[step.m_Src.col] + sGoType[JIN] + sBlackPingWords[step.m_Des.col];
        }
        else
        {
            return sPieceForManual[step.m_iPiece] + sBlackPingWords[step.m_Src.col] + sGoType[TUI] + sBlackPingWords[step.m_Des.col];
        }
    default :
        //逆天了！
        std::string sManual;
        return sManual;
    }
}





