#ifndef POINTCLASSIFIER_H
#define POINTCLASSIFIER_H

#include <vector>

struct Rect
{
    float x, y;
    float width;
    float height;
};

struct ClusteredPoint
{
    ClusteredPoint() {
        x = 0;
        y = 0;
        cluster = -1;
        isKernel = false;
    }

    ClusteredPoint(float xCor, float yCor) {
        x = xCor;
        y = yCor;
        cluster = -1;
        isKernel = false;
    }

    float x;
    float y;
    int cluster;
    bool isKernel;
};

class PointClassifier
{
public:
    Rect area_;
    std::vector<ClusteredPoint> points_;
    std::vector<ClusteredPoint> kernels_;

    PointClassifier(Rect points_area);

    void GeneratePoints(int count);
    void GenerateKernels(int count);
    void RecalculateClusters();
    void RecalculateNewKernels();
    void CalculateFinalKernels();

private:
    ClusteredPoint ClosestKernel(ClusteredPoint p);
    float GetDistanceBetween(ClusteredPoint a, ClusteredPoint b);
};

#endif // POINTCLASSIFIER_H
