set style data lines
set xlabel "Iteration"
set ylabel "x"
set xrange [0:1000]
set yrange [-0.5:1.5]
set key off
set term wxt 0
plot for [i=2:25] "./out/pos.G0.04.E0.001.P25" using 1:i ls 1
set term wxt 1
plot for [i=2:25] "./out/pos.G0.1.E0.001.P25" using 1:i ls 1
set term wxt 2
plot for [i=2:25] "./out/pos.G0.5.E0.001.P25" using 1:i ls 1

# density plots
set ylabel "density"
set yrange [0:30]
set key on bottom right
set term wxt 3
plot "./out/dens.G0.04.E0.001.P25", "./out/dens.G0.1.E0.001.P25", "./out/dens.G0.5.E0.001.P25"
