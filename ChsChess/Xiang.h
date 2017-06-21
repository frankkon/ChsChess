#pragma once
#include "piece.h"
#include "Match.h"

class CXiang :
    public CPiece
{
public:
    CXiang(void);
    ~CXiang(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);
};









