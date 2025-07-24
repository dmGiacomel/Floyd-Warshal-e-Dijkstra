g++ dijkstra_decrease_key.cpp -o dijkstra_decrease_key -O3
sizes=("10" "25" "50" "75" "100" "150" "200" "250" "300" "400" "500" "650" "800" "1000" "1500")


for size in "${sizes[@]}"; do
    echo "Executando grafo de tamanho $size, com Dijkstra DK"
    echo "Execution Time(s),Graph Size" > dijkstra_dk_$size.csv
    for i in {0..6}; do
        ./dijkstra_decrease_key < grafos/$size.txt >> dijkstra_dk_$size.csv
    done
done