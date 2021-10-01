#include <Rcpp.h>
#include "kmeansclust.h"
using namespace Rcpp;

//' K-means clustering
//'
//' K-means clustering algorithm for the given data matrix with the number
//' of clusters given.
//'
//' @param data_mat numeric data matrix, [number of samples] x  [number of features]
//' @param N_centers number of clusters
//'
//' @return Vector of cluster assignments, [number of samples]
//' @useDynLib CS599Clustering, .registration = TRUE
//' @importFrom Rcpp evalCpp
//' @export
//' 
//' @examples
//' kmeansclust_interface(as.matrix(iris[,1:2]),3)
// [[Rcpp::export]]
IntegerVector kmeansclust_interface
(NumericMatrix data_mat, int N_centers){
  int N_data = data_mat.nrow();
  int N_features = data_mat.ncol();
  double *data_ptr = &data_mat[0];
  NumericMatrix centers_mat(N_centers,N_features);
  double *centers_ptr = &centers_mat[0];
  IntegerVector cluster_vec(N_data);
  int *cluster_ptr = &cluster_vec[0];
  int status = kmeansclust
    (N_data,
     N_centers,
     N_features,
     data_ptr,
     //inputs above, outputs below.
     centers_ptr,
     cluster_ptr);
  if(status == ERROR_N_DATA_MUST_BE_POSITIVE){
    Rcpp::stop("Number of data points must be postiive");
  }
  if(status == ERROR_N_CENTERS_MUST_BE_POSITIVE){
    Rcpp::stop("Number of clusters must be postitive");
  }
  if(status == ERROR_N_CENTERS_MUST_BE_SMALLER_THAN_N_DATA){
    Rcpp::stop("Number of  clusters must be smaller than the number of data points");
  }
  if(status == WARNING_ITERATION_NUMBER){
    Rcpp::warning("Algorithm didn't converge in 30 iterations");
  }
  return cluster_vec;
}