CXX = g++-14.2.0 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header
HEADERS = iostream vector cstddef algorithm sstream fstream string cstdlib ctime
SQUARE = Square.cc Square-impl.cc
PROPERTY = Property.cc Property-impl.cc
NONPROPERTY = Non-Property.cc Non-Property-impl.cc
ACADEMIC = Academic.cc Academic-impl.cc
GYMS = Gyms.cc Gyms-impl.cc
RESIDENCE = Residence.cc Residence-impl.cc
OSAP = OSAP.cc OSAP-impl.cc
TUITION = Tuition.cc Tuition-impl.cc
GOOSE = Goose-Nesting.cc Goose-Nesting-impl.cc
COOP = COOP-Fee.cc COOP-Fee-impl.cc
SLC = SLC.cc SLC-impl.cc
NH = NH.cc NH-impl.cc
GOTOTIMS = GoToTims.cc GoToTims-impl.cc
DC = DCTimsLine.cc DCTimsLine-impl.cc
PROPERTYINFO = PropertyInfo.cc
PLAYER = Player.cc Player-impl.cc
GAMEBOARD = GameBoard.cc GameBoard-impl.cc
GAME = Game.cc Game-impl.cc
EXEC = watopoly

all: one two

one:
	$(CXX) $(HEADERFLAGS) $(HEADERS)

two:
	$(CXX) $(CXXFLAGS) -c $(SQUARE) $(PROPERTY) $(NONPROPERTY) $(ACADEMIC) $(GYMS) $(RESIDENCE)
	$(CXX) $(CXXFLAGS) -c $(OSAP) $(TUITION) $(GOOSE) $(COOP) $(SLC) $(NH) $(GOTOTIMS) $(DC)
	$(CXX) $(CXXFLAGS) -c $(PROPERTYINFO) $(PLAYER) $(GAMEBOARD) $(GAME)
	$(CXX) $(CXXFLAGS) *.o main.cc -o ${EXEC}

clean:
	rm -f $(EXEC)
	rm -f *.o
	rm -rf gcm.cache

.PHONY: all clean one two
