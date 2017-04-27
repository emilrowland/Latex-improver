#!/bin/sh

../build/LatexImprover testFile1.tex << EOF
q
EOF

echo ""

#compare files
if ! cmp newFile.tex testFile1CorrectResponse.tex
then
    #Error
    rm newFile.tex
    return 1
fi
rm newFile.tex
