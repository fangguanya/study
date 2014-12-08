package com.fanggang.broadcast;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class FSystemBroadcastReceiver extends BroadcastReceiver
{
	@Override
	public void onReceive(Context context, Intent intent)
	{
		Toast.makeText(context, "≤Â»ÎUSB¿≤¿≤¿≤¿≤", Toast.LENGTH_SHORT).show();
	}
}
