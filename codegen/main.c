void main(void)
{
    int x;
    int y;

    x = 1;
    y = 2;

    if(x == y)
        output(1);
    else
        output(2);
    output(3);

    if(x != y)
        output(4);
    else
        output(5);
    output(6);

    if(x == y)
        output(7);
    output(8);

    if(x != y)
        output(9);
    output(10);
}
