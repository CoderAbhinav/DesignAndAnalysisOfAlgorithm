#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

const int MATRIX_SIZE = 10;

/**
 * @brief Computes the product of two matrices `a` and `b` using multithreading
 *
 * @param a The first matrix
 * @param b The second matrix
 *
 * @return The product of the two matrices `a` and `b`
 */
vector<vector<int> > matrixMultiplication(const vector<vector<int> >& a, const vector<vector<int> >& b) {
    // Initialize the result matrix with all values set to 0
    vector<vector<int> > result(MATRIX_SIZE, vector<int>(MATRIX_SIZE, 0));
    // Create a mutex object to synchronize access to the result matrix
    mutex mtx;

    // Define a lambda function to compute the product of a chunk of rows
    auto multiplyChunk = [&](int start, int end) {
        for (int i = start; i < end; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                int sum = 0;
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    sum += a[i][k] * b[k][j];
                }
                // Lock the mutex before updating the result matrix to avoid race conditions
                mtx.lock();
                result[i][j] = sum;
                // Unlock the mutex after updating the result matrix
                mtx.unlock();
            }
        }
    };

    // Create a vector of threads to compute the product in parallel
    vector<thread> threads;
    // Compute the number of rows to assign to each thread
    int chunkSize = MATRIX_SIZE / 4;
    // Create a thread for each chunk of rows
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(multiplyChunk, i * chunkSize, (i + 1) * chunkSize);
    }

    // Wait for all threads to finish executing
    for (auto& thread : threads) {
        thread.join();
    }

    // Return the final product matrix
    return result;
}

/**
 * Main function to test the matrixMultiplication function
 */
int main() {
    // Initialize the matrices with random values
    vector<vector<int> > a(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
    vector<vector<int> > b(MATRIX_SIZE, vector<int>(MATRIX_SIZE));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }


    auto start = chrono::high_resolution_clock::now();
    // Compute the product of the matrices
    vector<vector<int>> c = matrixMultiplication(a, b);

    auto stop = chrono::high_resolution_clock::now();

    // Print the first and last values of the result matrix
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            cout << c[i][j] << "\t";
        }
        cout << "\n";
    }

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "\n\nMatrix multiplication runtime: " << duration.count() << " microseconds" << endl;

    return 0;
}
