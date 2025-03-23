#pragma once

#include <iostream>

/**
 * @description:   float32 to float16, refer to https://github.com/Tencent/ncnn/blob/master/src/mat.cpp
 * @return {*}     float16 
 */
uint16_t float32_to_float16(float value);

/**
 * @description:   float16 to float32, refer to https://github.com/Tencent/ncnn/blob/master/src/mat.cpp
 * @return {*}     float32 
 */
float float16_to_float32(uint16_t value);