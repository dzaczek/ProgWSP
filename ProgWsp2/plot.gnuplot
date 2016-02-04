reset
set term png truecolor 
set term png size 1600, 500
set output "profit_line.png"
set xlabel "ZAKRES"
set ylabel "WARTOSCI "
set grid
set boxwidth 1.95 relative
set style fill transparent solid 0.5 noborder
list=system('ls -1B *watek.txt | sort -h')
plot for[file in list] file  using 1:2 w line  title  file

reset
set term png truecolor 
set term png size 1600, 500
set output "profit_box.png"
set xlabel "ZAKRES"
set ylabel "WARTOSCI "
set grid
set boxwidth 0.95 relative
set style fill transparent solid 0.5 noborder
list=system('ls -1B *watek.txt | sort -h')
plot for[file in list] file  using 1:2 w boxes  title  file

reset
set term png truecolor 
set term png size 1600, 400
set output "profit_dots.png"
set xlabel "ZAKRES"
set ylabel "WARTOSCI "
set grid
set boxwidth 1.95 relative
set style fill transparent solid 0.5 noborder
list=system('ls -1B *watek.txt | sort -h')
plot for[file in list] file  using 1:2 w points  title  file
