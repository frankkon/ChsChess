#include "StdAfx.h"
#include "Ju.h"
#include "Match.h"

#include <iostream>

CJu::CJu(void)
{
}

CJu::~CJu(void)
{
}

bool CJu::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    CChnChessTable table = pMatch->getTable();

    //校验是否走的直线
    if(m_Pos.row != desPos.row && m_Pos.col != desPos.col)
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //判断走棋方向
    TPosition tmpPos = m_Pos;
    if(m_Pos.row == desPos.row)//横着走
    {
        //检查路径中是否有棋子
        if(m_Pos.col > desPos.col)//向左走
        {
            while((tmpPos.col - desPos.col) != 1)
            {
                tmpPos.col--;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
        else//向右走
        {
            while((tmpPos.col - desPos.col) != -1)
            {
                tmpPos.col++;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
    }
    else//竖着走
    {
        if(m_Pos.row > desPos.row)//向上走
        {
            while((tmpPos.row - desPos.row) != 1)
            {
                tmpPos.row--;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
        else//向下走
        {
            while((tmpPos.row - desPos.row) != -1)
            {
                tmpPos.row++;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
    }

    return CPiece::move(desPos, pMatch);
}

