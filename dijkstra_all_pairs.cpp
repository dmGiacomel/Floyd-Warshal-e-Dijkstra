#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <functional>
#include <unordered_set>

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



//version without using decrease_key 
// int* dijkstraWithoutDecrease(size_t n_vertices, int** adj_matrix, size_t source){
//     int *min_distances = new int [n_vertices];
//     std::fill(min_distances, min_distances + n_vertices, INF);

//     std::vector<bool> closed(n_vertices, false);
//     size_t n_closed_vertices = 0;
//     auto comp_tuples = [&](std::tuple<size_t, int> a, std::tuple<size_t, int> b){
//         return std::get<1>(a) > std::get<1>(b);
//     };
//     std::priority_queue<std::tuple<size_t, int>, std::vector<std::tuple<size_t, int>>, decltype(comp_tuples)> p_queue(comp_tuples);

//     p_queue.push(std::make_tuple(source, 0));
//     while(n_closed_vertices != n_vertices){
//         auto current = p_queue.top();
//         p_queue.pop();

//         auto current_vertex = std::get<0>(current);
//         auto current_cost = std::get<1>(current);

//         if (closed[current_vertex]) continue;

//         closed[current_vertex] = true;
//         n_closed_vertices++;
//         min_distances[current_vertex] = current_cost;
        
//         int* neighbourhood = adj_matrix[current_vertex];
//         for (size_t neighbour = 0; neighbour < n_vertices; neighbour++){
//             int* current_neighbour_edge_cost = &neighbourhood[neighbour];
//             int new_possible_cost = current_cost + *current_neighbour_edge_cost;
//             if (*current_neighbour_edge_cost < INF
//                 && !closed[neighbour]
//                 && new_possible_cost < min_distances[neighbour]
//             ){
//                 min_distances[neighbour] = new_possible_cost;
//                 p_queue.push(std::make_tuple(neighbour, new_possible_cost));
//             }
//         }
        
//     }

//     return min_distances;
// }

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
            int edge_cost = neighbourhood[neighbour];
            int new_possible_cost = current_cost + edge_cost;
            
            if (edge_cost < INF
                && !closed[neighbour]
                && new_possible_cost < min_distances[neighbour]
            ) {
                min_distances[neighbour] = new_possible_cost;
                p_queue.push(std::make_pair(new_possible_cost, neighbour));
            }
        }
    }

    return min_distances;
}



//version with decrease_key 
//to implement
// int* dijkstraWithDecrease(size_t n_vertices, int** adj_matrix, size_t source){
//     int *min_distances = new int [n_vertices];
//     std::fill(min_distances, min_distances + n_vertices, INF);

//     min_distances[source] = 0;
//     size_t visited_vertices = 0;

//     return min_distances;
// }

int** djikstraAllPairs (size_t n_vertices, int** adj_matrix){
    int **min_distances = new int* [n_vertices]; 
    for (size_t i = 0; i < n_vertices; i++){
        std::cout << "vertex " << i << std::endl;
        min_distances[i] = dijkstraWithoutDecrease(n_vertices, adj_matrix, i);
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
    min_distances = djikstraAllPairs(n_vertices, adj_matrix);
        // printMatrix(n_vertices, n_vertices, min_distances);

    freeMatrixContiguous(adj_matrix);
    freeMatrixNonContiguous(min_distances, n_vertices);


    return 0;
}