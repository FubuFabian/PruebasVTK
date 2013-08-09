//
//  QVTKImageWidget.h
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 01/12/11.
//  Copyright (c) 2011 __UNAM__. All rights reserved.
//

#ifndef US_Probe_Calibration_QVTKImageWidget_h
#define US_Probe_Calibration_QVTKImageWidget_h

#include <QtGui>
#include <QWidget>
#include <QVTKWidget.h>

#include <itkImage.h>
#include <itkRGBPixel.h>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>

#include <vtkCommand.h>
#include <vtkImageViewer2.h>
#include <vtkCornerAnnotation.h>

#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkTransform.h>

#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector.h>



typedef itk::RGBPixel< unsigned char > RGBPixelType;
typedef itk::Image< unsigned char > ImageType;
typedef itk::Image< RGBPixelType, 2> RGBImageType;

//!Display VTK images
/*!
  This class allows the user to display vtkImages on QT.
  It can display 2D and 3D scenes
*/
class QVTKImageWidget : public QWidget {
    Q_OBJECT    
    
public:
    /** 
     * Constructor for this ImageWidget 
     */
    QVTKImageWidget(QWidget *parent = 0);
    
    /**
     * Destructor
     */
    virtual ~QVTKImageWidget();
    
    /**
     * Sets and display an image from a given image path
     */
    void setAndDisplayImage(QString imageFilename);
    
    
    /**
     * \brief Sets and display the given vtkImageData
     * \param[in] a vtkImageData to set and display
     */
    void setAndDisplayImage(vtkSmartPointer<vtkImageData> image);
    
    
    /**
     * \brief Set and display multiple images from a given images filenames. Display 
     * the image corresponding to the first element on the filenmaes list.
     * \param[in] a QStringList that contain the filename of each image 
     */
    void setAndDisplayMultipleImages(QStringList filenames);
    
    /**
     * \brief Set and display images from a given images filenames that represent the volume data.
     * Display the image corresponding to the first element on the filenames list.
     * \param[in] a QStringList that contain the filename of each image,
     *  a QStringList that contain the filename of the rotation data of each image and
     *  a QStringList that contain the filename the translation data of each image.
     */
    void setAndDisplayVolumeImages(QStringList ImagesFilenames,QString rotationFilename, QString translatoinFilename, QString calibrationFilename);
    
    /**
     * \brief Set and display volume data.
     * \param[in] a QString that contain the filename of the volume
     */
    void setAndDisplayVolume(QString volumeFilename);

    /**
     * \brief Set and display volume data.
     * \param[in] a vtkImageData generated by VolumeReconstruction.h
     */
    void setAndDisplayVolume(vtkSmartPointer<vtkImageData> volumeData);

    /**
     * \brief Set and display multiple images from a given vtkImageData Array.      
     * \param[in] a std::vector of vtkImageData 
     */
    void setAndDisplayMultipleImages(std::vector< vtkSmartPointer<vtkImageData> > imageStack);
    
    
    /**
     * \brief display an image stored in this imageStack. 
     * \param[in] the index in the stack position of the image 
     */
    void displaySelectedImage(int idx);
    
    
    /***************************
     *   get and set methods
     ***************************/
    /**
     * \brief Returns the pixel type in loaded images
     */
    QString getPixelType();

    /**
     * \brief Returns the type of image displayed
     */
    QString getImageType();

    /**
     * \brief Return the numer of dimensions of the image
     */
    QString getNumOfDimesions();
    
    /** \brief return this image stack */
    std::vector< vtkSmartPointer<vtkImageData> > getImageStack();

    /** \brief return this volume image stack */
    std::vector< vtkSmartPointer<vtkImageData> > getVolumeImageStack();

	/** \brief return this transform stack */
    std::vector< vnl_matrix<double> > getTransformStack();
    
    /** 
     * returns an array with the width and height of the image
     */ 
    int* getImageSize();
    
    /**
     * returns this image width
     */
    int getImageWidth();
    
    /**
     * returns this image heigth
     */
    int getImageHeigth();
    
    /**
     * \brief Return the mouse x coordinate position when mouse left button is pressed
     * \param[out] int x position
     */
    int getXPicked();
    
    /**
     * \brief Return the mouse y coordinate position when mouse left button is pressed
     * \param[out] int y position
     */
    int getYPicked();
    
	vnl_vector<double> getTransformScale();

    /**
     * \brief Set the mouse x coordinate position when mouse left button is pressed
     */
    void setXPicked(int xPosition);
    
    /**
     * \brief Set the mouse y coordinate position when mouse left button is pressed
     */
    void setYPicked(int yPosition);

    /**
     * \brief Set the data of the display volume
     */
    void setVolumeData( vtkSmartPointer<vtkImageData> volumeData);

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

    /**
     * \brief Set the opacity for the displayed volume
     */
    void setVolumeOpacity(vtkSmartPointer<vtkPiecewiseFunction> opacity);

