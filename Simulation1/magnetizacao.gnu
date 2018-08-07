reset
set key left top

set xlabel 'T'
set ylabel 'Magnetização por spin'

plot 'n=2.simulation1' using 1:3 smooth bezier title 'N=4'
replot 'n=4.simulation1' using 1:3 smooth bezier title 'N=16'
replot 'n=8.simulation1' using 1:3 smooth bezier title 'N=64'
replot 'n=16.simulation1' using 1:3 smooth bezier title 'N=256'
replot 'n=32.simulation1' using 1:3 smooth bezier title 'N=1.024'
replot 'n=64.simulation1' using 1:3 smooth bezier title 'N=4.096'
replot 'n=128.simulation1' using 1:3 smooth bezier title 'N=16.384'
