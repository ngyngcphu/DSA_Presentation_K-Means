#include "k_means.h"

void cluster()
{
    string fileName{};
    int K{};
    string output_dir{};
    cin >> fileName >> K >> output_dir;
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "Error: Failed to open file." << endl;
        return;
    }
    string line{};
    int pointId{0};
    vector<Point> points{};
    while (getline(inFile, line))
    {
        stringstream ss{line};
        double val{};
        vector<double> attr{};
        while (ss >> val)
        {
            attr.push_back(val);
        }
        Point point(pointId, attr);
        points.push_back(point);
        ++pointId;
    }
    inFile.close();
    cout << "Data fetched successfully!" << endl;
    if (points.size() < K)
    {
        cout << "Error: Number of clusters greater than number of points." << endl;
        return;
    }
    KMeans kmeans(K, points[0].getTotalAttr(), pointId, 100, output_dir);
    srand(time(nullptr));
    kmeans.kMeansAlgo(points);
}

void predict(int K, string output_dir)
{
    double age{}, income{}, spending{};
    cout << "Enter Age of new custom: ";
    cin >> age;
    cout << "Enter Annual Income of new custom: ";
    cin >> income;
    cout << "Enter Spending of new custom: ";
    cin >> spending;
    ifstream inFile(output_dir + "/" + to_string(K) + "-cluster.txt");
    if (!inFile.is_open())
    {
        cout << "Error: Failed to open file." << endl;
        return;
    }
    string line{};
    bool evenLine{false};
    int loss = INT_MAX;
    int clusterId{1};
    int clusterIdPredict{clusterId};
    while (getline(inFile, line))
    {
        if (!evenLine)
        {
            evenLine = true;
            continue;
        }
        stringstream ss{line};
        double val{};
        vector<double> clusterAttr{};
        while (ss >> val)
        {
            clusterAttr.push_back(val);
        }
        double distance{};
        distance = sqrt(pow(age - clusterAttr[0], 2) + pow(income - clusterAttr[1], 2) +
                         pow(spending - clusterAttr[2], 2));
        if (distance < loss)
        {
            loss = distance;
            clusterIdPredict = clusterId;
        }
        ++clusterId;
        evenLine = false;
    }
    inFile.close();
    cout << "********************************************************" << endl;
    cout << "The new customer belongs to segment " << clusterIdPredict;
}

int main()
{
    //cluster();
    predict(5, "output");
    return 0;
}