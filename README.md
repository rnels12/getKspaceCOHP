# getKspaceCOHP
A code to filter out further the k-dependent COHP based on a given pair of orbitals and write them into a gnuplot format.

To compile the code:

g++ -o getKspaceCOHP.x getKspaceCOHP.cpp

Once succesfully compiled, the binary file needs to be put in your bin dir.

To run the program, simply run the following command on your terminal in your working directory:

getKspaceCOHP.x Atom-nth Orbital-mth Atom-jth Orbital-kth KspaceCOHPBandXth.lobster

where "Xth" is the band index.

The result will be output to the stdout. 

In kspace_example, you can find an example of input files. By using the following command in that directory:

/getKspaceCOHP.x F1 2s F1 2p_y KspaceCOHPBand*.lobster > foo

You will get the output in the file foo consisting of six columns: 
the first three columns represent the k-point fractional coordinates, the fourth the x axis points of the plot,
and the fifth the eigenvalues, and the sixth the COHP.

You can plot the data in foo with the gnuplot script included in the example directory. The output will be an eps file called "foo.eps".
And you can see the plot with, for instance, gv. Feel free to modify the script further as you see fit.


