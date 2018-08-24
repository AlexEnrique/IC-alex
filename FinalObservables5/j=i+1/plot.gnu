set yr[-0.05:1.05]
plot 'exact_ising2d.dat' with line lt 7 lw 2 title 'Solução Exata'
replot 'obsrv100.dat' using 1:3 with linespoint lt 6 title 'Simulação'
