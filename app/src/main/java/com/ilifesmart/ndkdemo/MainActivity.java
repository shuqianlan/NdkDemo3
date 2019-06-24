package com.ilifesmart.ndkdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

	public static final String TAG = "MainActivity";
	static {
		System.loadLibrary("DataProvider");
	}

	@BindView(R.id.wav_path)
	EditText mWavPath;
	@BindView(R.id.mp3_name)
	EditText mMp3Name;
	@BindView(R.id.lame_version)
	Button mLameVersion;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ButterKnife.bind(this);
	}

	@Override
	protected void onResume() {
		super.onResume();

		DataProvider provider = new DataProvider();
		// C调用Java
		provider.callHelloFromJava();
		provider.callJavaAdd();
		provider.callPrint();
		DataProvider.callStaticPrint();

		// Java调用C
		DataProvider.sayHello();
		int result = DataProvider.add_(3, 4);
		Log.d("Result", "onResume: result " + result);

		String str = "Hello,CST";
		String res = DataProvider.append(str);
		Log.d("Result", "onResume: res " + res);
	}

	@OnClick({R.id.lame_version, R.id.submit})
	public void onViewClicked(View view) {
		switch (view.getId()) {
			case R.id.lame_version:
				String ver = new Lame().getLameVersion();
				Log.d(TAG, "onViewClicked: ver " + ver);
				mLameVersion.setText(ver);
				break;
			case R.id.submit:
				break;
		}
	}
}
