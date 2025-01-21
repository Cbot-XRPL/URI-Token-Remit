/**
 * This hook just accepts any transaction coming through it
 */
#include "hookapi.h"
#include <stdint.h>

int64_t hook(uint32_t reserved) {
    // Define the value to be converted
    uint64_t value = 0x000000000000000E; // Example value

    // Buffer for storing the 8-byte representation
    uint8_t buffer[8] = {0};

    // Use the Hooks library's macro to store the value into the buffer
    UINT64_TO_BUF(buffer, value);

    // Debug output to check the buffer
    TRACEHEX(buffer);

    // Use the Hooks library's macro to reconstruct the value from the buffer
    uint64_t reconstructed_value = UINT64_FROM_BUF(buffer);

    // Debug output to verify the reconstructed value
    TRACEVAR(reconstructed_value);

    // Validate that the original and reconstructed values match
    if (reconstructed_value != value) {
        TRACESTR("Error: Reconstructed value does not match original!");
    } else {
        TRACESTR("Success: Values match!");
    }

    // Signal the transaction is accepted
    TRACESTR("Accept.c: Called.");
    accept(0, 0, 0);

    _g(1, 1); // Every hook needs to import guard function and use it at least once
    // Unreachable
    return 0;
}
