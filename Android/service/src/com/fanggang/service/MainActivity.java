package com.fanggang.service;

import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;

public class MainActivity extends Activity implements OnClickListener {

	// !< 与服务之间的数据关联
	private ServiceConnection sc;
	private boolean isBind;
	
	private static final String TAG = "Service_MainActivity";
	private static final String REMOTE_INTENT = FRemoteService.class.getName();
	
	private IMusicService mRemoteService = null; 
    private ServiceConnection sc_remote = new ServiceConnection() {
        @Override  
        public void onServiceDisconnected(ComponentName name) {  
            // TODO Auto-generated method stub  
            Log.d(TAG, "onServiceDisconnected()");  
            mRemoteService = null;  
        }  
          
        @Override  
        public void onServiceConnected(ComponentName name, IBinder service) {  
            // TODO Auto-generated method stub  
            Log.d(TAG, "onServiceConnected()");  
            mRemoteService = IMusicService.Stub.asInterface(service);  
        }  
    }; 
	
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

		findViewById(R.id.btnplaymusic).setOnClickListener(this);
		findViewById(R.id.btnstopmusic).setOnClickListener(this);
		findViewById(R.id.btnexitmusic).setOnClickListener(this);
		findViewById(R.id.btnpausemusic).setOnClickListener(this);
		
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
		findViewById(R.id.btnstart).setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				if (mRemoteService != null) return;
				// !< 服务
				Log.d("Service Remote--Initialize", "service class name=" + REMOTE_INTENT);
				// !< 在A进程中启动服务
				//startService(new Intent());
				bindService(new Intent(REMOTE_INTENT), sc_remote, Context.BIND_AUTO_CREATE);
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
	}
	
	@Override
	public void onClick(View v)
	{
		if (mRemoteService == null) return;
        switch(v.getId()) {  
        case R.id.btnplaymusic:  
            try {  
            	mRemoteService.play();  
            } catch (RemoteException e) {  
                Log.e(TAG, e.toString());  
            }  
            break;  
        case R.id.btnstopmusic:  
            try {  
            	mRemoteService.stop();  
            } catch (RemoteException e) {  
                Log.e(TAG, e.toString());  
            }  
            break;  
        case R.id.btnpausemusic:  
            try {  
            	mRemoteService.pause();  
            } catch (RemoteException e) {  
                Log.e(TAG, e.toString());  
            }  
            break;  
        case R.id.btnexitmusic:  
            finish();  
            break;  
        default:  
            break;  
        }  
    }

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
