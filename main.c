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
};

#define train_count (int)(sizeof(Train)/sizeof(Train[0]))

double rand_float(void){
    return (double) rand() / (double) RAND_MAX;
}


double cost( double w){
    double res = 0.0f;
    for (int i = 0; i < train_count ; ++i){
        double x = Train[i][0];
        double y = x*w;

        res += (y-Train[i][1])*(y-Train[i][1]);
    }

    return res/train_count;
}

int main(){
    srand(40);

    double w = rand_float()*100;

    printf ("cost: %f", cost(w));

    return 0;
}