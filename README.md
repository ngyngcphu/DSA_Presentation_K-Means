# K-Means Clustering Algorithms and Customer Segmentation Problem
> This is basic implementing of K-Means Clustering Algorithms in C++ and application in solving Customer Segmentation Problem.
## Table of contents

[I. Problem](#problem)

[II. K-Means Clustering Algorithm Implementing](#implement)

[III. Result](#result)

[IV. References](#ref)
*************************

<a name = "problem"></a>

## I. Problem
You are the owner of a shop. It doesn't matter if you own an e-commerce or a supermarket. It doesn't matter if it is a small shop or a huge company such as Amazon or Netflix, it's better to know your customers.

You were able to collect basic data about your customers holding a membership card such as age, annual income, and spending score. This last one is a score based on customer behavior and purchasing data. There are some new products on the market that you are interested in selling. But you want to target a specific type of clients for each one of the products.

Particularly, clustering, the most important unsupervised learning problem, is able to create categories grouping similar individuals. These categories are called clusters. A cluster is a collection of points in a dataset. These points are more similar between them than they are to points belonging to other clusters. Distance-based clustering groups the points into some number of clusters such that distances within the cluster should be small while distances between clusters should be large.
***

<a name = "implement"></a>

## II. K-Means Clustering Algorithm Implementing
My source code include 6 files: 
- `input.txt`: contain informations (include age, annual come, spending score) of 200 customers.
- `main.h`: contain declarations of libraries which I used.
- `k_means.h`: contain declarations of 3 classes: `class Point`, `class Cluster`, `class KMean`.
- `k_means.cpp`: implement methods of 3 classes above.
- `main.cpp`: read data from file **input.txt**, divided into K clusters and predict.
- `output`: include 2 files:
    - `k-cluster.txt`: include k customer segment.
    - `k-points.txt`: include points of each cluster.

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
vector<Point> points: all of points (customers) which cluster contains.
```
`class KMeans`

![classKMeans](/img/classKMeans.png)

This is the class representing all of clusters, all of points (customers) of each cluster, include:
```sh
K: number of clusters.
total_attr: number of attributes of each point (customer).
total_points: number of points (200 customers).
max-loop: limit the number of iterations of K-Means algorithm (<= 100 loops).
vector<Cluster> clusters: contains K clusters.
output_dir: name of output folder.
```
```sh
int getIdNearestCenter(const Point &point): return id of cluster which is nearest the point .
void kMeansAlgo(vector<Point> &point): implement K-Means Clustering Algorithm.
```
### 2. k_means.cpp
The K-Means Clustering Algorithms part is as follows:
```sh
    if (K > total_points)
    {
        return;
    }
    vector<int> init_center{};
    for (int i{0}; i < K; ++i)
    {
        while (true)
        {
            int id_center{rand() % total_points};
            if (find(init_center.begin(), init_center.end(), id_center) == init_center.end())
            {
                init_center.push_back(id_center);
                points[id_center].setCluster(i);
                Cluster cluster(i, points[id_center]);
                clusters.push_back(cluster);
                break;
            }
        }
    }
    int loop{1};
    while (true)
    {
        bool converge{true};
        for (int i{0}; i < total_points; ++i)
        {
            int id_old_cluster{points[i].getCluster()};
            int id_new_cluster{getIdNearestCenter(points[i])};
            if (id_new_cluster != id_old_cluster)
            {
                if (id_old_cluster != -1)
                {
                    clusters[id_old_cluster].removePoint(points[i].getId());
                }
                points[i].setCluster(id_new_cluster);
                clusters[id_new_cluster].addPoint(points[i]);
                converge = false;
            }
        }
        for (int i{0}; i < K; ++i)
        {
            for (int j{0}; j < total_attr; ++j)
            {
                int total_points_cluster{clusters[i].getTotalPoints()};
                double sum{0.0};
                if (total_points_cluster > 0)
                {
                    for (int p{0}; p < total_points_cluster; ++p)
                    {
                        sum += clusters[i].getPoint(p).getAttr(j);
                    }
                    clusters[i].setCenterAttr(j, sum / total_points_cluster);
                }
            }
        }
        if (converge || loop >= max_loop)
        {
            cout << "Break in loop: " << loop << endl;
            break;
        }
        ++loop;
    }
```
Analyze the complexity of the algorithm:

`Time Complexity: O(KxNxA)` (K: number of clusters, N: number of points, A: number attribute of each point).

`Space Complexity: O(K)` (because using temporary data structure: vector<int> init_center).
### 3. main.cpp
Include 2 main method:
- `void cluster`: reading input data from **input.txt** (include information of 200 customers), clustering data and writing data in folder **output**.
- `void predict`: predicting the segment of a new customer based on **output**

<a name = "result"></a>

## III. Results
`input.txt`

![input](/img/input.png)

- Compile: `g++ -o main main.cpp k_means.cpp -I . -std=c++11`.
- Run `.\main`.
- Enter `input.txt`, `5`, `output` respectively.

`output`

![k-cluster](/img/k-cluster.png)    ![k-points](/img/k-points.png)

`predict`

![predict](/img/predict.png)

<a name = "ref"></a>

## IV. References
- [ugis22/clustering_analysis](https://github.com/ugis22/clustering_analysis)
- [marcoscastro/kmeans](https://github.com/marcoscastro/kmeans)