int garr[15];

void main(void) {
    int x[30];
    x[6] = 6000;
    garr[1] = 100;
    garr[3] = 300;
    output(garr[1]);
    output(garr[3]);
    output(x[6]);
    {
        int x[10];
        int y[200];
        x[6] = 60000;
        y[4] = 40000;
        output(x[6]);
        output(y[4]);
    }
    /* garr[3+2] = 696969;*/
}