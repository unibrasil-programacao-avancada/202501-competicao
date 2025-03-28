#include "../include/warmup_solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char OUTPUT_DIR[] = "output/";
const char SOLUTION_FILE[] = "solution.txt";

typedef struct {
    int problem;
    int allowed;
} Problem;

static int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return ia - ib;
}

void solve_warmup(FILE* ptr_in_file, char* file_name, const char* warmup_instance) {

    FILE *fwsolptr;
    char out_file[100];

    out_file[0] = '\0';
    strcat(out_file, warmup_instance);
    strcat(out_file, OUTPUT_DIR);
    strcat(out_file, file_name);

    fwsolptr = fopen(SOLUTION_FILE, "w");
    if (fwsolptr == NULL) {
        printf("File '%s' can't be opened\n", SOLUTION_FILE);
        exit(1);
    }

    long long N;
    int A, B;
    while (fscanf(ptr_in_file, "%lld %d %d", &N, &A, &B) == 3) {

        int *alice = (int *)malloc(sizeof(int) * A);
        int *bob   = (int *)malloc(sizeof(int) * B);

        for (int i = 0; i < A; i++) {
            if (fscanf(ptr_in_file, "%d", &alice[i]) != 1) {
                fprintf(stderr, "Erro ao ler os problemas que Alice pode resolver.\n");
                exit(1);
            }
        }
        for (int i = 0; i < B; i++) {
            if (fscanf(ptr_in_file, "%d", &bob[i]) != 1) {
                fprintf(stderr, "Erro ao ler os problemas que Bob pode resolver.\n");
                exit(1);
            }
        }

        qsort(alice, A, sizeof(int), cmp_int);
        qsort(bob, B, sizeof(int), cmp_int);


        Problem *unionArr = (Problem *)malloc(sizeof(Problem) * (A + B));
        int idxAlice = 0, idxBob = 0, idxUnion = 0;
        while (idxAlice < A && idxBob < B) {
            if (alice[idxAlice] == bob[idxBob]) {
                unionArr[idxUnion].problem = alice[idxAlice];
                unionArr[idxUnion].allowed = 3; 
                idxAlice++; idxBob++; idxUnion++;
            } else if (alice[idxAlice] < bob[idxBob]) {
                unionArr[idxUnion].problem = alice[idxAlice];
                unionArr[idxUnion].allowed = 1; 
                idxAlice++; idxUnion++;
            } else {
                unionArr[idxUnion].problem = bob[idxBob];
                unionArr[idxUnion].allowed = 2; 
                idxBob++; idxUnion++;
            }
        }
        while (idxAlice < A) {
            unionArr[idxUnion].problem = alice[idxAlice];
            unionArr[idxUnion].allowed = 1;
            idxAlice++; idxUnion++;
        }
        while (idxBob < B) {
            unionArr[idxUnion].problem = bob[idxBob];
            unionArr[idxUnion].allowed = 2;
            idxBob++; idxUnion++;
        }
        int M = idxUnion;  

        int ans;
        if (M == 0) {
            ans = 0;
        } else {
           
            const int INF = 1000000000;
            int *dpAlice = (int *)malloc(sizeof(int) * M);
            int *dpBob   = (int *)malloc(sizeof(int) * M);

            dpAlice[0] = (unionArr[0].allowed & 1) ? 0 : INF;
            dpBob[0]   = (unionArr[0].allowed & 2) ? 0 : INF;

            for (int i = 1; i < M; i++) {
                dpAlice[i] = INF;
                dpBob[i]   = INF;
                if (unionArr[i].allowed & 1) {
                    int op1 = dpAlice[i-1];      
                    int op2 = dpBob[i-1] + 1;       
                    dpAlice[i] = (op1 < op2) ? op1 : op2;
                }
                if (unionArr[i].allowed & 2) {
                    int op1 = dpBob[i-1];         
                    int op2 = dpAlice[i-1] + 1;    
                    dpBob[i] = (op1 < op2) ? op1 : op2;
                }
            }
            ans = (dpAlice[M-1] < dpBob[M-1]) ? dpAlice[M-1] : dpBob[M-1];
            free(dpAlice);
            free(dpBob);
        }

        fprintf(fwsolptr, "%d\n", ans);

        free(alice);
        free(bob);
        free(unionArr);
    }

    fclose(fwsolptr);
}

int check_warmup_solution(const char* file_name, const char* warmup_instance) {

    FILE *fanswer, *fsolution;
    char answer_line[100], solution_line[100], answer_file[100];
    int is_correct = 1;

    answer_file[0] = '\0';
    strcat(answer_file, warmup_instance);
    strcat(answer_file, OUTPUT_DIR);
    strcat(answer_file, file_name);

    fanswer = fopen(answer_file, "r");
    if (fanswer == NULL) {
        printf("File '%s' can't be opened\n", answer_file);
        exit(1);
    }

    fsolution = fopen(SOLUTION_FILE, "r");
    if (fsolution == NULL) {
        printf("File '%s' can't be opened\n", SOLUTION_FILE);
        exit(1);
    }

    while (fgets(answer_line, 100, fanswer)) {
        fgets(solution_line, 100, fsolution);
        if (strcmp(answer_line, solution_line)) {
            is_correct = 0;
            break;
        }
    }

    fclose(fanswer);
    fclose(fsolution);

    return is_correct;
}
