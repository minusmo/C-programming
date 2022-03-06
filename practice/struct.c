#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Point;

float get_distance(Point source, Point target)
{
    int x_dist, y_dist, dist;

    x_dist = target.x - source.x;
    printf("%d\n", x_dist);
    y_dist = target.y - source.y;
    printf("%d\n", y_dist);

    dist = sqrt(x_dist * x_dist + y_dist * y_dist);

    return dist;
}

void main()
{   
    Point p1, p2;
    int distance;

    p1.x = 1;
    p1.y = 2;

    p2.x = 9;
    p2.y = 8;

    distance = get_distance(p1, p2);

    printf("%d\n", distance);
}