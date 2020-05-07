#!/bin/bash
# script created in 2020 by RN

    gnuplot <<- EOF
set terminal postscript enhanced eps color size 14,23 font ",60"
#
set palette defined ( 0 "blue", 1 "green", 2 "yellow", 3 "red", 4 "brown")
set macro
set border linewidth 6
set output 'foo.eps'
set ylabel "Energy (eV)" offset 1.0,0,0 font ",45"
set ytics nomirror
#
unset xtics
plot '${1}' u 4:5:6 w l lw 12 palette t ''
EOF

