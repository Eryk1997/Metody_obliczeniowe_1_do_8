
set xrange [-14:0]
set yrange [-8:0]
#set terminal wxt size 1280,900
set terminal png size 1366,768
set output "float.png"
set title 'float'
set ylabel 'log10(bledu)'
set xlabel 'log10(kroku)
set grid 
plot \
 "dane_float.txt" using 1:2 with lines title "x=0 progresywna 2p (float)",\
 "dane_float.txt" using 1:3 with lines title "x=0 progresywna 3p (float)",\
 "dane_float.txt" using 1:4 with lines title "x=pi/4 progresywna 2p (float)",\
 "dane_float.txt" using 1:5 with lines title "x=pi/4 centralna (float)",\
 "dane_float.txt" using 1:6 with lines title "x=pi/4 wsteczna 2p (float)",\
 "dane_float.txt" using 1:7 with lines title "x=pi/2 wsteczna 2p (float)",\
 "dane_float.txt" using 1:8 with lines title "x=pi/2 wsteczna 3p (float)"



set xrange [-14:0]
set yrange [-16:0]
#set terminal wxt size 1280,900
set terminal png size 1366,768
set output "double.png"
set title 'double'
set ylabel 'log10(bledu)'
set xlabel 'log10(kroku)
set grid 
plot \
 "dane_double.txt" using 1:2 with lines title "x=0 progresywna 2p (double)",\
 "dane_double.txt" using 1:3 with lines title "x=0 progresywna 3p (double)",\
 "dane_double.txt" using 1:4 with lines title "x=pi/4 progresywna 2p (double)",\
 "dane_double.txt" using 1:5 with lines title "x=pi/4 centralna (double)",\
 "dane_double.txt" using 1:6 with lines title "x=pi/4 wsteczna 2p (double)",\
 "dane_double.txt" using 1:7 with lines title "x=pi/2 wsteczna 2p (double)",\
 "dane_double.txt" using 1:8 with lines title "x=pi/2 wsteczna 3p (double)"



set xrange [-14:0]
set yrange [-16:0]
#set terminal wxt size 1280,900
set terminal png size 1366,768
set output "float_double.png"
set title 'float double'
set ylabel 'log10(bledu)'
set xlabel 'log10(kroku)
set grid 
plot \
 "dane_float.txt" using 1:2 with lines title "x=0 progresywna 2p (float)",\
 "dane_float.txt" using 1:3 with lines title "x=0 progresywna 3p (float)",\
 "dane_float.txt" using 1:4 with lines title "x=pi/4 progresywna 2p (float)",\
 "dane_float.txt" using 1:5 with lines title "x=pi/4 centralna (float)",\
 "dane_float.txt" using 1:6 with lines title "x=pi/4 wsteczna 2p (float)",\
 "dane_float.txt" using 1:7 with lines title "x=pi/2 wsteczna 2p (float)",\
 "dane_float.txt" using 1:8 with lines title "x=pi/2 wsteczna 3p (float)",\
 "dane_double.txt" using 1:2 with lines title "x=0 progresywna 2p (double)",\
 "dane_double.txt" using 1:3 with lines title "x=0 progresywna 3p (double)",\
 "dane_double.txt" using 1:4 with lines title "x=pi/4 progresywna 2p (double)",\
 "dane_double.txt" using 1:5 with lines title "x=pi/4 centralna (double)",\
 "dane_double.txt" using 1:6 with lines title "x=pi/4 wsteczna 2p (double)",\
 "dane_double.txt" using 1:7 with lines title "x=pi/2 wsteczna 2p (double)",\
 "dane_double.txt" using 1:8 with lines title "x=pi/2 wsteczna 3p (double)"

