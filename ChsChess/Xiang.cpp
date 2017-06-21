#include "StdAfx.h"
//#include "vld.h"
#include "Xiang.h"
#include "ChnChessTable.h"

#include <cmath>
#include <iostream>

CXiang::CXiang(void)
{
}

CXiang::~CXiang(void)
{
}

bool CXiang::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //不能过河，只能走田字，考虑别腿
    TPosition tmpPos;
    CChnChessTable table = pMatch->getTable();
    if( ((m_Pos.row >= 5) && (desPos.row >= 5)) || ((m_Pos.row <= 4) && (desPos.row <= 4)))
    {
        if( 2 == abs(m_Pos.row - desPos.row) && 2 == abs(m_Pos.col - desPos.col) )
        {
            if(desPos.row > m_Pos.row && desPos.col > m_Pos.col)
            {
                tmpPos.row = m_Pos.row + 1;
                tmpPos.col = m_Pos.col + 1;
                if(NO_PIECE == table.getPieceNameByPos(tmpPos))
                {
                    return CPiece::move(desPos, pMatch);
                }
            }
            else if(desPos.row > m_Pos.row && desPos.col < m_Pos.col)
            {
                tmpPos.row = m_Pos.row + 1;
                tmpPos.col = m_Pos.col - 1;
                if(NO_PIECE == table.getPieceNameByPos(tmpPos))
                {
                    return CPiece::move(desPos, pMatch);
                }
            }
            else if(desPos.row < m_Pos.row && desPos.col > m_Pos.col)
            {
                tmpPos.row = m_Pos.row - 1;
                tmpPos.col = m_Pos.col + 1;
                if(NO_PIECE == table.getPieceNameByPos(tmpPos))
                {
                    return CPiece::move(desPos, pMatch);
                }
            }
            else if(desPos.row < m_Pos.row && desPos.col < m_Pos.col)
            {
                tmpPos.row = m_Pos.row - 1;
                tmpPos.col = m_Pos.col - 1;
                if(NO_PIECE == table.getPieceNameByPos(tmpPos))
                {
                    return CPiece::move(desPos, pMatch);
                }
            }
        }
    }

    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
    return false;
}










