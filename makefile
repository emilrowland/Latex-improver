OBJS = main.o latexImprover.o KMP.o
IDIR = ./include
CXXFLAGS += -I$(IDIR)

LatexImprover: $(OBJS)
	g++ -o LatexImprover $(OBJS)

main.o: main.cpp
	g++ -c $(CXXFLAGS) main.cpp
	
latexImprover.o: src/latexImprover.cpp
	g++ -c $(CXXFLAGS) src/latexImprover.cpp

KMP.o: src/KMP.cpp
	g++ -c $(CXXFLAGS) src/KMP.cpp