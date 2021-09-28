#' Hierarchical clustering
#'
#' Agglomerative hierarchical clustering on a given data matrix with a given
#' number of clusters. Uses single-linkage method.
#'
#' @param data.mat input data matrix, [number of samples] x  [number of features]
#' @param K number of clusters
#'
#' @return Vector of cluster assignments, [number of samples]
#' @export
#'
#'@importFrom data.table :=
#'
#' @examples
#' HCLUST(iris[,1:2],3)
HCLUST <- function (data.mat, K){
  row.indices <- 1:nrow(data.mat)
  pair.dt <- data.table::data.table(expand.grid(row.i = row.indices, row.j = row.indices))
  pair.dt[,dist := rowSums(abs(data.mat[row.i,]-data.mat[row.j,]))]
  wide.dt <- data.table::dcast(pair.dt, row.i ~ row.j)
  d.mat <- as.matrix(wide.dt[,-1])
  no.iter = nrow(d.mat)-K
  diag(d.mat) <- NA
  obs.in.each.cluster <- as.list(1:nrow(data.mat))
  for (i in 1:no.iter){
    min.indices <- which(min(d.mat,na.rm = TRUE) == d.mat)
    min.index.dt<- data.table::data.table(min.indices,
                              row = row(d.mat)[min.indices],
                              col = col(d.mat)[min.indices])
    first.min <- min.index.dt[1]
    index.to.keep <- first.min[["row"]]
    index.to.remove <- first.min[["col"]]
    join.indices <- c(index.to.keep,index.to.remove)
    d.mat.copy <- d.mat
    # single linkage
    new.cluster.distances <- apply(d.mat[join.indices,],2,min)
    d.mat.copy[index.to.keep,] <- new.cluster.distances
    d.mat.copy[,index.to.keep] <- new.cluster.distances
    d.mat.new <- d.mat.copy[-index.to.remove,-index.to.remove]
    obs.in.each.cluster.copy <- obs.in.each.cluster
    obs.in.each.cluster.copy[[index.to.keep]] <- 
      unlist(obs.in.each.cluster[join.indices])
    obs.in.each.cluster.new <- obs.in.each.cluster.copy[-index.to.remove]
    obs.in.each.cluster <- obs.in.each.cluster.new
    d.mat <- d.mat.new
  }
  cluster.id.vec <- integer(nrow(data.mat))
  for(cluster.id in seq_along(obs.in.each.cluster.new)){
    obs.indices <- obs.in.each.cluster.new[[cluster.id]]
    cluster.id.vec[obs.indices] <- cluster.id
  }
  return <- cluster.id.vec
}
