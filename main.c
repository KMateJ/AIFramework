#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

double Train[][2]={
    {0,1},
    {1,3},
    {2,5},
    {3,7},
    {4,9},
    {5,11},
    {6,13},
    {7,15},
};

#define train_count (int)(sizeof(Train)/sizeof(Train[0]))

double rand_float(void){
    return (double) rand() / (double) RAND_MAX;
}


double cost( double w , double b){
    double res = 0.0f;
    for (int i = 0; i < train_count ; ++i){
        double x = Train[i][0];
        double y = x*w + b;

        res += (y-Train[i][1])*(y-Train[i][1]);
    }

    return res/train_count;
}


int main(){
    srand(40);

    //double w = rand_float()*100;

    double w =0.5;
    double b = 0.1; 

    double eps = 1e-4;    
    double rate = 1e-4;

    for (int i=0;i<100000000;++i){
        double dw = (cost(w+eps,b) - cost(w,b))/eps;
        double db = (cost(w,b+eps) - cost(w,b))/eps;
        w-=rate*dw;
        b-=rate*db;
        
    }

    printf("cost: %f, w: %f, b: %f\n", cost(w,b),w,b);
    printf("tests-------------------\n");
    printf("input: 2 -> %f\n", 2*w+b);
    printf("input: 4 -> %f\n", 4*w+b);
    printf("input: 10 -> %f\n", 10*w+b);
    printf("input: 32 -> %f\n", 32*w+b);
    printf("input: 24 -> %f\n", 24*w+b);
    printf("input: -2 -> %f\n", -2*w+b);

    return 0;
}