package com.fanggang.service;

import java.io.IOException;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.media.MediaPlayer;

public class FRemoteService extends Service {
	private static String TAG = "fanggang_remote_service";
	private MediaPlayer mPlayer = null;
	private IMusicService.Stub mBinder = new IMusicService.Stub() {
		
		@Override
		public void stop() throws RemoteException {
			if (mPlayer != null)
			{
				mPlayer.stop();
				 try 
				 {  
	                    mPlayer.prepare();
				 } 
				 catch (IllegalStateException e) 
				 {  
	                    Log.e(TAG, e.toString());
				 }
				 catch (IOException e) 
				 { 
	                    Log.e(TAG, e.toString());  
	             } 
			}
		}
		
		@Override
		public void resume() throws RemoteException {
			// TODO Auto-generated method stub
			
		}
		
		@Override
		public void play() throws RemoteException {
			if (mPlayer == null)
			{
				//mPlayer = MediaPlayer.create(FRemoteService.this, R.raw.tiger); 
			}
			
			if (mPlayer != null)
			{
				if (!mPlayer.isPlaying()) mPlayer.start();
			}
		}
		
		@Override
		public void pause() throws RemoteException {
			if (mPlayer != null && mPlayer.isPlaying())
			{
				mPlayer.pause();
			}
		}
	};
	
	@Override
	public IBinder onBind(Intent arg0) {
		try {  
			mBinder.play();  
        } catch (RemoteException e) {  
            Log.e(TAG, e.toString());  
        } 
		return mBinder;
	}
    @Override  
    public boolean onUnbind(Intent intent) {  
//		try {  
//			mBinder.pause();  
//        } catch (RemoteException e) {  
//            Log.e(TAG, e.toString());  
//        } 
        System.out.println(TAG + " -->onUnbind");  
        return super.onUnbind(intent);  
    }  
    @Override  
    public void onDestroy() {    
        System.out.println(TAG + " -->onDestroy");  
        mPlayer.stop();  
        mPlayer.release();  
        super.onDestroy();  
    } 

	// !< 当自己的服务被开启时,所处的Thread与之前的Activity肯定不是一个啦
	@Override
	public void onCreate()
	{
        System.out.println(TAG +" Id-->" + Thread.currentThread().getId());  
        System.out.println(TAG + " Name-->" + Thread.currentThread().getName());            
        System.out.println(TAG + " onCreate--onBind");  
        super.onCreate();  
	}
}
