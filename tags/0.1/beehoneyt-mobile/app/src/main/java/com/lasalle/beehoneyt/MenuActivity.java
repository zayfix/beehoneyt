package com.lasalle.beehoneyt;

/**
 * @file MenuActivity.java
 * @brief Déclaration de la classe MenuActivity
 * @author Ethan VILLESSECHE
 */

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

/**
 * @class MenuActivity
 * @brief Déclaration de la classe MenuActivity
 * @author Ethan VILLESSECHE
 */
 
public class MenuActivity extends AppCompatActivity {

    private static final String TAG = "MenuActivity";

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
        Log.d(TAG, "onCreate: started");

    }

}
