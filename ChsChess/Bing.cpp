#include "StdAfx.h"
//#include "vld.h"
#include "Bing.h"

#include <cmath>
#include <iostream>

CBing::CBing(void):m_bIsCrossRiver(false),m_iStepCount(0)
{
}

CBing::~CBing(void)
{
}

bool CBing::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }


    //通过和本方将（帅）的距离，校验是否后退
    CPiece* tmpPtrPiece = NULL;
    if(RED == m_iType)
    {
        tmpPtrPiece = pMatch->getPieceByName(SHUAI_RED);
        TPosition tmpPos = tmpPtrPiece->getPos();
        if( abs(m_Pos.row - tmpPos.row) > abs(desPos.row - tmpPos.row) )
        {
            //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
            return false;
        }
    }
    else
    {
        tmpPtrPiece = pMatch->getPieceByName(JIANG_BLACK);
        TPosition tmpPos = tmpPtrPiece->getPos();
        if( abs(m_Pos.row - tmpPos.row) > abs(desPos.row - tmpPos.row) )
        {
            //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
            return false;
        }
    }


    //前进一步
    if( (abs(desPos.row - m_Pos.row) == 1) && (desPos.col == m_Pos.col) )
    {
        m_iStepCount++;
        if(m_iStepCount >= 2)
        {
            m_bIsCrossRiver = true;
        }
        return CPiece::move(desPos, pMatch);
    }

    //向左一步or向右一步
    if( m_bIsCrossRiver 
        && (abs(desPos.col - m_Pos.col) == 1) && (desPos.row == m_Pos.row) ) /*向左or向右*/
    {
        return CPiece::move(desPos, pMatch);
    }
    
    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
    return false;
}

