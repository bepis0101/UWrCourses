#include "/home/bepis0101/all.h"
#define R 6371

FILE *input;

double x_count(double lat, double lon)
{
    return R*cos(lat)*cos(lon);
}
double y_count(double lat, double lon)
{
    return R*cos(lat)*sin(lon);
}
double z_count(double lat, double lon)
{
    return R*sin(lat);
}
double distance(double x, double y, double z, double xp, double yp, double zp)
{
    return sqrt((xp-x)*(xp-x) + (yp-y)*(yp-y) + (zp-z)*(zp-z));
}
int main(int argc, char** argv)
{
    input = fopen(argv[1], "r");
    char str[150];
    int wiersz = 0;
    int pointy = 0;
    double x, y, z, xp = 0, yp = 0, zp = 0;
    double suma = 0.0;
    while(fgets(str, 150, input) && !feof(input))
    {
        wiersz++;
        char* check = "<trkpt";
        if(strstr(str, check) == NULL) 
        {
            continue;
        }
        pointy++;
        char* lat = strstr(str, "lat=");
        char* lon = strstr(str, "lon=");
        lon += 5; lat += 5;
        int lat_s = 0, lon_s = 0;
        while(*(lat+lat_s) != '"') lat_s++;
        while(*(lon+lon_s) != '"') lon_s++;
        *(lat+lat_s) = '\0';
        *(lon+lon_s) = '\0';
        lat_s--; lon_s--;
        double longitude = atof(lon), latitude = atof(lat);
        //printf("%lf %lf\n", longitude, latitude);
        x = x_count(latitude*M_PI/180.0, longitude*M_PI/180.0);
        y = y_count(latitude*M_PI/180.0, longitude*M_PI/180.0);
        z = z_count(latitude*M_PI/180.0, longitude*M_PI/180.0);
        if(pointy > 1)
        {
            suma += distance(x, y, z, xp, yp, zp);
        }
        xp = x;
        yp = y;
        zp = z;
    }
    printf("size: %ld\nrows: %d\npoints: %d\ndistance: %lf\n", ftell(input), wiersz, pointy, suma*1000);
}