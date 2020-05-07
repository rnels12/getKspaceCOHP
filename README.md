# getKspaceCOHP
A code to filter out further the k-dependent COHP based on a given pair of orbitals and write them into a gnuplot format.

To compile the code:

g++ -o getKspaceCOHP.x getKspaceCOHP.cpp

Once succesfully compiled, the binary file needs to be put in your bin dir.

To run the program, simply run the following command on your terminal in your working directory:

getKspaceCOHP.x Atom-nth Orbital-mth Atom-jth Orbital-kth KspaceCOHPBandXth.lobster

where "Xth" is the band index.

The result will be output to the stdout. 

