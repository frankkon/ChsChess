#include "StdAfx.h"
#include "Piece.h"

#include <cassert>

CPiece::CPiece(void):m_iName(NO_PIECE),m_iType(NO_SIDE)
{
    //��ʼ��Ϊ��Чλ��
    m_Pos.row = -1; 
    m_Pos.col = -1; 
}

CPiece::~CPiece(void)
{
}

int CPiece::getName()
{
    return m_iName;
}

void CPiece::setName(int iName)
{
    m_iName = iName;
}

int CPiece::getType()
{
    return m_iType;
}

void CPiece::setType(int iType)
{
    m_iType = iType;
}

TPosition CPiece::getPos()
{
    return m_Pos;
}

void CPiece::setPos(TPosition pos)
{
    m_Pos = pos;
}

bool CPiece::move(TPosition desPos, CMatch* pMatch)
{
    assert(NULL != pMatch);

    setPos(desPos);
    return true;
}

bool CPiece::IsValidMove(CPiece* pPiece, TPosition desPos, CMatch* pMatch)
{
    //����Ƿ�ԭʼλ��
    if(pPiece->m_Pos.row == desPos.row && pPiece->m_Pos.col == desPos.col)
    {
        return false;
    }

    CChnChessTable table = pMatch->getTable();
    int tmpPiece = table.getPieceNameByPos(desPos);

    //���Ŀ��λ�������Ƿ񱾷�
    if(NO_PIECE != tmpPiece)
    {
        CPiece* tmpPtrPiece = pMatch->getPieceByName(tmpPiece);
        if( pPiece->m_iType == tmpPtrPiece->getType())
        {
            return false;
        }
    }

    return true;
}
