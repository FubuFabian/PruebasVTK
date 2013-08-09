#include "MeshToVTK.h"


int main(int argc, char * argv[]){

    CreateMesh();
    SetMeshBoundaries();

    grid = MeshToUnstructuredGrid(mesh);

    Display();

    std::cout<<"Press Enter to Exit"<<std::endl;


    bool exit = true;

    while(exit){
        if(std::cin.get()=='\n')
            exit=false;
    }

    return 0;
}

void CreateMesh(){

    //Initialize Points

    p0[0] = 0; p0[1] = 0; p0[2] = 1;
    p1[0] = 0; p1[1] = 0; p1[2] = 0;
    p2[0] = 1; p2[1] = 0; p2[2] = 0;
    p3[0] = 0; p3[1] = 1; p3[2] = 0;

    //Insert points to container

    int pointid = 0;

    pcontainer->InsertElement(pointid++,p0);
    pcontainer->InsertElement(pointid++,p1);
    pcontainer->InsertElement(pointid++,p2);
    pcontainer->InsertElement(pointid++,p3);

    //Add container to mesh

    mesh->SetPoints(pcontainer);

    //Create, Initialize and Add cells to container

    int cell = 0;

    //Tetrahedron cell

    cellautopointer.TakeOwnership(new TetrahedronCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,1);
    cellautopointer->SetPointId(2,2);
    cellautopointer->SetPointId(3,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    //Triangles Cells

    cellautopointer.TakeOwnership(new TriangleCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,1);
    cellautopointer->SetPointId(2,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new TriangleCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,3);
    cellautopointer->SetPointId(2,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new TriangleCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,1);
    cellautopointer->SetPointId(2,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new TriangleCell);
    cellautopointer->SetPointId(0,1);
    cellautopointer->SetPointId(1,3);
    cellautopointer->SetPointId(2,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    //Line Cells

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,1);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,1);
    cellautopointer->SetPointId(1,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,1);
    cellautopointer->SetPointId(1,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,3);
    cellautopointer->SetPointId(1,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new LineCell);
    cellautopointer->SetPointId(0,0);
    cellautopointer->SetPointId(1,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    //Vertex Cells

    cellautopointer.TakeOwnership(new VertexCell);
    cellautopointer->SetPointId(0,0);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new VertexCell);
    cellautopointer->SetPointId(0,1);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new VertexCell);
    cellautopointer->SetPointId(0,2);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    cellautopointer.TakeOwnership(new VertexCell);
    cellautopointer->SetPointId(0,3);
    cellcontainer->InsertElement(cell++, cellautopointer.ReleaseOwnership());

    //Add cell container to mesh
    mesh->SetCells(cellcontainer);

}

void SetMeshBoundaries(){

    //Set Tetrahedron boundaries with vertex

    cellId = 0;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set Tetrahedron boundaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set Tetrahedron boundaries with triangles

    dimension = 2;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 1);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 2);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 3);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 4);

    //Set triangle1 boundaries with vertex

    cellId = 1;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);

    //Set triangle1 boundaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set triangle1 boundaries with Triangles

    dimension = 2;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 2);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 3);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 4);

    //Set triangle2 boundaries with vertex

    cellId = 2;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set triangle2 boundaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set triangle2 boundaries with Triangles

    dimension = 2;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 1);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 3);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 4);

    //Set triangle3 boundaries with vertex

    cellId = 3;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set triangle3 boundaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);

    //Set triangle3 boundaries with Triangles

    dimension = 2;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 1);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 2);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 4);

    //Set triangle4 boundaries with vertex

    cellId = 4;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set triangle4 boundaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);

    //Set triangle4 boundaries with Triangles

    dimension = 2;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 1);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 2);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 3);

    //Set line1 boundaries with vertex

    cellId = 5;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);

    //Set line1 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set line2 boundaries with vertex

    cellId = 6;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set line2 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set line3 boundaries with vertex

    cellId = 7;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set line3 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);

    //Set line4 boundaries with vertex

    cellId = 8;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 12);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);

    //Set line4 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set line5 boundaries with vertex

    cellId = 9;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 14);

    //Set line5 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 7);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 10);

    //Set line6 boundaries with vertex

    cellId = 10;
    dimension = 0;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 11);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 13);

    //Set line6 bondaries with lines

    dimension = 1;
    featureId = 0;

    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 5);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 6);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 8);
    mesh->SetBoundaryAssignment(dimension, cellId, featureId++, 9);

}

void Display(){

    //Initializing visualization pointers

    mapper->SetInput(grid);

    actor->SetMapper(mapper);

    renderer->AddActor(actor);
    renderer->SetBackground(.2, 5, .4);

    renwin->SetSize(900, 900);
    renwin->AddRenderer(renderer);

    interactor->SetRenderWindow(renwin);

    //Visualize

    renwin->Render();
    interactor->Start();
}
