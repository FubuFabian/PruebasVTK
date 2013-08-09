#include <QtGui/QApplication>

#include "widget.h"
#include "Vtk3dView.h"
#include "vtkMath.h"
#include "vtkMetaimageReader.h"

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	Widget *wid = new Widget();

	return app.exec();

}

Vtk3dView::Vtk3dView()
{
	prueba();
}


void Vtk3dView::prueba()
{

	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("C:/Users/Administrador/Documents/Volume Reconstruction/volumenes/5x1 Hamster A2-subvolume-scale_1.mhd");
	reader->Update();

	vtkSmartPointer<vtkImageData> volumeData = reader->GetOutput();
	

	vtkSmartPointer<vtkColorTransferFunction>volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeColor->AddRGBPoint(0,0.0,0.0,0.0);
	volumeColor->AddRGBPoint(64,0.25,0.25,0.25);
	volumeColor->AddRGBPoint(128,0.5,0.5,0.5);
	volumeColor->AddRGBPoint(192,0.75,0.75,0.75);
	volumeColor->AddRGBPoint(255,1.0,1.0,1.0);

	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarOpacity->AddPoint(20,    0.00);
	volumeScalarOpacity->AddPoint(255,  0.2);

	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(volumeColor);
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);

	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> compositeFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New(); 

	vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	volumeMapper->SetVolumeRayCastFunction(compositeFunction);
	volumeMapper->CroppingOff(); 
	volumeMapper->SetInput(volumeData);

	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper); 
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1, 1, 1);
	renderer->AddVolume(volume);
    vtkSmartPointer<vtkRenderWindow> renwin = vtkSmartPointer<vtkRenderWindow>::New();
    renwin->AddRenderer(renderer);
    renwin->Render();
    
}

