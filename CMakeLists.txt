### CMake file for AnarKoid
###
###
###	CMake template from Sébastien Druon
###	
###	---Project started in October 2019---
###
###
###############################################################################


cmake_minimum_required (VERSION 3.11)

#Policy choice for the version of opengl that will be used in the project
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

project (AnarKoid)
set (AnarKoid_VERSION_MAJOR 0)
set (AnarKoid_VERSION_MINOR 1)

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )

set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )


# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()


### Search for Lib/Headers

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
#find_package(ICU COMPONENTS i18n io REQUIRED)
#find_package(CURL REQUIRED)
#find_package(LibXml2 REQUIRED)

### Config File


configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		 "${PROJECT_SOURCE_DIR}/src/config.h" )


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
	             "${CMAKE_CURRENT_BINARY_DIR}"
		     ${OPENGL_INCLUDE_DIRS}
		     ${GLUT_INCLUDE_DIRS}
		     ${GLEW_INCLUDE_DIRS}
		     )

# link_directories( "${VISION_LIBRARY_DIR}" )


### Main Target

file( GLOB src "src/*.c"  )
file( GLOB hdr "src/*.h"  "include/*.h" )

add_executable( "anarkoid" ${src} ${hdr} ) 

target_link_libraries( "anarkoid" m	
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
	${GLEW_LIBRARIES}
	)

install( TARGETS "anarkoid"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

### Test target

##file( GLOB test_src "src/test/*.c"  )
##file( GLOB test_hdr "src/test/*.h"  "include/*.h" )

##add_executable( "test" ${test_src} ${test_hdr} ) 

##target_link_libraries( "test" "${ICU_LIBRARIES}"
##			      "${CURL_LIBRARIES}"
##			      "${LIBXML2_LIBRARIES}" )

##install( TARGETS "test"
##	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
##	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
##            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )


