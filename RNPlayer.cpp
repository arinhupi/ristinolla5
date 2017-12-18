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
int RNPlayer::compMove(RNTable& rnTable, int oppVal, int round) {
	int row, col, len1 = 0, len2;
	RNSeqVec rnSeqs1, rnSeqPairs;

	//best own sequence
	if (round){
		rnTable.findSeqsAndPairs(myVal, rnSeqs1, rnSeqPairs);
		rnSeqs1.append(rnSeqPairs);
		rnSeqs1.removeBadSequences();
		len1 = rnSeqs1.sortByLengthAndPotential();
	}

	// best sequence of opponent
	RNSeqVec rnSeqs2, rnSeqPairs2;
	rnTable.findSeqsAndPairs(oppVal, rnSeqs2, rnSeqPairs2);
	rnSeqs2.append(rnSeqPairs2);
	rnSeqs2.removeBadSequences();
	len2 = rnSeqs2.sortByLengthAndPotential();

    // improve this later, e.g. taking the round into account
	if (len1 >= len2)
		rnSeqs1.findMove(row, col);
	else
		rnSeqs2.findMove(row, col);

	rnTable.setValue(row, col, myVal);
    return row*rnTable.getRows() + col;
}

