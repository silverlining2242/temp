* generate the .in binary file  height width \   
g++ generateBinary.cc 8 8 3 8.in  \
(in the code i set the random number generate between 1~100, it can change to generate more testcases)

* seq version run
./conv_seq ./eight.in eight.out 

* see the output file in txt (can compare with console print out using ./conv_seq)
./BinarytoTxt eight.out eight_see.txt 6 6
