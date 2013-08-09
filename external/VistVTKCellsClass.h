#include <iostream>
#include "itkMesh.h"
#include "itkTriangleCell.h"
#include "itkQuadrilateralCell.h"
#include "vtkDataSetWriter.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkActor.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDataSetReader.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSet.h"
#include "vtkCellArray.h"

typedef itk::Mesh<vtkFloatingPointType, 3,
  itk::DefaultStaticMeshTraits< vtkFloatingPointType, 3, 3, vtkFloatingPointType, vtkFloatingPointType > > FloatMesh;

#ifndef VISTVTKCELLSCLASS_H
#define VISTVTKCELLSCLASS_H

class VistVTKCellsClass
{
  vtkCellArray* m_Cells;
  int* m_LastCell;
  int* m_TypeArray;
public:
  // typedef the itk cells we are interested in
  typedef itk::CellInterface<
                      FloatMesh::PixelType,
                      FloatMesh::CellTraits >  CellInterfaceType;

  typedef itk::TriangleCell<CellInterfaceType>      floatTriangleCell;
  typedef itk::QuadrilateralCell<CellInterfaceType> floatQuadrilateralCell;

  // Set the vtkCellArray that will be constructed
  void SetCellArray(vtkCellArray* a)
    {
      m_Cells = a;
    }
  // Set the cell counter pointer
  void SetCellCounter(int* i)
    {
      m_LastCell = i;
    }
  // Set the type array for storing the vtk cell types
  void SetTypeArray(int* i)
    {
      m_TypeArray = i;
    }
  // Visit a triangle and create the VTK_TRIANGLE cell
  void Visit(unsigned long, floatTriangleCell* t)
    {
      m_Cells->InsertNextCell(3,  (vtkIdType*)t->PointIdsBegin());
      m_TypeArray[*m_LastCell] = VTK_TRIANGLE;
      (*m_LastCell)++;
    }
  // Visit a triangle and create the VTK_QUAD cell
  void Visit(unsigned long, floatQuadrilateralCell* t)
    {
      m_Cells->InsertNextCell(4,  (vtkIdType*)t->PointIdsBegin());
      m_TypeArray[*m_LastCell] = VTK_QUAD;
      (*m_LastCell)++;
    }
};

#endif // VISTVTKCELLSCLASS_H

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#ifndef vtkFloatingPointType
#define vtkFloatingPointType float
#endif

typedef itk::CellInterfaceVisitorImplementation<
vtkFloatingPointType, FloatMesh::CellTraits,
  itk::TriangleCell< itk::CellInterface<FloatMesh::PixelType, FloatMesh::CellTraits > >,
  VistVTKCellsClass> TriangleVisitor;


typedef itk::CellInterfaceVisitorImplementation<
vtkFloatingPointType, FloatMesh::CellTraits,
  itk::QuadrilateralCell< itk::CellInterface<FloatMesh::PixelType, FloatMesh::CellTraits > >,
  VistVTKCellsClass> QuadrilateralVisitor;

vtkUnstructuredGrid* MeshToUnstructuredGrid(FloatMesh* mesh)
{
  // Get the number of points in the mesh
  int numPoints = mesh->GetNumberOfPoints();
  if(numPoints == 0)
    {
    mesh->Print(std::cerr);
    std::cerr << "no points in Grid " << std::endl;
    exit(-1);
    }
  // Create a vtkUnstructuredGrid
  vtkUnstructuredGrid* vgrid = vtkUnstructuredGrid::New();

  // Create the vtkPoints object and set the number of points
  vtkPoints* vpoints = vtkPoints::New();
  vpoints->SetNumberOfPoints(numPoints);
  // iterate over all the points in the itk mesh filling in
  // the vtkPoints object as we go
  FloatMesh::PointsContainer::Pointer points = mesh->GetPoints();
  for(FloatMesh::PointsContainer::Iterator i = points->Begin();
      i != points->End(); ++i)
    {
    // Get the point index from the point container iterator
    int idx = i->Index();
    // Set the vtk point at the index with the the coord array from itk
    // itk returns a const pointer, but vtk is not const correct, so
    // we have to use a const cast to get rid of the const
    vpoints->SetPoint(idx, const_cast<vtkFloatingPointType*>(i->Value().GetDataPointer()));
    }
  // Set the points on the vtk grid
  vgrid->SetPoints(vpoints);

  // Now create the cells using the MulitVisitor
  // 1. Create a MultiVisitor
  FloatMesh::CellType::MultiVisitor::Pointer mv =
    FloatMesh::CellType::MultiVisitor::New();
  // 2. Create a triangle and quadrilateral visitor
  TriangleVisitor::Pointer tv = TriangleVisitor::New();
  QuadrilateralVisitor::Pointer qv =  QuadrilateralVisitor::New();
  // 3. Set up the visitors
  int vtkCellCount = 0; // running counter for current cell being inserted into vtk
  int numCells = mesh->GetNumberOfCells();
  int *types = new int[numCells]; // type array for vtk
  // create vtk cells and estimate the size
  vtkCellArray* cells = vtkCellArray::New();
  cells->EstimateSize(numCells, 4);
  // Set the TypeArray CellCount and CellArray for both visitors
  tv->SetTypeArray(types);
  tv->SetCellCounter(&vtkCellCount);
  tv->SetCellArray(cells);
  qv->SetTypeArray(types);
  qv->SetCellCounter(&vtkCellCount);
  qv->SetCellArray(cells);
  // add the visitors to the multivisitor
  mv->AddVisitor(tv);
  mv->AddVisitor(qv);
  // Now ask the mesh to accept the multivisitor which
  // will Call Visit for each cell in the mesh that matches the
  // cell types of the visitors added to the MultiVisitor
  mesh->Accept(mv);

  // Now set the cells on the vtk grid with the type array and cell array
  vgrid->SetCells(types, cells);

  // Clean up vtk objects (no vtkSmartPointer ... )
  cells->Delete();
  vpoints->Delete();
  // return the vtkUnstructuredGrid
  return vgrid;
}

