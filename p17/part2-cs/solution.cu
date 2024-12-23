#include <climits>
#include <cmath>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>

#define CUDA_CHECK(call)                                                       \
  do {                                                                         \
    cudaError_t error = call;                                                  \
    if (error != cudaSuccess) {                                                \
      printf("CUDA error at %s:%d: %s\n", __FILE__, __LINE__,                  \
             cudaGetErrorString(error));                                       \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

void printDeviceInfo() {
  int deviceCount;
  CUDA_CHECK(cudaGetDeviceCount(&deviceCount));

  if (deviceCount == 0) {
    printf("No CUDA devices found!\n");
    exit(1);
  }

  printf("Found %d CUDA devices:\n", deviceCount);

  for (int i = 0; i < deviceCount; i++) {
    cudaDeviceProp prop;
    CUDA_CHECK(cudaGetDeviceProperties(&prop, i));
    printf("Device %d: %s\n", i, prop.name);
    printf("  Compute capability: %d.%d\n", prop.major, prop.minor);
    printf("  Max threads per block: %d\n", prop.maxThreadsPerBlock);
    printf("  Max blocks per multiprocessor: %d\n",
           prop.maxBlocksPerMultiProcessor);
    printf("  Number of multiprocessors: %d\n", prop.multiProcessorCount);
  }
  printf("\n");
}

__device__ long long executeProgram(long long A) {
  // Program constants
  long long res = 0LL;
  long long B = 0LL;
  long long C = 0LL;

  do {
    B = A % 8;
    B ^= 7;
    C = A >> B;
    B ^= 7;
    B = B ^ C;
    A >>= 3;
    res += B % 8;
    res *= 10;
  } while (A);

  return res / 10;
}

__global__ void searchKernel(long long start_value, long long target,
                             int values_per_thread, bool *found,
                             long long *result) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  long long my_start = start_value + (long long)idx * values_per_thread;

  for (int i = 0; i < values_per_thread; i++) {
    long long current = my_start + i;
    long long computed = executeProgram(current);

    if (computed == target) {
      *found = true;
      *result = current;
      return;
    }
  }
}

int main() {
  printDeviceInfo();

  const long long target = 2417751746035530LL;
  const long long sta_value = 34464302400860LL;
  const long long end_value = 2146196000086000LL;

  // const long long target = 35430LL;
  // const long long sta_value = 0LL;
  // const long long end_value = LONG_LONG_MAX;

  // CUDA configuration
  const int BLOCK_SIZE = 1024;
  const int NUM_BLOCKS = 8192;
  int VALUES_PER_THREAD = 10000;

  bool *d_found;
  long long *d_result;
  CUDA_CHECK(cudaMalloc(&d_found, sizeof(bool)));
  CUDA_CHECK(cudaMalloc(&d_result, sizeof(long long)));

  bool h_found = false;
  long long h_result = 0;

  // Initialize device memory
  CUDA_CHECK(cudaMemset(d_found, 0, sizeof(bool)));

  printf("Starting GPU search from value: %lld to %lld\n", sta_value,
         end_value);

  long long current_start = sta_value;
  while (!h_found && current_start < end_value) {
    // Calculate remaining values to process
    long long batch_size =
        (long long)BLOCK_SIZE * NUM_BLOCKS * VALUES_PER_THREAD;
    long long remaining = end_value - current_start;
    if (remaining < batch_size) {
      // Adjust VALUES_PER_THREAD for the last batch
      VALUES_PER_THREAD = (int)((remaining + (BLOCK_SIZE * NUM_BLOCKS - 1)) /
                                (BLOCK_SIZE * NUM_BLOCKS));
    }

    searchKernel<<<NUM_BLOCKS, BLOCK_SIZE>>>(
        current_start, target, VALUES_PER_THREAD, d_found, d_result);
    CUDA_CHECK(cudaGetLastError());      // Check for launch errors
    CUDA_CHECK(cudaDeviceSynchronize()); // Check for execution errors

    // Check if we found the result
    CUDA_CHECK(
        cudaMemcpy(&h_found, d_found, sizeof(bool), cudaMemcpyDeviceToHost));
    if (h_found) {
      CUDA_CHECK(cudaMemcpy(&h_result, d_result, sizeof(long long),
                            cudaMemcpyDeviceToHost));
      printf("Found result: %lld\n", h_result);
      break;
    }

    // Move to next batch
    current_start += (long long)BLOCK_SIZE * NUM_BLOCKS * VALUES_PER_THREAD;

    // Print progress every iteration
    printf("Processed up to: %lld (%.2f%%)\n", current_start,
           ((double)(current_start - sta_value) / (end_value - sta_value)) *
               100.0);
    fflush(stdout); // Force output to be displayed immediately
  }

  // Cleanup
  CUDA_CHECK(cudaFree(d_found));
  CUDA_CHECK(cudaFree(d_result));

  return 0;
}
