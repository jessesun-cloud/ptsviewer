set(BUILD_BUILD_LIBRPLY OFF CACHE BOOL "Option to librply library.")
if (BUILD_BUILD_LIBRPLY)
	add_definitions(-DBUILD_LIBRPLY)
endif()

set(PUBLIC_HEADERS 
  src/ptsviewer.h  
)
set(PROJECT_SRCS
  src/ptsviewer.c
)

set(PUBLIC_HEADER_PATH "${CMAKE_SOURCE_DIR}/ptsviewer/src")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
set(APP "ptsViewer")
add_executable(${APP} "${PROJECT_SRCS}" "${PUBLIC_HEADERS}" readme)
AddExternalDependency(${APP} PRIVATE glew)
AddExternalDependency(${APP} PRIVATE FreeGLUT)
if (BUILD_BUILD_LIBRPLY)
target_link_libraries(${APP} PRIVATE librply)
endif()