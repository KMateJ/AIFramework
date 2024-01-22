#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define MAT_AT(m,i,j) (m).es[(i)*(m).cols + (j)]

double sigf(double x){
    return 1.f/(1.f+expf(-x));
}


double rand_double(){
    return (double) rand () / (double) RAND_MAX; 
}

typedef struct {
    size_t rows;
    size_t cols;
    double *es;

}Mat;

Mat mat_init(size_t r, size_t c){
    Mat matrix ;

    matrix.rows = r,
    matrix.cols = c;
    matrix.es = malloc(sizeof(*matrix.es)*r*c);

    return matrix;
}

void mat_dot(Mat dst, Mat A, Mat B){

    if (A.cols != B.rows) {printf("The given matrixes are not compatible\n")   ;return;}
    if (A.rows != dst.rows || B.cols != dst.cols) {printf("The given dst matrix is not compatible\n")   ;return;}

    for ( size_t i; i < A.rows; ++i ){
        for (size_t j; j < B.cols; ++j ){
            MAT_AT(dst,i,j) = 0;
            for (size_t k; k < A.cols; ++k){
                MAT_AT(dst,i,j) += MAT_AT(A,i,k)*MAT_AT(B,k,j);
            }
        }
    }
}

void mat_sum(Mat dst, Mat A){

    if (dst.cols != A.cols || dst.rows != A.rows) {printf("The given matrixes are not compatible\n")   ;return;}

    for (int i=0; i< dst.rows; ++i) {
        for (int j=0; j< dst.cols; ++j) {
            MAT_AT(dst,i,j) += MAT_AT(A,i,j);
        }
    }
}

void mat_rand( Mat m, double low, double high){
    for (size_t i = 0; i< m.rows; ++i){
        for (size_t j = 0; j< m.cols; ++j) {
            MAT_AT(m,i,j) = rand_double() * (high - low) + low;
        }
    }
}

void mat_fill(Mat m, double value){
    for (size_t i = 0; i< m.rows; ++i){
        for (size_t j = 0; j< m.cols; ++j) {
            MAT_AT(m,i,j) = value;
        }
    }
}

void mat_print(Mat m){
    for (size_t i = 0; i< m.rows; ++i){
        for (size_t j = 0; j< m.cols; ++j) {
            printf("%.3f ",m.es[i*m.cols + j]);
        }
        printf("\n");
    }
}



double Train[][3]={
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,0},
};


int main(){

    srand(time(NULL));

    Mat w1 = mat_init(2,2);
    Mat b1 = mat_init(1,2);
    Mat w2 = mat_init(2,1);
    Mat b2 = mat_init(1,1);

    mat_rand(w1,0,1);
    mat_rand(b1,0,1);
    mat_rand(w2,0,1);
    mat_rand(b2,0,1);
/*
    mat_print(w1);
    printf("--------------\n");

    mat_print(b1);
    printf("--------------\n");

    mat_print(w2);
    printf("--------------\n");

    mat_print(b2);
    printf("--------------\n");
*/

    


    return 0;
}