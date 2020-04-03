package com.lasalle.beehoneyt;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

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
    private TextView nom_ruche;
    private TextView topic_ruche;
    private TextView message_ruche;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ruche);

        nom_ruche = (TextView) this.findViewById(R.id.nom_ruche);
        topic_ruche = (TextView) this.findViewById(R.id.topic_ruche);
        message_ruche = (TextView) this.findViewById(R.id.message_ruche);

        Intent intent = getIntent();
        // Attention : un nouvel objet Ruche est créé
        ruche = (Ruche)intent.getSerializableExtra("Ruche");

        if(ruche != null)
        {
            Log.d(TAG, "Ruche : " + ruche.getNom() + " " + ruche);
            afficherInfo();
            communiquerTTN(ruche.getDeviceID());
        }
    }

    /**
     * @brief afficher les information d'un ruche
     * @fn RucheActivity::afficherInfo()
     */
    private void afficherInfo()
    {
        afficherNom(ruche.getNom());
        afficherTopic(ruche.getDeviceID());
    }

    /**
     * @brief afficher le nom d'un ruche
     * @fn RucheActivity::afficherNom(String message)
     */
    public void afficherNom(String message)
    {
        nom_ruche.setText("Nom : " + message);
    }

    /**
     *
     * @brief afficher le topic
     * @fn RucheActivity::afficherTopic(String message)
     *
     * @param message
     */
    public void afficherTopic(String message)
    {
        topic_ruche.setText("Topic : " + message);
    }

    public void afficherJSON(String message)
    {
        message_ruche.setText("Message : " + message);
    }

    private void communiquerTTN(String deviceID)
    {
        Log.d(TAG, "deviceID : " + deviceID);
        CommunicationMQTT.setCallback(new MqttCallbackExtended()
        {
            @Override
            public void connectComplete(boolean b, String s) {

            }

            @Override
            public void connectionLost(Throwable throwable) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.d(TAG, "Topic : " + topic);
                Log.d(TAG, "Message : " + mqttMessage.toString());
                afficherJSON(mqttMessage.toString());

                /**
                 * @todo Extraire les données du message en filtrant le dev_id
                 */
                CommunicationMQTT.decoderMessage(mqttMessage.toString());

                String horodatage = CommunicationMQTT.extraireHorodatage(mqttMessage.toString());
                String horodatageFormate = formaterHorodatge(horodatage);
                Log.d(TAG, "Horodatage formaté : " + horodatageFormate);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
            }
        });
    }

    private String formaterHorodatge(String horodatage)
    {
        /**
         * @todo Finaliser le formatage de l'horodatage
         */
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss", Locale.FRENCH);
        df.setTimeZone(TimeZone.getTimeZone("UTC"));
        Date date = null;
        String horodatageFormate = horodatage;
        try
        {
            date = df.parse(horodatage);
            df.setTimeZone(TimeZone.getDefault());
            horodatageFormate = df.format(date);
        }
        catch (ParseException e)
        {
            e.printStackTrace();
        }

        return horodatageFormate;
    }
}

