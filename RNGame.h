/*
 * All communication with QML via this class.
 */

#ifndef RNGAME_H
#define RNGAME_H

#include <QObject>
#include <QVector>
#include "RNPlayer.h"
#include "RNTable.h"

class RNGame : public QObject
{
    Q_OBJECT
public:
    explicit RNGame(QObject *parent = 0);
    void initTable(int rows, int cols);
    void initPlayer(int plNumber, std::string name, int value);
    Q_INVOKABLE bool checkMove(int row, int col, int value);
    Q_INVOKABLE int getComputerMove();
    Q_INVOKABLE QVector<int> fullSeqFound(int value);
    Q_INVOKABLE void resetTable();

//signals:
//public slots:

private:
    RNPlayer* player1;
    RNPlayer* player2;
    RNTable* rntable;
    void getRNTableIndexes(RNSequence& rnseq, QVector<int>& qvec);
};

#endif // RNGAME_H
