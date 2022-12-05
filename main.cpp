#include "k_means.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Error: command-line argument count mismatch. \n ./kmeans <INPUT> <K> <OUT-DIR>" << endl;
        return 1;
    }
    string output_dir{argv[3]};
    int K{atoi(argv[2])};
    string filename{argv[1]};
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cout << "Error: Failed to open file." << endl;
        return 1;
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
        return 1;
    }
    KMeans kmeans(K, points[0].getTotalAttr(), pointId, 100, output_dir);
    srand(time(nullptr));
    kmeans.kMeansAlgo(points);
    return 0;
}