	void setVolumeColor(vtkSmartPointer<vtkColorTransferFunction> color);

	void setVolumeOrigin(vnl_vector<double> volumeOrigin);
    
    /**
     * \brief Return this widget image viewer
     * \param[out] imageViewer vtkImageViewer2 target 2D image.
     */
    vtkSmartPointer<vtkImageViewer2> getImageViewer();
    
    /**
     * \brief Return this qvtkWidget 
     * \param[out] the QVTKWidget
     */
    QVTKWidget* getQVTKWidget();
    
    
    /** \brief If an image stack is loaded, then return the index in the image 
     * stack of displayed image 
     */
    int getImageDisplayedIndex();
    
    
    /** \brief Flag to know if it's displayed an image stack */
    bool isImageStackLoaded;

    /** \brief Flag to know if it's displayed an volume image stack */
    bool isVolumeImageStackLoaded;
    
    
private:    

    /** 
     * The QVTKWidget for display and interact with the images
     */
    QVTKWidget* qvtkWidget;
    
    /** The grayscale image displayed in this widget */
    ImageType::Pointer itkImage;
    
    /** The RGB image displayed for this widget */
    RGBImageType::Pointer rgbItkImage;
    
    /** The VTK image to display i this window */
    vtkSmartPointer <vtkImageData> vtkImage;  

    /** The VTK render window*/
    vtkSmartPointer<vtkRenderWindow> renwin;

    /** The VTK renderer */
    vtkSmartPointer<vtkRenderer> renderer;

    /** The displayed volume data*/
    vtkSmartPointer<vtkVolume> volume;

    /** The displayed volume data*/
    vtkSmartPointer<vtkImageData> volumeData;

	/** The displayed volume opacity*/
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity;

	/////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	vtkSmartPointer<vtkColorTransferFunction> volumeColor;

    /** The displayed volume properties*/
    vtkSmartPointer<vtkVolumeProperty> volumeProperty;

    int opacityPoint;
    
    /** \brief A vtkImageData Vector for keep the image references when load an 
     * image stack.
     */
    std::vector< vtkSmartPointer<vtkImageData> > imageStack;

    /** \brief A vtkImageData Vector for keep the volume image references when load an
     * image stack.
     */
    std::vector< vtkSmartPointer<vtkImageData> > volumeImageStack;

	/** \brief A vtkImageData Vector for keep the volume image references when load an
     * image stack Transformed.
     */
    std::vector< vnl_matrix<double> > transformStack;

    /** \brief A vtkImageData Vector for keep the volume image actor references when load an
     * image stack.
     */
    std::vector< vtkSmartPointer<vtkImageActor> > volumeImageActorStack;

    /** The type of the image pixels */
    std::string pixelType;
    
    /** Estimated scale of the images */
	vnl_vector<double> scale;

    /** the number of scalar components in the image 1 => grayscale, 3 => rgb */
    int imageType;
    
    /** The number of the image dimensions */
    size_t numDimensions;
    
    /** Width of the image */
    int imageWidth;
    
    /** Heigth of the image */
    int imageHeight;
     
    /** current x coordinate of mouse position over the image */
    int xPosition;
    
    /** current y coordinate of mouse position over the image */
    int yPosition;

    /** The x coordinate of the picked position over the image */
    int xPicked;
    
    /** current y coordinate of picked position over the image */
    int yPicked;
    
    /** If image stack is displayed this sets a reference to current image displayed */
    int imageDisplayedIndex;
    
    /** \brief a vnl_matrix to store the rotations of each image given by the tracker */
    vnl_matrix<double> volumeDataRotations;

    /** \brief a vnl_matrix to store the translations of each image given by the tracker */
    vnl_matrix<double> volumeDataTranslations;

    /** The angles and translation estimated */
	std::vector<double> volumeDataCalibration;
    
    /**
     * Set the needed image properties (pixelType, imageType, num of dimensions)     
     */
    void setImageProperties(bool verbose);
    
    /**
     * Display the given vtkImage
     */
    void displayImage(vtkImageData *image);

    /**
     * Display the given volume images
     */
    void displayVolumeImages(std::vector< vtkSmartPointer<vtkImageData> > volumeImageStack,
                             vnl_matrix<double> volumeDataRotations, vnl_matrix<double> volumeDataTranslations,
							 std::vector<double> volumeDataCalibration);

    /**
     * Display the given volume
     */
    void displayVolume(vtkSmartPointer<vtkVolume> volume);
    
    /**
     * Compute the transformation matricez of each image
     */
    vnl_matrix<double> computeTransformation(vnl_vector<double> quaternion,
                                                        vnl_vector<double> translation,
														std::vector<double> calibration);


    
    /* -------- necesary vtk objects to display an image ------ */
    
    /** the image viewer for display images */
    vtkSmartPointer<vtkImageViewer2> imageViewer;
    
    /** \brief Object for display information in the corners of the vtkImageViewer2 */
    vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation;

	
    

};

#endif
