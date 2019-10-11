reset
set xlabel 'The n of array'
set ylabel 'time(nsec)'
set output 'runtime_merge.png'
set format x "%3.0e"
set term png enhanced font 'Verdana,10'
set logscale y 2
set key left bottom

plot [:][:]'../ana_merge.txt' using 1:2 with lp title 'mean method',\
'' using 1:3 with lp title 'first method',\
'' using 1:4 with lp title 'random method'