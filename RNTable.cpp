/*
 * RNTable.cpp
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#include "RNTable.h"
#include <iostream>
#include <algorithm>

RNTable::RNTable(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	rnTable.assign(rows, std::vector<int> (cols,0));
}

RNTable::~RNTable() {
	// TODO Auto-generated destructor stub
}

void RNTable::displayAll() {
	char cv[4] = "_XO";

	for (int i=0; i<rows; i++){
		std::cout << "|";
		for (int j=0; j<cols; j++){
			int value = rnTable.at(i).at(j);
			char c = cv[value];
			std::cout << c << "|";
		}
		std::cout << std::endl;
	}
}

void RNTable::setValue(int r, int c, int newVal) {
	rnTable.at(r).at(c) = newVal;
}

int RNTable::getValue(int r, int c) {
	return rnTable.at(r).at(c);
}

int RNTable::findLongestSeq(int value) {
	RNSeqVec rnSeq;
	findAllSeqs(value, rnSeq);
	return rnSeq.sortByLength();
}


void RNTable::findAllSeqs(int value, RNSeqVec& seqVec) {
	findHorizontalSeqs(value, seqVec);
	findVerticalSeqs(value, seqVec);
	findDiagonalUpSeqs(value, seqVec);
	findDiagonalDownSeqs(value, seqVec);	
}

void RNTable::findHorizontalSeqs(int value, RNSeqVec& seqVec) {
	for (int i=0; i<rows; i++){
		findSeqsInRow(rnTable.at(i), i, 0, RNSequence::HORIZONTAL, value, seqVec);
	}
}

void RNTable::findVerticalSeqs(int value, RNSeqVec& seqVec) {
	std::vector<int> column(rows);
	for (int i=0; i<cols; i++){
		for (int j=0; j<rows; j++)
			column.at(j) = rnTable.at(j).at(i);
		findSeqsInRow(column, 0, i, RNSequence::VERTICAL, value, seqVec);
	}
}

void RNTable::findDiagonalUpSeqs(int value, RNSeqVec& seqVec) {
	std::vector<int> diagRow;

	for (int i = 0, sr=3, sc=0; i <rows + cols-7; i++){
		diagRow.clear();
		for (int cr = sr, cc = sc; cr >= 0 && cc < cols; cr--, cc++)
			diagRow.push_back( rnTable.at(cr).at(cc));

		findSeqsInRow(diagRow, sr, sc, RNSequence::DIAGONAL_UP, value, seqVec);
		sr < rows-1 ? sr++ : sc++;
	}
}

void RNTable::findDiagonalDownSeqs(int value, RNSeqVec& seqVec) {
	std::vector<int> diagRow;

	for (int i = 0, sr=rows-4, sc=0; i <rows + cols-7; i++){
		diagRow.clear();
		for (int cr = sr, cc = sc; cr < rows && cc < cols; cr++, cc++)
			diagRow.push_back( rnTable.at(cr).at(cc));

		findSeqsInRow(diagRow, sr, sc, RNSequence::DIAGONAL_DOWN, value, seqVec);
		sr > 0 ? sr-- : sc++;
	}
}


void RNTable::findSeqsInRow(const std::vector<int>& virtualRow, int absRow, int absCol, int dir, int value, RNSeqVec& seqVec) {
	RNSequence rnSeq;
	int seqLen = 0;
	for (unsigned int i=0; i<virtualRow.size(); i++){
		if (virtualRow.at(i) == value){
			seqLen++;
			if (i == virtualRow.size()-1){ // end of row
				rnSeq.fillValues(absRow, absCol, i-seqLen+1, dir, seqLen, virtualRow, value);
				seqVec.add(rnSeq);
			}

		} else if (virtualRow.at(i) != value && seqLen > 0){
			rnSeq.fillValues(absRow, absCol, i-seqLen, dir, seqLen, virtualRow, value);
			seqVec.add(rnSeq);
			seqLen = 0;
		}
	}
}


void RNTable::findSeqsAndPairs(int value, RNSeqVec& seqVec, RNSeqVec& pairVec) {
	findAllSeqs(value, seqVec);
	findSeqPairs(seqVec, pairVec);
}


void RNTable::findSeqPairs(RNSeqVec& seqVec, RNSeqVec& seqPairVec) {
	RNSequence seqPair;
	for (int i=0; i<seqVec.getSize()-1; i++){
		if (seqVec.isSeqPairWithNext(i)){
			seqPair.fillSeqPairValues(seqVec.getSequenceAt(i), seqVec.getSequenceAt(i+1));
			seqPairVec.add(seqPair);
		}
	}
}

void RNTable::printColumn(const std::vector<int>& col) {
	for (unsigned int i=0; i<col.size(); i++)
		std::cout << col.at(i) << " ";
	std::cout << std::endl;
}

