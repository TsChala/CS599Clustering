% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{kmeansclust_interface}
\alias{kmeansclust_interface}
\title{K-means clustering}
\usage{
kmeansclust_interface(data_mat, N_centers)
}
\arguments{
\item{data_mat}{numeric data matrix, [number of samples] x  [number of features]}

\item{N_centers}{number of clusters}
}
\value{
Vector of cluster assignments, [number of samples]
}
\description{
K-means clustering algorithm for the given data matrix with the number
of clusters given.
}
\examples{
kmeansclust_interface(as.matrix(iris[,1:2]),3)
}
