package com.lasalle.beehoneyt;

/**
 * @file RucheActivity.java
 * @brief Déclaration de la classe RucheActivity
 * @author Ethan VILLESSECHE
 */

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONException;
import org.json.JSONObject;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.Locale;
import java.util.TimeZone;

/**
 * @class RucheActivity
 * @brief Déclaration de la classe RucheActivity
 * @author Ethan VILLESSECHE
 */
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

    static private TextView poids_ruche;
    static private TextView temperature_interieure_ruche;
    static private TextView temperature_exterieure_ruche;
    static private TextView humidite_interieure_ruche;
    static private TextView humidite_exterieure_ruche;
    static private TextView pression_ruche;
    static private TextView ensoleillement_ruche;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ruche);

        nom_ruche = (TextView) this.findViewById(R.id.nom_ruche);
        topic_ruche = (TextView) this.findViewById(R.id.topic_ruche);
        message_ruche = (TextView) this.findViewById(R.id.message_ruche);
        poids_ruche = (TextView) this.findViewById(R.id.poids_ruche);
        temperature_interieure_ruche = (TextView) this.findViewById(R.id.temperature_interieure_ruche);
        temperature_exterieure_ruche = (TextView) this.findViewById(R.id.temperature_exterieure_ruche);
        humidite_interieure_ruche = (TextView) this.findViewById(R.id.humidite_interieure_ruche);
        humidite_exterieure_ruche = (TextView) this.findViewById(R.id.humidite_exterieure_ruche);
        pression_ruche = (TextView) this.findViewById(R.id.pression_ruche);
        ensoleillement_ruche = (TextView) this.findViewById(R.id.ensoleillement_ruche);



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

    /**
     * @brief affiche le dernier message JSON recu
     * @param message
     */
    public void afficherJSON(String message)
    {
        message_ruche.setText("Message : " + message);
    }

    /**
     * @brief paramete la communication avec le ttn
     *
     * @param deviceID
     */
    private void communiquerTTN(final String deviceID)
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
                if(estBonneRuche(deviceID, mqttMessage.toString()))
                {
                    afficherJSON(mqttMessage.toString());
                    CommunicationMQTT.decoderMessage(mqttMessage.toString(),ruche);
                    String horodatage = CommunicationMQTT.extraireHorodatage(mqttMessage.toString());
                    String horodatageFormate = formaterHorodatge(horodatage);
                    Log.d(TAG, "Horodatage formaté : " + horodatageFormate);
                }

            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
            }
        });
    }

    /**
     * @brief verifie si le json reçu correspond a la ruche souhaité
     * @param deviceID
     * @param message
     * @return
     */
    private boolean estBonneRuche(String deviceID,String message)
    {
        try
        {
            JSONObject json = null;
            Iterator<String> it = null;

            json = new JSONObject(message);
            int port = json.getInt("port");

            it = json.keys();
            while (it.hasNext())
            {
                String cle = it.next();
                Log.i(TAG, "clé = " + cle);
                Log.i(TAG, "valeur = " + json.getString(cle));
                //Log.i(TAG, "type = " + json.get(cle).getClass());

                if (cle.equals("dev_id"))
                {
                    if(json.getString(cle).equals(deviceID)) {
                        return true;
                    }
                }
            }
            return false;
        }
        catch (JSONException e)
        {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * @brief formate l'horodatage
     * @param horodatage
     * @return String
     */
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

    /**
     * @brief affichie le poid dans le layout
     * @param message
     */
    static public void afficherPoids(int message)
    {
        poids_ruche.setText("Poids : " + message + "kg");
    }
    public void setPoids(int poids)
    {
        ruche.setPoids(poids);
    }
    /**
     * @brief affichie la Temperature interieure  dans le layout
     * @param message
     */
    static public void afficherTemperatureInterieure(String message)
    {
        temperature_interieure_ruche.setText("Temperature interieure : " + message + " °C");
    }
    /**
     * @brief affichie la Temperature exterieure dans le layout
     * @param message
     */
    static public void afficherTemperatureExterieure(String message)
    {
        temperature_exterieure_ruche.setText("Temperature exterieure : " + message + " °C");
    }
    /**
     * @brief affichie l'humiditer interieure dans le layout
     * @param message
     */
    static public void afficherHumiditeInterieure(String message)
    {
        humidite_interieure_ruche.setText("Humidité interieure : " + message + " %");
    }
    /**
     * @brief affichie l'humiditer exterieure dans le layout
     * @param message
     */
    static public void afficherHumiditerExterieure(String message)
    {
        humidite_exterieure_ruche.setText("Humidité exterieure : " + message+ " %");
    }
    /**
     * @brief affichie la pression  dans le layout
     * @param message
     */
    static public void afficherPression(String message)
    {
        pression_ruche.setText("Pression atmosphérique : " + message + " hPa");
    }
    /**
     * @brief affichie l'Ensoleillement dans le layout
     * @param message
     */
    static public void afficherEnsoleillement(String message)
    {
        ensoleillement_ruche.setText("Ensoleillement : " + message + " lux");
    }

}

