* generate the .in binary file  height width \   
g++ generateBinary.cc 8 8 3 8.in  \
./BinarytoTxt 8.out temp2out_see.txt out
(in the code i set the random number generate between 1~100, it can change to generate more testcases)

* seq version
./conv_seq ./eight.in eight.out 

* output 
./BinarytoTxt eight.out eight_see.txt 6 6
