#include "catch.hpp"
#include "RNSeqVec.h"

TEST_CASE( "RNSeqVec init and remove bad", "[RNSeqVec]" ){
	RNSeqVec seqVec;
	std::vector<int> virtualRow = {1, 1, 1, 2, 1, 0, 0, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 7, 1 /*HORIZONTAL*/, 2, virtualRow, 1);
	seqVec.add(rnseq1);
	seqVec.add(rnseq2);
	seqVec.add(rnseq3);
	REQUIRE (seqVec.getSize() == 3);
	seqVec.removeBadSequences();
	REQUIRE (seqVec.getSize() == 2);
}

TEST_CASE( "RNSeqVec sort by length", "[RNSeqVec]" ){
	RNSeqVec seqVec;
	std::vector<int> virtualRow = {1, 1, 0, 0, 1, 0, 1, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 2, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 6, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	seqVec.add(rnseq1);
	seqVec.add(rnseq2);
	seqVec.add(rnseq3);
	seqVec.sortByLength();

	// expecting that last sequence starting at index 6 is first
	REQUIRE (seqVec.getSequenceAt(0).getSeqStartIndex() == 6);
}

TEST_CASE( "RNSeqVec sort by potential", "[RNSeqVec]" ){
	RNSeqVec seqVec;
	std::vector<int> virtualRow = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 6, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	seqVec.add(rnseq1);
	seqVec.add(rnseq2);
	seqVec.add(rnseq3);
	seqVec.sortByLengthAndPotential();

	// expecting that last sequence starting at index 6 is first
	REQUIRE (seqVec.getSequenceAt(0).getSeqStartIndex() == 6);
}

TEST_CASE( "RNSeqVec isSeqPairWithNext", "[RNSeqVec]" ){
	RNSeqVec seqVec;
	std::vector<int> virtualRow = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 6, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	seqVec.add(rnseq1);
	seqVec.add(rnseq2);
	seqVec.add(rnseq3);
	REQUIRE (seqVec.isSeqPairWithNext(0) == true);
	REQUIRE (seqVec.isSeqPairWithNext(1) == true);
	REQUIRE	(seqVec.isSeqPairWithNext(2) == false);
}

TEST_CASE( "RNSeqVec append", "[RNSeqVec]" ){
	RNSeqVec seqVec, pairVec;
	std::vector<int> virtualRow = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair1, seqPair2;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 6, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	seqVec.add(rnseq1);
	seqVec.add(rnseq2);
	seqVec.add(rnseq3);
	seqPair1.fillSeqPairValues(rnseq1, rnseq2);
	seqPair2.fillSeqPairValues(rnseq2, rnseq3);
	pairVec.add(seqPair1);
	pairVec.add(seqPair2);
	seqVec.append(pairVec);
	REQUIRE( seqVec.getSize() == 5);
}


/*
class RNSeqVec {
public:
	RNSeqVec();
	virtual ~RNSeqVec();
	int sortByLength();
	int sortByLengthAndPotential();
	void removeBadSequences();
	void add(RNSequence& rnSeq);
	int getSize() const;
	RNSequence& getSequenceAt(int index);
	bool isSeqPairWithNext(int firstIndex);
	void append(RNSeqVec& otherVec);
	const std::vector<RNSequence>& getSeqVec() const {
		return seqVec;
	}

};
*/

