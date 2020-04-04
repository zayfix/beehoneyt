package com.lasalle.beehoneyt;

/**
 * @file CommunicationMQTT.java
 * @brief Déclaration de la classe CommunicationMQTT
 * @author Ethan VILLESSECHE
 */

import android.content.Context;
import android.util.Log;
import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.DisconnectedBufferOptions;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;
import java.util.Iterator;

/**
 * @class CommunicationMQTT
 * @brief Déclaration de la classe CommunicationMQTT
 */
public class CommunicationMQTT
{
    /**
     * Constantes
     */
    private static final String TAG = "CommunicationMQTT";
    /**
     * Attributs
     */
    static public MqttAndroidClient mqttAndroidClient;
    /**
     * @todo Prévoir autre chose pour configurer/stocker les paramètres de connexion TTN
     */
    private String serverUri = "tcp://eu.thethings.network:1883"; //!<  lien vers TTN
    static public String clientId = "mes_ruches"; //!< Application ID
    private String username = "mes_ruches"; //!<  nom d'utilisateur
    private String password = "ttn-account-v2.vC-aqMRnLLzGkNjODWgy81kLqzxBPAT8_mE-L7U2C_w"; //!<  mot de passe TTN
    /**
     * @brief Constructeur de la classe CommunicationMQTT
     *
     * @fn CommunicationMQTT::CommunicationMQTT(Context context)
     * @param context
     */
    public CommunicationMQTT(Context context)
    {
        Log.v(TAG, "ClientMQTT " + clientId);
        mqttAndroidClient = new MqttAndroidClient(context, serverUri, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended()
        {
            @Override
            public void connectComplete(boolean b, String s)
            {
                Log.w(TAG, "connectComplete() " + s + " -> " + mqttAndroidClient.isConnected());
            }

            @Override
            public void connectionLost(Throwable throwable)
            {
                Log.w(TAG, "connectionLost()");
            }

            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.w(TAG, "messageArrived() " + topic + " " + mqttMessage.toString());
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
                Log.w(TAG, "deliveryComplete()");
            }
        });

