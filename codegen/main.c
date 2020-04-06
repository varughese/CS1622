
int g;

void j(int y) {
    output(y+g);
}

void f(int x) {
    g = 4;
    j(9);
}

void main(void)
{
    f(3);
}