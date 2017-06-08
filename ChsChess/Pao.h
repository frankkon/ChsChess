#pragma once
#include "piece.h"
#include "Match.h"

class CPao :
    public CPiece
{
public:
    CPao(void);
    ~CPao(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);
};
