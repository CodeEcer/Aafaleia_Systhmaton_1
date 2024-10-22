#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "performance.h"
#include "key_generation.h"
#include "encrypt_rsa.h"
#include "decrypt_rsa.h"
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>  // For memory usage on Windows
#else
#include <sys/resource.h>  // For memory usage on Unix-like systems
#endif

// Cross-platform function to get current time in milliseconds
long long current_time_millis() {
#ifdef _WIN32
    SYSTEMTIME time;
    GetSystemTime(&time);
    return (long long)(time.wSecond * 1000 + time.wMilliseconds);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
}

// Function to get peak memory usage (in bytes)
long long get_memory_usage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PeakWorkingSetSize;
#else
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss * 1024;  // Convert kilobytes to bytes
#endif
}

void test_performance() {
    long long start_time, end_time;
    FILE *file = fopen("performance.txt", "w");

    if (!file) {
        printf("Error: Could not open performance.txt for writing\n");
        return;
    }

    // Measure performance for 1024-bit keys
    key_generate(1024);

    start_time = current_time_millis();
    encrypt("public_1024.key", "test_performance.txt", "output.txt");
    end_time = current_time_millis();
    double encryption_time_1024 = (end_time - start_time) / 1000.0;
    long long encryption_memory_1024 = get_memory_usage();

    start_time = current_time_millis();
    decrypt("private_1024.key", "output.txt", "original_message.txt");
    end_time = current_time_millis();
    double decryption_time_1024 = (end_time - start_time) / 1000.0;
    long long decryption_memory_1024 = get_memory_usage();

    fprintf(file, "Key Length: 1024 bits\n");
    fprintf(file, "Encryption Time: %.2fs\n", encryption_time_1024);
    fprintf(file, "Decryption Time: %.2fs\n", decryption_time_1024);
    fprintf(file, "Peak Memory Usage (Encryption): %lld Bytes\n", encryption_memory_1024);
    fprintf(file, "Peak Memory Usage (Decryption): %lld Bytes\n\n", decryption_memory_1024);

    // Measure performance for 2048-bit keys
    key_generate(2048);

    start_time = current_time_millis();
    encrypt("public_2048.key", "test_performance.txt", "output.txt");
    end_time = current_time_millis();
    double encryption_time_2048 = (end_time - start_time) / 1000.0;
    long long encryption_memory_2048 = get_memory_usage();

    start_time = current_time_millis();
    decrypt("private_2048.key", "output.txt", "original_message.txt");
    end_time = current_time_millis();
    double decryption_time_2048 = (end_time - start_time) / 1000.0;
    long long decryption_memory_2048 = get_memory_usage();

    fprintf(file, "Key Length: 2048 bits\n");
    fprintf(file, "Encryption Time: %.2fs\n", encryption_time_2048);
    fprintf(file, "Decryption Time: %.2fs\n", decryption_time_2048);
    fprintf(file, "Peak Memory Usage (Encryption): %lld Bytes\n", encryption_memory_2048);
    fprintf(file, "Peak Memory Usage (Decryption): %lld Bytes\n\n", decryption_memory_2048);

    // Measure performance for 4096-bit keys
    key_generate(4096);

    start_time = current_time_millis();
    encrypt("public_4096.key", "test_performance.txt", "output.txt");
    end_time = current_time_millis();
    double encryption_time_4096 = (end_time - start_time) / 1000.0;
    long long encryption_memory_4096 = get_memory_usage();

    start_time = current_time_millis();
    decrypt("private_4096.key", "output.txt", "original_message.txt");
    end_time = current_time_millis();
    double decryption_time_4096 = (end_time - start_time) / 1000.0;
    long long decryption_memory_4096 = get_memory_usage();

    fprintf(file, "Key Length: 4096 bits\n");
    fprintf(file, "Encryption Time: %.2fs\n", encryption_time_4096);
    fprintf(file, "Decryption Time: %.2fs\n", decryption_time_4096);
    fprintf(file, "Peak Memory Usage (Encryption): %lld Bytes\n", encryption_memory_4096);
    fprintf(file, "Peak Memory Usage (Decryption): %lld Bytes\n", decryption_memory_4096);

    fclose(file);
    printf("Performance data written to performance.txt\n");
}
