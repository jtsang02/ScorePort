package com.droiduino.bluetoothconn

import android.annotation.SuppressLint
import android.os.Bundle
import android.os.Handler
import android.widget.Button
import android.widget.TextView
import android.widget.ToggleButton
import androidx.appcompat.app.AppCompatActivity
import android.view.LayoutInflater
import androidx.appcompat.app.AlertDialog
import kotlinx.android.synthetic.main.fun_dialog.*
import kotlinx.android.synthetic.main.reset_time.view.*

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
        //val toggleClock : ToggleButton = findViewById(R.id.buttonToggleClock2)

        val resetTime = findViewById<Button>(R.id.buttonResetClock)
        val resetScore = findViewById<Button>(R.id.resetScore)
        val changeMode = findViewById<Button>(R.id.buttonToggleMode)
        val funBtn = findViewById<Button>(R.id.funBtn)
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

        // change period. send cmd to arduino
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

        // toggle clock start/stop. sends cmd to arduino
        /*
        toggleClock.setOnCheckedChangeListener { _, isChecked ->
            toggleClock.setTextOn("Stop");
            toggleClock.setTextOff("Start");
            if (isChecked) {
                // The toggle is enabled
                cmdText = "<start>"
            } else {
                // The toggle is disabled
                cmdText = "<stop>"
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }*/
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

        // reset score and shots. sends cmd to arduino
        resetScore.setOnClickListener {
            homeScore = 0
            guestScore = 0
            homeShots = 0
            guestShots = 0
            homeScoreView.text = homeScore.toString()
            guestScoreView.text = guestScore.toString()
            homeShotsView.text = homeShots.toString()
            guestShotsView.text = guestShots.toString()
            MainActivity.connectedThread!!.write("<reset score>")   // Send command to Arduino board
        }

        // button click to open dialog and show reset clock options. send cmd to arduino
        resetTime.setOnClickListener {

            // Inflate the layout using LayoutInflater
            val mDialogView = LayoutInflater.from(this).inflate(R.layout.reset_time, null)
            //alertDialogBuilder
            val mBuilder = AlertDialog.Builder(this).setView(mDialogView)
            // show dialog
            val mAlertDialog = mBuilder.show()

            // logic btns click on custom layout
            mDialogView.setPeriodLength.setOnClickListener {
                var userPeriodLength = mDialogView.userSetPeriodLength.text.toString()
                if (userPeriodLength.length == 1)   userPeriodLength = '0' + userPeriodLength   // convert single digit to string of length 2
                if (userPeriodLength.isNotEmpty()){
                    MainActivity.connectedThread!!.write("<set period to ${userPeriodLength}>")   // Send command to Arduino board
                }
            }
            // toggle countup/coundown mode. sends cmd to arduino
            mDialogView.countUpSwitch.setOnCheckedChangeListener { _, isChecked ->
                if (isChecked) {
                    // The toggle is enabled
                    cmdText = "<countup mode>"
                } else {
                    // The toggle is disabled
                    cmdText = "<countdown mode>"
                }
                MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
            }

            mDialogView.resetCustomTime.setOnClickListener {
                mAlertDialog.dismiss()  // dismiss dialog
                var userMinutes = mDialogView.userSetMinutes.text.toString()
                var userSeconds = mDialogView.userSetSeconds.text.toString()

                // convert single digits to string of length 2
                if (userMinutes.length == 1)    userMinutes = '0' + userMinutes
                if (userSeconds.length == 1)    userSeconds = '0' + userSeconds

                // more btn logic
                if (userMinutes.isNotEmpty() && userSeconds.isNotEmpty())
                    MainActivity.connectedThread!!.write("<reset clock to ${userMinutes}:${userSeconds}>")   // Send command to Arduino board
                else if (userMinutes.isNotEmpty())
                    MainActivity.connectedThread!!.write("<reset clock to ${userMinutes}:00>")
                else if (userSeconds.isNotEmpty())
                    MainActivity.connectedThread!!.write("<reset clock to 00:${userSeconds}>")
                else
                    MainActivity.connectedThread!!.write("<reset>")   // Send command to Arduino board
            }
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
                homeScoreView.text = homeScore.toString()       // get rid of this
            } else {
                cmdText = "<increment home shots>"
                homeShots += 1
                homeShotsView.text = homeShots.toString()       // get rid of this
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // decrement home score or shots
        decrementHome.setOnClickListener {
            if (scoreMode) {
                cmdText = "<decrement home score>"
                homeScore -= 1
                homeScoreView.text = homeScore.toString()
            } else {
                cmdText = "<decrement home shots>"
                homeShots -= 1
                homeShotsView.text = homeShots.toString()
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
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
                cmdText = "<decrement guest score>"
                guestScore -= 1
                guestScoreView.text = guestScore.toString()
            } else {
                cmdText = "<decrement guest shots>"
                guestShots -= 1
                guestShotsView.text = guestShots.toString()
            }
            MainActivity.connectedThread!!.write(cmdText)   // Send command to Arduino board
        }

        // fun button dialog box
        funBtn.setOnClickListener {
            // Inflate the layout using LayoutInflater
            val funDialogView = LayoutInflater.from(this).inflate(R.layout.fun_dialog, null)
            //alertDialogBuilder
            val funBuilder = AlertDialog.Builder(this).setView(funDialogView)
            // show dialog
            val funAlertDialog = funBuilder.show()

            funAlertDialog.goalBtn.setOnClickListener {
                MainActivity.connectedThread!!.write("<goal>")   // Send command to Arduino board
                Handler().postDelayed({}, 3000)
            }
            funAlertDialog.igenMsg.setOnClickListener {
                MainActivity.connectedThread!!.write("<igen>")   // Send command to Arduino board
                Handler().postDelayed({}, 3000)
            }
        }
    }
}