#include <jni.h>
#include <string>
#include "libyuv/include/libyuv.h"

#define WIDTH 1280
#define HEIGHT 720

extern "C" JNIEXPORT jstring JNICALL
Java_com_vectoros_libyuvexample_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_vectoros_libyuvexample_MainActivity_nativeConvertFromI420(JNIEnv *env, jobject thiz) {
    int ret = 0;
    uint8_t *i420Buffer = new uint8_t [WIDTH * HEIGHT * 3 / 2];
    memset(i420Buffer, 0, WIDTH * HEIGHT * 3 / 2);
    uint8_t *rgbaBuffer = new uint8_t [WIDTH * HEIGHT * 4];
    memset(rgbaBuffer, 0, WIDTH * HEIGHT * 4);
    uint8_t *srcYBuffer = i420Buffer;
    int srcYStride = WIDTH;
    uint8_t *srcUBuffer = i420Buffer + WIDTH * HEIGHT;
    uint8_t *srcVBuffer = srcUBuffer + WIDTH * HEIGHT / 4;
    int srcUVStride = WIDTH / 2;
    bool verticalFlip = true;
    ret = libyuv::ConvertFromI420(
            srcYBuffer, srcYStride,
            srcUBuffer, srcUVStride,
            srcVBuffer, srcUVStride,
            rgbaBuffer, WIDTH * 4,
            WIDTH, verticalFlip ? -HEIGHT : HEIGHT,
            libyuv::FOURCC_RGBA);
    assert(ret == 0);
    delete[] i420Buffer;
    delete[] rgbaBuffer;
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_vectoros_libyuvexample_MainActivity_nativeConvertToI420(JNIEnv *env, jobject thiz) {
    int ret = 0;
    uint8_t *i420Buffer = new uint8_t [WIDTH * HEIGHT * 3 / 2];
    memset(i420Buffer, 0, WIDTH * HEIGHT * 3 / 2);
    uint8_t *rgbaBuffer = new uint8_t [WIDTH * HEIGHT * 4];
    memset(rgbaBuffer, 0, WIDTH * HEIGHT * 4);
    uint8_t *dstYBuffer = i420Buffer;
    int dstYStride = WIDTH;
    uint8_t *dstUBuffer = i420Buffer + WIDTH * HEIGHT;
    uint8_t *dstVBuffer = dstUBuffer + WIDTH * HEIGHT / 4;
    int dstUVStride = WIDTH / 2;
    bool verticalFlip = true;
    ret = libyuv::ConvertToI420(
            rgbaBuffer, WIDTH * 4,
            dstYBuffer, dstYStride,
            dstUBuffer, dstUVStride,
            dstVBuffer, dstUVStride,
            0, 0,
            WIDTH, verticalFlip ? -HEIGHT : HEIGHT,
            WIDTH, HEIGHT,
            libyuv::kRotate180,
            libyuv::FOURCC_RGBA);
    assert(ret == 0);
    delete[] i420Buffer;
    delete[] rgbaBuffer;
    return ret;
}