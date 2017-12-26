/*
 * RNPlayer.h
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#ifndef RNPLAYER_H_
#define RNPLAYER_H_

#include "RNTable.h"

#include <string>

class RNPlayer {

public:
	RNPlayer(std::string name, int myVal) ;
	virtual ~RNPlayer();
	int compMove(RNTable& rnTable, int oppVal, int round) const;
	const std::string& getName() const {
		return name;
	}

	int getMyVal() const {
		return myVal;
	}

private:
	std::string name;
	int myVal;
	int moveRow;
	int moveCol;
	void findBestMove(RNSeqVec& ownSeqs, RNSeqVec& oppSeqs, int& row, int& col) const;
	void findBestMove2(RNSeqVec& ownSeqs, RNSeqVec& oppSeqs);
};

#endif /* RNPLAYER_H_ */

