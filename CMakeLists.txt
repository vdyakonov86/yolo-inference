cmake_minimum_required(VERSION 3.23)
project(yoloInference LANGUAGES C CXX VERSION 1.0.0)

option(WITH_OPENCV "build _YOLO_OPENCV" ON)
option(WITH_ONNXRUNTIME "build _YOLO_ONNXRUNTIME" ON)
option(WITH_OPENVINO "build _YOLO_OPENVINO" ON)
option(WITH_LIBTORCH "build _YOLO_LIBTORCH" ON)

add_compile_options(-w)
if(WITH_OPENCV)
    add_compile_options(-D_YOLO_OPENCV)
endif()
if(WITH_ONNXRUNTIME)
    add_compile_options(-D_YOLO_ONNXRUNTIME)
endif()
if(WITH_OPENVINO)
    add_compile_options(-D_YOLO_OPENVINO)
endif()
# if(WITH_LIBTORCH)
#     add_compile_options(-D_YOLO_LIBTORCH)
# endif()

find_package(OpenCV REQUIRED)

add_library(yoloInference SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/yolo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp)
target_include_directories(yoloInference PRIVATE ${OpenCV_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(yoloInference ${OpenCV_LIBRARIES})

if(WITH_OPENCV)
    add_subdirectory("yolo-opencv")
endif()

if(WITH_ONNXRUNTIME)
    add_subdirectory("yolo-onnxruntime")
    set(ONNXRUNTIME_INCLUDE_DIRS /onnxruntime/include)
    set(ONNXRUNTIME_LIBRARY_DIRS /onnxruntime/lib)

    target_include_directories(yoloInference PRIVATE ${ONNXRUNTIME_INCLUDE_DIRS})
    target_link_libraries(yoloInference ${ONNXRUNTIME_LIBRARY_DIRS}/libonnxruntime.so)
endif()

if(WITH_OPENVINO)
    add_subdirectory("yolo-openvino")
    set(OPENVINO_INCLUDE_DIRS /openvino_toolkit/runtime/include)
    set(OPENVINO_LIBRARY_DIRS /openvino_toolkit/runtime/lib/intel64)
    target_include_directories(yoloInference PRIVATE ${OPENVINO_INCLUDE_DIRS})
    target_link_libraries(yoloInference ${OPENVINO_LIBRARY_DIRS}/libopenvino.so ${OPENVINO_LIBRARY_DIRS}/libopenvino_intel_cpu_plugin.so ${OPENVINO_LIBRARY_DIRS}/libopenvino_intel_gpu_plugin.so)
endif()

# if(WITH_LIBTORCH)
#     # add_subdirectory("yolo-libtorch")
#     # set(TORCH_INCLUDE_DIRS /libtorch/include /libtorch/include/torch/csrc/api/include)
#     # set(TORCH_LIBRARIES /libtorch/lib)

#     # file(GLOB LIBTORCH_LIBS "/libtorch/lib/*.so")
#     # target_include_directories(yoloInference PRIVATE ${TORCH_INCLUDE_DIRS})
#     # target_link_libraries(yoloInference ${TORCH_LIBRARIES} ${LIBTORCH_LIBS})

#     # set(CMAKE_PREFIX_PATH /libtorch)
#     # # set(Torch_DIR /libtorch/share/cmake/Torch)
#     # find_package(Torch REQUIRED)

#     # target_include_directories(yoloInference PUBLIC ${TORCH_INCLUDE_DIRS})
#     # target_link_libraries(yoloInference ${TORCH_LIBRARIES})
#     file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/yolo-libtorch/*.h ${CMAKE_CURRENT_SOURCE_DIR}/yolo-libtorch/*.cpp)
#     aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/yolo-libtorch/ SRCS)
#     include_directories(${CMAKE_CURRENT_SOURCE_DIR}/yolo-libtorch/)

#     set(Torch_DIR /libtorch/share/cmake/Torch)
#     find_package(Torch REQUIRED)
#     # target_include_directories(yoloInference PUBLIC ${TORCH_INCLUDE_DIRS})
#     include_directories(${TORCH_INCLUDE_DIRS})
#     target_link_libraries(yoloInference ${TORCH_LIBRARIES})
# endif()

# For installing package
install(TARGETS yoloInference 
    EXPORT yoloInferenceTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(DIRECTORY include/ DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "yoloInferenceConfigVersion.cmake"
    VERSION ${yoloInference_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(EXPORT yoloInferenceTargets
    FILE yoloInferenceTargets.cmake
    NAMESPACE yoloInference::
    DESTINATION lib/cmake/yoloInference)

install(FILES "yoloInferenceConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/yoloInferenceConfigVersion.cmake"
    DESTINATION lib/cmake/yoloInference)

# uninstall target
if(NOT TARGET uninstall)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()