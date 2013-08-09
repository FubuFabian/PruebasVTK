#ifndef VTK3DVIEW_H
#define VTK3DVIEW_H

#endif // VTK3DVIEW_H

#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageReader2.h"
#include "vtkImageReader2Factory.h"
#include "vtkImageMapper.h"
#include "vtkImageFlip.h"
#include "vtkMatrix4x4.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkTransform.h"
#include "vtkPicker.h"
#include <vtkVolume.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkMath.h>

#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector.h>

//#include <stdio.h>
#include <string>
#include <math.h>


//using namespace std;

class Vtk3dView
{

public:


     vtkSmartPointer <vtkImageReader2Factory> readerFactory;
     vtkSmartPointer<vtkImageReader2> reader;
     vtkSmartPointer <vtkImageData> image1;
     vtkSmartPointer <vtkImageData> image2;
     vtkSmartPointer<vtkImageActor> actor1;
     vtkSmartPointer<vtkImageActor> actor2;
     vtkSmartPointer<vtkRenderer> renderer;
     vtkSmartPointer<vtkRenderWindow> renwin;
     vtkSmartPointer<vtkRenderWindowInteractor> interactor;
     vnl_matrix<double> transform1;
	 vnl_matrix<double> transform2;
	 vtkSmartPointer<vtkTransform> transform;
	 vtkSmartPointer<vtkPicker> picker;

     vnl_matrix<double> setTransformation(double[4], double[3]);
	 void prueba();
     
     Vtk3dView();

};
