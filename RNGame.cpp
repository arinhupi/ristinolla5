#include "RNGame.h"

RNGame::RNGame(QObject *parent) : QObject(parent)
{
}

void RNGame::initTable(int rows, int cols)
{
    rntable = new RNTable(rows, cols);
}

void RNGame::initPlayer(int plNumber, std::__cxx11::string name, int value)
{
    if (plNumber == 1)
        player1 = new RNPlayer(name, value);
    else if (plNumber == 2)
        player2 = new RNPlayer(name, value);
}

bool RNGame::checkMove(int row, int col, int value)
{
    if (rntable->getValue(row, col) == 0){
        rntable->setValue(row, col, value);
        return true;
    } else
        return false;
}

int RNGame::getComputerMove()
{
    return player2->compMove(*rntable, 1, 1);
}

QVector<int> RNGame::fullSeqFound(int value)
{
    QVector<int> qv;
    RNSeqVec rnvec;
    rntable->findAllSeqs(value, rnvec);
    rnvec.sortByLength();
    if (rnvec.getSequenceAt(0).getLength() >= RNSequence::MAX_LEN){
        qv.push_back(5 /*RNSequence::MAX_LEN*/);
        getRNTableIndexes(rnvec.getSequenceAt(0), qv);
    }
    return qv;
}

void RNGame::resetTable()
{
    for (int i=0; i<rntable->getRows(); i++){
        for (int j=0; j<rntable->getCols(); j++)
            rntable->setValue(i, j, 0);
    }
}

void RNGame::getRNTableIndexes(RNSequence& rnseq, QVector<int>& qvec){
    for (int i=0; i<rnseq.getLength(); i++){
        int direction = rnseq.getDirection();
        int seqStart = rnseq.getSeqStartIndex();
        int row = rnseq.getStartRow();
        int col = rnseq.getStartCol();

        if (direction == RNSequence::HORIZONTAL)
            col += seqStart + i;
        if (direction == RNSequence::VERTICAL)
            row += seqStart + i;
        if (direction == RNSequence::DIAGONAL_DOWN){
            row += seqStart +i;
            col += seqStart + i;
        }
        if (direction == RNSequence::DIAGONAL_UP){
            row -= seqStart + i;
            col += seqStart + i;
        }
        qvec.push_back(row*rntable->getRows() + col);
    }
}
