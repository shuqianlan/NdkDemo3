package com.ilifesmart.ndkdemo;

import android.util.Log;

public class DataProvider {
	public static final String TAG = "DataProvider";

	public void helloFromJava() {
		Log.d(TAG, "helloFromJava: call from java .");
	}

	public int add(int a, int b) {
		Log.d(TAG, "add: a " + a + " b " + b);
		return a + b;
	}

	public void print(String s) {
		Log.d(TAG, "print: s " + s);
	}

	public static void statticPrint() {
		Log.d(TAG, "statticPrint: call static method ");
	}
	/*  ------------ JNI -------------  */

	public native void callJavaAdd();
	public native void callHelloFromJava();
	public native void callPrint();
	public static native void callStaticPrint();
	public static native void sayHello();
	public static native int add_(int x, int y);
	public static native String append(String s);
}
