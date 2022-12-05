# DSA_Presentation_K-Means
> This is a C++ implementation of the simple K-Means clustering algorithm.
***
Examples of dataset is in **input.txt** (include point coordinates).


## Instruction
* Clone code from repository.
`git clone https://github.com/ngyngcphu/DSA_Presentation_K-Means.git`
* Compile.
`g++ -o main main.cpp k_means.cpp -I . -std=c++11`
* Run with format: **.\kmeans <INPUT> <K> <OUT-DIR>** (K clusters - K = 5 in this code)
`.\main input.txt 5 output`
* The output will be 2 files in the output directory (eg: output) which contains the center point of each cluster (**K-points.txt**), and cluster detail for each point (**K-cluster.txt**).
