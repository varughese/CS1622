void g(int a[], int index) {
    output(a[index]);
}

void f(int a[]) {
    int x;
    a[3] = 99;
    x = 1;
    g(a, x+x+x);
}
void main(void){
    int y[4];
    int x;

    x = 1;
    y[x+1] = 102;
    output(y[1+1]);
    f(y);
}
