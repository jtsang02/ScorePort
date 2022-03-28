package com.droiduino.bluetoothconn

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.Button
import android.widget.Switch
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class Scoreboard : AppCompatActivity() {
    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_scoreboard)

        // define buttons
        val incrementHome = findViewById<Button>(R.id.buttonIncrementHome)
        val decrementHome = findViewById<Button>(R.id.buttonDecrementHome)
        val incrementGuest = findViewById<Button>(R.id.buttonIncrementGuest)
        val decrementGuest = findViewById<Button>(R.id.buttonDecrementGuest)
        val toggleClock = findViewById<Button>(R.id.buttonToggleClock)
        val resetClock = findViewById<Button>(R.id.buttonResetClock)
        val changeMode = findViewById<Button>(R.id.buttonToggleMode)
        val goalBtn = findViewById<Button>(R.id.buttonGoal)
        val toggleCountUp : Switch = findViewById(R.id.countUpSwitch)
        val changePeriod = findViewById<Button>(R.id.period)
        // define text views
        val homeScoreView = findViewById<TextView>(R.id.homeScore)
        val guestScoreView = findViewById<TextView>(R.id.guestScore)
        val homeShotsView = findViewById<TextView>(R.id.homeShots)
        val guestShotsView = findViewById<TextView>(R.id.guestShots)
        // variables
        var homeScore = 0
        var guestScore = 0
        var homeShots = 0
        var guestShots = 0
        var scoreMode = true
        var clockOn = false
        var period = 1
        var cmdText = ""

        changePeriod.setOnClickListener {
            if (period < 4){
                period++;
            } else {
                period = 1;
            }
            changePeriod.text = period.toString()
            cmdText = "<change period to ${period.toString()}>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        toggleCountUp.setOnCheckedChangeListener { _, isChecked ->
            if (isChecked) {
                // The toggle is enabled
                cmdText = "<countup mode>"
            } else {
                // The toggle is disabled
                cmdText = "<countdown mode>"
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // toggle clock on/off. sends cmd to arduino
        toggleClock.setOnClickListener {
            if (!clockOn) {
                cmdText = "<start>"
                toggleClock.text = "Stop"
                clockOn = true
            }
            else {
                cmdText = "<stop>"
                toggleClock.text = "Start"
                clockOn = false
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // reset clock. send cmd to arduino
        resetClock.setOnClickListener {
            clockOn = false
            cmdText = "<reset>"
            toggleClock.text = "Start"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

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
            if (scoreMode){
                cmdText = "<increment home score>"
                homeScore += 1
                homeScoreView.text = homeScore.toString()
            } else {
                cmdText = "<increment home shots>"
                homeShots += 1
                homeShotsView.text = homeShots.toString()
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // decrement home score or shots
        decrementHome.setOnClickListener {
            if (scoreMode) {
                if (homeScore > 0) {
                    cmdText = "<decrement home score>"
                    homeScore -= 1
                    homeScoreView.text = homeScore.toString()
                    MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
                }
            } else {
                if (homeShots > 0) {
                    cmdText = "<decrement home shots>"
                    homeShots -= 1
                    homeShotsView.text = homeShots.toString()
                    MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
                }
            }

        }

        // increment guest score or shot
        incrementGuest.setOnClickListener {
            if (scoreMode){
                cmdText = "<increment guest score>"
                guestScore += 1
                guestScoreView.text = guestScore.toString()
            } else {
                cmdText = "<increment guest shots>"
                guestShots += 1
                guestShotsView.text = guestShots.toString()
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // decrement guest score or shots
        decrementGuest.setOnClickListener {
            if (scoreMode) {
                if (guestScore > 0) {
                    cmdText = "<decrement guest score>"
                    guestScore -= 1
                    guestScoreView.text = guestScore.toString()
                    MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
                }
            } else {
                if (guestShots > 0) {
                    cmdText = "<decrement guest shots>"
                    guestShots -= 1
                    guestShotsView.text = guestShots.toString()
                    MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
                }
            }
        }

        // goal button
        goalBtn.setOnClickListener {
            cmdText = "<goal>"
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }
    }
}

