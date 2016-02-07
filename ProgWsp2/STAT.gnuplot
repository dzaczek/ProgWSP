reset
set term png truecolor
set datafile separator ' '
set term png size 1900, 1000
set output "profit_line.png"
set xlabel "ZAKRES"
set ylabel "WARTOSCI "
set grid
set boxwidth 1 relative
set style fill transparent solid 0.5 noborder
set key autotitle columnhead
#$list=system('ls -1B *STATS.csv | sort -h')
plot for [col=2:17] '2016-02-07_03:21:10STATS.csv'  using 1:(column(int(col))) w line t 
