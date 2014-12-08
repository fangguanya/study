package com.fanggang.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

// !< ���ػ��ķ���,������̰󶨵�
public class FLocalService extends Service 
{

	// !< ���ڿ��Ʒ�����Activity֮�佻����Binder
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
