package com.fanggang.service;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class FForegroundService extends Service {

	private NotificationManager mNM;
	
	// !< 用来前置的反射函数:主要是不同版本的Android,API不一样!!!
	// !< set是老版本!
	private static final Class[] mStartForegroundSignature = new Class[]
			{
				int.class, Notification.class
			};
	private static final Class[] mStopForegroundSignature = new Class[]
			{
				boolean.class
			};
	private static final Class<?>[] mSetForegroundSignature = new Class[] {  
	    boolean.class}; 
	
	private Method mSetForeground;
	private Method mStartForeground;
	private Method mStopForeground;
	private Object[] mSetForegroundArgs = new Object[1]; 
	private Object[] mStartForegroundArgs = new Object[2];
	private Object[] mStopForegroundArgs = new Object[1];
	
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate()
	{
		super.onCreate();
		mNM = (NotificationManager)this.getSystemService(Context.NOTIFICATION_SERVICE);
		Notification notification = new Notification(R.drawable.ic_launcher, "foreground started.", System.currentTimeMillis());
		PendingIntent intent = PendingIntent.getActivity(this, 0, new Intent(this, MainActivity.class), 0);
		notification.setLatestEventInfo(this, "Forground", "Foreground service stoped.", intent);
		
		try {  
	        mStartForeground = getClass().getMethod("startForeground",  
	                mStartForegroundSignature);  
	        mStopForeground = getClass().getMethod("stopForeground",  
	                mStopForegroundSignature);  
	    } catch (NoSuchMethodException e) {  
	        // Running on an older platform.  
	        mStartForeground = mStopForeground = null;  
	    }  
	    try {  
	        mSetForeground = getClass().getMethod("setForeground",  
	                mSetForegroundSignature);  
	    } catch (NoSuchMethodException e) {  
	        throw new IllegalStateException(  
	                "OS doesn't have Service.startForeground OR Service.setForeground!");  
	    }

        startForegroundCompat(1, notification);
	}
	
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		stopForegroundCompat(1);
	}
	 
	/** 
	 * This is a wrapper around the new startForeground method, using the older 
	 * APIs if it is not available. 
	 */  
	void startForegroundCompat(int id, Notification notification) {  
	    // If we have the new startForeground API, then use it.  
	    if (mStartForeground != null) {  
	        mStartForegroundArgs[0] = Integer.valueOf(id);  
	        mStartForegroundArgs[1] = notification;  
	        invokeMethod(mStartForeground, mStartForegroundArgs);  
	        return;  
	    }  
	  
	    // Fall back on the old API.  
	    mSetForegroundArgs[0] = Boolean.TRUE;  
	    invokeMethod(mSetForeground, mSetForegroundArgs);  
	    mNM.notify(id, notification);  
	}  
	  
	/** 
	 * This is a wrapper around the new stopForeground method, using the older 
	 * APIs if it is not available. 
	 */  
	void stopForegroundCompat(int id) {  
	    // If we have the new stopForeground API, then use it.  
	    if (mStopForeground != null) {  
	        mStopForegroundArgs[0] = Boolean.TRUE;  
	        invokeMethod(mStopForeground, mStopForegroundArgs);  
	        return;  
	    }  
	  
	    // Fall back on the old API.  Note to cancel BEFORE changing the  
	    // foreground state, since we could be killed at that point.  
	    mNM.cancel(id);  
	    mSetForegroundArgs[0] = Boolean.FALSE;  
	    invokeMethod(mSetForeground, mSetForegroundArgs);  
	}  
	
	void invokeMethod(Method method, Object[] args) {  
	    try {  
	        method.invoke(this, args);  
	    } catch (InvocationTargetException e) {  
	        // Should not happen.  
	        Log.w("ApiDemos", "Unable to invoke method", e);  
	    } catch (IllegalAccessException e) {  
	        // Should not happen.  
	        Log.w("ApiDemos", "Unable to invoke method", e);  
	    }  
	}  
}
