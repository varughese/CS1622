int garr[15];

void foo(int a[], int a1) {
    output(a[1]);  /* 103 */
}

void food(int a) {
    output(a);
}

void main(void) {
    int y[4];

    y[0] = 102;
    y[1] = 103;
    y[2] = 104;
    y[3] = 105;
/*int y;
y = 6999; */
    foo(y, 4);
}
