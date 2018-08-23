set key right top

#plot 'obsrv2.dat' using 1:3 title 'N = 4' with linespoint
#replot 'obsrv3.dat' using 1:3 title 'N = 9' with linespoint
#replot 'obsrv4.dat' using 1:3 title 'N = 16' with linespoint
plot 'obsrv5.dat' using 1:3 title 'N = 25' with linespoint
replot 'obsrv8.dat' using 1:3 title 'N = 64' with linespoint
replot 'obsrv12.dat' using 1:3 title 'N = 144' with linespoint
replot 'obsrv15.dat' using 1:3 title 'N = 225' with linespoint
replot 'obsrv100.dat' using 1:3 title 'N = 10000' with linespoint lt 8
