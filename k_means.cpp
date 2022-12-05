#include "k_means.h"

Point::Point(int id_point, const vector<double> &attr)
{
    this->id_point = id_point;
    this->id_cluster = -1;
    this->total_attr = attr.size();
    for (int i{0}; i < total_attr; ++i)
    {
        this->attr.push_back(attr[i]);
    }
}

int Point::getTotalAttr() const
{
    return total_attr;
}

double Point::getAttr(int index) const
{
    return attr[index];
}

int Point::getId() const
{
    return id_point;
}

void Point::setCluster(int id_cluster)
{
    this->id_cluster = id_cluster;
}

int Point::getCluster() const
{
    return id_cluster;
}

Cluster::Cluster(int id_cluster, const Point &point)
{
    this->id_cluster = id_cluster;
    for (int i{0}; i < point.getTotalAttr(); ++i)
    {
        this->center_attr.push_back(point.getAttr(i));
    }
    points.push_back(point);
}

void Cluster::setCenterAttr(int index, double attr)
{
    center_attr[index] = attr;
}

double Cluster::getCenterAttr(int index) const
{
    return center_attr[index];
}

int Cluster::getTotalPoints() const
{
    return points.size();
}

int Cluster::getId() const
{
    return id_cluster;
}

bool Cluster::removePoint(int id_point)
{
    for (int i{0}; i < points.size(); ++i)
    {
        if (id_point == points[i].getId())
        {
            points.erase(points.begin() + i);
            return true;
        }
    }
    return false;
}

void Cluster::addPoint(const Point &point)
{
    points.push_back(point);
}

Point Cluster::getPoint(int index) const
{
    return points[index];
}

int KMeans::getIdNearestCenter(const Point &point)
{
    int id_cluster_center{};
    double sum_sqrt{0.0};
    for (int i{0}; i < total_attr; ++i)
    {
        sum_sqrt += pow(point.getAttr(i) - clusters[0].getCenterAttr(i), 2);
    }
    double min_dist{sqrt(sum_sqrt)};
    for (int i{1}; i < K; ++i)
    {
        sum_sqrt = 0.0;
        for (int j{0}; j < total_attr; ++j)
        {
            sum_sqrt += pow(point.getAttr(j) - clusters[i].getCenterAttr(j), 2);
        }
        double dist{sqrt(sum_sqrt)};
        if (dist < min_dist)
        {
            min_dist = dist;
            id_cluster_center = i;
        }
    }
    return id_cluster_center;
}

KMeans::KMeans(int K, int total_attr, int total_points, int max_loop, const string &output_dir)
{
    this->K = K;
    this->total_attr = total_attr;
    this->total_points = total_points;
    this->max_loop = max_loop;
    this->output_dir = output_dir;
}

void KMeans::kMeansAlgo(vector<Point> &points)
{
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
    ofstream pointsFile;
    pointsFile.open(output_dir + "/" + to_string(K) + "-points.txt", ios::out);

    for (int i{0}; i < K; ++i)
    {
        int total_points_cluster = clusters[i].getTotalPoints();
        if (i != 0)
        {
            pointsFile << endl;
        }
        pointsFile << "Cluster " << clusters[i].getId() + 1 << endl;
        for (int j{0}; j < total_points_cluster; ++j)
        {
            pointsFile << "Point " << clusters[i].getPoint(j).getId() + 1 << ": ";
            for (int p{0}; p < total_attr; ++p)
            {
                pointsFile << clusters[i].getPoint(j).getAttr(p) << " ";
            }
            pointsFile << endl;
        }
    }
    pointsFile.close();
    ofstream outFile;
    outFile.open(output_dir + "/" + to_string(K) + "-cluster.txt", ios::out);
    for (int i{0}; i < K; ++i)
    {
        cout << "Cluster " << clusters[i].getId() + 1 << ": ";
        outFile << "Cluster " << clusters[i].getId() + 1 << ": ";
        for (int j{0}; j < total_attr; ++j)
        {
            cout << clusters[i].getCenterAttr(j) << " ";
            outFile << clusters[i].getCenterAttr(j) << " ";
        }
        cout << endl;
        outFile << endl;
    }
    outFile.close();
}