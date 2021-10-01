#include "kmeansclust.h"
#include <math.h>
#include <iostream>
#include <Rcpp.h>
#include <cmath>

int kmeansclust
  (const int N_data,
   const int N_centers,
   const int N_features,
   const double *data_ptr,
   //inputs above, outputs below.
   double *centers_ptr,
   int *cluster_ptr
  ){
  if(N_data < 1){
    return ERROR_N_DATA_MUST_BE_POSITIVE;
  }
  if(N_centers < 1){
    return ERROR_N_CENTERS_MUST_BE_POSITIVE;
  }
  
  if(N_centers > N_data){
    return ERROR_N_CENTERS_MUST_BE_SMALLER_THAN_N_DATA;
  }
  
  // Initialize cluster centers to random data points
  // Generate random indices
  int *rand_index = new int[N_centers];
  //std::srand(1);
  for(int rand_i=0; rand_i < N_centers; rand_i++){
    rand_index[rand_i] = std::rand() % N_data;
  }
  
  double sum_center_i=0;
  int num_points_cluster_i=0;
  
  // Assign cluster centers to the random data points
  for(int i=0;i<N_centers;i++){
    for(int j=0;j<N_features;j++){
      centers_ptr[j*N_centers+i] = data_ptr[j*N_data + rand_index[i]];
      //Rcpp::Rcout << new_centers[j*N_centers + i] << std::endl;
    }
  }

  int iteration = 0;
  int *cluster_old_ptr = new int[N_data];
  int cluster_difference = 1;
  
  do{
    // Assign each data point to the closest center
    
    iteration++;
    
    for(int data_i=0; data_i<N_data; data_i++){
      cluster_old_ptr[data_i] = cluster_ptr[data_i];
      double min_error = INFINITY;
      for(int center_i=0;
          center_i<N_centers; center_i++){
        double error = 0;
        for(int feature_i=0;
            feature_i<N_features; feature_i++){
          double data_value =
            data_ptr[feature_i*N_data + data_i];
          double center_value =
            centers_ptr[feature_i*N_centers + center_i];
          double diff = data_value - center_value;
          error += diff * diff;
        }
        if(error < min_error){
          min_error = error;
          cluster_ptr[data_i] = center_i+1;
        }
      }
    }
    
    // Recalculate the cluster centers based on the new cluster assignments
    
    for(int center_i=0; center_i<N_centers; center_i++){
  
      for(int feature_i=0; feature_i<N_features; feature_i++){
        sum_center_i = 0;
        num_points_cluster_i = 0;
        for(int data_i=0; data_i<N_data; data_i++){
          
          double data_value =
            data_ptr[feature_i*N_data + data_i];
          
          if(center_i+1 == cluster_ptr[data_i]){
          sum_center_i +=  data_value;
          num_points_cluster_i++;}
        }
        sum_center_i = sum_center_i/num_points_cluster_i;
        centers_ptr[feature_i*N_centers + center_i] = sum_center_i;
        //Rcpp::Rcout << sum_center_i <<" " << iteration << std::endl;
      }
    }
    
    cluster_difference = 0;
    
    for(int data_i=0; data_i<N_data;data_i++){
      cluster_difference += std::abs(cluster_ptr[data_i]-cluster_old_ptr[data_i]);
    }
    //Rcpp::Rcout<<cluster_difference << std::endl;
    
  // Stop if the cluster assignments didn't change or we reached 30 iterations  
  }while(cluster_difference != 0 && iteration < 30);
  
  if(iteration ==30){
    return WARNING_ITERATION_NUMBER;
  }
  
  return 0;//SUCCESS
}