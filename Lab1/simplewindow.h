#ifndef SIMPLEWINDOW_H
#define SIMPLEWINDOW_H

#include <QWidget>

class SimpleWindow : public QWidget
{
    Q_OBJECT

public:
    SimpleWindow(QWidget *parent = nullptr);
    ~SimpleWindow();
};
#endif // SIMPLEWINDOW_H
