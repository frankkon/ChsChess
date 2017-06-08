#pragma once
#include "piece.h"
#include "Match.h"

class CShi :
    public CPiece
{
public:
    CShi(void);
    ~CShi(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);
};
