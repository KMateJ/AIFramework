#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


double sigf(double x){
    return 1.f/(1.f+expf(-x));
}

typedef struct Xor{
    double or_w1;
    double or_w2;
    double or_b;

    double nand_w1;
    double nand_w2;
    double nand_b;

    double and_w1;
    double and_w2;
    double and_b;

}Xor;

double forward(Xor m, double x, double y){
    double a = sigf(m.or_w1*x+m.or_w2*y+m.or_b);
    double b = sigf(m.nand_w1*x+m.nand_w2*y+m.nand_b);
    return sigf(m.and_w1*a+m.and_w2*b+m.and_b);
}


double Train[][3]={
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,0},
};

#define train_count (int)(sizeof(Train)/sizeof(Train[0]))



double cost(Xor m){
    double res = 0.0f;
    for (int i = 0; i < train_count ; ++i){
        double x1 = Train[i][0];
        double x2 = Train[i][1];
        double y = forward(m,x1,x2);

        res += (y-Train[i][2])*(y-Train[i][2]);
    }

    return res/train_count;
}

double rand_float(void){
    return (double) rand() / (double) RAND_MAX;
}

Xor rand_xor(){
    Xor m;
    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_b = rand_float();
    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b = rand_float();
    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_b = rand_float();
    return m;
}

void print_xor(Xor m){

    printf("or_w1 = %f\n",m.or_w1);
    printf("or_w2 = %f\n",m.or_w2);
    printf("or_b = %f\n",m.or_b);
    printf("nand_w1 = %f\n",m.nand_w1);
    printf("nand_w2 = %f\n",m.nand_w2);
    printf("nand_b = %f\n",m.nand_b);
    printf("and_w1 = %f\n",m.and_w1);
    printf("and_w2 = %f\n",m.and_w2);
    printf("and_b = %f\n",m.and_b);

}

int main(){
    srand(time(NULL));

    Xor m = rand_xor();

    print_xor(m);

    return 0;
}