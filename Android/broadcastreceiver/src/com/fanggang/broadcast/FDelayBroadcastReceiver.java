package com.fanggang.broadcast;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class FDelayBroadcastReceiver extends BroadcastReceiver
{
	private static String DELAY_ACTION = "com.fanggang.delay";
	@Override
	public void onReceive(Context context, Intent intent)
	{
		if (intent.getAction().equals(DELAY_ACTION))
		{
			String msg = intent.getStringExtra("msg");
			Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
			NotificationManager nm = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
	        int id =(int)(Math.random()*10000.0f)+1;
	        Notification notification = new Notification(R.drawable.ic_launcher, "new msg", System.currentTimeMillis());
	        
	        // !< ÉèÖÃÄÚÈÝ;
	        PendingIntent contentIntent = PendingIntent.getActivity(context, id, new Intent(context, MainActivity.class), 0);
	        notification.setLatestEventInfo(context, "new msg", msg, contentIntent);
	        notification.flags |= Notification.FLAG_AUTO_CANCEL;
	        
	        nm.notify(id, notification);
		}
	}
}
