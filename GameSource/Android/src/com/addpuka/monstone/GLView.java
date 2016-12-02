package com.addpuka.monstone;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.view.MotionEvent;

public class GLView extends GLSurfaceView implements Renderer {

	public GLView(Context context) {
		super(context);
		this.setEGLContextClientVersion(2);	
		this.setRenderer(this);
		this.requestFocus();
		this.setRenderMode(RENDERMODE_WHEN_DIRTY);
		this.setFocusableInTouchMode(true);
	}

	public void onDrawFrame(GL10 gl) {
		NativeCall.nativeUpdateGame();
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		NativeCall.nativeChanged(w, h); 
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		NativeCall.nativeCreated();
	} 
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		NativeCall.nativeOnTouchEvent((int)event.getX(), (int)event.getY(), event.getAction());
		return true;
	}

}