package com.fanggang.service;

import android.os.Bundle;
import android.os.IBinder;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;

public class MainActivity extends Activity {

	// !< 与服务之间的数据关联
	private ServiceConnection sc;
	private boolean isBind;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		sc = new ServiceConnection()
		{
			@Override
			public void onServiceDisconnected(ComponentName name)
			{
				
			}
			@Override
			public void onServiceConnected(ComponentName name, IBinder service)
			{
				//FLocalService.FSimpleBinder sBinder = (FLocalService.FSimpleBinder)service;
			}
		};
		
		// !< 注册按钮事件
		findViewById(R.id.btnbind).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				// !< 绑定时需要提供谁绑定的信息..
				bindService(new Intent(MainActivity.this, FLocalService.class), sc, Context.BIND_AUTO_CREATE);
				isBind = true;
			}
		});
		findViewById(R.id.btnunbind).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				if (isBind)
				{
					unbindService(sc);
					isBind = false;
				}
			}
		});
		findViewById(R.id.btnstart).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				//startService(new Intent(MainActivity.this, FLocalService.class));
			}
		});
		findViewById(R.id.btnstop).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				//stopService(new Intent(MainActivity.this, FLocalService.class));
			}
		});
		findViewById(R.id.btnforground).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				startService(new Intent(MainActivity.this, FForegroundService.class));
			}
		});
		findViewById(R.id.btnunforground).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				stopService(new Intent(MainActivity.this, FForegroundService.class));
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
