reset
set ylabel 'time(nsec)'
set output 'runtime.png'
set format x "%3.0e"
set term png enhanced font 'Verdana,10'
set logscale y 2
set key left bottom
set style boxplot outliers pointtype 7
set style data boxplot
set pointsize 0.5
set boxwidth 0.5
set pointsize 0.5
set xtics ("Insert sort" 1, "Quick sort" 2, "Merge sort" 3) scale 0.0
set xtics nomirror

plot [:][30000:500000]'output.txt' using (1):1  title 'insert sort',\
'' using (2):2  title 'quick sort',\
'' using (3):3  title 'merge sort'