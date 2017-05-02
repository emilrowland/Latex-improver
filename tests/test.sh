#!/bin/sh

time -v ../build/LatexImprover testFile1.tex

echo ""

#compare files
if ! cmp newFile1.tex testFile1CorrectResponse.tex
then
    #Error
    echo "Failed"
    rm newFile1.tex
    return 1
fi
rm newFile1.tex
