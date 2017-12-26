/*
 * RNPlayer.cpp
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#include "RNPlayer.h"
#include "RNSeqVec.h"
#include "RNTable.h"

RNPlayer::RNPlayer(std::string name, int myVal) {
	this->name = name;
	this->myVal = myVal;
}

RNPlayer::~RNPlayer() {
	// TODO Auto-generated destructor stub
}

// returns index of target location in qml table
int RNPlayer::compMove(RNTable& rnTable, int oppVal, int round) const {
    int row, col;

    //own potential sequences
    RNSeqVec rnSeqs1, rnSeqPairs;
	if (round){
		rnTable.findSeqsAndPairs(myVal, rnSeqs1, rnSeqPairs);
		rnSeqs1.append(rnSeqPairs);
		rnSeqs1.removeBadSequences();
	}

	// potential sequences of human player
	RNSeqVec rnSeqs2, rnSeqPairs2;
	rnTable.findSeqsAndPairs(oppVal, rnSeqs2, rnSeqPairs2);
	rnSeqs2.append(rnSeqPairs2);
	rnSeqs2.removeBadSequences();

	findBestMove(rnSeqs1, rnSeqs2, row, col);
	rnTable.setValue(row, col, myVal);
	return row * rnTable.getRows() + col;
}

void RNPlayer::findBestMove(RNSeqVec &ownSeqs, RNSeqVec &oppSeqs, int &row, int &col) const {
	int len1 = ownSeqs.sortByLengthAndPotential();
	int len2 = oppSeqs.sortByLengthAndPotential();
	if (len1 >= len2)
		ownSeqs.getSequenceAt(0).getOptimalMove(row, col);
	else
		oppSeqs.getSequenceAt(0).getOptimalMove(row, col);
}
/*
void RNPlayer::findBestMove2(RNSeqVec &ownSeqs, RNSeqVec &oppSeqs){
    int len1 = ownSeqs.sortByLengthAndPotential();
    int len2 = oppSeqs.sortByLengthAndPotential();
    if (len1 >= len2)
        ownSeqs.getSequenceAt(0).getOptimalMove(moveRow, moveCol);
    else
        oppSeqs.getSequenceAt(0).getOptimalMove(moveRow, moveCol);
}
*/
