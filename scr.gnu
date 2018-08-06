#set format x "%.2e"
#set format y "%.3e"
set xtics auto
set ytics auto
#unset key
set key left top

plot 'obsrv2.dat' using 1:2 smooth bezier title 'N=4'
replot 'obsrv3.dat' using 1:2 smooth bezier title 'N=8'
replot 'obsrv4.dat' using 1:2 smooth bezier title 'N=16'
replot 'obsrv5.dat' using 1:2 smooth bezier title 'N=25'
replot 'obsrv8.dat' using 1:2 smooth bezier title 'N=64'
replot 'obsrv12.dat' using 1:2 smooth bezier title 'N=144'
replot 'obsrv15.dat' using 1:2 smooth bezier title 'N=225'


#set term eps
#set output 'teste.eps'
#replot
#unset term
