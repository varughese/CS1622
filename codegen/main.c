int g;
int garr[4];

void bar(int a[], int b, int c, int d)
{
    output(a[1]);
    a[2] = 6;
    b = 6;
    c = 6;
    d = 6;
}

void foo(int a[], int b, int c)
{
    output(a[1]);
    a[0] = 6;
    a[1] = 6;
    bar(a, a[1], b, c);
    b = 6;
    c = 6;
}

void main(void)
{
    int x;
    int y[4];

    x = 101;
    y[0] = 102;
    y[1] = 103;
    y[2] = 104;
    y[3] = 105;

    foo(y, x, y[3]);

    output(y[0]);
    output(y[1]);
    output(y[2]);
    output(y[3]);
    output(x);

    g = 201;
    garr[0] = 202;
    garr[1] = 203;
    garr[2] = 204;
    garr[3] = 205;

    foo(garr, g, garr[3]);

    output(garr[0]);
    output(garr[1]);
    output(garr[2]);
    output(garr[3]);
    output(g);
}
