package com.droiduino.bluetoothconn

import android.content.Context
import androidx.recyclerview.widget.RecyclerView
import android.widget.TextView
import android.widget.LinearLayout
import com.droiduino.bluetoothconn.R
import android.view.ViewGroup
import android.view.LayoutInflater
import com.droiduino.bluetoothconn.DeviceInfoModel
import android.content.Intent
import android.view.View
import com.droiduino.bluetoothconn.MainActivity

class DeviceListAdapter(private val context: Context, private val deviceList: List<Any>) :
    RecyclerView.Adapter<RecyclerView.ViewHolder>() {
    class ViewHolder(v: View) : RecyclerView.ViewHolder(v) {
        var textName: TextView
        var textAddress: TextView
        var linearLayout: LinearLayout

        init {
            textName = v.findViewById(R.id.textViewDeviceName)
            textAddress = v.findViewById(R.id.textViewDeviceAddress)
            linearLayout = v.findViewById(R.id.linearLayoutDeviceInfo)
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val v = LayoutInflater.from(parent.context)
            .inflate(R.layout.device_info_layout, parent, false)
        return ViewHolder(v)
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val itemHolder = holder as ViewHolder
        val deviceInfoModel = deviceList[position] as DeviceInfoModel
        itemHolder.textName.text = deviceInfoModel.deviceName
        itemHolder.textAddress.text = deviceInfoModel.deviceHardwareAddress

        // When a device is selected
        itemHolder.linearLayout.setOnClickListener {
            val intent = Intent(context, MainActivity::class.java)
            // Send device details to the MainActivity
            intent.putExtra("deviceName", deviceInfoModel.deviceName)
            intent.putExtra("deviceAddress", deviceInfoModel.deviceHardwareAddress)
            // Call MainActivity
            context.startActivity(intent)
        }
    }

    override fun getItemCount(): Int {
        return deviceList.size
    }
}