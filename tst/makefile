TARGET_EXEC := rnollaTest

BUILD_DIR ?= .

SRCS := rnollaTest.cpp RNTableTest.cpp RNPlayerTest.cpp RNSequenceTest.cpp RNSeqVecTest.cpp ../RNTable.cpp ../RNPlayer.cpp ../RNSequence.cpp ../RNSeqVec.cpp
OBJS := $(addsuffix .o,$(basename $(SRCS)))

INC_FLAGS := -I.. -I.

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CXXFLAGS := -Wall -std=c++11

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) *.o






