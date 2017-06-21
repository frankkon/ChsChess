#include "StdAfx.h"
//#include "vld.h"
#include "Shi.h"

#include <cmath>
#include <iostream>

CShi::CShi(void)
{
}

CShi::~CShi(void)
{
}

bool CShi::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //校验是否属于固定5个位置
    if( (7 == desPos.row && 3 == desPos.col) || (7 == desPos.row && 5 == desPos.col) 
        || (9 == desPos.row && 3 == desPos.col) || (9 == desPos.row && 5 == desPos.col)
        || (8 == desPos.row && 4 == desPos.col) 
        || (0 == desPos.row && 3 == desPos.col) || (0 == desPos.row && 5 == desPos.col)
        || (2 == desPos.row && 3 == desPos.col) || (2 == desPos.row && 5 == desPos.col)
        || (1 == desPos.row && 4 == desPos.col) )
    {
        //只能斜着走一格
        if( 1 == abs(m_Pos.row - desPos.row) && 1 == abs(m_Pos.col - desPos.col) )
        {
            return CPiece::move(desPos, pMatch);
        }
    }
    
    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
    return false;
}
















