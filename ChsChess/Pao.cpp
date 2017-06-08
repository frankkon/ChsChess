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

    //���Ŀ��λ���Ƿ��ез����ӣ�������
    bool bEatFlag = false;
    int tmpPiece = table.getPieceNameByPos(desPos);
    if(NO_PIECE != tmpPiece)
    {
        bEatFlag = true;
    }



    //�ж����巽��
    TPosition tmpPos = m_Pos;

    //����ʱ·���б�����һ���������ܼ���
    int iCountTrestle = 0;

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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
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
                    if(bEatFlag)
                    {
                        iCountTrestle++;
                    }
                    else
                    {
                        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
                }
           }
        }
        else//������
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
                        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
                        return false;
                    }
                }
            }
        }
    }

    //����ֻ����һ�������ڼ���
    if(bEatFlag && (iCountTrestle > 1 || 0 == iCountTrestle) ) 
    {
        //std::cout<<"��Ч����λ��("<<desPos.row<<","<<desPos.col<<")���ܼ��Ӵ���"<<std::endl;
        return false;
    }

    return CPiece::move(desPos, pMatch);
}

