#include <stdio.h>
#include <time.h>

#define ITERATIONS 10000000
#define ROWS 25
#define COLS 40
char screen_mem[ROWS][COLS];

inline void scroll_up();

// Alkuun meni 14.6s

int main()
{
    clock_t t1, t2;
    int i;

    t1 = clock();
    for (i = 0; i < ITERATIONS; ++i)
    {
        scroll_up();
    }
    t2 = clock();
    printf("%.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

    return 0;
}


/*
  "Scrollaa" näyttömuistia yhden rivin ylöspäin.
*/
inline void scroll_up()
{
    /*
      OptimizeIt!
    */
    int r, c;
    for (r = 1; r < ROWS; ++r)
    {
        for (c = 0; c < COLS; ++c)
        {
            screen_mem[r - 1][c] = screen_mem[r][c];
        }
    }
}