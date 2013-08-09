#ifndef VTKTHREEVIEWS_H
#define VTKTHREEVIEWS_H

#include <QWidget>

namespace Ui {
class VTKThreeViews;
}

class VTKThreeViews : public QWidget
{
    Q_OBJECT
    
public:
    explicit VTKThreeViews(QWidget *parent = 0);
    ~VTKThreeViews();
    
private:
    Ui::VTKThreeViews *ui;

private slots:

    void axialSliderMove(int);
    void sagitalSliderMove(int);
    void coronalSliderMove(int);
};

#endif // VTKTHREEVIEWS_H
