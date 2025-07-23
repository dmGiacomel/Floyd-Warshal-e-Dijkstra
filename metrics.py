import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sizes = [10, 25, 50, 75, 100, 150, 200, 250, 300, 400, 500, 650, 800, 1000, 1500]
dijkstra_df = pd.read_csv('dijkstra_data.csv')
floyd_w_df = pd.read_csv('floyd_warshall_data.csv')

for size in sizes:
    # processando o csv de dijkstra
    d_filename = "dijkstra_" + str(size) + ".csv"
    dijkstra_current = pd.read_csv(d_filename)

    # tirar o maior e menor em tempo de execucao
    index_max = dijkstra_current['Execution Time(s)'].idxmax()
    dijkstra_current = dijkstra_current.drop(index_max)

    index_min = dijkstra_current['Execution Time(s)'].idxmin()
    dijkstra_current = dijkstra_current.drop(index_min)

    new_data = {
        "Execution Time(s)": dijkstra_current['Execution Time(s)'].mean(),
        "Graph Size": size,
        "Distance": 0 # vai precisar mudar isso depois! to fazendo assim por enquanto
    }

    dijkstra_df.loc[len(dijkstra_df)] = new_data

    # ----------------------------------------------------------
    # processando o csv de floyd warhsall
    f_filename = "floyd_warhsall_" + str(size) + ".csv"
    floyd_current = pd.read_csv(f_filename)

    # tirar o maior e menor em tempo de execucao
    index_max = floyd_current['Execution Time(s)'].idxmax()
    floyd_current =floyd_current.drop(index_max)

    index_min = floyd_current['Execution Time(s)'].idxmin()
    floyd_current = floyd_current.drop(index_min)

    new_data = {
        "Execution Time(s)": floyd_current['Execution Time(s)'].mean(),
        "Graph Size": size,
        "Distance": 0 # vai precisar mudar isso depois! to fazendo assim por enquanto
    }
    floyd_w_df.loc[len(floyd_w_df)] = new_data

