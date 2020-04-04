package com.lasalle.beehoneyt;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @file MainActivity.java
 * @brief Déclaration de la classe MainActivity
 * @author Ethan VILLESSECHE
 */

/**
 * Logcat : MainActivity:|RucheActivity:|Ruche:|CommunicationMQTT:
 */

/**
 * @class MainActivity
 * @brief Déclaration de la classe MainActivity
 */
public class MainActivity extends AppCompatActivity
{
    /**
     * Constantes
     */
    private static final String TAG = "MainActivity";
    private static final int NB_RUCHES = 5; //!< le nombre max. de ruches

    /**
     * Attributs
     */
    private List<Ruche> ruches = new ArrayList<>(); //!< la liste des ruches connues
    private boolean nouvelleRuche = false; //!< indique si une nouvelle ruche a été récupérée
    private CommunicationMQTT communicationMQTT;

    /**
     * Ressources graphiques
     */
    private RecyclerView recyclerView; // la vue
    private RecyclerView.Adapter adapter; // l'adaptateur
    private RecyclerView.LayoutManager layoutManager; // le gestionnaire de mise en page
    private SwipeRefreshLayout swipeRefreshLayout;

    /**
     * @brief Méthode appelée à la création de l'activité MainActivity
     *
     * @fn MainActivity::onCreate(Bundle savedInstanceState)
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d(TAG, "onCreate()");

        communicationMQTT = new CommunicationMQTT(getApplicationContext(), handler);

        initialiserVue();

        nouvelleRuche = true;
        recupererRuches();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
        Log.i(TAG,"onStart()");
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        Log.i(TAG,"onResume()");
        /**
         * @todo Il faut rappeler connecterTTN
         */

    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override
    protected void onPause()
    {
        super.onPause();
        Log.i(TAG,"onPause()");

    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override
    protected void onStop()
    {
        super.onStop();
        Log.i(TAG,"onStop()");

    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop() et détruite par le système Android)
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.i(TAG,"onDestroy()");

    }

    private void initialiserVue()
    {
        Log.d(TAG, "initialiserVue()");
        swipeRefreshLayout = (SwipeRefreshLayout)findViewById(R.id.swipeRefreshLayout);
        swipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener()
        {
            @Override
            public void onRefresh()
            {
                recupererRuches();
            }
        });

        recyclerView = (RecyclerView) findViewById(R.id.listeRuche);
        recyclerView.setHasFixedSize(true);

        layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);

        adapter = new RucheAdapter(this, ruches);
        recyclerView.setAdapter(adapter);
    }

    /**
     * @brief Méthode pour récupérer les ruches
     *
     * @fn MainActivity::recupererRuches()
     */
    private void recupererRuches()
    {
        Log.d(TAG, "recupererRuches()");
        /**
         * @todo Récupérer les ruches à partir de la base de données SQLite et vérifier si il y a des nouvelles ruches
         */
        if(nouvelleRuche)
        {
            nouvelleRuche = false;

            // Pour les tests
            List<Ruche> listeRuches = Arrays.asList(
                    new Ruche("Ruche 1", "ruche_1"),
                    new Ruche("Ruche 2", "ruche_2"),
                    new Ruche("Ruche 3", "ruche_3"),
                    new Ruche("Ruche 4", "ruche_3")
            );

            listeRuches.get(0).setInfos("Simulateur");
            listeRuches.get(1).setPoids(35);
            listeRuches.get(1).setInfos("Simulateur");
            listeRuches.get(2).setPoids(32);
            listeRuches.get(2).setInfos("Simulateur");
            listeRuches.get(3).setPoids(40);
            listeRuches.get(3).setInfos("Simulateur");

            ruches.clear();
            for (int i = 0; i < listeRuches.size(); i++)
            {
                ruches.add(listeRuches.get(i));
            }

            rafraichir();
        }
    }

    /**
     * @brief Méthode pour rafraîchir la liste des ruches connues
     *
     * @fn MainActivity::rafraichir(List<Ruche> ruches)
     */
    private void rafraichir()
    {
        swipeRefreshLayout.setRefreshing(false);
        adapter.notifyDataSetChanged();
    }

    private void communiquerTTN(final String deviceID)
    {
        Log.d(TAG, "communiquerTTN() deviceID = " + deviceID);
        CommunicationMQTT.setCallback(new MqttCallbackExtended()
        {
            @Override
            public void connectComplete(boolean b, String s)
            {
            }
            @Override
            public void connectionLost(Throwable throwable)
            {
            }
            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.d(TAG, "communiquerTTN() topic = " + topic);
                Log.d(TAG, "communiquerTTN() mqttMessage = " + mqttMessage.toString());
                /**
                 * @todo Décoder les messages et mettre à jour l'affichage
                 */
                // Juste pour tester (à retirer rapidement) !
                JSONObject json = new JSONObject(mqttMessage.toString());
                String deviceID = json.getString("dev_id");
                for (int i = 0; i < ruches.size(); i++)
                {
                    if(ruches.get(i).getDeviceID().equals(deviceID))
                    {
                        ruches.get(i).setInfos("Message reçu !");
                    }
                    else
                    {
                        ruches.get(i).setInfos("Simulateur");
                    }
                }
                // fin du test

                rafraichir();
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
            }
        });
    }

    private void abonnerRuches()
    {
        for (int i = 0; i < ruches.size(); i++)
        {
            ruches.get(i).souscrireTopic();
            communiquerTTN(ruches.get(i).getDeviceID());
        }
    }

    /**
     * @brief Handler de communication entre l'activité et la communication MQTT
     */
    final private Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);

            Bundle bundle = msg.getData();

            switch(bundle.getInt("etat"))
            {
                case CommunicationMQTT.TTN_CONNECTE:
                    Log.d(TAG, "handleMessage() TTN connecté");
                    abonnerRuches();
                    break;
                case CommunicationMQTT.TTN_DECONNECTE:
                    Log.d(TAG, "handleMessage() TTN déconnecté");
                    break;
                case CommunicationMQTT.TTN_MESSAGE:
                    Log.d(TAG, "handleMessage() TTN topic = " + bundle.getString("topic") + " message = " + bundle.getString("message"));
                    break;
            }
        }
    };
}
