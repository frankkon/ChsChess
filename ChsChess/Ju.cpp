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
        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    CChnChessTable table = pMatch->getTable();

    //У���Ƿ��ߵ�ֱ��
    if(m_Pos.row != desPos.row && m_Pos.col != desPos.col)
    {
        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //�ж����巽��
    TPosition tmpPos = m_Pos;
    if(m_Pos.row == desPos.row)//������
    {
        //���·�����Ƿ�������
        if(m_Pos.col > desPos.col)//������
        {
            while((tmpPos.col - desPos.col) != 1)
            {
                tmpPos.col--;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
        else//������
        {
            while((tmpPos.col - desPos.col) != -1)
            {
                tmpPos.col++;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
    }
    else//������
    {
        if(m_Pos.row > desPos.row)//������
        {
            while((tmpPos.row - desPos.row) != 1)
            {
                tmpPos.row--;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
        else//������
        {
            while((tmpPos.row - desPos.row) != -1)
            {
                tmpPos.row++;
                if(NO_PIECE != table.getPieceNameByPos(tmpPos))
                {
                    //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                    return false;
                }
            }
        }
    }

    return CPiece::move(desPos, pMatch);
}

