OBJS = main.o latexImprover.o KMP.o
IDIR = ./include
CXXFLAGS += -I$(IDIR)

LatexImprover: $(OBJS)
	clang++ -std=c++11 -o LatexImprover $(OBJS)

main.o: main.cpp
	clang++ -std=c++11 -c $(CXXFLAGS) main.cpp
	
latexImprover.o: src/latexImprover.cpp
	clang++ -std=c++11 -c $(CXXFLAGS) src/latexImprover.cpp

KMP.o: src/KMP.cpp
	clang++ -std=c++11 -c $(CXXFLAGS) src/KMP.cpp