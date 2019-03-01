echo "Libquantum\n"
cd ./libquantum/src/
./make.out
time ./libquantum 100 8
echo "MCF\n"
cd ../../
cd ./mcf/src/
./make.out
time ./mcf inp.in
