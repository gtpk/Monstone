#include "NativeCall.h"

JNIEXPORT void JNICALL Java_com_addpuka_monstone_NativeCall_nativeCreated (JNIEnv*  env)
{
	onSurfaceCreate();
}

JNIEXPORT void JNICALL Java_com_addpuka_monstone_NativeCall_nativeChanged (JNIEnv* env, jobject thiz, jint w, jint h)
{
	onSurfaceChanged(w, h);
}

JNIEXPORT void JNICALL Java_com_addpuka_monstone_NativeCall_nativeUpdateGame (JNIEnv* env)
{
	updateGameLoop();
}

JNIEXPORT void JNICALL Java_com_addpuka_monstone_NativeCall_nativeOnTouchEvent (JNIEnv* env, jobject thiz, jint x, jint y, jint touchFlag)
{
	onTouchEvent(x, y, touchFlag);
}
