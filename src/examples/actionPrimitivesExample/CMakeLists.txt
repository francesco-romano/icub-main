# Copyright: (C) 2010 RobotCub Consortium
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

SET(PROJECTNAME actionPrimitivesExample)

PROJECT(${PROJECTNAME})

SET(folder_source main.cpp)

SOURCE_GROUP("Source Files" FILES ${folder_source})

INCLUDE_DIRECTORIES(${actionPrimitives_INCLUDE_DIRS}
                    ${perceptiveModels_INCLUDE_DIRS}
                    ${YARP_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECTNAME} ${folder_source})

TARGET_LINK_LIBRARIES(${PROJECTNAME} actionPrimitives
                                     ${YARP_LIBRARIES})

INSTALL(TARGETS ${PROJECTNAME} DESTINATION bin)

########## application
file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
yarp_install(FILES ${conf} DESTINATION ${ICUB_CONTEXTS_INSTALL_DIR}/${PROJECTNAME})


