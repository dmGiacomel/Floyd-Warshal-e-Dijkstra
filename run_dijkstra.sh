g++ dijkstra_all_pairs.cpp -o dijkstra_all_pairs -O3
sizes=("10" "25" "50" "75" "100" "150" "200" "250" "300" "400" "500" "650" "800" "1000" "1500")


for size in "${sizes[@]}"; do
    echo "Executando grafo de tamanho $size, com Dijkstra"
    echo "Execution Time(s),Graph Size,Distance" > dijkstra_$size.csv
    for i in {0..6}; do
        ./dijkstra_all_pairs < grafos/$size.txt >> dijkstra_$size.csv
    done
done