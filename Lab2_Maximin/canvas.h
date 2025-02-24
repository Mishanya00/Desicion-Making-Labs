#ifndef CANVAS_H
#define CANVAS_H

#include <memory>
#include <QWidget>
#include <unordered_map>
#include "pointclassifier.h"
#include <QColor>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void IterateButtonPressed();
    void IterateAllButtonPressed();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::unique_ptr<PointClassifier> pcMain;
    std::unordered_map<int, Qt::GlobalColor> color_map_;

signals:
};

#endif // CANVAS_H
