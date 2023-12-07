//C++ code, CPU only computation
#include <iostream>
#include <cmath>
#include <chrono>

// Function to add the elements of two arrays
void add(int n, float *x, float *y)
{
    for (int i = 0; i < n; i++)
        y[i] = x[i] + y[i];
}

int main(void)
{
    // Number of elements in the arrays
    int N = 1 << 29; // 1M elements

    // Allocate memory for arrays on the host
    float *x = new float[N];
    float *y = new float[N];

    // Initialize x and y arrays on the host
    for (int i = 0; i < N; i++)
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Measure the execution time using chrono
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

    // Run kernel (addition) on 1M elements on the CPU
    add(N, x, y);

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Check for errors (all values should be 3.0f)
    float maxError = 0.0f;
    for (int i = 0; i < N; i++)
        maxError = std::fmax(maxError, std::fabs(y[i] - 3.0f));

    // Output the maximum error and elapsed time
    std::cout << "Max error: " << maxError << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    // Free allocated memory
    delete[] x;
    delete[] y;

    return 0;
}

