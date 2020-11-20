# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror -D_GLIBCXX_DEBUG
# The object files for the program.
OFILES = scrabbleAssistant.o hashFunctions.o

# The header files for the program
HFILES = $(shell ls -1 *.h)

#common executable dependencies
DEPS = $(HFILES) $(OFILES)

all: scrabbleAssistant

# This target builds your main program.
scrabbleAssistant:  $(DEPS) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f *.o
	rm -f scrabbleAssistant
