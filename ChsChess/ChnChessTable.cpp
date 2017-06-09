#include "StdAfx.h"
#include "ChnChessTable.h"

#include <iostream>

void printPiece(int iPieceNum)
{
    std::cout<<sPiecies[iPieceNum];
}


CChnChessTable::CChnChessTable(void)
{
    memset(iArrChnChessTable, 0, sizeof(iArrChnChessTable));
}

CChnChessTable::~CChnChessTable(void)
{
}

//�������
void CChnChessTable::clean()
{
    memset(iArrChnChessTable, 0, sizeof(iArrChnChessTable));
}

//��ʼ������
void CChnChessTable::init()
{
    //������
    memset(iArrChnChessTable, 0, sizeof(iArrChnChessTable));

    iArrChnChessTable[9][0] = JU_LEFT_RED;
    iArrChnChessTable[9][8] = JU_RIGHT_RED;
    iArrChnChessTable[9][1] = MA_LEFT_RED;
    iArrChnChessTable[9][7] = MA_RIGHT_RED;
    iArrChnChessTable[9][2] = XIANG_LEFT_RED;
    iArrChnChessTable[9][6] = XIANG_RIGHT_RED;
    iArrChnChessTable[9][3] = SHI_LEFT_RED;
    iArrChnChessTable[9][5] = SHI_RIGHT_RED;
    iArrChnChessTable[9][4] = SHUAI_RED;
    iArrChnChessTable[7][1] = PAO_LEFT_RED;
    iArrChnChessTable[7][7] = PAO_RIGHT_RED;
    iArrChnChessTable[6][0] = BING_ONE_RED;
    iArrChnChessTable[6][2] = BING_TWO_RED;
    iArrChnChessTable[6][4] = BING_THREE_RED;
    iArrChnChessTable[6][6] = BING_FOUR_RED;
    iArrChnChessTable[6][8] = BING_FIVE_RED;

    iArrChnChessTable[0][0] = JU_LEFT_BLACK;
    iArrChnChessTable[0][8] = JU_RIGHT_BLACK;
    iArrChnChessTable[0][1] = MA_LEFT_BLACK;
    iArrChnChessTable[0][7] = MA_RIGHT_BLACK;
    iArrChnChessTable[0][2] = XIANG_LEFT_BLACK;
    iArrChnChessTable[0][6] = XIANG_RIGHT_BLACK;
    iArrChnChessTable[0][3] = SHI_LEFT_BLACK;
    iArrChnChessTable[0][5] = SHI_RIGHT_BLACK;
    iArrChnChessTable[0][4] = JIANG_BLACK;
    iArrChnChessTable[2][1] = PAO_LEFT_BLACK;
    iArrChnChessTable[2][7] = PAO_RIGHT_BLACK;
    iArrChnChessTable[3][0] = ZU_ONE_BLACK;
    iArrChnChessTable[3][2] = ZU_TWO_BLACK;
    iArrChnChessTable[3][4] = ZU_THREE_BLACK;
    iArrChnChessTable[3][6] = ZU_FOUR_BLACK;
    iArrChnChessTable[3][8] = ZU_FIVE_BLACK;

}

//�����̵�ǰ״̬�������Ļ
void CChnChessTable::print()
{
    std::cout<<std::endl;

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(0 == iArrChnChessTable[i][j])
            {
                std::cout<<"-��-";
            }
            else
            {
                printPiece(iArrChnChessTable[i][j]);
            }
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
}

//�������ӵ�֪ͨ���������ӵ�λ��
//���Ա�go��goBack�������ã�go����ʱstep.m_iDesPiece=NO_PIECE
void CChnChessTable::update(TStepInfo step)
{
    iArrChnChessTable[step.m_Src.row][step.m_Src.col] = step.m_iDesPiece;
    iArrChnChessTable[step.m_Des.row][step.m_Des.col] = step.m_iPiece;

}

int CChnChessTable::getPieceNameByPos(TPosition pos)
{
    return iArrChnChessTable[pos.row][pos.col];
}