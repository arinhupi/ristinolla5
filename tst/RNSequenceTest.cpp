#include "catch.hpp"
#include "RNSequence.h"

TEST_CASE( "RNSequence fill", "[RNSequence]" ){
	std::vector<int> virtualRow = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
	RNSequence rnseq;
	rnseq.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	REQUIRE (rnseq.getStartRow() == 0);
	REQUIRE (rnseq.getStartCol() == 0);
	REQUIRE (rnseq.getSeqStartIndex() == 0);
	REQUIRE (rnseq.getDirection() == 1 /*HORIZONTAL*/ );
}

TEST_CASE ("RNSequence is seq pair", "[RNSequence]" ){
	std::vector<int> virtualRow = {1, 1, 1, 0, 1, 0, 0, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	rnseq3.fillValues(0, 0, 7, 1 /*HORIZONTAL*/, 2, virtualRow, 1);
	REQUIRE (rnseq1.isSeqPair(rnseq2) == true );
	REQUIRE (rnseq2.isSeqPair(rnseq3) == false );
}

TEST_CASE( "RNSequence pair fill", "[RNSequence]" ){
	std::vector<int> virtualRow = {1, 1, 1, 0, 1, 0, 0, 1, 1, 0};
	RNSequence rnseq1, rnseq2, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow, 1);
	seqPair.fillSeqPairValues(rnseq1, rnseq2);
	REQUIRE (seqPair.getLength() == 4);
	REQUIRE (seqPair.getStartRow() == 0);
	REQUIRE (seqPair.getStartCol() == 0);
	REQUIRE (seqPair.getSeqStartIndex() == 0);
	REQUIRE (seqPair.getDirection() == 1 /*HORIZONTAL*/ );
}

TEST_CASE( "RNSequence good for move", "[RNSequence]" ){
	std::vector<int> virtualRow1 = {1, 1, 1, 0, 1, 0, 0, 1, 1, 0};
	std::vector<int> virtualRow2 = {1, 1, 1, 2, 1, 0, 0, 1, 1, 0};
	std::vector<int> virtualRow3 = {1, 1, 1, 0, 1, 2, 1, 1, 1, 0};
	RNSequence rnseq1, rnseq2, rnseq3;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow1, 1);
	REQUIRE (rnseq1.isGoodForMove() == true);

	//not good for move because no free ending
	rnseq2.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow2, 1);
	REQUIRE (rnseq2.isGoodForMove() == false);

	//not good for move because not enough potential length
	rnseq3.fillValues(0, 0, 6, 1 /*HORIZONTAL*/, 3, virtualRow3, 1);
	REQUIRE (rnseq3.isGoodForMove() == false);
}

TEST_CASE( "RNSequence get optimal move", "[RNSequence]" ){
	std::vector<int> virtualRow1 = {1, 1, 1, 0, 1, 0, 0, 1, 1, 0};
	std::vector<int> virtualRow2 = {1, 1, 1, 2, 1, 0, 0, 1, 1, 0};
	std::vector<int> virtualRow3 = {1, 1, 1, 0, 1, 2, 1, 1, 1, 0};
	int row, col;
	RNSequence rnseq1, rnseq2, rnseq3;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow1, 1);
	rnseq1.getOptimalMove(row, col);
	REQUIRE (row == 0);	REQUIRE (col == 3);

	rnseq1.fillValues(0, 0, 0, 2 /*VERTICAL*/, 3, virtualRow1, 1);
	rnseq1.getOptimalMove(row, col);
	REQUIRE (row == 3); REQUIRE (col == 0);

	rnseq1.fillValues(0, 0, 0, 4 /*DIAGONAL_DOWN*/, 3, virtualRow1, 1);
	rnseq1.getOptimalMove(row, col);
	REQUIRE (row == 3); REQUIRE (col == 3);
}

TEST_CASE( "RNSequence optimal move of seq pair", "[RNSequence]" ){
	std::vector<int> virtualRow1 = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0};
	int row, col;
	RNSequence rnseq1, rnseq2, seqPair;
	rnseq1.fillValues(0, 0, 1, 1 /*HORIZONTAL*/, 2, virtualRow1, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow1, 1);
	seqPair.fillSeqPairValues(rnseq1, rnseq2);
	seqPair.getOptimalMove(row, col);
	REQUIRE (row == 0); REQUIRE (col == 3);
}

TEST_CASE( "RNSequence getFreedom", "[RNSequence]" ){
	std::vector<int> virtualRow1 = {1, 1, 1, 0, 1, 0, 0, 0, 0, 0};
	RNSequence rnseq1, rnseq2, seqPair;
	rnseq1.fillValues(0, 0, 0, 1 /*HORIZONTAL*/, 3, virtualRow1, 1);
	rnseq2.fillValues(0, 0, 4, 1 /*HORIZONTAL*/, 1, virtualRow1, 1);
	seqPair.fillSeqPairValues(rnseq1, rnseq2);

	REQUIRE (rnseq1.getFreedom() == 1);
	REQUIRE (rnseq2.getFreedom() == 2);
	REQUIRE (seqPair.getFreedom() == 3);
}


/*
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
*/
