#pragma once
#include "piece.h"
#include "Match.h"

class CBing :
    public CPiece
{
public:
    CBing(void);
    ~CBing(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);

private:
    bool m_bIsCrossRiver;
    int m_iStepCount;
};





