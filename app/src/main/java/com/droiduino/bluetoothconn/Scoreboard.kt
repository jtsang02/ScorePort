package com.droiduino.bluetoothconn

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class Scoreboard : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_scoreboard)

        val incrementHome = findViewById<Button>(R.id.buttonIncrementHome)
        val decrementHome = findViewById<Button>(R.id.buttonDecrementHome)
        val incrementGuest = findViewById<Button>(R.id.buttonIncrementGuest)
        val decrementGuest = findViewById<Button>(R.id.buttonDecrementGuest)
        val changeMode = findViewById<Button>(R.id.buttonToggleMode)
        var scoreMode = true
        var homeScore = 0
        var guestScore = 0

        // change score/shots mode. does not have to send arduino cmd
        changeMode.setOnClickListener {
            when (changeMode.text.toString().lowercase()) {
                "score" -> {
                    changeMode.text = "Shots"
                    scoreMode = false
                }
                "shots" -> {
                    changeMode.text = "Score"
                    scoreMode = true
                }
            }
        }

        // increment home score or shot
        incrementHome.setOnClickListener {
            val cmdText : String = if (scoreMode) "<increment home score>" else "<increment home shots>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // decrement home score or shots
        decrementHome.setOnClickListener {
            val cmdText : String = if (scoreMode) "<decrement home score>" else "<decrement home shots>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // increment guest score or shot
        incrementGuest.setOnClickListener {
            val cmdText : String = if (scoreMode) "<increment guest score>" else "<increment guest shots>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // decrement guest score or shots
        decrementGuest.setOnClickListener {
            val cmdText : String = if (scoreMode) "<decrement guest score>" else "<decrement guest shots>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

    }


}

