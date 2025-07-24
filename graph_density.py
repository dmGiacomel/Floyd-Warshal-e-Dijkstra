import os
import numpy as np
import pandas as pd

def read_graph_from_file(filepath):
    """
    Lê um arquivo de grafo e retorna o número de vértices e a matriz de adjacência.
    
    Formato esperado do arquivo:
    - Primeira linha: número de vértices
    - Linhas seguintes: matriz de adjacência com pesos
    """
    with open(filepath, 'r') as file:
        lines = file.readlines()
    
    # Número de vértices
    num_vertices = int(lines[0].strip())
    
    # Matriz de adjacência
    adjacency_matrix = []
    for i in range(1, num_vertices + 1):
        row = list(map(float, lines[i].strip().split()))  # float para suportar pesos decimais
        adjacency_matrix.append(row)
    
    return num_vertices, np.array(adjacency_matrix)

def calculate_density_weighted_undirected(num_vertices, adjacency_matrix):
    """
    Calcula a densidade de um grafo não direcionado com pesos.
    Considera apenas se existe aresta (peso > 0), não o valor do peso.
    
    Densidade = 2 * número_de_arestas / (vertices * (vertices - 1))
    """
    if num_vertices <= 1:
        return 0
    
    # Cria matriz binária: 1 se existe aresta (peso > 0), 0 caso contrário
    binary_matrix = (adjacency_matrix > 0).astype(int)
    
    # Para grafo não direcionado, conta apenas o triângulo superior (evita contar arestas duas vezes)
    num_edges = np.sum(np.triu(binary_matrix, k=1))
    print("num_edges=", num_edges)
    # Máximo possível de arestas em grafo não direcionado
    max_edges = num_vertices * (num_vertices - 1) / 2
    print("max_edges=", max_edges)
    # Calcula densidade
    density = num_edges / max_edges if max_edges > 0 else 0
    
    return density

def get_graph_density(size):
    """
    Obtém a densidade do grafo para um tamanho específico.
    Procura arquivo no formato: grafo_{size}.txt
    """
    filename = f"{size}.txt"
    filepath = os.path.join("grafos", filename)
    
    if not os.path.exists(filepath):
        print(f"Arquivo {filepath} não encontrado!")
        return 0
    
    try:
        num_vertices, adjacency_matrix = read_graph_from_file(filepath)
        density = calculate_density_weighted_undirected(num_vertices, adjacency_matrix)
        return density
    except Exception as e:
        print(f"Erro ao processar arquivo {filename}: {e}")
        return 0

def analyze_all_graph_densities(sizes):
    """
    Analisa a densidade de todos os grafos nos tamanhos especificados.
    """
    densities = {}
    
    print("=== ANÁLISE DE DENSIDADE DOS GRAFOS ===")
    for size in sizes:
        density = get_graph_density(size)
        densities[size] = density
        
        # Informações adicionais do grafo
        filename = f"{size}.txt"
        filepath = os.path.join("grafos", filename)
        
        if os.path.exists(filepath):
            try:
                num_vertices, adjacency_matrix = read_graph_from_file(filepath)
                binary_matrix = (adjacency_matrix > 0).astype(int)
                num_edges = np.sum(np.triu(binary_matrix, k=1))
                
                print(f"Tamanho {size}: {num_vertices} vértices, {num_edges} arestas, densidade = {density:.4f} ({density*100:.2f}%)")
            except:
                print(f"Tamanho {size}: densidade = {density:.4f} (erro ao ler detalhes)")
        else:
            print(f"Tamanho {size}: arquivo não encontrado")
    
    return densities

sizes = [10, 25, 50, 75, 100, 150, 200, 250, 300, 400, 500, 650, 800, 1000, 1500]
analyze_all_graph_densities(sizes)