#pragma once
#include "piece.h"
#include "Match.h"

class CShuai :
    public CPiece
{
public:
    CShuai(void);
    ~CShuai(void);

    virtual bool move(TPosition desPos, CMatch* pMatch);
};
