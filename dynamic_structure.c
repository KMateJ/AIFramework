#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define MAT_AT(m,i,j) (m).es[(i)*(m).stride + (j)]
#define MAT_PRINT(m) mat_print(m, #m)

double sigf(double x){
    return 1.f/(1.f+expf(-x));
}


double rand_double(){
    return (double) rand () / (double) RAND_MAX; 
}

typedef struct {
    size_t rows;
    size_t cols;
    size_t stride;
    double *es;

}Mat;

typedef struct {
    Mat a0;
    Mat w1,b1,a1;
    Mat w2,b2,a2;
} Xor;

Mat mat_init(size_t r, size_t c){
    Mat matrix ;

    matrix.rows = r,
    matrix.cols = c;
    matrix.stride = c;
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

void mat_print(Mat m, char* name){
    printf("%s = [\n",name);
    for (size_t i = 0; i< m.rows; ++i){
        for (size_t j = 0; j< m.cols; ++j) {
            printf("    %.3f ",MAT_AT(m,i,j));
        }
        printf("\n");
    }
    printf("]\n");
}

Mat mat_row(Mat m, size_t row){
    return (Mat){
        .rows=1,
        .cols = m.cols,
        .stride = m.stride,
        .es = &MAT_AT(m,row,0)
    };
}

Mat mat_column(Mat m, size_t column){
    return (Mat){
        .rows=m.rows,
        .cols = column,
        .es = &MAT_AT(m,0,column)
    };
}

void mat_copy(Mat dst, Mat src){
    if (dst.rows != src.rows) {printf("The given matrixes are not compatible\n")   ;return;}
    if (dst.cols != src.cols) {printf("The given matrixes are not compatible\n")   ;return;}

    for (size_t i = 0; i < dst.rows; ++i){
        for(size_t j = 0; j < dst.cols; ++j){
            MAT_AT(dst,i,j) =  MAT_AT(src,i,j);
        }
    }

}

void mat_sig(Mat m){
    for (size_t i; i < m.rows; ++i){
        for (size_t j; j< m.cols; ++j ){
            MAT_AT(m,i,j) = sigf(MAT_AT(m,i,j));
        }
    }
}

void forward_Xor(Xor m){
    mat_dot(m.a1,m.a0,m.w1);
    mat_sum(m.a1,m.b1);
    mat_sig(m.a1);

    mat_dot(m.a2,m.a1,m.w2);
    mat_sum(m.a2,m.b2);
    mat_sig(m.a2);
}

double cost(Xor m, Mat input, Mat output){

    double res = 0;

    for (size_t i = 0; i < input.rows; ++i){
        mat_copy(m.a0,mat_row(input,i));
        Mat y = mat_row(output,i);
        forward_Xor(m);

        for (size_t j = 0; j < output.cols; ++j){
            double dif = abs(MAT_AT(m.a2,0,j) - MAT_AT(y,0,j));
            res += dif*dif;
        }
    }

    return res/input.rows;
}



double data[] = {
    0,0,0,
    1,0,1,
    0,1,1,
    1,1,0,
};


int main(){

    srand(time(NULL));

    size_t n = sizeof(data)/sizeof(data[0])/3;
    size_t stride = 3;

    Mat ti = {
        .rows = n,
        .cols = 2,
        .stride = stride,
        .es = data,
    };

    Mat to = {
        .rows = n,
        .cols = 1,
        .stride = stride,
        .es = data + 2,
    };


    MAT_PRINT(ti);
    MAT_PRINT(to);


    Xor m;

    m.a0 = mat_init(1,2);

    m.w1 = mat_init(2,2);
    m.b1 = mat_init(1,2);
    m.a1 = mat_init(1,2);

    m.w2 = mat_init(2,1);
    m.b2 = mat_init(1,1);
    m.a2 = mat_init(1,1);


    mat_rand(m.w1,0,1);
    mat_rand(m.b1,0,1);
    mat_rand(m.w2,0,1);
    mat_rand(m.b2,0,1);

    //printf("cost of the model: %.3f\n",cost(m,));



    return 0;
}