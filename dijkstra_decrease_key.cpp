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
        boost::heap::arity<2>,
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

int** djikstraAllPairs (size_t n_vertices, int** adj_matrix){
    int **min_distances = new int* [n_vertices]; 
    for (size_t i = 0; i < n_vertices; i++){
        //std::cout << "vertex " << i << std::endl;
        min_distances[i] = dijkstraWithDecrease(n_vertices, adj_matrix, i);
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

    std::cout << duration.count() << "," << n_vertices << std::endl;
        // printMatrix(n_vertices, n_vertices, min_distances);

    freeMatrixContiguous(adj_matrix);
    freeMatrixNonContiguous(min_distances, n_vertices);


    return 0;
}