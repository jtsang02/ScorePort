package com.droiduino.bluetoothconn

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.droiduino.bluetoothconn.R
import android.widget.ProgressBar
import android.widget.TextView
import android.bluetooth.BluetoothAdapter
import com.droiduino.bluetoothconn.MainActivity
import com.droiduino.bluetoothconn.MainActivity.CreateConnectThread
import android.os.Looper
import android.content.Intent
import com.droiduino.bluetoothconn.SelectDeviceActivity
import android.content.ContentValues
import com.droiduino.bluetoothconn.MainActivity.ConnectedThread
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.os.Handler
import android.os.Message
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.ImageButton
import android.widget.ImageView
import androidx.appcompat.widget.Toolbar
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream

class Scoreboard : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_scoreboard)

        val incrementHomeScore = findViewById<Button>(R.id.buttonIncrementHomeScore)
        val decrementHomeScore = findViewById<Button>(R.id.buttonDecrementHomeScore)

        // increment home score

        incrementHomeScore.setOnClickListener {
            val cmdText = "<increment home score>"
            // Send command to Arduino board
            MainActivity.connectedThread!!.write(cmdText)
        }

        decrementHomeScore.setOnClickListener {
            val cmdText = "<decrement home score>"
            // Send command to Arduino board
            MainActivity.connectedThread!!.write(cmdText)
        }

    }


}

