#ifndef HOLAMUNDO_VTK_ITK_H
#define HOLAMUNDO_VTK_ITK_H

#endif // HOLAMUNDO_VTK_ITK_H


//ITK libraries
#include "itkImageFileReader.h"
#include "itkImage.h"
#include "itkVector.h"
#include "itkBinaryThresholdImageFilter.h"

//ITK_VTK_GLUE libraries
#include "external/itkImageToVTKImageFilter.h"

//VTK libraries
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageActor.h"
#include "vtkImageMapper.h"
#include "vtkImageFlip.h"

//Normal Libraries
#include <stdio.h>
#include <string>

using namespace std;

//declare funtions
void ColorImage(); //Diplay Color Image
void BWImage(); //Display grayscale Image
void FilterImage(); //Display filtered image
void Initialize(); //Initilize the map for User Menu
void Flip(); //Flips vtk image

//declare variables and constants
enum StringValue { evNotDefined, //Define the User menu
                          evStringValue1,
                          evStringValue2,
                          evStringValue3,
						  evStringValue4};

static std::map<std::string, StringValue> s_mapStringValues; //Maps values of the User menu with enum variable

typedef itk::Vector<unsigned char, 3> PixelType; //pixel data of the image
const unsigned int Dimension = 2; //dimensión of the image

typedef itk::Image<PixelType, Dimension> ImageType; //new type of image
ImageType::Pointer itk_image_color = ImageType::New(); //create a new image

typedef itk::Image<unsigned char, Dimension> ImageTypeBW; //new type of image
ImageTypeBW::Pointer itk_image_bw = ImageTypeBW::New(); //create a new image

typedef itk::ImageFileReader<ImageType> ReaderType; //new type of reader for ImageType images
ReaderType::Pointer reader = ReaderType::New(); //create new reader

typedef itk::ImageFileReader<ImageTypeBW> ReaderTypeBW; //new type of reader for ImageType images
ReaderTypeBW::Pointer reader_bw = ReaderTypeBW::New(); //create new reader

const char * filename = "C:/Users/Administrador/Documents/NavegadorBiopsia/Debug/PreAcquired/imgcut/Img00001.bmp"; //PAth de la imagen a procesar y ver

typedef itk::ImageToVTKImageFilter<ImageType> itkVtkConverter; //creates new type of converter for ImageType
itkVtkConverter::Pointer conv = itkVtkConverter::New(); //creates new converter

typedef itk::ImageToVTKImageFilter<ImageTypeBW> itkVtkConverterBW; //creates new type of converter for ImageType
itkVtkConverterBW::Pointer conv_bw = itkVtkConverterBW::New(); //creates new converter

typedef itk::BinaryThresholdImageFilter<ImageTypeBW, ImageTypeBW> FilterType; //creates new type of filter for ImageTypeBW
FilterType::Pointer filter = FilterType::New(); //creates a new threshold filter

vtkSmartPointer<vtkImageData> vtk_image = vtkSmartPointer<vtkImageData>::New(); //creates new vtk image

vtkSmartPointer<vtkImageFlip> flipYFilter = vtkSmartPointer<vtkImageFlip>::New(); //creates new flipper

vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New(); //Image actor for setting up image
vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New(); //Image renderer for image representation
vtkSmartPointer<vtkRenderWindow> renwin = vtkSmartPointer<vtkRenderWindow>::New(); //Image Window to display render
vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New(); //creates a new interactor for the window

