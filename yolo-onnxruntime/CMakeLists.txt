target_sources(yoloInference 
    PRIVATE yolo_onnxruntime.cpp 
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES yolo_onnxruntime.h)