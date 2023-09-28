#include <iostream>
#include <vector>

#include "slu_ddefs.h"

using namespace std;

// This is the small 5x5 example used in the Sections 2 and 3 of the
// Users' Guide to illustrate how to call a SuperLU routine, and the
// matrix data structures used by SuperLU.

int main(int argc, char **argv) try {

    cout << " >>>>> ~+~+~+~+~+~+~+~+~+~+~+~+ <<<<< " << endl;
    cout << " . . . Hello SuperLU Example 01 . . . " << endl;
    cout << " >>>>> ~+~+~+~+~+~+~+~+~+~+~+~+ <<<<< " << endl;

    // initialize matrix A
    // s . u u .
    // l u . . .
    // . l p . .
    // . . . e u
    // l l . . r
    int m = 5;
    int n = 5;
    int nnz = 12;
    double s = 19.0;
    double u = 21.0;
    double p = 16.0;
    double e = 5.0;
    double r = 18.0;
    double l = 12.0;
    auto values = vector<double>{
        // also called "a"
        s, l, l, // j=0 p=(0),1,2,
        u, l, l, // j=1 p=(3),4,5
        u, p,    // j=2 p=(6),7
        u, e,    // j=3 p=(8),9
        u, r,    // j=4 p=(10),11
    };           //     p=(12)
    auto row_indices = vector<int>{
        // also called "asub"
        0, 1, 4, //
        1, 2, 4, //
        0, 2,    //
        0, 3,    //
        3, 4,    //
    };
    auto col_pointers = vector<int>{0, 3, 6, 8, 10, 12}; // also called "xa"

    // create matrix A in the format expected by SuperLU
    SuperMatrix super_mat_a;
    dCreate_CompCol_Matrix(&super_mat_a,
                           m,
                           n,
                           nnz,
                           values.data(),
                           row_indices.data(),
                           col_pointers.data(),
                           SLU_NC,
                           SLU_D,
                           SLU_GE);

    // create right-hand side matrix B
    int nrhs = 1;
    auto rhs = vector<double>(nrhs, 1.0);
    SuperMatrix super_mat_b;
    dCreate_Dense_Matrix(&super_mat_b,
                         m,
                         nrhs,
                         rhs.data(),
                         m,
                         SLU_DN,
                         SLU_D,
                         SLU_GE);

    // allocate permutation vectors
    // auto perm_r = vector<int>(m); // row permutations from partial pivoting
    // auto perm_c = vector<int>(n); // column permutation vector

    int *perm_c; /* column permutation vector */
    int *perm_r; /* row permutations from partial pivoting */
    if (!(perm_c = int32Malloc(n)))
        ABORT("Malloc fails for perm_c[].");
    if (!(perm_r = int32Malloc(m)))
        ABORT("Malloc fails for perm_r[].");

    // set the default input options
    superlu_options_t options;
    set_default_options(&options);
    options.ColPerm = NATURAL;

    // initialize the statistics variables
    SuperLUStat_t stat;
    StatInit(&stat);

    // solve the linear system
    SuperMatrix super_mat_l;
    SuperMatrix super_mat_u;
    int info = 0;
    dgssv(&options,
          &super_mat_a,
          perm_c,
          perm_r,
          &super_mat_l,
          &super_mat_u,
          &super_mat_b,
          &stat,
          &info);

    if (info == 0) {

        if (options.PrintStat) {
            StatPrint(&stat);
        }

        /* This is how you could access the solution matrix. */
        // double *sol = (double *)((DNformat *)super_mat_b.Store)->nzval;
        // (void)sol; // suppress unused variable warning
        // printf("x = ");
        // for (int k = 0; k < n; k++) {
        // printf("%g ", sol[k]);
        // }
        // printf("\n");

        SCformat *Lstore = (SCformat *)super_mat_l.Store;
        NCformat *Ustore = (NCformat *)super_mat_u.Store;
        printf("No of nonzeros in factor L = %lld\n", (long long)Lstore->nnz);
        printf("No of nonzeros in factor U = %lld\n", (long long)Ustore->nnz);
        printf("No of nonzeros in L+U = %lld\n", (long long)Lstore->nnz + Ustore->nnz - n);
        printf("FILL ratio = %.1f\n", (float)(Lstore->nnz + Ustore->nnz - n) / nnz);

        mem_usage_t mem_usage;
        dQuerySpace(&super_mat_l, &super_mat_u, &mem_usage);
        printf("L\\U MB %.3f\ttotal MB needed %.3f\n",
               mem_usage.for_lu / 1e6, mem_usage.total_needed / 1e6);

    } else {
        printf("dgssv() error returns INFO= %lld\n", (long long)info);
        if (info <= n) { /* factorization completes */
            mem_usage_t mem_usage;
            dQuerySpace(&super_mat_l, &super_mat_u, &mem_usage);
            printf("L\\U MB %.3f\ttotal MB needed %.3f\n",
                   mem_usage.for_lu / 1e6, mem_usage.total_needed / 1e6);
        }
    }

    // print matrices
    // dPrint_CompCol_Matrix("A", &super_mat_a);
    // dPrint_CompCol_Matrix("U", &super_mat_u);
    // dPrint_SuperNode_Matrix("L", &super_mat_l);
    // print_int_vec("\nperm_r", m, perm_r.data());

    // deallocate storage
    // Destroy_CompCol_Matrix(&super_mat_a);
    // Destroy_SuperMatrix_Store(&super_mat_b);
    // Destroy_SuperNode_Matrix(&super_mat_l);
    // Destroy_CompCol_Matrix(&super_mat_u);
    // StatFree(&stat);

    // done
    return 0;

} catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
} catch (std::string &msg) {
    std::cout << msg.c_str() << std::endl;
    return 1;
} catch (const char *msg) {
    std::cout << msg << std::endl;
    return 1;
} catch (...) {
    std::cout << "some unknown exception happened" << std::endl;
    return 1;
}
