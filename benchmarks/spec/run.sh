echo "Libquantum\n"
cd ./libquantum/src/
time ./make.out 1397 8
echo "MCF\n"
cd ../../
cd ./mcf/src/
time ./make.out inp.in 
