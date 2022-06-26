project(ADSLab2)

set (CMAKE_CXX_STANDARD 14)

SET(HEADERS 
    234Heap.hpp 
    binaryHeap.hpp 
    binomialHeap.hpp
    binomialHeap_2.hpp
    fibonacciHeap.hpp
    skewHeap.hpp
    leftistHeap.hpp
    pairingHeap.hpp 
    commons.hpp
)

if(WIN32)
    add_definitions(-D WINDOWS)
endif()
if(UNIX)
    add_definitions(-D LINUX)
endif()

set(SOURCES main.cpp dijkstra.cpp utils.cpp)



add_executable(main ${HEADERS} ${SOURCES})

add_executable(test test.cpp)
