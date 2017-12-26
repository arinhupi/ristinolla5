#include "catch.hpp"
#include "RNPlayer.h"

TEST_CASE( "RNPlayer init", "[RNPlayer]" ){
	RNPlayer player("testplayer", 2);
	REQUIRE( player.getName() == "testplayer" );
	REQUIRE( player.getMyVal() == 2 );
}

TEST_CASE( "RNPlayer move", "[RNPlayer]" ){
	RNTable rntable(10, 10);
	RNPlayer player("testplayer", 2);
	rntable.setValue(0, 0, 1);
	rntable.setValue(0, 1, 1);
	rntable.setValue(0, 2, 1);
	REQUIRE( player.compMove(rntable, 1, 0) == 3 );
	REQUIRE( rntable.getValue(0, 3) == 2 );
}


/*
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
*/

