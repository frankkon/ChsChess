#pragma once
#include "ChnChessTable.h"
#include "Match.h"

enum TSide
{
    NO_SIDE, //ÎÞÐ§
    RED,
    BLACK
};

class CPiece
{
public:
    CPiece(void);
    virtual ~CPiece(void);

    virtual bool move(TPosition desPos, CMatch* pMatch) = 0;

    int getName();
    void setName(int iName);

    int getType();
    void setType(int iType);

    TPosition getPos();
    void setPos(TPosition pos);

protected:
    int m_iName;
    int m_iType;
    TPosition m_Pos;

    bool IsValidMove(CPiece* pPiece, TPosition desPos, CMatch* pMatch);


};















