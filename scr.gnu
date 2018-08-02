#set format x "%.2e"
#set format y "%.3e"
set xtics auto
set ytics auto
#unset key
set key left top

plot 'teste.dat' w linespoint
#plot 'teste2.dat' w l title 'numSpins = 4'
#replot 'teste3.dat' w l title 'numSpins = 9'
#replot 'teste4.dat' w l title 'numSpins = 16'
#replot 'teste5.dat' w l title 'numSpins = 25'
#replot 'teste6.dat' w l title 'numSpins = 36'

#set term eps
#set output 'teste.eps'
#replot
#unset term
