
# Libtorch
./yolo 0 2 6 0 0 ../../weights/yolov11n_seg_fp32_cpu.torchscript

# ONNXruntime
./yolo 1 2 6 0 0 ../weights/yolov11n_seg_fp32.onnx

# Opencv
./yolo 2 2 6 0 0 ../weights/yolov11n_seg_fp32.onnx
./yolo 2 2 6 0 1 ../weights/yolov11n_seg_fp16.onnx

# Openvino
./yolo 3 2 6 0 0 ../weights/yolov11n_seg_fp32.onnx