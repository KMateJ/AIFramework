#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


double sigf(double x){
    return 1.f/(1.f+expf(-x));
}


typedef struct {
    size_t rows;
    size_t cols;
    double *e;

}Mat;

Mat init_mat(size_t r, size_t c){

}



int main(){

    printf("Fuckin awsome\n");

    return 0;
}