#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y; } Point;

Point p0;

int orientation(Point a, Point b, Point c) {
    int v = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (v == 0) return 0;          // collinear
    return (v > 0) ? 1 : 2;        // 1 = clockwise, 2 = counterclockwise
}

int dist(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int cmp(const void *a, const void *b) {
    Point p1 = *(Point*)a, p2 = *(Point*)b;
    int o = orientation(p0, p1, p2);
    if (o == 0) return dist(p0, p1) <= dist(p0, p2) ? -1 : 1;
    return (o == 2) ? -1 : 1;  // keep counterclockwise first
}

void convexHull(Point pts[], int n) {
    int ymin = pts[0].y, min = 0;
    for (int i = 1; i < n; i++)
        if (pts[i].y < ymin || (pts[i].y == ymin && pts[i].x < pts[min].x))
            ymin = pts[i].y, min = i;

    Point temp = pts[0]; pts[0] = pts[min]; pts[min] = temp;
    p0 = pts[0];

    qsort(&pts[1], n-1, sizeof(Point), cmp);

    Point stack[n];
    int top = 0;
    stack[top++] = pts[0];
    stack[top++] = pts[1];
    stack[top++] = pts[2];

    for (int i = 3; i < n; i++) {
        while (orientation(stack[top-2], stack[top-1], pts[i]) != 2)
            top--;
        stack[top++] = pts[i];
    }

    printf("Convex Hull:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    Point points[] = {{0,3},{2,2},{1,1},{2,1},{3,0},{0,0},{3,3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);
    return 0;
}