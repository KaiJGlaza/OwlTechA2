#include <stdio.h>
#include <stdint.h>
#include <string.h>

void oct_to_bin(const char *oct, char *out) {
    int i = 0, j = 0; // init
    while (oct[i] != '\0') { // go through the whole string
        int d = oct[i] - '0';  // convert char to number ('7' -> 7)

        // extract 3 bits
        out[j++] = ((d >> 2) & 1) ? '1' : '0'; // bit shift, only care about last bit, set out to 1 if it ends in a 1
        out[j++] = ((d >> 1) & 1) ? '1' : '0';
        out[j++] = ((d >> 0) & 1) ? '1' : '0';

        i++;
    }
    out[j] = '\0'; // null terminate
}

void oct_to_hex(const char *oct, char *out) {
    char bin[100];      // original binary string from octal
    char padded[100];   // binary string with leading zeros

    oct_to_bin(oct, bin);

    int len = 0;
    while (bin[len] != '\0') len++;

    // Skip leading zeros
    int start = 0;
    while (start < len && bin[start] == '0') start++;
    if (start == len) { // all zeros
        out[0] = '0';
        out[1] = '\0';
        return;
    }

    int rem = (4 - ((len - start) % 4)) % 4; // # of zeros to pad
    int pos = 0;

    // Add padding zeros
    for (int i = 0; i < rem; i++) {
        padded[pos++] = '0';
    }

    // Copy rest of binary
    for (int i = start; i < len; i++) {
        padded[pos++] = bin[i];
    }
    padded[pos] = '\0';

    // Now convert 4 bits at a time
    int padded_len = pos;
    pos = 0; // reuse for output index
    for (int i = 0; i < padded_len; i += 4) {
        int v = (padded[i] - '0') * 8 + // follow binary format
                (padded[i+1] - '0') * 4 +
                (padded[i+2] - '0') * 2 +
                (padded[i+3] - '0') * 1;
        out[pos++] = (v < 10) ? ('0' + v) : ('A' + (v - 10)); // if < 10, keep a number, more than - make it letter
    }
    out[pos] = '\0'; // null terminate
}


void hex_to_bin(const char *hex, char *out) {
    int i = 0, j = 0;
    while (hex[i] != '\0') {
        char c = hex[i];
        int d;

        // convert hex char to number
        if (c >= '0' && c <= '9') {
            d = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            d = 10 + (c - 'A');
        } else if (c >= 'a' && c <= 'f') {
            d = 10 + (c - 'a');
        } else {
            out[0] = '\0';
            return;
        }

        // each hex digit -> 4 binary digits: use same thing from the pdf
        out[j++] = ((d >> 3) & 1) ? '1' : '0';
        out[j++] = ((d >> 2) & 1) ? '1' : '0';
        out[j++] = ((d >> 1) & 1) ? '1' : '0';
        out[j++] = ((d >> 0) & 1) ? '1' : '0';

        i++;
    }
    out[j] = '\0'; // null terminate
}

void to_sign_magnitude(int32_t n, char *out) {
    int32_t magnitude = (n >= 0) ? n : -n;

    // first bit is the sign
    out[0] = (n >= 0) ? '0' : '1';

    // fill the remaining 31 bits
    for (int i = 30; i >= 0; i--) {
        out[31 - i] = ((magnitude >> i) & 1) ? '1' : '0';
    }

    out[32] = '\0';
}


void to_ones_complement(int32_t n, char *out) {
    uint32_t value;
    if (n >= 0) {
        value = (uint32_t)n; // positive: value as-is
    } else {
        value = (uint32_t)(-n); // magnitude of negative
        value = ~value; // flip all bits
    }

    // build 32-bit binary string
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_twos_complement(int32_t n, char *out) {
    uint32_t value;
    if (n >= 0) {
        value = (uint32_t)n; // positive: value as-is
    } else {
        value = (uint32_t)(-n); // magnitude of negative
        value = ~value + 1; // flip all bits and add 1
    }

    // build 32-bit binary string
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}
