#ifndef __K_MEANS_H__
#define __K_MEANS_H__

#include "main.h"

class Point
{
private:
    int id_point{};
    int id_cluster{};
    vector<double> attr{};
    int total_attr{};

public:
    Point(int id_point, const vector<double> &attr);

    int getTotalAttr() const;
    double getAttr(int index) const;
    int getId() const;
    void setCluster(int id_cluster);
    int getCluster() const;
};

class Cluster
{
private:
    int id_cluster{};
    vector<double> center_attr{};
    vector<Point> points{};

public:
    Cluster(int id_cluster, const Point &point);
    void setCenterAttr(int index, double attr);
    double getCenterAttr(int index) const;
    int getTotalPoints() const;
    int getId() const;
    bool removePoint(int id_point);
    void addPoint(const Point &point);
    Point getPoint(int index) const;
};

class KMeans
{
private:
    int K{};
    int total_attr{};
    int total_points{};
    int max_loop{};
    vector<Cluster> clusters{};
    string output_dir{};

    int getIdNearestCenter(const Point &point);

public:
    KMeans(int K, int total_attr, int total_points, int max_loop, const string &output_dir);
    void kMeansAlgo(vector<Point> &points);
};

#endif
