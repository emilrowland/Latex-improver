OBJS = main.o latexImprover.o KMP.o
COMPILER = clang++ -std=c++11
IDIR = ./include
CXXFLAGS += -I$(IDIR)

LatexImprover: $(OBJS)
	$(COMPILER) -o LatexImprover $(OBJS)

main.o: main.cpp
	$(COMPILER) -c $(CXXFLAGS) main.cpp
	
latexImprover.o: src/latexImprover.cpp
	$(COMPILER) -c $(CXXFLAGS) src/latexImprover.cpp

KMP.o: src/KMP.cpp
	$(COMPILER) -c $(CXXFLAGS) src/KMP.cpp