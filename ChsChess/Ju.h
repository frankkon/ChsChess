#pragma once
#include "piece.h"
#include "Match.h"

class CJu :
    public CPiece
{
public:
    CJu(void);
    ~CJu(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);
};





