#include "StdAfx.h"
#include "Ma.h"

#include <cmath>
#include <iostream>

CMa::CMa(void)
{
}

CMa::~CMa(void)
{
}

bool CMa::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //上左,上右,下左,下右
    TPosition tmpPos;
    CChnChessTable table = pMatch->getTable();
    if( 2 == abs(desPos.row - m_Pos.row) && 1 == abs(desPos.col - m_Pos.col) )
    {
        //检查是否別腿
        if( 2 == desPos.row - m_Pos.row )  //向下
        {
            tmpPos.row = m_Pos.row + 1;
            tmpPos.col = m_Pos.col;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")，别腿"<<std::endl;
                return false;
            }
        }
        else //向上
        {
            tmpPos.row = m_Pos.row - 1;
            tmpPos.col = m_Pos.col;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")，别腿"<<std::endl;
                return false;
            }
        }

        return CPiece::move(desPos, pMatch);
    }
    else if(abs(desPos.row - m_Pos.row) == 1 && abs(desPos.col - m_Pos.col) == 2) //左上,左下,右上,右下
    {
        //检查是否別腿
        //检查是否別腿
        if( 2 == desPos.col - m_Pos.col )  //向右
        {
            tmpPos.row = m_Pos.row;
            tmpPos.col = m_Pos.col + 1;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")，别腿"<<std::endl;
                return false;
            }
        }
        else //向左
        {
            tmpPos.row = m_Pos.row;
            tmpPos.col = m_Pos.col - 1;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")，别腿"<<std::endl;
                return false;
            }
        }

        return CPiece::move(desPos, pMatch);
    }

    return false;
}
