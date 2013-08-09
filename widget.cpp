#include "widget.h"
#include "ui_widget.h"
#include "vtkMetaimageReader.h"
#include "vtkSmartPointer.h"
#include "vtkImageData.h"

#include <QBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);



      this->setAttribute(Qt::WA_DeleteOnClose);

      this->displayWidget = new QVTKImageWidget();

      QVBoxLayout *layout = new QVBoxLayout;
      layout->setContentsMargins(0, 0, 0, 0);
      layout->setSpacing(0);
      layout->QLayout::addWidget(displayWidget);
      ui->widget->setLayout(layout);

	  vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	  reader->SetFileName("C:/Users/Administrador/Documents/Volume Reconstruction/volumenes/5x1 Hamster A2-subvolume-scale_1.mhd");
	  reader->Update();

	  QString filename = "C:/Users/Administrador/Documents/Volume Reconstruction/volumenes/5x1 Hamster A2-subvolume-scale_1.mhd";
	  vtkSmartPointer<vtkImageData> volumeData = reader->GetOutput(); 

	  this->displayWidget->setAndDisplayVolume(reader->GetOutput());
	  this->show();
	  
}

Widget::~Widget()
{
    delete ui;
}
