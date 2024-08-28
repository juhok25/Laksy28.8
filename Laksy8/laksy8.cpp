#include <stdio.h>
#include <time.h>
#include <math.h>

#define DEG_TO_RAD(A) (A / 57.296)
#define ITERATIONS 1000000


// aikaa kului ensin 5.9s

// hakutaululla aikaa kului 0.2s
// hakutaulu on tallennetu stackkiin joten stack memory usage nousi
// heap ei vaikutusta

int main()
{
	clock_t t1, t2;
	unsigned i, a;
	double val;
	double sine_hakutaulu[360];

	// esilasketaa sine valuet ja laitetaan ne array
	for (a = 0; a < 360; ++a)
	{
		sine_hakutaulu[a] = sin(DEG_TO_RAD(a));
	}

	t1 = clock();
	for (i = 0; i < ITERATIONS; ++i)
	{
		for (a = 0; a < 360; ++a)
		{
			
			val = sine_hakutaulu[a];
		}
	}
	t2 = clock();
	printf("%.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	return 0;
}
