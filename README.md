# K-Means Clustering Algorithms and Customer Segmentation Problem
> This is basic implementing of K-Means Clustering Algorithms in C++ and application in solving Customer Segmentation Problem.
## Table of contents

[I. Problem](#problem)

[II. K-Means Clustering Algorithm Implementing](#implement)

[III. Solving problem and Predicting](#solve)
***

<a name = "problem">

## I. Problem
You are the owner of a shop. It doesn't matter if you own an e-commerce or a supermarket. It doesn't matter if it is a small shop or a huge company such as Amazon or Netflix, it's better to know your customers.

You were able to collect basic data about your customers holding a membership card such as age, annual income, and spending score. This last one is a score based on customer behavior and purchasing data. There are some new products on the market that you are interested in selling. But you want to target a specific type of clients for each one of the products.

Particularly, clustering, the most important unsupervised learning problem, is able to create categories grouping similar individuals. These categories are called clusters. A cluster is a collection of points in a dataset. These points are more similar between them than they are to points belonging to other clusters. Distance-based clustering groups the points into some number of clusters such that distances within the cluster should be small while distances between clusters should be large.
***

<a name = "implement">

## II. K-Means Clustering Algorithm Implementing
My source code include 6 files: 
- `input.txt`: contain informations (include age, annual come, spending score) of 200 customers.
- `main.h`: contain declarations of libraries which I used.
- `k_means.h`: contain declarations of 3 classes: `class Point`, `class Cluster`, `class KMean`.
- `k_means.cpp`: implement methods of 3 classes above.
- `main.cpp`: read data from file **input.txt**, divided into 5 customer clusters and predict segment of a new customer.
- `output`: include 2 files:
    - `5-cluster.txt`: include 5 customer segment.
    - `5-points.txt`: include points of each cluster.

### 1. k_means.h
`class Point`

![classPoint](/img/classPoint.png)

This is the class reprensenting each customer, include:
```sh
id_point: id of a customer.
id_cluster: id of cluster which contains customer.
vector<double> attr: contains attributes of a customer (3 attributes include age, annual income, spending respectively).
total_attr: number of attributes.
```
`class Cluster`

![classCluster](/img/classCluster.png)

This is the class representing each cluster, include:
```sh
id_cluster: id of cluster.
vector<double> center_attr: attributes of center cluster point.
vector<Point> points: all of points (customers) which cluster contanis
```
`class KMeans`

![classKMeans](/img/classKMeans.png)

This is the class representing all of clusters, all of points (customers) of each cluster, include:
```sh
K: number of clusters.
total_attr: number of attributes of each point (customer).
total_points: number of points (200 customers).
max-loop: limit the number of iterations of K-Means algorithm (<= 100 loops).
vector<Cluster> clusters: contains clusters (include 5 clusters).
output_dir: name of output folder.
```
```sh
int getIdNearestCenter(const Point &point): return id of cluster which is nearest the point .
void kMeansAlgo(vector<Point> &point): implement K-Means Clustering Algorithm.
```

## Instruction
* Clone code from repository.
`git clone https://github.com/ngyngcphu/DSA_Presentation_K-Means.git`
* Compile.
`g++ -o main main.cpp k_means.cpp -I . -std=c++11`
* Run with format: **.\kmeans INPUT K OUT-DIR** (K clusters - K = 5 in this code)
`.\main input.txt 5 output`
* The output will be 2 files in the output directory (eg: output) which contains the center point of each cluster (**K-points.txt**), and cluster detail for each point (**K-cluster.txt**).
