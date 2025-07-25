g++ compare_results.cpp -o compare_results -O3
sizes=("10" "25" "50" "75" "100" "150" "200" "250" "300" "400" "500" "650" "800" "1000" "1500")

for size in "${sizes[@]}"; do
    echo "Checando a igualdade dos resultados para grafo $size"
    echo "(Deve imprimir a mensagem 'Pass :D')"
    ./compare_results < grafos/$size.txt
done