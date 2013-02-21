set style data lines
set xlabel "Iteration"
set ylabel "x"
set xrange [0:1000]
set yrange [-0.5:1.5]
set key off

set term wxt 0
set title '0.04'
plot for [i=2:25] "./out/pos.G0.04.P25" using 1:i ls 1
set term png
set output "0.04.png"
replot

set term wxt 1
set title '0.1'
plot for [i=2:25] "./out/pos.G0.1.P25" using 1:i ls 1
set term png
set output "0.1.png"
replot

set term wxt 2
set title '0.5'
plot for [i=2:25] "./out/pos.G0.5.P25" using 1:i ls 1
set term png
set output "0.5.png"
replot

# density plots
set ylabel "density"
set yrange [0:50]
set key on bottom right
set term wxt 3
set title 'density'
plot "./out/dens.G0.04.P25", "./out/dens.G0.1.P25", "./out/dens.G0.5.P25"
set term png
set output "density.png"
replot
