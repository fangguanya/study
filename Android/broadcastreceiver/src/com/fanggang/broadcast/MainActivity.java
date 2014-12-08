package com.fanggang.broadcast;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.util.Log;
import android.view.Menu;
import android.widget.*;
import android.content.*;
import android.view.View;
import android.view.View.OnClickListener;

public class MainActivity extends Activity {
	private Button btnDynamic;
	private Button btnStatic;
	private Button btnSystem;
	private Button btnDelay; 
	private Button btnCleanDelay;
	
	// !< 定义事件的名称
	private static String STATIC_ACTION = "com.fanggang.static";
	private static String DYNAMIC_ACTION = "com.fanggang.dynamic";
	private static String SYSTEM_ACTION = Intent.ACTION_POWER_CONNECTED;
	private static String DELAY_ACTION = "com.fanggang.delay";
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnDynamic = (Button)findViewById(R.id.btn_dynamic);
        btnStatic = (Button)findViewById(R.id.btn_static);
        btnSystem = (Button)findViewById(R.id.btn_system);
        btnDelay = (Button)findViewById(R.id.btn_delay);
        btnCleanDelay = (Button)findViewById(R.id.btn_cleandelay);

        btnDynamic.setOnClickListener(new FButtonClickDispatcher());
        btnStatic.setOnClickListener(new FButtonClickDispatcher());
        btnSystem.setOnClickListener(new FButtonClickDispatcher());
        btnDelay.setOnClickListener(new FButtonClickDispatcher());
        btnCleanDelay.setOnClickListener(new FButtonClickDispatcher());
    }
    // !< 事件处理的类
    class FButtonClickDispatcher implements OnClickListener
    {
    	@Override
    	public void onClick(View v)
    	{
    		if (v.getId() == R.id.btn_dynamic)
    		{
    			Intent i = new Intent();
    			i.setAction(DYNAMIC_ACTION);
    			i.putExtra("msg", "接收到了动态广播!!");
    			sendBroadcast(i);
    		}
    		else if (v.getId() == R.id.btn_static)
    		{
    			Intent i = new Intent();
    			i.setAction(STATIC_ACTION);
    			i.putExtra("msg", "接收到了延静态广播!!");
    			sendBroadcast(i);
    		}
    		else if (v.getId() == R.id.btn_delay)
    		{
    			Intent i = new Intent(MainActivity.this, FDelayBroadcastReceiver.class);
    			i.setAction(DELAY_ACTION);
    			i.putExtra("msg", "接收到了延迟广播!!");
    			AlarmManager am = (AlarmManager)MainActivity.this.getSystemService(Context.ALARM_SERVICE);
    			am.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP, 5*1000, 2000, PendingIntent.getBroadcast(MainActivity.this, 0, i, 0));
    		}
    		else if (v.getId() == R.id.btn_cleandelay)
    		{
    			AlarmManager am = (AlarmManager)MainActivity.this.getSystemService(Context.ALARM_SERVICE);
    			Intent i = new Intent(MainActivity.this, FDelayBroadcastReceiver.class);
    			Toast.makeText(MainActivity.this, "清除延迟广播!", Toast.LENGTH_SHORT).show();
    		}
    		else if (v.getId() == R.id.btn_system)
    		{
    			Toast.makeText(MainActivity.this, "系统广播自动的!", Toast.LENGTH_SHORT).show();
    		}
    	}
    }
    
    @Override
    protected void onStart()
    {
    	super.onStart();
    	
    	// !< 程序内设置receiver!!
    	IntentFilter filter_dynamic = new IntentFilter();
    	filter_dynamic.addAction(DYNAMIC_ACTION);
    	registerReceiver(dynamicReceiver, filter_dynamic);
    	IntentFilter filter_static = new IntentFilter();
    	filter_static.addAction(STATIC_ACTION);
    	registerReceiver(staticReceiver, filter_static);
    	IntentFilter filter_system = new IntentFilter();
    	filter_system.addAction(SYSTEM_ACTION);
    	registerReceiver(new FSystemBroadcastReceiver(), filter_system);
    }

	private BroadcastReceiver dynamicReceiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context context, Intent intent) {
			Log.e("MainActivity", "接收动态注册广播消息");
			if(intent.getAction().equals(DYNAMIC_ACTION)){
				String msg = intent.getStringExtra("msg");
				Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
				NotificationManager nm = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
		        int id =(int)(Math.random()*10000.0f)+1;
		        Notification notification = new Notification(R.drawable.ic_launcher, "new msg", System.currentTimeMillis());
		        
		        // !< 设置内容;
		        PendingIntent contentIntent = PendingIntent.getActivity(context, id, new Intent(context, MainActivity.class), 0);
		        notification.setLatestEventInfo(context, "new msg", msg, contentIntent);
		        notification.flags |= Notification.FLAG_AUTO_CANCEL;
		        		
		        nm.notify(id, notification);
			}
		}
	};
	private BroadcastReceiver staticReceiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context context, Intent intent) {
			Log.e("MainActivity", "接收静态注册广播消息");
			if(intent.getAction().equals(STATIC_ACTION)){
				String msg = intent.getStringExtra("msg");
				Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
				NotificationManager nm = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
		        int id =(int)(Math.random()*10000.0f)+1;
		        Notification notification = new Notification(R.drawable.ic_launcher, "new msg", System.currentTimeMillis());
		        
		        // !< 设置内容;
		        PendingIntent contentIntent = PendingIntent.getActivity(context, id, new Intent(context, MainActivity.class), 0);
		        notification.setLatestEventInfo(context, "new msg", msg, contentIntent);
		        
		        nm.notify(id, notification);
			}
		}
	};
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
