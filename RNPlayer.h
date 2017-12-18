/*
 * RNPlayer.h
 *
 *  Created on: 14.11.2017
 *      Author: ari
 */

#ifndef RNPLAYER_H_
#define RNPLAYER_H_

#include "RNTable.h"

#include <string>

class RNPlayer {

public:
    RNPlayer(std::string name, int myVal) ;
	virtual ~RNPlayer();
    //int move(RNTable& rnTable);
	int compMove(RNTable& rnTable, int oppVal, int round);    
	const std::string& getName() const {
		return name;
	}

	int getMyVal() const {
		return myVal;
	}

private:
	std::string name;
	int myVal;
    //void queryLocation(RNTable& rnTable, int& row, int& col) const;

};

#endif /* RNPLAYER_H_ */
