/*
 * RNSequence.h
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#ifndef RNSEQUENCE_H_
#define RNSEQUENCE_H_

#include <string>
#include <vector>

class RNSequence {
public:
	static const int MAX_LEN = 5;
	static const int HORIZONTAL = 1;
	static const int VERTICAL = 2;
	static const int DIAGONAL_UP = 3;
	static const int DIAGONAL_DOWN = 4;
	static const int GUIDE_FREE_ENDING = 1;
	static const int GUIDE_ANY_ENDING = 2;
	RNSequence();
	virtual ~RNSequence();
	void fillValues(int absRow, int absCol, int index, int dir, int len, const std::vector<int>& virtualRow, int value);
	void fillSeqPairValues(RNSequence& rnSeq1, RNSequence& rnSeq2);
	void printSeqValues(std::string myText) const;
	bool isSeqPair(RNSequence& rnSeq2) const;
	void getOptimalMove(int& row, int& col) const;
	bool isGoodForMove();
	int getLength() const {
		return length;
	}

	int getDirection() const {
		return direction;
	}

	int getStartCol() const {
		return startCol;
	}

	int getStartRow() const {
		return startRow;
	}

    int getSeqStartIndex() const {
        return seqStartIndex;
    }

	int getFreedom() const;

private:
	int value;
	int startRow;
	int startCol;
	int seqStartIndex;
	int direction;
	int length;
	int freeAtStart;
	int freeAtEnd;
	bool seqPair;
	int freeIndexOfPair;

	int countFreeBefore(int startIndex, const std::vector<int>& virtualRow, int value);
	int countFreeAfter(int endIndex, const std::vector<int>& virtualRow, int value);
	int potentialLength();
};

#endif /* RNSEQUENCE_H_ */
