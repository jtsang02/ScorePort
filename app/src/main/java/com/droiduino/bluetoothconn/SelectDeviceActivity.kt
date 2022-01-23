package com.droiduino.bluetoothconn

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.droiduino.bluetoothconn.R
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.view.View
import com.droiduino.bluetoothconn.DeviceInfoModel
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.LinearLayoutManager
import com.droiduino.bluetoothconn.DeviceListAdapter
import androidx.recyclerview.widget.DefaultItemAnimator
import com.google.android.material.snackbar.Snackbar
import java.util.ArrayList

class SelectDeviceActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_select_device)

        // Bluetooth Setup
        val bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()

        // Get List of Paired Bluetooth Device
        val pairedDevices = bluetoothAdapter.bondedDevices
        val deviceList: MutableList<Any> = ArrayList()
        if (pairedDevices.size > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (device in pairedDevices) {
                val deviceName = device.name
                val deviceHardwareAddress = device.address // MAC address
                val deviceInfoModel = DeviceInfoModel(deviceName, deviceHardwareAddress)
                deviceList.add(deviceInfoModel)
            }
            // Display paired device using recyclerView
            val recyclerView = findViewById<RecyclerView>(R.id.recyclerViewDevice)
            recyclerView.layoutManager = LinearLayoutManager(this)
            val deviceListAdapter = DeviceListAdapter(this, deviceList)
            recyclerView.adapter = deviceListAdapter
            recyclerView.itemAnimator = DefaultItemAnimator()
        } else {
            val view = findViewById<View>(R.id.recyclerViewDevice)
            val snackbar = Snackbar.make(
                view,
                "Activate Bluetooth or pair a Bluetooth device",
                Snackbar.LENGTH_INDEFINITE
            )
            snackbar.setAction("OK") { }
            snackbar.show()
        }
    }
}