#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define EULER_NUMBER_L 2.7182818


double Train[][3]={
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1},
};

#define train_count (int)(sizeof(Train)/sizeof(Train[0]))


long double sigf(double x){
    return (1 / (1 + pow(EULER_NUMBER_L, -x)));
}

double cost( double w1 , double w2){
    double res = 0.0f;
    for (int i = 0; i < train_count ; ++i){
        double x1 = Train[i][0];
        double x2 = Train[i][1];
        double y =sigf( w1*x1 + w2*x2);

        res += (y-Train[i][2])*(y-Train[i][2]);
    }

    return res/train_count;
}


#define train_count (int)(sizeof(Train)/sizeof(Train[0]))

int main(){

    double w1 = 0.05;
    double w2 = -1.2;

    double eps = 1e-1;    
    double rate = 1e-1;

    for (int i =0; i< 100000; ++i){
        
        double dw1 = (cost(w1+eps,w2) -cost(w1,w2))/eps;
        double dw2 = (cost(w1,w2+eps) -cost(w1,w2))/eps;

        w1=rate*dw1;
        w2=rate*dw2;
        
    }


    printf("cost: %f, w1: %f, w2: %f\n",cost(w1,w2),w1,w2);

    return 0;
}