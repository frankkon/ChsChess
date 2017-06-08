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
        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //����,����,����,����
    TPosition tmpPos;
    CChnChessTable table = pMatch->getTable();
    if( 2 == abs(desPos.row - m_Pos.row) && 1 == abs(desPos.col - m_Pos.col) )
    {
        //����Ƿ�e��
        if( 2 == desPos.row - m_Pos.row )  //����
        {
            tmpPos.row = m_Pos.row + 1;
            tmpPos.col = m_Pos.col;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")������"<<std::endl;
                return false;
            }
        }
        else //����
        {
            tmpPos.row = m_Pos.row - 1;
            tmpPos.col = m_Pos.col;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")������"<<std::endl;
                return false;
            }
        }

        return CPiece::move(desPos, pMatch);
    }
    else if(abs(desPos.row - m_Pos.row) == 1 && abs(desPos.col - m_Pos.col) == 2) //����,����,����,����
    {
        //����Ƿ�e��
        //����Ƿ�e��
        if( 2 == desPos.col - m_Pos.col )  //����
        {
            tmpPos.row = m_Pos.row;
            tmpPos.col = m_Pos.col + 1;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")������"<<std::endl;
                return false;
            }
        }
        else //����
        {
            tmpPos.row = m_Pos.row;
            tmpPos.col = m_Pos.col - 1;
            if(NO_PIECE != table.getPieceNameByPos(tmpPos))
            {
                //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")������"<<std::endl;
                return false;
            }
        }

        return CPiece::move(desPos, pMatch);
    }

    return false;
}
