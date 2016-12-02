package com.addpuka.monstone;

public class NativeCall {
	
	static {
        System.loadLibrary("monstone_jni_lib");
    }
	
	public static native void nativeCreated(); 
    public static native void nativeChanged(int w, int h);
    public static native void nativeUpdateGame();
    public static native void nativeOnTouchEvent(int x, int y, int touchFlag);
}
