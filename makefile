OBJS = main.o latexImprover.o KMP.o
IDIR = ./include
CXXFLAGS += -I$(IDIR)

LatexImprover: $(OBJS)
	g++ -std=c++11 -o LatexImprover $(OBJS)

main.o: main.cpp
	g++ -std=c++11 -c $(CXXFLAGS) main.cpp
	
latexImprover.o: src/latexImprover.cpp
	g++ -std=c++11 -c $(CXXFLAGS) src/latexImprover.cpp

KMP.o: src/KMP.cpp
	g++ -std=c++11 -c $(CXXFLAGS) src/KMP.cpp