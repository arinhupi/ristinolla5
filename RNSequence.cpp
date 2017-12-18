/*
 * RNSequence.cpp
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#include "RNSequence.h"
#include <stdio.h> // printf
#include <iostream>

RNSequence::RNSequence() {
	// TODO Auto-generated constructor stub

}

RNSequence::~RNSequence() {
	// TODO Auto-generated destructor stub
}

void RNSequence::fillValues(int absRow, int absCol, int index, int dir, int len, const std::vector<int>& virtualRow, int myValue) {
	value = myValue;
	startRow = absRow;
	startCol = absCol;
	seqStartIndex = index;
	direction = dir;
	length = len;
	freeAtStart = countFreeBefore(index, virtualRow, value);
	freeAtEnd = countFreeAfter(index+len, virtualRow, value);
	seqPair = false;
	freeIndexOfPair = 0;
	//printSeqValues("RNSequence fillValues found sequence");

    //return true;
}

void RNSequence::fillSeqPairValues(RNSequence& rnSeq1, RNSequence& rnSeq2) {
	startRow = rnSeq1.startRow;
	startCol = rnSeq1.startCol;
	seqStartIndex = rnSeq1.seqStartIndex;
	direction = rnSeq1.direction;
	length = rnSeq1.length+rnSeq2.length;
	freeAtStart = rnSeq1.freeAtStart;
	freeAtEnd = rnSeq2.freeAtEnd;
	seqPair = true;
	freeIndexOfPair = rnSeq1.seqStartIndex + rnSeq1.length;
	value = rnSeq1.value;
    //printSeqValues("fillSeqPairValues found pair");
}

void RNSequence::printSeqValues(std::string myText) {
	printf("%s: val:%d r:%d c:%d ix:%d dir:%d len:%d fs:%d fe:%d\n", myText.c_str(), value, startRow, startCol, seqStartIndex, direction,
			length,	freeAtStart, freeAtEnd);
}

bool RNSequence::isSeqPair(RNSequence& rnSeq2) {
    if (startRow != rnSeq2.startRow || startCol != rnSeq2.startCol || direction != rnSeq2.direction)
		return false;

	if (freeAtEnd &&rnSeq2.seqStartIndex == seqStartIndex+length+1){
		return true;
	} else
		return false;
}

void RNSequence::getOptimalMove(int& row, int& col) {
	int index;
	row = startRow;	col = startCol;

	if (seqPair)
		index = freeIndexOfPair;
	else if (freeAtStart)
		index = seqStartIndex - 1;
	else
		index = seqStartIndex + length;

	if (direction == HORIZONTAL)
		col = index;
	else if (direction == VERTICAL)
		row = index;
	else if (direction == DIAGONAL_UP){
		row -= index;
		col += index;
	}
	else if (direction == DIAGONAL_DOWN){
		row += index;
		col += index;
	}
    //std::cout << "getOptimal: " << row << " - " << col << std::endl;
}

bool RNSequence::isGoodForMove() {
    if ((freeAtStart || freeAtEnd) && potentialLength() >= MAX_LEN)
		return true;
	else return false;

}

int RNSequence::countFreeBefore(int startIndex,	const std::vector<int>& virtualRow, int value) {
	int counter = 0;
	for (int i = startIndex-1; i >= 0; i--){
		if (virtualRow.at(i) == 0 || virtualRow.at(i) == value)
			counter++;
		else
			break;
	}
	return counter;
}

int RNSequence::countFreeAfter(int endIndex, const std::vector<int>& virtualRow, int value) {
	int counter = 0;
	for (unsigned int i = endIndex; i < virtualRow.size(); i++){
		if (virtualRow.at(i) == 0 || virtualRow.at(i) == value)
			counter++;
		else
			break;
	}
	return counter;
}

int RNSequence::potentialLength() {
	return length + freeAtStart + freeAtEnd;
}

int RNSequence::getFreedom() const{
	int retVal = 0;
	if (freeAtStart) retVal++;
	if (freeAtEnd) retVal++;
    if (seqPair) length == 4 ? retVal+=2 : retVal++;

	return retVal;
}
