reset
set key right top

set xlabel 'T'
set ylabel 'Corr(S^z_i, S^z_j)'

#plot 'n=2.simulation1' using 1:6 smooth bezier title '|i-j|='
plot 'n=4.simulation1' using 1:6 smooth bezier title '|i-j|=1'
replot 'n=8.simulation1' using 1:6 smooth bezier title '|i-j|=2'
replot 'n=16.simulation1' using 1:6 smooth bezier title '|i-j|=5'
replot 'n=32.simulation1' using 1:6 smooth bezier title '|i-j|=12'
replot 'n=64.simulation1' using 1:6 smooth bezier title '|i-j|=13'
replot 'n=128.simulation1' using 1:6 smooth bezier title '|i-j|=6'
