package com.addpuka.monstone;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class MainActivity extends Activity {

	private GLSurfaceView mGLView;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        mGLView = new GLView(getApplicationContext());
        setContentView(mGLView);
    }
    

}
