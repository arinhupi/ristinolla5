#include "catch.hpp"
#include "RNTable.h"

TEST_CASE("RNTable size", "[RNTable]"){
	RNTable rtable(5, 5);
	REQUIRE( rtable.getCols() == 5 );
	REQUIRE( rtable.getRows() == 5 );
}

TEST_CASE("RNTable set and get", "[RNTable]"){
	RNTable rtable(10, 10);
	rtable.setValue(0, 0, 1);
	REQUIRE( rtable.getValue(0,0) == 1 );
	REQUIRE( rtable.getValue(1,1) == 0 );
}

TEST_CASE("RNTable findAllSeqs", "[RNTable]"){
	RNTable rtable(10, 10);
	RNSeqVec seqVec;
	rtable.setValue(5, 5, 1);
	rtable.findAllSeqs(1, seqVec);
	REQUIRE( seqVec.getSize() == 4 );
}

TEST_CASE("RNTable findSeqsAndPairs", "[RNTable]"){
	RNTable rtable(10, 10);
	RNSeqVec seqVec, pairVec;
	rtable.setValue(5, 5, 1);
	rtable.setValue(5, 7, 1);
	rtable.setValue(7, 7, 1);
	rtable.findSeqsAndPairs(1, seqVec, pairVec);
	REQUIRE (pairVec.getSize() == 3);
}

/* 
class RNTable {
public:
	RNTable(int rows, int cols);
	virtual ~RNTable();
	void displayAll();
	void setValue(int r, int c, int newVal);
	int getValue(int r, int c);
	int findAllSeqs(int value, RNSeqVec& seqVec);
	int findSeqsAndPairs(int value, RNSeqVec& seqVec, RNSeqVec& pairVec);

	int getCols() const {
		return cols;
	}

	int getRows() const {
		return rows;
	}
*/

