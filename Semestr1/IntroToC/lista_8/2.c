#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#define FLT_MAX 3.402823466e+38F
#define FASTFLOOR(x) ( ((int)(x)<=(x)) ? ((int)x) : (((int)x)-1) )
unsigned char perm[512] = {151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
  151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 
};
float  grad2( int hash, float x, float y ) {
    int h = hash & 7;      // Convert low 3 bits of hash code
    float u = h<4 ? x : y;  // into 8 simple gradient directions,
    float v = h<4 ? y : x;  // and compute the dot product with (x,y).
    return ((h&1)? -u : u) + ((h&2)? -2.0f*v : 2.0f*v);
}
float snoise2(float x, float y) {

#define F2 0.366025403 // F2 = 0.5*(sqrt(3.0)-1.0)
#define G2 0.211324865 // G2 = (3.0-Math.sqrt(3.0))/6.0

    float n0, n1, n2; // Noise contributions from the three corners

    // Skew the input space to determine which simplex cell we're in
    float s = (x+y)*F2; // Hairy factor for 2D
    float xs = x + s;
    float ys = y + s;
    int i = FASTFLOOR(xs);
    int j = FASTFLOOR(ys);

    float t = (float)(i+j)*G2;
    float X0 = i-t; // Unskew the cell origin back to (x,y) space
    float Y0 = j-t;
    float x0 = x-X0; // The x,y distances from the cell origin
    float y0 = y-Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;}      // upper triangle, YX order: (0,0)->(0,1)->(1,1)

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6

    float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.0f + 2.0f * G2;

    // Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
    int ii = i & 0xff;
    int jj = j & 0xff;

    // Calculate the contribution from the three corners
    float t0 = 0.5f - x0*x0-y0*y0;
    if(t0 < 0.0f) n0 = 0.0f;
    else {
      t0 *= t0;
      n0 = t0 * t0 * grad2(perm[ii+perm[jj]], x0, y0); 
    }

    float t1 = 0.5f - x1*x1-y1*y1;
    if(t1 < 0.0f) n1 = 0.0f;
    else {
      t1 *= t1;
      n1 = t1 * t1 * grad2(perm[ii+i1+perm[jj+j1]], x1, y1);
    }

    float t2 = 0.5f - x2*x2-y2*y2;
    if(t2 < 0.0f) n2 = 0.0f;
    else {
      t2 *= t2;
      n2 = t2 * t2 * grad2(perm[ii+1+perm[jj+1]], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 40.0f * (n0 + n1 + n2); // TODO: The scale factor is preliminary!}
}

#define X 8000
#define Y 8000
#define and && 
#define local 7000
float siatka[X][Y];

int lok_maks(int x, int y)
{
    if(siatka[x][y] <= siatka[x-1][y-1]) return 0;
    if(siatka[x][y] <= siatka[x-1][y]) return 0;
    if(siatka[x][y] <= siatka[x-1][y+1]) return 0;
    if(siatka[x][y] <= siatka[x][y-1]) return 0;
    if(siatka[x][y] <= siatka[x][y+1]) return 0;
    if(siatka[x][y] <= siatka[x+1][y-1]) return 0;
    if(siatka[x][y] <= siatka[x+1][y]) return 0;
    if(siatka[x][y] <= siatka[x+1][y+1]) return 0;
    return 1;
}
typedef struct pair
{
    int x; 
    int y;
}pair;
float odl(pair p1, pair p2)
{
    float distance = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    return distance;
}
pair maksy[local];
float dist[local][local];
int main()
{
    int xres, yres, k, d;
    int z = scanf("%d%d%d%d", &xres, &yres, &k, &d);
    float step = 1.0/k;
    for(int y = 0; y < yres; y++)
    {
        for(int x = 0; x < xres; x++)
        {
            siatka[x][y] = snoise2(x*step, y*step);
        }
    }
    z = 0;
    for(int y = 1; y < yres-1; y++)
    {
        for(int x = 1; x < xres-1; x++)
        {
            if(lok_maks(x, y) == 1)
            {
                maksy[z].x = x;
                maksy[z].y = y;
                z++;
            }   
        }
    }
    float minimum = FLT_MAX;
    int imin = 0, jmin = 0;
    for(int i = 0; i < z; i++)
    {
        for(int j = 0; j < z; j++)
        {
            dist[i][j] = odl(maksy[i], maksy[j]);
            if(dist[i][j] < minimum and i != j)
            {
                minimum = dist[i][j];
            }
        }
    }
    printf("%d %.1f %d ", z, minimum, z-d);
    while(d != 0)
    {
        for(int i = 0; i < z; i++)
        {
            for(int j = 0; j < z; j++)
            {
                if(i != j and maksy[i].x != -1 and maksy[j].x != -1)
                {
                    if(dist[i][j] < minimum)
                    {
                        minimum = dist[i][j];
                        imin = i;
                        jmin = j;
                    }
                }
            }
        }
        float sumdist1 = 0, sumdist2 = 0;
        for(int i = 0; i < z; i++)
        {
            if(maksy[imin].x != -1 and maksy[jmin].x != -1)
            {
                sumdist1 += dist[imin][i];
                sumdist2 += dist[i][jmin];
            }
        }
        if(sumdist1 < sumdist2)
        {
            maksy[imin].x = -1;
        }
        else
        {
            maksy[jmin].x = -1;
        }
        minimum = FLT_MAX;
        d--;
    }
    minimum = FLT_MAX;
    for(int i = 0; i < z; i++)
    {
        for(int j = 0; j < z; j++)
        {
            if(i != j and maksy[i].x != -1 and maksy[j].x != -1)
            {
                if(dist[i][j] < minimum)
                {
                    minimum = dist[i][j];
                }
            }
        }
    }
    printf("%.1f", minimum);
}