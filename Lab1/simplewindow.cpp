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

    auto btnCalculate = new QPushButton("Calculate", this);
    connect(btnCalculate, &QPushButton::clicked, cnvMain, &Canvas::CalculateButtonPressed);
    inner->addWidget(btnCalculate);

    auto btnIterate = new QPushButton("Iterate", this);
    connect(btnIterate, &QPushButton::clicked, cnvMain, &Canvas::IterateButtonPressed);
    inner->addWidget(btnIterate);

    auto btnIterateAll = new QPushButton("Iterate All", this);
    connect(btnIterateAll, &QPushButton::clicked, cnvMain, &Canvas::IterateAllButtonPressed);
    inner->addWidget(btnIterateAll);

    inner->setStretch(0, 1);
    inner->setStretch(1, 9);
    inner->addStretch();
}

SimpleWindow::~SimpleWindow() {}
