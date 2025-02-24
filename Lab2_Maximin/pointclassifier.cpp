#include "pointclassifier.h"

#include "random.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>


PointClassifier::PointClassifier(Rect area) : area_(area) {}

void PointClassifier::AddNewMaxKernel()
{
    std::vector<std::pair<float, int>>
        farthest_points(kernels_.size(), {0, {}}); // replace with std::pair
    std::pair<float, int> candidate;

    float avg_distance = 0;
    int distances_cnt = 0;
    float distance;

    for (int i = 0; i < kernels_.size(); ++i) {
        for (int j = i+1; j < kernels_.size(); ++j) {
            ++distances_cnt;
            avg_distance += std::sqrt(std::pow(kernels_[i].x - kernels_[j].x, 2)
                                      + std::pow(kernels_[i].y - kernels_[j].y, 2));
        }
    }

    if (distances_cnt != 0)
        avg_distance /= distances_cnt;

    for (int i = 0; i < kernels_.size(); ++i)
    {
        for (int j = 0; j < points_.size(); ++j)
        {
            if (points_[j].cluster == i+1) {
                distance = std::sqrt(std::pow(kernels_[i].x - points_[j].x, 2)
                                     + std::pow(kernels_[i].y - points_[j].y, 2));

                if (distance > farthest_points[i].first)
                {
                    farthest_points[i].first = distance;
                    farthest_points[i].second = j;
                }
            }
        }
    }

    candidate = *std::max_element(farthest_points.begin(), farthest_points.end(),
                     [](const std::pair<float, int> a, const std::pair<float, int> b) {
        return a.first < b.first;
    });

    if (candidate.first > avg_distance / 2) {
        points_[candidate.second].isKernel = true;
        points_[candidate.second].cluster = kernels_.size() + 1;
        kernels_.push_back(points_[candidate.second]);
    }
}

void PointClassifier::GeneratePoints(int count) {
    for (int i = 0; i < count; ++i) {
        float x = rnd::RandFloat(area_.x, area_.x + area_.width);
        float y = rnd::RandFloat(area_.y, area_.y + area_.height);
        points_.emplace_back(ClusteredPoint(x, y));
    }
}

void PointClassifier::GenerateKernels(int count) {
    std::unordered_set<int> selected_indexes;

    while (selected_indexes.size() < count) {
        selected_indexes.insert(rnd::Randint(0, points_.size()-1));
    }

    for (int i = 0; i < selected_indexes.size(); ++i) {
        points_[i].cluster = i+1;
        points_[i].isKernel = true;
        kernels_.emplace_back(points_[i]);
    }
}

ClusteredPoint PointClassifier::ClosestKernel(ClusteredPoint p)
{
    ClusteredPoint closest_kernel;
    float distance;
    float min_distance = std::numeric_limits<float>::max();

    for (auto kernel : kernels_)
    {
        distance = std::sqrt(std::pow(p.x - kernel.x, 2) + std::pow(p.y - kernel.y, 2));
        if (distance < min_distance) {
            closest_kernel = kernel;
            min_distance = distance;
        }
    }
    return closest_kernel;
}

void PointClassifier::RecalculateClusters()
{
    for (auto &point : points_)
    {
        point.cluster = ClosestKernel(point).cluster;
    }
}

float PointClassifier::GetDistanceBetween(ClusteredPoint a, ClusteredPoint b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

void PointClassifier::RecalculateNewKernels() {
    std::unordered_map<int, int> counts;
    std::unordered_map<int, ClusteredPoint> cluster_averages;
    std::unordered_map<int, ClusteredPoint> new_kernels;

    for (int i = 0; i < kernels_.size(); ++i) {
        counts[i+1] = 0;
        cluster_averages[i+1] = ClusteredPoint(0, 0);
        new_kernels[i+1] = kernels_[i];
    }

    for (auto p : points_)
    {
        counts[p.cluster]++;
        cluster_averages[p.cluster].x += p.x;
        cluster_averages[p.cluster].y += p.y;
    }

    for (auto &cluster : cluster_averages) {
        cluster.second.x /= counts[cluster.first];
        cluster.second.y /= counts[cluster.first];
    }

    for (auto p : points_) {
        for (auto cluster: cluster_averages) {
            if (GetDistanceBetween(p, cluster.second) < GetDistanceBetween(cluster.second, new_kernels[cluster.first])) {
                new_kernels[cluster.first] = p;
            }
        }
    }

    for (auto new_kernel : new_kernels) {
        new_kernel.second.isKernel = true;
        kernels_[new_kernel.first-1].isKernel = false;
        kernels_[new_kernel.first-1] = new_kernel.second;
    }
}

void PointClassifier::CalculateFinalKernels() {
    bool isAtLeastOneKernelChanged = true;
    std::vector<ClusteredPoint> kernels_prev(kernels_.size());

    while (isAtLeastOneKernelChanged) {
        for (int i = 0; i < kernels_.size(); ++i) {
            kernels_prev[i] = kernels_[i];
        }

        RecalculateNewKernels();
        RecalculateClusters();

        isAtLeastOneKernelChanged = false;
        for (int i = 0; i < kernels_.size(); ++i) {
            if (kernels_prev[i].x != kernels_[i].x || kernels_prev[i].y != kernels_[i].y) {
                isAtLeastOneKernelChanged = true;
            }
        }
    }
}
