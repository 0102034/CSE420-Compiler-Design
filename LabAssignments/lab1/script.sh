#!/bin/bash
/*generates parser*/
yacc -d -y --debug --verbose 22301002.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'

/*generates lexar*/
flex 22301002.l
echo 'Generated the scanner C file'
g++ -fpermissive -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'

/*linking*/
g++ y.o l.o
echo 'All ready, running'
#./a.exe input.txt