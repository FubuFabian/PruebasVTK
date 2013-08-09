#include "VTKThreeViews.h"
#include "ui_VTKThreeViews.h"

VTKThreeViews::VTKThreeViews(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VTKThreeViews)
{
    ui->setupUi(this);
}

VTKThreeViews::~VTKThreeViews()
{
    delete ui;
}
