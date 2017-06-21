#pragma once
#include "piece.h"
#include "Match.h"

class CMa :
    public CPiece
{
public:
    CMa(void);
    ~CMa(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);

};









