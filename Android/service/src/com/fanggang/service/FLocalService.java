package com.fanggang.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

// !< 本地化的服务,是与进程绑定的
public class FLocalService extends Service 
{

	// !< 用于控制服务与Activity之间交互的Binder
	public class FSimpleBinder extends Binder
	{
		public FLocalService getService()
		{
			return FLocalService.this;
		}
	}
	
	public FSimpleBinder mBinder;
	@Override
	public IBinder onBind(Intent arg0) {
		return mBinder;
	}

	@Override
	public void onCreate()
	{
		super.onCreate();
		mBinder = new FSimpleBinder();
	}
	
	@Override
	public void onDestroy()
	{
		super.onDestroy();
	}
}
