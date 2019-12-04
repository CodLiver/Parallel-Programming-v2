#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int m;
	int n;
	double tol;// = 0.0001;

	//int i, j, iter;

	m = atoi(argv[1]);
	n = atoi(argv[2]);
	tol = atof(argv[3]);

	double t[m + 2][n + 2], tnew[m + 1][n + 1];

	printf("%d %d %lf\n", m, n, tol);

	double start_time = omp_get_wtime();
	//task1

	// initialise temperature array
	#pragma parallel
	{
		#pragma omp for schedule(static)
		for (int i = 0; i <= m + 1; i++) {
			for (int j = 0; j <= n + 1; j++) {
				t[i][j] = 30.0;
			}
		}

		#pragma omp for schedule(static)
		// fix boundary conditions
		for (int i = 1; i <= m; i++) {
			t[i][0] = 10.0;//40.0;
			t[i][n + 1] = 140.0;//90.0;
		}

		#pragma omp for schedule(static)
		for (int j = 1; j <= n; j++) {
			t[0][j] = 20.0;//30.0;
			t[m + 1][j] = 100.0;//50.0;
		}

	}

	//task2
	// main loop
	int iter = 0;
	double difmax = 1000000.0;
	#pragma omp parallel
	{
		while (difmax > tol) {
			#pragma omp single
			++iter;

			//either go with part 2 version or this but like part 2 version. critical seems to work becaue race conditions.
			difmax = 0.0;

			double priv_difmax = 0.0;
			// update temperature for next iteration
			#pragma omp for schedule(static)
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {

					#pragma omp critical
					tnew[i][j] = (t[i - 1][j] + t[i + 1][j] + t[i][j - 1] + t[i][j + 1]) / 4.0;

					// work out maximum difference between old and new temperatures
					double diff = fabs(tnew[i][j] - t[i][j]);
					if (diff > priv_difmax) {
						priv_difmax = diff;
					}

					#pragma omp critical
					t[i][j] = tnew[i][j];
				}

				#pragma omp critical
				if (priv_difmax > difmax)
				{
					difmax = priv_difmax;
				}

			}

			//#pragma omp single
			//printf("difmax: %f\n", difmax);
		}
	}
	

	double time = omp_get_wtime() - start_time;
	printf("time: %f\n", time);

	int isPrint = 1;

	if (isPrint == 1) {
		for (int i = 0; i <= m + 1; i++) {
			printf("\n");
			for (int j = 0; j <= n + 1; j++) {
				printf("%3.5lf ", t[i][j]);
			}
		}
	}

	// print results
	printf("iter = %d  difmax = %9.11lf", iter, difmax);
	printf("\n");

}