vmstat > output-vm.txt
echo "Libquantum\n"
cd ./libquantum/src/
chmod +x make.out
./make.out
time ./libquantum 500 8 > output-time.txt
vmstat > output-vm.txt
echo "MCF\n"
cd ../../
cd ./mcf/src/
chmod +x make.out
./make.out
time ./mcf inp.in > output-time.txt
vmstat > output-vm.txt
