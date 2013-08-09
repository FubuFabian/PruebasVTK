#ifndef CHANGEVOLUMEPROPERTIESWIDGET_H
#define CHANGEVOLUMEPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class ChangeVolumePropertiesWidget;
}

class ChangeVolumePropertiesWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChangeVolumePropertiesWidget(QWidget *parent = 0);
    ~ChangeVolumePropertiesWidget();
    
private:
    Ui::ChangeVolumePropertiesWidget *ui;

private slots:

    void changeLowerThreshold(int);
    void changeUpperThreshold(int);
    void changeOpacity(int);
};

#endif // CHANGEVOLUMEPROPERTIESWIDGET_H
