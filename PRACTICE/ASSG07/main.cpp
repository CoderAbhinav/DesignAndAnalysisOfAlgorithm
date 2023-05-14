#include <iostream>
#include <random>
#include <thread>
#include <vector>

#define SIZE 1000
#define NUM_THREADS 4

int matrixA[SIZE][SIZE];
int matrixB[SIZE][SIZE];
int resultMatrix[SIZE][SIZE];

// Function to perform matrix multiplication on a given range of rows
void multiplyMatrix(int row_start, int row_end) {
    for (int i = row_start; i < row_end; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main() {
    // Initialize matrices with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrixA[i][j] = dist(gen);
            matrixB[i][j] = dist(gen);
        }
    }

    // Create threads
    std::vector<std::thread> threads;
    int chunk_size = SIZE / NUM_THREADS;
    int remainder = SIZE % NUM_THREADS;
    int row_start = 0;
    int row_end;

    for (int i = 0; i < NUM_THREADS; ++i) {
        row_end = row_start + chunk_size;
        if (remainder > 0) {
            row_end++;
            remainder--;
        }

        threads.emplace_back(multiplyMatrix, row_start, row_end);

        row_start = row_end;
    }

    // Wait for threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the result matrix
    std::cout << "Result Matrix:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << resultMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
