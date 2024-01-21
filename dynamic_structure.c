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
    double *es;

}Mat;

Mat init_mat(size_t r, size_t c){
    Mat matrix ;

    matrix.rows = r,
    matrix.cols = c;
    matrix.es = malloc(sizeof(*matrix.es)*r*c);

    return matrix;
}

void mat_dot(Mat dst, Mat A, Mat B){

}

void mat_sum(Mat dst, Mat A){

}

void mat_print(Mat m){
    for (size_t i = 0; i< m.rows; ++i){
        for (size_t j = 0; j< m.cols; ++j) {
            printf("%.3f ",m.es[i*m.cols + j]);
        }
        printf("\n");
    }
}



int main(){


    int r =10;
    int c =9;
    Mat m = init_mat(r,c);

    for (int i=1;i<r*c+1;++i){
        m.es[i-1] = i;
    }

    mat_print(m);

    free(m.es);

    return 0;
}