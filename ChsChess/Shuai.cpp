#include "StdAfx.h"
//#include "vld.h"
#include "Shuai.h"

#include <cmath>
#include <iostream>

CShuai::CShuai(void)
{
}

CShuai::~CShuai(void)
{
}

bool CShuai::move(TPosition desPos, CMatch* pMatch)
{
    if(!IsValidMove(this, desPos, pMatch))
    {
        //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
        return false;
    }

    //检查是否超出了帅的活动范围
    if( ((m_Pos.row > 6) && (desPos.row > 6 && desPos.col < 6 && desPos.col > 2)) 
        || ((m_Pos.row < 3) &&(desPos.row < 3 && desPos.col < 6 && desPos.col > 2)) )
    {
        //只能横or竖走一格
        if( ((m_Pos.row == desPos.row) && (1 == abs(m_Pos.col - desPos.col))) 
            || ((m_Pos.col == desPos.col) && (1 == abs(m_Pos.row - desPos.row))))
        {
            return CPiece::move(desPos, pMatch);
        }
    }

    //std::cout<<"无效走棋位置("<<desPos.row<<","<<desPos.col<<")"<<std::endl;
    return false;
}










