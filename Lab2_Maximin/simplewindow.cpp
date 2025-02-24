#include "simplewindow.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "random.h"
#include "canvas.h"


SimpleWindow::SimpleWindow(QWidget *parent)
    : QWidget(parent)
{
    rnd::Init();

    this->resize(1280, 720);

    auto outer = new QHBoxLayout(this);

    auto cnvMain = new Canvas(this);
    outer->addWidget(cnvMain);
    outer->setStretch(0, 9);

    auto inner = new QVBoxLayout;
    outer->addLayout(inner);
    outer->setStretch(1, 1);

    auto btnMaximinIterate = new QPushButton("Iterate Maximin", this);
    connect(btnMaximinIterate, &QPushButton::clicked, cnvMain, &Canvas::IterateMaximin);
    inner->addWidget(btnMaximinIterate);

    auto btnMaximinIterateAll = new QPushButton("Iterate All Maximin", this);
    connect(btnMaximinIterateAll, &QPushButton::clicked, cnvMain, &Canvas::IterateAllMaximin);
    inner->addWidget(btnMaximinIterateAll);

    auto btnKAverageIterate = new QPushButton("Finish K-average", this);
    connect(btnKAverageIterate, &QPushButton::clicked, cnvMain, &Canvas::IterateKAverage);
    inner->addWidget(btnKAverageIterate);

    auto btnKAverageIterateAll = new QPushButton("Finish K-average", this);
    connect(btnKAverageIterateAll, &QPushButton::clicked, cnvMain, &Canvas::IterateAllKAverage);
    inner->addWidget(btnKAverageIterateAll);

    inner->setStretch(0, 1);
    inner->setStretch(1, 9);
    inner->addStretch();
}

SimpleWindow::~SimpleWindow() {}
