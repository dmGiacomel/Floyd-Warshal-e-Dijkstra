#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iomanip>

const int INF = INT32_MAX/2;

int** getMatrix(size_t rows, size_t columns){
    int **matrix = new int*[rows];
    matrix[0] = new int[columns * rows];
    for (size_t i = 1; i < rows; i++){
        matrix[i] = matrix[i - 1] + columns;
    }
    return matrix;
}

void initMatrix(size_t rows, size_t columns, int** matrix, int default_value){
    for (size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            matrix[i][j] = default_value;
        }
    }
}

//necessary considering that the entries have 0 as a weight for non-existing edges
void fillInfinitys(size_t rows, size_t columns, int** matrix){
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < columns; j++){
            if (matrix[i][j] == 0){
                matrix[i][j] = INF;
            }
        }
    }
}

void readMatrix(size_t rows, size_t columns, int** matrix){
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < columns; j++){
            std::cin >> matrix[i][j];
        }
    }
}

void freeMatrixContiguous(int** matrix){
    delete[] matrix[0];
    delete[] matrix;
}

void freeMatrixNonContiguous(int** matrix, size_t rows){
    for (size_t i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}

void printMatrix(size_t rows, size_t columns, int** matrix){
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int* dijkstraWithVector(size_t n_vertices, int** adj_matrix, size_t source) {
    int* min_distances = new int[n_vertices];
    std::fill(min_distances, min_distances + n_vertices, INF);
    min_distances[source] = 0;

    std::vector<bool> visited(n_vertices, false);

    for (size_t i = 0; i < n_vertices; ++i) {
        // Find the unvisited vertex with the smallest distance
        int min_dist = INF;
        size_t u = n_vertices; // invalid initially
        for (size_t v = 0; v < n_vertices; ++v) {
            if (!visited[v] && min_distances[v] < min_dist) {
                min_dist = min_distances[v];
                u = v;
            }
        }

        // All reachable vertices processed
        if (u == n_vertices) break;

        visited[u] = true;

        int* neighbourhood = adj_matrix[u];
        for (size_t v = 0; v < n_vertices; ++v) {
            int edge_cost = neighbourhood[v];
            if (edge_cost < INF && !visited[v]) {
                int new_cost = min_distances[u] + edge_cost;
                if (new_cost < min_distances[v]) {
                    min_distances[v] = new_cost;
                }
            }
        }
    }

    return min_distances;
}

int** djikstraAllPairs (size_t n_vertices, int** adj_matrix){
    int **min_distances = new int* [n_vertices]; 
    for (size_t i = 0; i < n_vertices; i++){
        //std::cout << "vertex " << i << std::endl;
        min_distances[i] = dijkstraWithVector(n_vertices, adj_matrix, i);
    }

    return min_distances;
}

int main(){
    size_t n_vertices{0};
    int **adj_matrix;
    int **min_distances;

    std::cin >> n_vertices;

    adj_matrix = getMatrix(n_vertices, n_vertices);
    readMatrix(n_vertices, n_vertices, adj_matrix);
    fillInfinitys(n_vertices, n_vertices, adj_matrix);

    auto start = std::chrono::high_resolution_clock::now();

    min_distances = djikstraAllPairs(n_vertices, adj_matrix);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << duration.count() << "," << n_vertices << "," << std::endl;
        // printMatrix(n_vertices, n_vertices, min_distances);

    freeMatrixContiguous(adj_matrix);
    freeMatrixNonContiguous(min_distances, n_vertices);


    return 0;
}