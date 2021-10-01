test_that("k-means returns a vector with the same length as the input data set", {
  expect_equal(length(kmeansclust_interface(as.matrix(iris[,1:4]), 3)), nrow(iris[,1:4]))
})
test_that("cluster assignments are all between 1 and K", {
  expect_equal(c(min(kmeansclust_interface(as.matrix(iris[,1:4]), 3)),max(HCLUST(iris[,1:4], 3))), c(1,3))
})