echo "Libquantum\n"
cd ./libquantum/src/
chmod +x make.out
./make.out
time ./libquantum 100 8
echo "MCF\n"
cd ../../
cd ./mcf/src/
chmod +x make.out
./make.out
time ./mcf inp.in
