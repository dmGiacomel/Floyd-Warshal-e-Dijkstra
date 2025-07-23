sizes=("10" "25" "50" "75" "100" "150" "200" "250" "300" "400" "500" "650" "800" "1000" "1500")

for size in "${sizes[@]}"; do
    echo "Executando grafo de tamanho $size, com Dijkstra"
    ./dijkstra_all_pairs < grafos/$size.txt
done