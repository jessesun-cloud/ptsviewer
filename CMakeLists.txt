set(BUILD_BUILD_LIBRPLY OFF CACHE BOOL "Option to librply library.")
if (BUILD_BUILD_LIBRPLY)
	add_definitions(-DBUILD_LIBRPLY)
endif()
set(READER_SUPPORT_PTX ON CACHE BOOL "Option to open ptx.")
set(READER_SUPPORT_E57 OFF CACHE BOOL "Option to open e57.")

set(PUBLIC_HEADERS 
  src/ptsviewer.h  
  src/ImpVertexBuffer.hpp
)
set(PROJECT_SRCS
  src/ptsviewer.cpp
  src/ImpVertexBuffer.cpp
  reader.cpp
)

set(PUBLIC_HEADER_PATH "${CMAKE_SOURCE_DIR}/ptsviewer/src")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
set(APP "ptsViewer")
add_executable(${APP} "${PROJECT_SRCS}" "${PUBLIC_HEADERS}" readme)
AddExternalDependency(${APP} PRIVATE glew)
AddExternalDependency(${APP} PRIVATE FreeGLUT)
AddExternalDependency(${APP} PRIVATE Glext)
if (BUILD_BUILD_LIBRPLY)
  target_link_libraries(${APP} PRIVATE librply)
endif()
if (READER_SUPPORT_PTX)
	add_definitions(-DSUPPORT_PTX)
	target_link_libraries(${APP} PRIVATE ptxlib)
endif()
if (READER_SUPPORT_E57)
	add_definitions(-DSUPPORT_E57)
	target_link_libraries(${APP} PRIVATE e57reader)
endif()