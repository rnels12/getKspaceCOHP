# getKspaceCOHP
A code to filter out further the k-dependent COHP based on a given pair of orbitals to be plotted.

To compile the code:

g++ -o getKspaceCOHP.x getKspaceCOHP.cpp

Once succesfully compiled, the binary file needs to be put in your bin dir.

To run the program, simply run the following command on your terminal in your working directory:

getKspaceCOHP.x Atom-nth Orbital-mth Atom-jth Orbital-kth KspaceCOHPBandXth.lobster

where "Xth" is the band index.

The result will be output to the stdout. Once the QE input file is produced, you still need to set the values for the variables ecutwfc and nbnd, the pseudo-potential filenames, and the number of KPOINTS in order for the input file to be useable for a QE calculation.

