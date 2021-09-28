# CS599Clustering
##### CS599 Unsupervised Learning - R package coding project 1
This is sample package written for the course CS599 Unsupervised Learning.
This package includes two unsupervised clustering algorithms:
- Hiearchical clustering algorithm using the single linkage method
- K-Means algorithm
***
## Installation
You can install the latest version of this package from [GitHub](https://github.com/TsChala/CS599Clustering). For installation the *remotes* package is needed.

    # install.packages("remotes")
    remotes::install_github("TsChala/CS599Clustering")
***
## Usage
Here is an example code for demonstrating the usage of this package.

    ## Example
    library(CS599Clustering)
    data.mat <- iris[,1:4]
    K <- 3
    hclust.result <- HCLUST(data.mat,K)
    > hclust.result
    #>    [1] 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 3 3 3 3 3 3 3 3 3
    #>    [60] 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 3 3 3 3 3 3 3 3 3 3 3
    #>    [119] 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

    
