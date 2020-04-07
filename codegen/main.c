int g;
int garr[4];

void bar(int a[], int b, int c, int d){
    output(a[1]);
}

void foo(int a[], int b, int c){
    output(a[1]);
    bar(a, a[1], b, c);
}

void main(void){
    int x;
    int y[4];

    x = 101;
    y[0] = 102;
    y[1] = 103;
    y[2] = 104;
    y[3] = 105;

    foo(y, x, y[3]);
}
