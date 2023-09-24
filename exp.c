#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN_N 1
#define MAX_N 4999

#define MIN_M 2
#define MAX_M 4

#define MIN_X 1
#define MAX_X 30000

int main()
{
	FILE *fin = fopen("exp.in", "r");

	if (!fin) {
		printf("Eroare fisier exp.in\n");
		return 1;
	}
	
	unsigned short n, m;

	fscanf(fin, "%hu %hu", &m, &n);

	if (m < MIN_M || m > MAX_M) {
		printf("Eroare valoare M\n");
		return 2;
	}

	if (n < MIN_N || n > MAX_N) {
		printf("Eroare valoare N\n");
		return 3;
	}

	unsigned short *dp, i, x, d, nrdp;

	nrdp = round(sqrt(MAX_X));

	dp = (unsigned short*)calloc(nrdp+1, sizeof(unsigned short));

	if (!dp) {
		printf("Eroare alocare memorie *dp\n");
		return 4;
	}

	for (i = 0; i < n; i++) {
		fscanf(fin, "%hu", &x);

		if (x < MIN_X || x > MAX_X) {
			printf("Eroare valoare X\n");
			return 5;
		}

		for (d = 2; d*d <= x; d++) {
			for (; x % d == 0; dp[d]++, x /= d);
		}

		if (x > 1) {
			dp[x]++;
		}
	}

	fclose(fin);

	char ok = 1;

	for (i = 2; i <= nrdp && ok; i++) {
		if (dp[i] > 0) {
			if (dp[i] % m) {
				ok = 0;
			} else {
				dp[i] /= m;
			}
		}
	}

	FILE *fout = fopen("exp.out", "w");

	if (!ok) {
		fprintf(fout, "0");
	} else {
		fprintf(fout, "1\n");

		for (i = 2; i <= nrdp; i++) {
			if (dp[i] > 0) {
				fprintf(fout, "%hu %hu\n", i, dp[i]);
			}
		}
	}

	fclose(fout);

	free(dp);

	return 0;
}
// scor 100
