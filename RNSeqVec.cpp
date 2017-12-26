/*
 * RNSeqVec.cpp
 *
 *  Created on: 23.11.2017
 *      Author: ari
 */

#include "RNSeqVec.h"
#include <iostream>
#include <algorithm> //sort

RNSeqVec::RNSeqVec() {
	// TODO Auto-generated constructor stub
}

RNSeqVec::~RNSeqVec() {
	// TODO Auto-generated destructor stub
}

bool len_with_freedom_cmp(const RNSequence& s1, const RNSequence& s2)
{
	if (s1.getLength() != s2.getLength())
		return s1.getLength() > s2.getLength();
	return (s1.getFreedom() > s2.getFreedom());
}

bool len_cmp(const RNSequence& s1, const RNSequence& s2)
{
	return s1.getLength() > s2.getLength();
}

int RNSeqVec::sortByLength() {
	if (seqVec.size()){
		sort(seqVec.begin(), seqVec.end(), len_cmp);
		int longest = seqVec.at(0).getLength();
		return longest;
	} else
		return 0;

}

int RNSeqVec::sortByLengthAndPotential() {
	if (seqVec.size()){
		sort(seqVec.begin(), seqVec.end(), len_with_freedom_cmp);
		int longest = seqVec.at(0).getLength();
		return longest;
	} else
		return 0;

}

void RNSeqVec::removeBadSequences() {
	unsigned int i=0;
	while(i<seqVec.size()){
		if (seqVec.at(i).isGoodForMove())
			i++;
		else
			seqVec.erase(seqVec.begin()+i);
	}
}

void RNSeqVec::add(RNSequence& rnSeq) {
	seqVec.push_back(rnSeq);
}

RNSequence& RNSeqVec::getSequenceAt(int index) {
	return seqVec.at(index);
}

int RNSeqVec::getSize() const {
	return seqVec.size();
}

bool RNSeqVec::isSeqPairWithNext(int firstIndex) {
	if (firstIndex >= (int)seqVec.size()-1)
		return false;

	if (seqVec.at(firstIndex).isSeqPair(seqVec.at(firstIndex+1)))
		return true;
	else
		return false;
}

void RNSeqVec::append(RNSeqVec& otherVec) {
	seqVec.insert(seqVec.end(), otherVec.getSeqVec().begin(), otherVec.getSeqVec().end());
}
