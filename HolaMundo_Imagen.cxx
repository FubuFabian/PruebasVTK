#include "vtkBMPReader.h"
#include "vtkSmartPointer.h"
#include "vtkImageMapper.h"
#include "vtkImageViewer.h"
#include "vtkRenderer.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"


int main(int argc, char * argv[]){

    // Leer imagen /////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New(); //Crea un nuevo lector de imagenes
    reader->SetFileName("C:/Users/Administrador/Documents/NavegadorBiopsia/Debug/PreAcquired/imgcut/Img00001.bmp"); //indica el archivo a leer
    reader->SetDataExtent(0,800,0,600,0,0); //indica el tamaño de la imagen

    reader->Update(); //actualiza el lector

	std::cout<<"Tipo de componentes:"<<reader->GetOutput()->GetScalarTypeAsString()<<std::endl;
	std::cout<<"Numero de componentes:"<<reader->GetOutput()->GetNumberOfScalarComponents()<<std::endl;
			
	float pixels1 = reader->GetOutput()->GetScalarComponentAsFloat(200,200,0,0);
	float pixels2 = reader->GetOutput()->GetScalarComponentAsFloat(200,200,0,1);
	float pixels3 = reader->GetOutput()->GetScalarComponentAsFloat(200,200,0,2);


	std::cout<<"Valor del pixel: "<<pixels1<<","<<pixels2<<","<<pixels3<<std::endl;

    //vtkSmartPointer<vtkImageMapper> mapper = vtkSmartPointer<vtkImageMapper>::New(); // crea nuevbo mapper
    //mapper->SetInput(reader->GetOutput()); //indica la imagen a mapear
    //mapper->SetScalarRange(0,255); //indica el rango de color

    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New(); //crea nuevo actor para imagenes
    actor->SetInput(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New(); //crea nueva representación
    render->AddActor(actor); //añade los actores a la representación
    render->SetBackground(0,0,255); //indica el colo de fondo de la representación

    vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New(); //crea nueva venta (escena)
    renderwindow->AddRenderer(render); //añade las representaciónes a la ventana
    renderwindow->SetSize(900,900); //indica el tamaño de la ventana

    //renderwindow->Render(); //muestra la ventana

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Agregar Interacción /////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New(); //crea nuevo objeto para la interacción de la ventana
    interactor->SetRenderWindow(renderwindow); //indica con que ventana se va a interactuar

    renderwindow->Render(); //muestra la ventana

    interactor->Start(); //inicia la interacción. No regresa hasta que se cierre la ventana

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////


    std::cout<<"Presiona Enter Para salir"<<std::endl;


    bool salir = true;

    while(salir){
        if(std::cin.get()=='\n')
            salir=false;
    }

    return 0;

}
