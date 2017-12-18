/*
 * RNSeqVec.h
 *
 *  Created on: 23.11.2017
 *      Author: ari
 */

#ifndef RNSEQVEC_H_
#define RNSEQVEC_H_
#include "RNSequence.h"
#include <vector>

class RNSeqVec {
public:
	RNSeqVec();
	virtual ~RNSeqVec();
	int sortByLength();
	int sortByLengthAndPotential();
	void removeBadSequences();
	void findMove(int& row, int& col);
	void add(RNSequence& rnSeq);
	int getSize();
	RNSequence& getSequenceAt(int index);
	bool isSeqPairWithNext(int firstIndex);
	void append(RNSeqVec& otherVec);
	const std::vector<RNSequence>& getSeqVec() const {
		return seqVec;
	}

private:
	std::vector<RNSequence> seqVec;
};

#endif /* RNSEQVEC_H_ */
