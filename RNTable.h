/*
 * RNTable.h
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#ifndef RNTABLE_H_
#define RNTABLE_H_

#include <vector>
#include "RNSequence.h"
#include "RNSeqVec.h"

class RNTable {
public:  
    RNTable(int rows, int cols);
	virtual ~RNTable();
	void displayAll();
	void setValue(int r, int c, int newVal);
	int getValue(int r, int c);
	int findLongestSeq(int value);
    void findAllSeqs(int value, RNSeqVec& seqVec);
    void findSeqsAndPairs(int value, RNSeqVec& seqVec, RNSeqVec& pairVec);

	int getCols() const {
		return cols;
	}

	int getRows() const {
		return rows;
	}

private:
	int rows, cols;
	std::vector< std::vector<int> > rnTable;

	void findHorizontalSeqs(int value, RNSeqVec& seqVec);
	void findVerticalSeqs(int value, RNSeqVec& seqVec);
	void findDiagonalUpSeqs(int value, RNSeqVec& seqVec);
	void findDiagonalDownSeqs(int value, RNSeqVec& seqVec);
	void findSeqsInRow(const std::vector<int>& virtualRow, int absRol, int absCol, int dir, int value, RNSeqVec& seqVec);
    void findSeqPairs(RNSeqVec& seqVec, RNSeqVec& seqPairVec);
	void printColumn(const std::vector<int>&);
};

#endif /* RNTABLE_H_ */
