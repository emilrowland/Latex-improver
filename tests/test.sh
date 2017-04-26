#!/bin/sh
cd ..

LatexImprover tests/testFile1.tex << EOF
q
EOF

echo ""
cd tests

#compare files
if ! cmp newFile.tex testFile1CorrectResponse.tex
then
    #Error
    rm newFile.tex
    return 1
fi
rm newFile.tex
