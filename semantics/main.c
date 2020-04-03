int foo(int a, int b[]) {
    return a + b[0];
}

void main(void)
{
    int jack;
    int x;
    int y;
    int arr[10];

    jack;
    x = 1;
    y = 2;
    foo(x, arr);
    jack;
    arr; /* semantically bad */
    arr[1];
    arr[x];
    arr[x+2];
}