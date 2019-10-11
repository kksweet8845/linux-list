reset
set xlabel 'The array length'
set ylabel 'time(nsec)'
set output 'runtime_diff2.png'
set term png enhanced font 'Verdana,10'
set logscale y 2

plot [:][:]'diff_len2.txt' using 1:2 with lp title 'insert sort',\
'' using 1:3 with lp title 'quick sort',\
'' using 1:4 with lp title 'merge sort'