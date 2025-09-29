#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Prototypes for A2 functions
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main(void) {
    printf("Program started!\n");

    FILE *infile = fopen("A2_tests.txt", "r");
    FILE *outfile = fopen("output.txt", "w");

    if (!infile) {
        printf("Error: could not open A2_tests.txt\n");
        return 1;
    }
    if (!outfile) {
        printf("Error: could not open output.txt\n");
        return 1;
    }

    char line[256];
    int test_num = 1;
    int pass_count = 0, total_count = 0;

    while (fgets(line, sizeof(line), infile) != NULL) {

        // skip comments and blank lines
        if (line[0] == '#' || line[0] == '\n') continue;

        char func[50], input[100], expected[100];

        if (sscanf(line, "%s %s %s", func, input, expected) == 3) {
            char buffer[100];
            total_count++;

            if (strcmp(func, "oct_to_bin") == 0) {
                oct_to_bin(input, buffer);
            } else if (strcmp(func, "oct_to_hex") == 0) {
                oct_to_hex(input, buffer);
            } else if (strcmp(func, "hex_to_bin") == 0) {
                hex_to_bin(input, buffer);
            } else if (strcmp(func, "to_sign_magnitude") == 0) {
                int32_t n = atoi(input);
                to_sign_magnitude(n, buffer);
            } else if (strcmp(func, "to_ones_complement") == 0) {
                int32_t n = atoi(input);
                to_ones_complement(n, buffer);
            } else if (strcmp(func, "to_twos_complement") == 0) {
                int32_t n = atoi(input);
                to_twos_complement(n, buffer);
            } else {
                continue;
            }

            if (strcmp(buffer, expected) == 0) {
                fprintf(outfile, "Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                        test_num, func, input, expected, buffer);
                pass_count++;
            } else {
                fprintf(outfile, "Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                        test_num, func, input, expected, buffer);
            }

            test_num++;
        }
    }

    fprintf(outfile, "\nSummary: %d/%d tests passed\n", pass_count, total_count);
    fclose(infile);
    fclose(outfile);

    printf("Results written to output.txt\n");
    return 0;
}
