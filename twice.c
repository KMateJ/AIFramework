#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


double Train[][3]={
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1},
};

#define train_count (int)(sizeof(Train)/sizeof(Train[0]))


double sigf(double x){
    return 1.f/(1.f+expf(-x));
}

double cost( double w1 , double w2, double b){
    double res = 0.0f;
    for (int i = 0; i < train_count ; ++i){
        double x1 = Train[i][0];
        double x2 = Train[i][1];
        double y =sigf( w1*x1 + w2*x2 + b);

        res += (y-Train[i][2])*(y-Train[i][2]);
    }

    return res/train_count;
}

 void predict(int x, int y,double w1,double w2,double b){
    printf("%d | %d => %f\n",x,y,sigf( w1*x + w2*y + b));
 }

int main(){

    double w1 = 0.05;
    double w2 = 0.2;
    double b = 0.23;

    double eps = 1e-2;    
    double rate = 1e-2;

    for (int i =0; i< 1000000; ++i){
        
        double dw1 = (cost(w1+eps,w2,b) -cost(w1,w2,b))/eps;
        double dw2 = (cost(w1,w2+eps,b) -cost(w1,w2,b))/eps;
        double db = (cost(w1,w2,b+eps) -cost(w1,w2,b))/eps;

        w1-=rate*dw1;
        w2-=rate*dw2;
        b-=rate*db;
    }


    printf("cost: %f, w1: %f, w2: %f, b: %f\n",cost(w1,w2,b),w1,w2,b);

    for (int i=0;i<train_count;++i){
        predict(Train[i][0],Train[i][1],w1,w2,b);
    }


    return 0;
}