#include <iostream>
#include <limits>

//preventing overflow
//eliminate the need for checking boundaries inside of the loop 
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
//for this algorithm to work properly, those should be set to INF
//maybe two loops is overkill for pipeline, but the code bottleneck won't be here...
void fillInfinitys(size_t rows, size_t columns, int** matrix){
    //upper triangular
    for (size_t i = 0; i < rows; i++){
        for (size_t j = i + 1; j < columns; j++){
            if (matrix[i][j] == 0){
                matrix[i][j] = INF;
            }
        }
    }
    //lower triangular
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < i; j++){
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

void freeMatrix(int** matrix){
    delete[] matrix[0];
    delete[] matrix;
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

void printMatrix(size_t rows, size_t columns, int** matrix){
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main (){
    size_t n_vertices{0};
    int **adj_matrix;

    std::cin >> n_vertices;

    adj_matrix = getMatrix(n_vertices, n_vertices);
    readMatrix(n_vertices, n_vertices, adj_matrix);
    // printMatrix(n_vertices, n_vertices, adj_matrix);
    // std::cout << std::endl;
    fillInfinitys(n_vertices, n_vertices, adj_matrix);
    // printMatrix(n_vertices, n_vertices, adj_matrix);
    // std::cout << std::endl;
    floydWarshall(n_vertices, adj_matrix);
    // printMatrix(n_vertices, n_vertices, adj_matrix);
    // std::cout << std::endl;
    freeMatrix(adj_matrix);
    return 0;
}