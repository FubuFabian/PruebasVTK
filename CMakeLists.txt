CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

PROJECT(VTKThreeViews)

FIND_PACKAGE(VTK)
IF(VTK_FOUND)
	INCLUDE(${VTK_USE_FILE})
ELSE(VTK_FOUND)
	MESSAGE(FATAL_ERROR
		"VTK NOT FOUND. PLEASE SET VTK_DIR.")
ENDIF(VTK_FOUND)


FIND_PACKAGE(ITK)
IF(ITK_FOUND)
	INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR
		"ITK NOT FOUND. PLEASE SET ITK_DIR.")
ENDIF(ITK_FOUND)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )

# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} #this is where ui_ImageViewerUI.h is generated
  ${CMAKE_CURRENT_SOURCE_DIR}
)

#HolaMundoQt.cpp PolarisTrackerTest.cpp
SET(AppSrcs ChangeVolumePropertiesWidget.cpp widget.cpp QVTKImageWidget.cpp QVTKImageWidgetCommand.cpp Vtk3dView.cpp)
    
SET(AppHeaders ChangeVolumePropertiesWidget.h widget.h QVTKImageWidget.h QVTKImageWidgetCommand.h Vtk3dView.h)

SET(AppUI widget.ui ChangeVolumePropertiesWidget.ui)

# for generate qt aditional files 
QT4_WRAP_UI(UISrcs ${AppUI})
QT4_WRAP_CPP(MOCSrcs ${AppHeaders} )

# Packaging source code in same files 
SOURCE_GROUP("Resources" FILES
  ${AppUI}
)
 
SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
)


ADD_EXECUTABLE(VTKThreeViews ${AppSrcs} ${AppHeaders} ${UISrcs} ${MOCSrcs})

TARGET_LINK_LIBRARIES(VTKThreeViews QVTK ${VTK_LIBRARIES} ${ITK_LIBRARIES})
