#define ERROR_N_DATA_MUST_BE_POSITIVE 1
#define ERROR_N_CENTERS_MUST_BE_POSITIVE 2
#define ERROR_N_CENTERS_MUST_BE_SMALLER_THAN_N_DATA 3
int kmeansclust
(const int N_data,
 const int N_centers,
 const int N_features,
 const double *data_ptr,
 double *centers_ptr,
 //inputs above, outputs below.
 int *cluster_ptr
 );