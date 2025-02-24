#include "canvas.h"

#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QWidget{parent}
{
    this->resize(1100, 720);
    Rect points_area;
    points_area.x = this->pos().x() + 10;
    points_area.y = this->pos().y() + 10;
    points_area.width = this->size().width() - 10;
    points_area.height = this->size().height() - 50;

    color_map_[-1] = Qt::gray;
    color_map_[1] = Qt::red;
    color_map_[2] = Qt::green;
    color_map_[3] = Qt::blue;
    color_map_[4] = Qt::yellow;
    color_map_[5] = Qt::cyan;
    color_map_[6] = Qt::magenta;
    color_map_[7] = Qt::white;
    color_map_[8] = Qt::black;

    pcMain = std::make_unique<PointClassifier>(points_area);
    pcMain->GeneratePoints(2000);
    pcMain->GenerateKernels(1);
    pcMain->RecalculateClusters();
}

void Canvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    for (auto &point : pcMain->points_) {
        painter.setBrush(color_map_[point.cluster]);
        painter.drawEllipse(point.x, point.y, 5, 5);
    }
    for (auto &point : pcMain->kernels_) {
        painter.setBrush(color_map_[point.cluster]);
        painter.drawRect(point.x, point.y, 10, 10);
    }
}

void Canvas::IterateButtonPressed() {
    /*
    pcMain->RecalculateNewKernels();
    pcMain->RecalculateClusters();
    */
    pcMain->AddNewMaxKernel();
    pcMain->RecalculateClusters();
    this->repaint();
}

void Canvas::IterateAllButtonPressed() {
    pcMain->CalculateFinalKernels();
    //pcMain->RecalculateClusters(); // Its already done inside CalculateFinalKernels
    this->repaint();
}
