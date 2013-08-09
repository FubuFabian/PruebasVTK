#include "ChangeVolumePropertiesWidget.h"
#include "ui_ChangeVolumePropertiesWidget.h"

ChangeVolumePropertiesWidget::ChangeVolumePropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeVolumePropertiesWidget)
{
    ui->setupUi(this);
}

ChangeVolumePropertiesWidget::~ChangeVolumePropertiesWidget()
{
    delete ui;
}

void ChangeVolumePropertiesWidget::changeLowerThreshold(int threshVal)
{

}

void ChangeVolumePropertiesWidget::changeUpperThreshold(int threshVal)
{

}


void ChangeVolumePropertiesWidget::changeOpacity(int opacityVal)
{

}
