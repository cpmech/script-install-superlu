#include "slu_ddefs.h"

main(int argc, char *argv[]) {
    /*
     * Purpose
     * =======
     *
     * This is the small 5x5 example used in the Sections 2 and 3 of the
     * Users’ Guide to illustrate how to call a SuperLU routine, and the
     * matrix data structures used by SuperLU.
     *
     */
    SuperMatrix super_mat_a, super_mat_l, super_mat_u, super_mat_b;
    double *values, *rhs;
    int *row_indices, *col_pointers;
    int *perm_r; /* row permutations from partial pivoting */
    int *perm_c; /* column permutation vector */
    int nrhs, info, i, m, n, nnz;
    superlu_options_t options;
    SuperLUStat_t stat;
    /* Initialize matrix A. */
    m = n = 5;
    nnz = 12;
    if (!(values = doubleMalloc(nnz)))
        ABORT("Malloc fails for a[].");
    if (!(row_indices = intMalloc(nnz)))
        ABORT("Malloc fails for asub[].");
    if (!(col_pointers = intMalloc(n + 1)))
        ABORT("Malloc fails for xa[].");
    double s = 19.0;
    double u = 21.0;
    double p = 16.0;
    double e = 5.0;
    double r = 18.0;
    double l = 12.0;
    values[0] = s;
    values[1] = l;
    values[2] = l;
    values[3] = u;
    values[4] = l;
    values[5] = l;
    values[6] = u;
    values[7] = p;
    values[8] = u;
    values[9] = e;
    values[10] = u;
    values[11] = r;
    row_indices[0] = 0;
    row_indices[1] = 1;
    row_indices[2] = 4;
    row_indices[3] = 1;
    row_indices[4] = 2;
    row_indices[5] = 4;
    row_indices[6] = 0;
    row_indices[7] = 2;
    row_indices[8] = 0;
    row_indices[9] = 3;
    row_indices[10] = 3;
    row_indices[11] = 4;
    col_pointers[0] = 0;
    col_pointers[1] = 3;
    col_pointers[2] = 6;
    col_pointers[3] = 8;
    col_pointers[4] = 10;
    col_pointers[5] = 12;

    /* Create matrix A in the format expected by SuperLU. */
    dCreate_CompCol_Matrix(&super_mat_a, m, n, nnz, values, row_indices, col_pointers, SLU_NC, SLU_D, SLU_GE);

    /* Create right-hand side matrix B. */
    nrhs = 1;
    if (!(rhs = doubleMalloc(m * nrhs)))
        ABORT("Malloc fails for rhs[].");
    for (i = 0; i < m; ++i)
        rhs[i] = 1.0;
    dCreate_Dense_Matrix(&super_mat_b, m, nrhs, rhs, m, SLU_DN, SLU_D, SLU_GE);
    if (!(perm_r = intMalloc(m)))
        ABORT("Malloc fails for perm_r[].");
    if (!(perm_c = intMalloc(n)))
        ABORT("Malloc fails for perm_c[].");

    /* Set the default input options. */
    set_default_options(&options);
    options.ColPerm = NATURAL;

    /* Initialize the statistics variables. */
    StatInit(&stat);

    /* Solve the linear system. */
    dgssv(&options, &super_mat_a, perm_c, perm_r, &super_mat_l, &super_mat_u, &super_mat_b, &stat, &info);

    dPrint_CompCol_Matrix("A", &super_mat_a);
    dPrint_CompCol_Matrix("U", &super_mat_u);
    dPrint_SuperNode_Matrix("L", &super_mat_l);
    print_int_vec("\nperm_r", m, perm_r);
    printf("\n");

    if (info == 0) {

        if (options.PrintStat) {
            StatPrint(&stat);
        }

        /* This is how you could access the solution matrix. */
        double *sol = (double *)((DNformat *)super_mat_b.Store)->nzval;
        (void)sol; // suppress unused variable warning
        printf("x = ");
        for (int k = 0; k < n; k++) {
            printf("%g ", sol[k]);
        }
        printf("\n");

    } else {
        printf("dgssv() error returns INFO= %lld\n", (long long)info);
    }

    /* De-allocate storage */
    SUPERLU_FREE(rhs);
    SUPERLU_FREE(perm_r);
    SUPERLU_FREE(perm_c);
    Destroy_CompCol_Matrix(&super_mat_a);
    Destroy_SuperMatrix_Store(&super_mat_b);
    Destroy_SuperNode_Matrix(&super_mat_l);
    Destroy_CompCol_Matrix(&super_mat_u);
    StatFree(&stat);
}
