#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <functional>
#include <unordered_set>
#include <chrono>
#include <iomanip>
#include <boost/heap/d_ary_heap.hpp>

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

void fillZerosInDiagonal(size_t rows, size_t columns, int** matrix){
    //upper triangular
    for (size_t i = 0; i < rows; i++){
        matrix[i][i] = 0;
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

int* dijkstraWithDecrease(size_t n_vertices, int** adj_matrix, size_t source){
    int* min_distances = new int[n_vertices];
    std::fill(min_distances, min_distances + n_vertices, INF);
    min_distances[source] = 0;

    std::vector<bool> closed(n_vertices, false);

    using Heap = boost::heap::d_ary_heap<
        std::pair<int, size_t>,
        boost::heap::arity<4>,
        boost::heap::mutable_<true>,
        boost::heap::compare<std::greater<>>
    >;

    Heap p_queue;
    std::vector<Heap::handle_type> handles(n_vertices);

    for (size_t i = 0; i < n_vertices; i++) {
        handles[i] = p_queue.push(std::make_pair(min_distances[i], i));
    }

    while (!p_queue.empty()) {
        auto current = p_queue.top();
        p_queue.pop();

        size_t current_vertex = current.second;
        int current_cost = current.first;

        closed[current_vertex] = true;

        int* neighbourhood = adj_matrix[current_vertex];
        int edge_cost, new_possible_cost;

        for (size_t neighbour = 0; neighbour < n_vertices; ++neighbour) {
            if (closed[neighbour]) continue;

            edge_cost = neighbourhood[neighbour];
            if (edge_cost >= INF) continue;

            new_possible_cost = current_cost + edge_cost;
            if (new_possible_cost < min_distances[neighbour]) {
                min_distances[neighbour] = new_possible_cost;
                p_queue.update(handles[neighbour], std::make_pair(new_possible_cost, neighbour));
            }
        }
    }

    return min_distances;
}

int* dijkstraWithoutDecrease(size_t n_vertices, int** adj_matrix, size_t source) {
    int* min_distances = new int[n_vertices];
    std::fill(min_distances, min_distances + n_vertices, INF);

    std::vector<bool> closed(n_vertices, false);
    size_t n_closed_vertices = 0;

    std::priority_queue<std::pair<int, size_t>,
                        std::vector<std::pair<int, size_t>>,
                        std::greater<std::pair<int, size_t>>> p_queue;

    p_queue.push(std::make_pair(0, source));
    while (n_closed_vertices != n_vertices) {
        std::pair<int, size_t> current = p_queue.top();
        p_queue.pop();

        int current_cost = current.first;
        size_t current_vertex = current.second;

        if (closed[current_vertex]) continue;

        closed[current_vertex] = true;
        n_closed_vertices++;
        min_distances[current_vertex] = current_cost;

        int* neighbourhood = adj_matrix[current_vertex];
        for (size_t neighbour = 0; neighbour < n_vertices; neighbour++) {

            if (closed[neighbour]) continue;

            int edge_cost = neighbourhood[neighbour];
            if (edge_cost >= INF) continue;

            int new_possible_cost = current_cost + edge_cost;
            if (new_possible_cost < min_distances[neighbour]) {
                min_distances[neighbour] = new_possible_cost;
                p_queue.push(std::make_pair(new_possible_cost, neighbour));
            }
        }
    }
    return min_distances;
}

int** djikstraAllPairs (size_t n_vertices, int** adj_matrix){
    int **min_distances = new int* [n_vertices]; 
    for (size_t i = 0; i < n_vertices; i++){
        //std::cout << "vertex " << i << std::endl;
        min_distances[i] = dijkstraWithDecrease(n_vertices, adj_matrix, i);
    }

    return min_distances;
}

int** djikstraAllPairsNoDecrease (size_t n_vertices, int** adj_matrix){
    int **min_distances = new int* [n_vertices]; 
    for (size_t i = 0; i < n_vertices; i++){
        //std::cout << "vertex " << i << std::endl;
        min_distances[i] = dijkstraWithoutDecrease(n_vertices, adj_matrix, i);
    }

    return min_distances;
}

void floydWarshall(size_t n_vertices, int** adj_matrix){
    for (size_t k = 0; k < n_vertices; k++){
        for(size_t i = 0; i < n_vertices; i++){
            int ik = adj_matrix[i][k];
            if (ik == INF){
                continue;
            }   
            for(size_t j = 0; j < n_vertices; j++){
                adj_matrix[i][j] = std::min(
                    adj_matrix[i][j],
                    ik + adj_matrix[k][j]
                );
            }
        }
    }
}

bool cpmMatrixes(size_t n_vertices, int **matrix_a, int **matrix_b){
    for (size_t i = 0; i < n_vertices; i++){
        for (size_t j = 0; j < n_vertices; j++){
            if (matrix_a[i][j] != matrix_b[i][j]) return false;
        }
    }
    return true;
}

int main(){
    size_t n_vertices{0};
    int **adj_matrix;
    int **min_distances_decrease, **min_distances_no_dec;

    std::cin >> n_vertices;

    adj_matrix = getMatrix(n_vertices, n_vertices);
    readMatrix(n_vertices, n_vertices, adj_matrix);
    fillInfinitys(n_vertices, n_vertices, adj_matrix);

    min_distances_decrease = djikstraAllPairs(n_vertices, adj_matrix);
    min_distances_no_dec = djikstraAllPairsNoDecrease(n_vertices, adj_matrix);
    fillZerosInDiagonal(n_vertices, n_vertices, adj_matrix);
    floydWarshall(n_vertices, adj_matrix);

    if(cpmMatrixes(n_vertices, adj_matrix, min_distances_decrease) 
       && cpmMatrixes(n_vertices, min_distances_no_dec, min_distances_decrease))
    {
        std::cout << "Pass :D" << std::endl;
    }

    // std::cout << "resultado FW:" << std::endl;
    // printMatrix(n_vertices, n_vertices, adj_matrix);
    // std::cout << std::endl;

    // std::cout << "resultado DIJ:" << std::endl;
    // printMatrix(n_vertices, n_vertices, adj_matrix);
    // std::cout << std::endl;

    freeMatrixContiguous(adj_matrix);
    freeMatrixNonContiguous(min_distances_decrease, n_vertices);
    freeMatrixNonContiguous(min_distances_no_dec, n_vertices);


    return 0;
}