        connecter();
    }

    /**
     * @brief
     *
     * @fn CommunicationMQTT::setCallback(MqttCallbackExtended callback)
     * @param callback le retour
     */
    static public void setCallback(MqttCallbackExtended callback)
    {
        mqttAndroidClient.setCallback(callback);
    }

    /**
     * @brief connection au ttn
     *
     * @fn CommunicationMQTT::connecter()
     */
    private void connecter()
    {
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setAutomaticReconnect(true);
        mqttConnectOptions.setCleanSession(false);
        mqttConnectOptions.setUserName(username);
        mqttConnectOptions.setPassword(password.toCharArray());

        try
        {
            Log.d(TAG, "connecter() " + serverUri + " " + clientId);
            mqttAndroidClient.connect(mqttConnectOptions, null, new IMqttActionListener()
            {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    DisconnectedBufferOptions disconnectedBufferOptions = new DisconnectedBufferOptions();
                    disconnectedBufferOptions.setBufferEnabled(true);
                    disconnectedBufferOptions.setBufferSize(100);
                    disconnectedBufferOptions.setPersistBuffer(false);
                    disconnectedBufferOptions.setDeleteOldestMessages(false);
                    mqttAndroidClient.setBufferOpts(disconnectedBufferOptions);
                    Log.d(TAG, "onSuccess() " + serverUri + " " + clientId);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG, "onFailure() " + serverUri + " " + clientId + " " + exception.toString());
                }
            });
        }
        catch (MqttException ex)
        {
            ex.printStackTrace();
        }
    }

    /**
     * @brief reconnection au ttn
     *
     * @fn CommunicationMQTT::reconnecter()
     */
    public void reconnecter()
    {
        Log.w(TAG, "mqttAndroidClient : reconnecter");
        if (estConnecte())
            deconnecter();
        connecter();
    }

    /**
     * @brief deconetion du ttn
     *
     * @fn CommunicationMQTT::deconnecter()
     */
    public void deconnecter()
    {
        Log.d(TAG, "deconnecter() " + serverUri + " " + clientId);
        try {
            IMqttToken disconToken = mqttAndroidClient.disconnect();
            disconToken.setActionCallback(new IMqttActionListener()
            {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.d(TAG, "onSuccess() : " + serverUri + " " + clientId);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG, "onFailure() " + serverUri + " " + clientId + " " + exception.toString());
                }
            });
        }
        catch (MqttException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * @brief boolaine retourne si le ttn est connecter
     *
     * @fn CommunicationMQTT::estConnecte()
     */
    static public boolean estConnecte()
    {
        Log.w(TAG, "estConnecte() " + mqttAndroidClient.isConnected());

        return mqttAndroidClient.isConnected();
    }

    /**
     * @brief S'abone a un device
     *
     * @fn CommunicationMQTT::souscrireTopic(String topic)
     * @param topic le topic au quel s'aboner
     */
    static public boolean souscrireTopic(String topic)
    {
        String subTopic = clientId + "/devices/" + topic + "/up";
        Log.w(TAG, "MqttAndroidClient : souscrire -> " + subTopic);
        try
        {
            final boolean[] retour = {false};
            mqttAndroidClient.subscribe(subTopic, 0, null, new IMqttActionListener()
            {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.w(TAG, "souscrire : onSuccess");
                    retour[0] = true;
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.w(TAG, "souscrire : onFailure");
                    retour[0] = false;
                }
            });
            return retour[0];
        }
        catch (MqttException ex)
        {
            Log.e(TAG, "souscrire : exception");
            ex.printStackTrace();
            return false;
        }
    }

    /**
     * @brief decode le message recu
     *
     * @fn CommunicationMQTT::decoderMessage(String message)
     * @param message le message reçu
     * @param ruche
     */
    static public void decoderMessage(String message, Ruche ruche )
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

                if (cle.equals("payload_fields"))
                {
                    decoderPayload(port, json.getString(cle), ruche);
                }
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * @brief d'ecode le payload
     * @param port
     * @param payload
     * @param ruche
     */
    static public void decoderPayload(int port, String payload, Ruche ruche)
    {

        Log.i(TAG, "port = " + port );
        if ( port == 3)
        {
            decoderDonneInterieure(payload, ruche);
        }
        else
            {
            decoderDonneExterieure(payload, ruche);
        }
    }

    /**
     * @brief decode les donné de l'interieur de la ruche
     * @param payload
     * @param ruche
     */
    static public void decoderDonneInterieure(String payload, Ruche ruche)
    {
        try
        {
            JSONObject json = null;
            json = new JSONObject(payload);

            Iterator<String> it = null;
            it = json.keys();
            while (it.hasNext())
            {
                String cle = it.next();
                if (cle.equals("temperature"))
                {
                    Log.i(TAG, "temperature = " + json.getString(cle));
                    RucheActivity.afficherTemperatureInterieure(json.getString(cle));
                }
                else if (cle.equals("humidite"))
                {
                    Log.i(TAG, "humidite = " + json.getString(cle));
                    RucheActivity.afficherHumiditeInterieure(json.getString(cle));
                }
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * @brief decode les donné de l'exterieure de la ruche
     * @param payload
     * @param ruche
     */
    static public void decoderDonneExterieure(String payload, Ruche ruche)
    {
        try {
            JSONObject json = null;
            json = new JSONObject(payload);

            Iterator<String> it = null;
            it = json.keys();
            while (it.hasNext()) {
                String cle = it.next();
                if (cle.equals("temperature"))
                {
                    Log.i(TAG, "temperature = " + json.getString(cle));
                    RucheActivity.afficherTemperatureExterieure(json.getString(cle));
                }
                else if (cle.equals("humidite"))
                {
                    Log.i(TAG, "humidite = " + json.getString(cle));
                    RucheActivity.afficherHumiditerExterieure(json.getString(cle));
                }
                else if (cle.equals("ensoleillement"))
                {
                    Log.i(TAG, "ensoleillement = " + json.getString(cle));
                    RucheActivity.afficherEnsoleillement(json.getString(cle));
                }
                else if (cle.equals("pression"))
                {
                    Log.i(TAG, "pression = " + json.getString(cle));
                    RucheActivity.afficherPression(json.getString(cle));
                }
                else if (cle.equals("poids"))
                {
                    double poids = json.getDouble(cle);
                    poids = poids * 0.01;
                    Log.i(TAG, "poids = " + json.getInt(cle));
                    ruche.setPoids(json.getInt(cle));
                    RucheActivity.afficherPoids(json.getInt(cle));
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    /**
     * @brief extrait l'horodatage
     * @param message
     */
    static public String extraireHorodatage(String message)
    {
        String date = "";

        try
        {
            JSONObject json = null;
            json = new JSONObject(message);

            date = json.getJSONObject("metadata").getString("time");
            date = date.substring(0, 10) + " " + date.substring(11, 19);
            Log.d(TAG, "Horodatage : " + date + " <- time : " + json.getJSONObject("metadata").getString("time"));

        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }

        return  date;
    }
}
