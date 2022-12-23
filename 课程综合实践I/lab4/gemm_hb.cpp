#include "hw.h"

#define N __X_N
#define min( i, j ) ( (i)<(j) ? (i): (j) )
#define inc_j 128
#define inc_p 256

void AddDot(int, int *, int *, int *);
void AddDot4x4(int, int32_t *, int32_t *, int32_t *);
void Blocking(int, int, int,int32_t *, int32_t *, int32_t *);

int32_t matA[N*N], matB[N*N],
        matCm[N*N], matCm2[N*N];

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int pid, numprocs, elements_per_process;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    elements_per_process = 624;
    omp_set_num_threads(8);

    int index, i, j, p, t, k, loops;
    int *matC = matCm, *matC2 = matCm2, *exchange;
    if (pid==0){
        input(matA, matB);
        memcpy(matC, matA, sizeof(int[N*N]));
    }

    int n=1;
    for (loops=0;loops<n;loops++){
        if (pid==0){
            if (loops==0){
                #pragma omp parallel for schedule(guided, 100) num_threads(8)
                for (i=0;i<N;i++)
                    for (j=0;j<i;j++) {
                        t = matA[i * N + j];
                        matA[i * N + j] = matA[j * N + i];
                        matA[j * N + i] = t;

                        t = matB[i * N + j];
                        matB[i * N + j] = matB[j * N + i];
                        matB[j * N + i] = t;
                    }
            }

            #pragma omp parallel for schedule(static) num_threads(8)
            for (i=0; i<N*N;i++){
                matA[i] += matB[i];
            }
        }

        if (pid==1 && loops!=0){
            #pragma omp parallel for schedule(static) num_threads(8)
            for (i=0; i<N*N;i++){
                matC2[i] = 0;
            }
        }
        if (loops!=0)
            MPI_Bcast(&matC2[0], N*N, MPI_INT, 1, MPI_COMM_WORLD);
        MPI_Bcast(&matA[0], N*N, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&matC[0], N*N, MPI_INT, 0, MPI_COMM_WORLD);

        if (pid==0){
            MPI_Status status;
            int block_k, block_n;
            #pragma omp parallel for schedule(guided, 100) num_threads(8)
            for (p=0; p<elements_per_process; p+=inc_p){
                block_k = min(elements_per_process-p, inc_p);
                for (j=0; j<N-1; j+=inc_j) {
                    block_n = min(N-1-j, inc_j);
                    Blocking(N, block_n, block_k, &matC[j*N+p], &matA[p], &matC2[j*N]);
                }
            }

            int *tmp = (int *)malloc(sizeof(int)*N*N*numprocs);
            if (numprocs > 1){
                int for_loop;
                MPI_Gather(&matC2[0],N*N,MPI_INT,&tmp[0],N*N,MPI_INT,0,MPI_COMM_WORLD);

                for (i=1;i<numprocs;i++){
                    for (j=0; j<N-1; j++){
                        for (for_loop=0; for_loop<N;for_loop++){
                            matC2[j*N+for_loop] += tmp[j*N+for_loop+i*N*N];
                        }
                    }
                }
            }
            free(tmp);
            tmp = (int *)malloc(sizeof(int)*N*N);
            MPI_Recv(&tmp[0], N*N, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
            for (i=0;i<N;i++){
                matC2[i*N+N-1] = tmp[i*N+N-1];
                matC2[(N-1)*N+i] = tmp[(N-1)*N+i];
            }
            free(tmp);
        }
        else{
            int _N=10001, _inc_j=64, _inc_p=256, p,
                    j, _step = 624, n_elements_received,
                    block_k, block_n; // 624
            MPI_Status status;
            int *tmp;
            if (pid!=numprocs-1)
                n_elements_received = _step;
            else
                n_elements_received = _N - (numprocs-1)*_step;

            #pragma omp parallel for schedule(guided, 100) num_threads(8)
            for (p=pid*_step; p<n_elements_received+_step*pid; p+=_inc_p){
                block_k = min(n_elements_received+_step*pid-p, _inc_p);
                for (j=0; j<_N-1; j+=_inc_j) {
                    block_n = min(_N-j-1, _inc_j);
                    Blocking(_N, block_n, block_k, &matC[j*_N+p], &matA[p], &matC2[j*_N]);
                }
            }
            MPI_Gather(&matC2[0],_N*_N,MPI_INT,&tmp[0],_N*_N,MPI_INT,0,MPI_COMM_WORLD);

            if (pid==2){
                #pragma omp parallel for schedule(static) num_threads(8)
                for (i=0;i<N;i++){
                    AddDot(N, &matC[i*N], &matA[(N-1)*N], &matC2[i*N+N-1]);
                    AddDot(N, &matC[(N-1)*N], &matA[i*N], &matC2[(N-1)*N+i]);
                }
                MPI_Send(&matC2[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }

        }
        if (pid==0){
            exchange = matC; matC = matC2; matC2 = exchange;
        }
    }
    if (pid==0)
        output(matC, n);
    MPI_Finalize();
}

void Blocking(int m, int block_n, int block_k, int32_t *C, int32_t *A, int32_t *result){
    int i,j, N_=10001;
    #pragma omp parallel for schedule(static) num_threads(8)
    for (j=0; j<m-1; j+=4){
        for (i=0; i<block_n; i+=4) {
            AddDot4x4(block_k, &C[i*N_], &A[j*N_], &result[i*N_+j]);
        }
    }
}


void AddDot(int l, int32_t *C, int32_t *A, int32_t *result){
    int sum=0;
    #pragma omp parallel for schedule(static) num_threads(8)
    for (int p=0; p<l; p++){
        sum += C[p] * A[p];
    }
    *result = sum;
}

void AddDot4x4(int l, int32_t *C, int32_t *A, int32_t *result){
     int
            result_00_reg,   result_01_reg,   result_02_reg,   result_03_reg,
            result_10_reg,   result_11_reg,   result_12_reg,   result_13_reg,
            result_20_reg,   result_21_reg,   result_22_reg,   result_23_reg,
            result_30_reg,   result_31_reg,   result_32_reg,   result_33_reg,
            c_0p_reg, c_1p_reg, c_2p_reg, c_3p_reg,
            a_p0_reg, a_p1_reg, a_p2_reg, a_p3_reg;

    // int *a_p0_pntr = &A[0], *a_p1_pntr=&A[1], *a_p2_pntr=&A[2], *a_p3_pntr=&A[3];
    result_00_reg=0,   result_01_reg=0,   result_02_reg=0,   result_03_reg=0,
    result_10_reg=0,   result_11_reg=0,   result_12_reg=0,   result_13_reg=0,
    result_20_reg=0,   result_21_reg=0,   result_22_reg=0,   result_23_reg=0,
    result_30_reg=0,   result_31_reg=0,   result_32_reg=0,   result_33_reg=0;

    for(int p = 0; p < l; ++p)
    {
        c_0p_reg = C[p];
        c_1p_reg = C[N+p];
        c_2p_reg = C[2*N+p];
        c_3p_reg = C[3*N+p];

        a_p0_reg = A[p], a_p1_reg = A[p+N], a_p2_reg = A[p+2*N], a_p3_reg = A[p+3*N];
 
        // 1st row of C
        result_00_reg += c_0p_reg * a_p0_reg;
        result_01_reg += c_0p_reg * a_p1_reg;
        result_02_reg += c_0p_reg * a_p2_reg;
        result_03_reg += c_0p_reg * a_p3_reg;

        // 2nd row of C
        result_10_reg += c_1p_reg * a_p0_reg;
        result_11_reg += c_1p_reg * a_p1_reg;
        result_12_reg += c_1p_reg * a_p2_reg;
        result_13_reg += c_1p_reg * a_p3_reg;

        // 3rd row of C
        result_20_reg += c_2p_reg * a_p0_reg;
        result_21_reg += c_2p_reg * a_p1_reg;
        result_22_reg += c_2p_reg * a_p2_reg;
        result_23_reg += c_2p_reg * a_p3_reg;

        // 4th row of C
        result_30_reg += c_3p_reg * a_p0_reg;
        result_31_reg += c_3p_reg * a_p1_reg;
        result_32_reg += c_3p_reg * a_p2_reg;
        result_33_reg += c_3p_reg * a_p3_reg;
    }

    result[0] += result_00_reg;   result[1] += result_01_reg;   result[2] += result_02_reg;   result[3] += result_03_reg;
    result[N] += result_10_reg;   result[N+1] += result_11_reg;   result[N+2] += result_12_reg;   result[N+3] += result_13_reg;
    result[2*N] += result_20_reg;  result[2*N+1] += result_21_reg;   result[2*N+2] += result_22_reg;   result[2*N+3] += result_23_reg;
    result[3*N] += result_30_reg;   result[3*N+1] += result_31_reg;   result[3*N+2] += result_32_reg;   result[3*N+3] += result_33_reg;
}
