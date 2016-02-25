reset
 set title "{/=20 Uśredniony czas pracy } \n Rozmiar Zbioru 6000000  elentów od 0 do 16384 \n ilosc prób 2 "  
  
  set term png truecolor
  set datafile separator ' '
  set term png size 1920,1080 
  set output "PLOT.png" 
 set xlabel "Liczba wątków" 
 set origin 0,0
 set multiplot
 set size 1,0.5
 set origin 0,0.5
 set label 11 center at graph 0.5,char 1 " \nRozmiar zbioru:" font ",14" 
  set grid 
  set xtics rotate 
  set nokey 
  set key font ",14" 
  set style fill transparent solid 1 
  set boxwidth 0.5 
  set style fill solid 1.000000 border -1 
  set bmargin 3 
 set ytics auto 
  set y2range [:100]
 # set y4range auto [0:1]
  #set y3tics auto
  set y2tics auto 
  #set y2tics nomirror 
  set ytics nomirror 
  set ylabel "czas [ms]  " 
  set y2label "% poprawnosci" 
  set key autotitle columnhead
  #set y3tics 20 nomirror tc lt 3
  set bmargin 6
 set tmargin  5
  plot '2016-02-25_08:22:35AVERAGE_TIME.csv' using 0:2:xtic(1) axes x1y1 w boxes t columnhead,  \
	''       using 0:2:2 with labels  rotate by -90 offset -0,+1  font   'arial,9'   notitle, \
	''	 using 0:3 axes x1y2  w lines t columnhead lt 2 lc rgb "red" lw 3

set size 1,0.5
set origin 0,0
set boxwidth 0.5
set ytics auto
set ytics nomirror
set xlabel "Wątki"
set ylabel "I/0"
set y2label "czas"
set y2tic auto
set y2range [0:1]
set y2tic nomirror
   plot  '2016-02-25_08:22:35AVERAGE_TIME.csv'  using 1:4:xtic(1) axes x1y1  w lines  t columnhead, \
         '' using 1:5 axes x1y2 w filledcurves  t columnhead
