package com.lasalle.beehoneyt;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class RucheActivity extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "RucheActivity";

    /**
     * Attributs
     */
    private Ruche ruche = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ruche);

        Intent intent = getIntent();
        ruche = (Ruche)intent.getSerializableExtra("Ruche");

        if(ruche != null)
            Log.d(TAG, "Ruche : " + ruche.getNom());
    }
}
