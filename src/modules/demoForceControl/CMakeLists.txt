# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences, Istituto Italiano di Tecnologia
# Authors: Marco Randazzo
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

SET(PROJECTNAME demoForceControl)
PROJECT(${PROJECTNAME})

FILE(GLOB_RECURSE folder_header *.h)
FILE(GLOB_RECURSE folder_source *.cpp)
SOURCE_GROUP("Header Files" FILES ${folder_header})
SOURCE_GROUP("Source Files" FILES ${folder_source})

ADD_DEFINITIONS(${GTK_DEFINITIONS})

INCLUDE_DIRECTORIES(${iCubDev_INCLUDE_DIRS}
			        ${ctrlLib_INCLUDE_DIRS}
                    ${GtkPlus_INCLUDE_DIRS}
                    ${GTK2_INCLUDE_DIRS}
		            ${YARP_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECTNAME} ${folder_header} ${folder_source})

TARGET_LINK_LIBRARIES(${PROJECTNAME} ctrlLib
										icubmod
                                        ${GtkPlus_LIBRARIES}
										${GTK2_LIBRARIES}
										${YARP_LIBRARIES})

INSTALL(TARGETS ${PROJECTNAME} DESTINATION bin)


