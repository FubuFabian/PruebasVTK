#ifndef MESHTOVTK_H
#define MESHTOVTK_H

#endif // MESHTOVTK_H

//ITK Includes
#include "itkMesh.h"
#include "itkTriangleCell.h"
#include "itkLineCell.h"
#include "itkVertexCell.h"
#include "itkTetrahedronCell.h"

//ITK mesh to VTK Grid Include
#include "external/VistVTKCellsClass.h"

//VTK Include
#include"vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkUnstructuredGrid.h"

//Definitions of ITK
typedef FloatMesh::CellType CellType;
typedef itk::VertexCell<CellType> VertexCell;
typedef itk::LineCell<CellType> LineCell;
typedef itk::TriangleCell<CellType> TriangleCell;
typedef itk::TetrahedronCell<CellType> TetrahedronCell;
typedef FloatMesh::PointsContainer PointsContainer;
typedef FloatMesh::CellsContainer CellsContainer;

//ITK Pointers and objects
FloatMesh::Pointer mesh = FloatMesh::New();
FloatMesh::PointType p0;
FloatMesh::PointType p1;
FloatMesh::PointType p2;
FloatMesh::PointType p3;
PointsContainer::Pointer pcontainer = PointsContainer::New();
CellType::CellAutoPointer cellautopointer;
CellsContainer::Pointer cellcontainer = CellsContainer::New();
FloatMesh::CellIdentifier cellId = 0;
FloatMesh::CellFeatureIdentifier featureId = 0;

//VTK Pointers and Objects
vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renwin = vtkSmartPointer<vtkRenderWindow>::New();
vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

//Normal objects and pointers
int dimension;

//Functions
void CreateMesh();
void SetMeshBoundaries();
void Display();