#ifndef VTK_HAS_ID_TYPE
// if you get a syntax error hear, then your VTK
// has vtkIdType already defined
typedef long vtkIdType;
#endif

FloatMesh::Pointer MeshFromUnstructuredGrid(vtkUnstructuredGrid* grid)
{
  // Create a new mesh
  FloatMesh::Pointer mesh(FloatMesh::New());
  // Get the points from vtk
  vtkPoints* vtkpoints = grid->GetPoints();
  int numPoints = vtkpoints->GetNumberOfPoints();
  // Create a compatible point container for the mesh
  // the mesh is created with a null points container
  FloatMesh::PointsContainer::Pointer points = 
    FloatMesh::PointsContainer::New();
  // Resize the point container to be able to fit the vtk points
  points->Reserve(numPoints);
  // Set the point container on the mesh
  mesh->SetPoints(points);
  for(int i =0; i < numPoints; i++)
    {
    vtkFloatingPointType* apoint = vtkpoints->GetPoint(i);
    mesh->SetPoint(i, FloatMesh::PointType(apoint));
    }
  vtkCellArray* vtkcells = grid->GetCells();
  FloatMesh::CellsContainerPointer cells = FloatMesh::CellsContainer::New();
  mesh->SetCells(cells);
  // extract the cell id's from the vtkUnstructuredGrid
  int numcells = vtkcells->GetNumberOfCells();
  int* vtkCellTypes = new int[numcells];
  int cellId =0;
  for(; cellId < numcells; cellId++)
    {
    vtkCellTypes[cellId] = grid->GetCellType(cellId);
    }
  
  cells->Reserve(numcells);
  vtkIdType npts;
  vtkIdType* pts;
  cellId = 0;
  for(vtkcells->InitTraversal(); vtkcells->GetNextCell(npts, pts); cellId++)
    {
    FloatMesh::CellAutoPointer c;
    switch(vtkCellTypes[cellId])
      {
      case VTK_TRIANGLE:
        {
        typedef itk::CellInterface<vtkFloatingPointType, FloatMesh::CellTraits> CellInterfaceType;
        typedef itk::TriangleCell<CellInterfaceType> TriangleCellType;
        TriangleCellType * t = new TriangleCellType;
        t->SetPointIds((unsigned long*)pts);
        c.TakeOwnership( t );
        break;
        }  
      case VTK_QUAD:
        {
        typedef itk::CellInterface<vtkFloatingPointType, FloatMesh::CellTraits> CellInterfaceType;
        typedef itk::QuadrilateralCell<CellInterfaceType> QuadrilateralCellType;
        QuadrilateralCellType * t = new QuadrilateralCellType;
        t->SetPointIds((unsigned long*)pts);
        c.TakeOwnership( t );
        break;
        }  
      case VTK_EMPTY_CELL:
      case VTK_VERTEX:
      case VTK_POLY_VERTEX:
      case VTK_LINE:
      case VTK_POLY_LINE:
      case VTK_TRIANGLE_STRIP:
      case VTK_POLYGON:
      case VTK_PIXEL:
      case VTK_TETRA:
      case VTK_VOXEL:
      case VTK_HEXAHEDRON:
      case VTK_WEDGE:
      case VTK_PYRAMID:
      case VTK_PARAMETRIC_CURVE:
      case VTK_PARAMETRIC_SURFACE:
      default:
        std::cerr << "Warning unhandled cell type " 
                  << vtkCellTypes[cellId] << std::endl;
        ;
      }
    mesh->SetCell(cellId, c);
    }

  mesh->Print(std::cout);
  return mesh;
}
