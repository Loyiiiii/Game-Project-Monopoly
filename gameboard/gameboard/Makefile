CXX := g++
CXXFLAGS := -c
OBJS := Square.o Square-impl.o \
        Property.o Property-impl.o \
        Non-Property.o Non-Property-impl.o \
        Academic.o Academic-impl.o \
        Gyms.o Gyms-impl.o \
        Residence.o Residence-impl.o \
        OSAP.o OSAP-impl.o \
        Tuition.o Tuition-impl.o \
        Goose-Nesting.o Goose-Nesting-impl.o \
        COOP-Fee.o COOP-Fee-impl.o \
        SLC.o SLC-impl.o \
        NH.o NH-impl.o \
        GoToTims.o GoToTims-impl.o \
        DCTimsLine.o DCTimsLine-impl.o \
        PropertyInfo.o \
        Player.o Player-impl.o \
        GameBoard.o GameBoard-impl.o \
        Game.o Game-impl.o

all: executable

executable: $(OBJS) main.cc
	$(CXX) -o $@ $(OBJS) main.cc

%.o %-impl.o: %.cc %-impl.cc
	$(CXX) $(CXXFLAGS) $^ 

PropertyInfo.o: PropertyInfo.cc
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -f $(OBJS) executable
	rm -r gcm.cache
.PHONY: all clean
