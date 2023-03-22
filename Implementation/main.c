#include "peano.h"
#include <time.h>

char* helpMessage = "-V <int>: Version of the algorithm to use, if not set the main implementation is used\n-B <int>: If set the runtime is measured and the optional argument specifies the number of iterations. No output is generated.\n-n <int>: Degree of the peano curve\n-o <string>: Name of the output file\n-h: Print this help message\n--help: Print this help message\n";
char* examples = "Usage examples:\nGenerate curve of degree 5 with version 1 and output file 'out.svg': './peano -V1 -n5 -o out.svg'\nBenchmark version 0 with degree 3 and 10 iterations: './peano -B10 -V0 -n3'\n";

void throw_error(char* message) {
    fprintf(stderr, "%s\n", message);
    printf("%s%s", helpMessage, examples);
    exit(EXIT_FAILURE);
}

// Creates an SVG file with the coordinates in x and y
void printSvg(const coord_t* x, const coord_t* y, FILE* file, unsigned long long int n, int degree) {
    int length = degree > 4 ? degree*2750*2 : degree == 4 ? degree*1750*2 : degree*1000*2;
    int adjustment = degree > 4 ? length/2 - degree*degree*500 : degree == 4 ? length/2 - degree*degree*225 : length/2 - degree*degree*125;

    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%s\" height=\"%s\" viewBox=\"0 0 %d %d\">\n","100%","100%", length, length);
    fprintf(file, "<rect height=\"100%%\" width=\"100%%\" fill=\"white\"/>\n");
    fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%lu\" y2=\"%lu\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", adjustment, length - adjustment, (x[1] * 100) + adjustment, length - adjustment - (y[1] * 100));
    for (unsigned long long int i = 1; i < n - 1; i++) {
        if ((x[i] == 0 && y[i] == 0) || (x[i+1] == 0 && y[i+1] == 0)) {
            continue;
        }
        int err = fprintf(file, "<line x1=\"%lu\" y1=\"%lu\" x2=\"%lu\" y2=\"%lu\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", (x[i] * 100) + adjustment, length - adjustment - (y[i] * 100), (x[i+1] * 100) + adjustment, length - adjustment - (y[i+1] * 100));
        if (err < 0) {
            throw_error("Error while writing in file.");
        }
    }
    fprintf(file, "</svg>\n");
}

void benchmark (int b, int  v, unsigned n, coord_t* x, coord_t* y) {
    printf("Benchmarking V%i for degree %u with %i iterations...\n", v, n, b);
    struct timespec start, end;
    double time_used;
    double total_time = 0.0;

    // V0
    if (v == 0) {
        for(int i = 0; i < b; i++) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            peano_V0(n, x, y);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_used = (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
            printf("Took %f seconds.\n", time_used);
            total_time += time_used;
        }
    // V1
    } else if (v == 1) {
        for(int i = 0; i < b; i++) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            peano_V1(n, x, y);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_used = (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
            printf("Took %f seconds.\n", time_used);
            total_time += time_used;
        }
    // V2
    } else {
        for(int i = 0; i < b; i++) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            peano_V2(n, x, y);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_used = (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
            printf("Took %f seconds.\n", time_used);
            total_time += time_used;
        }
    }
    printf("Total computing time over %i iterations: %f seconds.\n", b, total_time);
    printf("Average: %f seconds.\n", total_time / b);
}

int main(int argc, char** argv) {
    // Default values
    int v = 0;
    int n = 3;
    int b = 3;
    int measure = 0;
    char* name = "peano.svg";

    // Parse command line arguments and set variables
    int opt;

    // getopt should not print error messages, we do it ourselves
    opterr = 0;

    while ((opt = getopt(argc, argv, "V:B::n:o:h")) != -1) {
        switch (opt) {
            // Version
            case 'V':
                // Check if optarg is "0" or "1" and set it accordingly
                if (strcmp(optarg, "0") == 0) {
                    v = 0;
                } else if (strcmp(optarg, "1") == 0) {
                    v = 1;
                } else if (strcmp(optarg, "2") == 0) {
                    v = 2;
                } else {
                    throw_error("Invalid version number. Must be 0, 1 or 2.");
                }
                break;
            // Benchmark and iterations
            case 'B':
                measure = 1;
                if (optarg) {
                    b = atoi(optarg);
                }
                if (b <= 0) {
                    throw_error("Invalid number of iterations. Must be a positive integer.");
                }
                break;
            // Degree
            case 'n':
                n = atoi(optarg);
                if (n < 1 || n > 20) {
                    throw_error("Invalid degree. Must be a positive integer between 1 and 20.");
                }
                break;
            // Output file name
            case 'o':
                name = optarg;
                break;
            // Help
            case 'h':
                printf("%s%s", helpMessage, examples);
                exit(0);
            // Unknown option
            case '?':
                if (argc > 1 && strcmp(argv[1], "--help") == 0) {
                    printf("%s%s", helpMessage, examples);
                    exit(0);
                }
                throw_error("Invalid option.");
            default:
                throw_error("Invalid option.");
        }
    }    

    // Throw error if something other than the options is given as argument
    if (argc > optind) {
        throw_error("Invalid argument.");
    }


    // Allocate memory for the coordinates
    coord_t* x = (coord_t*) calloc(pow(3, 2 * n), sizeof(coord_t));
    coord_t* y = (coord_t*) calloc(pow(3, 2 * n), sizeof(coord_t));
    
    if (x == NULL || y == NULL) {
        throw_error("Could not allocate memory. This can indicate that your device does not have enough memory to to compute a curve of this degree.\nE.g. for degree 10 appr. 28GB of available memory are necessary.");
    }

    // Run the program with the specified parameters
    if (measure == 0) {
        // Warning if degree is too high
        if (n > 7) {
            printf("CAUTION: For degrees higher than 7 the output file can become very large and generating it can take extremly long.\nWould you like to continue (Y/N)?\n");
            char ans;
            int err = scanf("%c", &ans);
            if (err == EOF) {
                free(x);
                free(y);
                throw_error("Error while reading input.");
            }
            if (ans != 'y' && ans != 'Y') {
                free(x);
                free(y);
                return 0;
            }
        }

        // Open and check the output file
        FILE* file = fopen(name, "w");
        if (file == NULL) {
            free(x);
            free(y);
            throw_error("Could not open output file.");
        }

        // Generate the curve with the specified version
        switch (v) {
            case 0:
                peano_V0(n, x, y);
                break;
            case 1:
                peano_V1(n, x, y);
                break;
            case 2:
                peano_V2(n, x, y);
                break;
        }

        // Write the curve to the output file
        printSvg(x, y, file, pow(3, 2 * n), n);
        fclose(file);

    // Run the requested benchmark
    } else {
        benchmark(b, v, n, x, y);
    }
    free(x);
    free(y);
    return 0;
}
