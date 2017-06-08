#include "StdAfx.h"
#include "Pao.h"

#include <iostream>

CPao::CPao(void)
{
}

CPao::~CPao(void)
{
}

bool CPao::move(TPosition desPos, CMatch* pMatch)
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

    //检查目标位置是否有敌方棋子，即吃子
    bool bEatFlag = false;
    int tmpPiece = table.getPieceNameByPos(desPos);
    if(NO_PIECE != tmpPiece)
    {
        bEatFlag = true;
    }



    //判断走棋方向
    TPosition tmpPos = m_Pos;

    //吃棋时路径中必须有一个棋子做跑架子
    int iCountTrestle = 0;

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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
                }
           }
        }
        else//向下走
        {
            while( (tmpPos.row - desPos.row) != -1 )
            {
                tmpPos.row++;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
                }
            }
        }
    }

    //有且只能有一个子做炮架子
    if(bEatFlag && (iCountTrestle > 1 || 0 == iCountTrestle) ) 
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")，跑架子错误"<<std::endl;
        return false;
    }

    return CPiece::move(desPos, pMatch);
}

