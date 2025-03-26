target_sources(yoloInference 
    PRIVATE yolo_libtorch.cpp 
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES yolo_libtorch.h)