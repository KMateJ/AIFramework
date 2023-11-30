#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

double Train[][2]={
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10},
    {6,12},
    {7,14},
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

    double w =10.0;
    double b = 5.0; 

    double eps = 1e-3;    
    double rate = 1e-3;

    for (int i=0;i<1000;++i){
        double dw = (cost(w+eps,b) - cost(w,b))/eps;
        double db = (cost(w,b+eps) - cost(w,b))/eps;
        w-=rate*dw;
        b-=rate*db;
        printf("cost: %f\n", cost(w,b));
    }

    printf("cost: %f, w: %f, b: %f", cost(w,b),w,b);

    return 0;
}