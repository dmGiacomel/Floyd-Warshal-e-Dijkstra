g++ floyd_warshall_all_pairs.cpp -o floyd_warshall_all_pairs -O3
sizes=("10" "25" "50" "75" "100" "150" "200" "250" "300" "400" "500" "650" "800" "1000" "1500")

for size in "${sizes[@]}"; do
    echo "Execution Time(s),Graph Size,Distance" > floyd_warshall_$size.csv
    echo "Executando grafo de tamanho $size, com Floyd-Warshall"
    for i in {0..6}; do
        ./floyd_warshall_all_pairs < grafos/$size.txt >> floyd_warshall_$size.csv
    done
done