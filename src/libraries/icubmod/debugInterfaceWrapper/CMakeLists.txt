# Copyright: (C) 2014 RobotCub Consortium
# Authors: Alberto Cardellino
# CopyPolicy: Released under the terms of the GNU GPL v2.0.


 yarp_prepare_device(debugInterfaceWrapper TYPE    DebugInterfaceWrapper
                                      INCLUDE DebugInterfaceWrapper.h
                                      WRAPPER debugInterfaceWrapper)

IF (NOT SKIP_debugInterfaceWrapper)
 include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS} ${iCubDev_INCLUDE_DIRS})
 yarp_add_plugin(debugInterfaceWrapper DebugInterfaceWrapper.h DebugInterfaceWrapper.cpp WrappedDevice.h WrappedDevice.cpp RpcMsgHandler.h RpcMsgHandler.cpp)
 target_link_libraries(debugInterfaceWrapper  ${YARP_LIBRARIES})
 icub_export_plugin(debugInterfaceWrapper)
 yarp_install(FILES debugInterfaceWrapper.ini  DESTINATION ${ICUB_PLUGIN_MANIFESTS_INSTALL_DIR})
ENDIF (NOT SKIP_debugInterfaceWrapper)




