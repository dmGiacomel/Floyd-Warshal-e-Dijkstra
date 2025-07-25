import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sizes = [10, 25, 50, 75, 100, 150, 200, 250, 300, 400, 500, 650, 800, 1000, 1500]
dijkstra_df = pd.DataFrame(columns=["Mean Execution Time", "StdDev Execution Time", "Graph Size"])
floyd_w_df = pd.DataFrame(columns=["Mean Execution Time", "StdDev Execution Time", "Graph Size"])
dijkstra_dk_df = pd.DataFrame(columns=["Mean Execution Time", "StdDev Execution Time", "Graph Size"])

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
        "Mean Execution Time": dijkstra_current['Execution Time(s)'].mean(),
        "StdDev Execution Time": dijkstra_current["Execution Time(s)"].std(),
        "Graph Size": size
    }

    dijkstra_df.loc[len(dijkstra_df)] = new_data

    # ----------------------------------------------------------
    # processando o csv de floyd warhsall
    f_filename = "floyd_warshall_" + str(size) + ".csv"
    floyd_current = pd.read_csv(f_filename)

    # tirar o maior e menor em tempo de execucao
    index_max = floyd_current['Execution Time(s)'].idxmax()
    floyd_current =floyd_current.drop(index_max)

    index_min = floyd_current['Execution Time(s)'].idxmin()
    floyd_current = floyd_current.drop(index_min)

    new_data = {
        "Mean Execution Time": floyd_current['Execution Time(s)'].mean(),
        "StdDev Execution Time": floyd_current["Execution Time(s)"].std(),
        "Graph Size": size
    }
    floyd_w_df.loc[len(floyd_w_df)] = new_data

    # ----------------------------------------------------------
    # processando o csv de dijkstra dk
    f_filename = "dijkstra_dk_" + str(size) + ".csv"
    dijkstra_dk_current = pd.read_csv(f_filename)

    # tirar o maior e menor em tempo de execucao
    index_max = dijkstra_dk_current['Execution Time(s)'].idxmax()
    dijkstra_dk_current =dijkstra_dk_current.drop(index_max)

    index_min = dijkstra_dk_current['Execution Time(s)'].idxmin()
    dijkstra_dk_current = dijkstra_dk_current.drop(index_min)

    new_data = {
        "Mean Execution Time": dijkstra_dk_current['Execution Time(s)'].mean(),
        "StdDev Execution Time": dijkstra_dk_current["Execution Time(s)"].std(),
        "Graph Size": size
    }
    dijkstra_dk_df.loc[len(dijkstra_dk_df)] = new_data

dijkstra_df.to_csv("dijkstra_data.csv", index=False)

floyd_w_df.to_csv("floyd_warshall_data.csv", index=False)

dijkstra_dk_df.to_csv("dijkstra_dk_data.csv", index=False)

# ------------------------------------------------------------------------------------------------
# graficos de comparacao dos algoritmos ----------------------------------------------------------
plt.figure(figsize=(12,8))

# plotar linhas de cada alg
plt.plot(dijkstra_df['Graph Size'], dijkstra_df['Mean Execution Time'], 
         marker='o', linewidth=2, label='Dijkstra (S/ DecreaseKey)', color='blue')

plt.plot(floyd_w_df['Graph Size'], floyd_w_df['Mean Execution Time'], 
         marker='s', linewidth=2, label='Floyd-Warshall', color='red')

plt.plot(dijkstra_dk_df['Graph Size'], dijkstra_dk_df['Mean Execution Time'], 
         marker='^', linewidth=2, label='Dijkstra (C/ DecreaseKey)', color='green')

# Configurações do gráfico
plt.xlabel('Tamanho do Grafo (número de vértices)', fontsize=14)
plt.ylabel('Tempo Médio de Execução (segundos)', fontsize=14)
#plt.title('Comparação de Performance: Dijkstra vs Floyd-Warshall vs Dijkstra DK', fontsize=14)
plt.legend(fontsize=14)
plt.grid(True, alpha=0.3)
# Configurar o eixo X com os valores reais dos tamanhos
plt.xticks(sizes, rotation=90)
#plt.yscale('log')  # Escala logarítmica para melhor visualização
#plt.xscale('log')  # Escala logarítmica para o eixo X também
plt.tight_layout()
plt.tick_params(axis='both', which='major', labelsize=12)

plt.savefig('comparacao_total.png', dpi=300, bbox_inches='tight')
plt.show()


# ========== GRÁFICO ZOOM (10 a 500 vértices) ==========
plt.figure(figsize=(12, 8))

# Filtrar dados para zoom (10 a 500 vértices)
zoom_sizes = [s for s in sizes if 10 <= s <= 300]

# Filtrar DataFrames
dijkstra_zoom = dijkstra_df[dijkstra_df['Graph Size'].isin(zoom_sizes)]
floyd_zoom = floyd_w_df[floyd_w_df['Graph Size'].isin(zoom_sizes)]
dijkstra_dk_zoom = dijkstra_dk_df[dijkstra_dk_df['Graph Size'].isin(zoom_sizes)]

# Plotar linhas para o zoom
plt.plot(dijkstra_zoom['Graph Size'], dijkstra_zoom['Mean Execution Time'], 
         marker='o', linewidth=2, label='Dijkstra (S/ DecreaseKey)', color='blue')

plt.plot(floyd_zoom['Graph Size'], floyd_zoom['Mean Execution Time'], 
         marker='s', linewidth=2, label='Floyd-Warshall', color='red')

plt.plot(dijkstra_dk_zoom['Graph Size'], dijkstra_dk_zoom['Mean Execution Time'], 
         marker='^', linewidth=2, label='Dijkstra (C/ DecreaseKey)', color='green')

# Configurações do gráfico zoom
plt.xlabel('Tamanho do Grafo (número de vértices)', fontsize=14)
plt.ylabel('Tempo Médio de Execução (segundos)', fontsize=14)
#plt.title('Comparação de Performance - Zoom (10 a 500 vértices)', fontsize=14)
plt.legend(fontsize=14)
plt.grid(True, alpha=0.3)

# Configurar eixo X apenas com os tamanhos do zoom
plt.xticks(zoom_sizes, rotation=45)
plt.tick_params(axis='both', which='major', labelsize=12)
# Opcional: usar escala logarítmica se necessário
# plt.yscale('log')

plt.tight_layout()
plt.savefig('comparacao_ate_300.png', dpi=300, bbox_inches='tight')

plt.show()