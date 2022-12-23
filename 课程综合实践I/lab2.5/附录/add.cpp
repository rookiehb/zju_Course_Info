#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <smmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>

#define MAXN 100000000

float a[MAXN];
float b[MAXN];
float c[MAXN];
float d[MAXN];

int main()
{
    for (int i = 0; i < MAXN; ++i)
    {
        a[i] = 1.0 / (rand() + 1);
        b[i] = 1.0 / (rand() + 1);
    }
    for (int n = 0; n < 20; ++n)
    {
        for (int i = 0; i < MAXN; ++i)
        {
            d[i] += a[i] * b[i];
        }
    }
    clock_t start, end;
    start = clock();
    for (int n = 0; n < 20; ++n)
    {
        /* 可以修改的代码区域 */
        // -----------------------------------
        __m512 tmp1;
        __m512 tmp2;
        __m512 tmp;
        for (int i = 0; i < MAXN/16; i+=16)
        {
            // c[i] += a[i] * b[i];
            //
            tmp1 = _mm512_loadu_ps(&a[i]);
            tmp2 = _mm512_loadu_ps(&b[i]);
            tmp = _mm512_mul_ps(tmp1, tmp2);
            tmp = _mm512_add_ps(_mm512_loadu_ps(&c[i]),tmp);
            _mm512_storeu_ps(&c[i],tmp);
        }
        // -----------------------------------
    }
    end = clock();
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < MAXN; ++i)
    {
        if ((c[i] - d[i]) / d[i] > 0.0001)
        {
            printf("Check Failed at %d\n", i);
            exit(1);
        }
    }
    puts("Check Passed");
}
