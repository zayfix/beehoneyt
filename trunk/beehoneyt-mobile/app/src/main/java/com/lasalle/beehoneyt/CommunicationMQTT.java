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
    public MqttAndroidClient mqttAndroidClient;
    /**
     * @todo Prévoir autre chose pour configurer/stocker les paramètres de connexion TTN
     */
    private String serverUri = "tcp://eu.thethings.network:1883";
    private String clientId = "mes_ruches";
    private String username = "mes_ruches"; // <ApplicationID>
    private String password = "ttn-account-v2.vC-aqMRnLLzGkNjODWgy81kLqzxBPAT8_mE-L7U2C_w";
    private boolean connecte;

    public CommunicationMQTT(Context context)
    {
        Log.v(TAG, "ClientMQTT " + clientId);
        connecte = false;
        mqttAndroidClient = new MqttAndroidClient(context, serverUri, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended()
        {
            @Override
            public void connectComplete(boolean b, String s)
            {
                Log.w(TAG, "connectComplete() " + s);
            }

            @Override
            public void connectionLost(Throwable throwable)
            {
                Log.w(TAG, "connectionLost()");
                connecte = false;
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

    public void setCallback(MqttCallbackExtended callback)
    {
        mqttAndroidClient.setCallback(callback);
    }

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
                    connecte = true;
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

    public void deconnecter()
    {
        Log.d(TAG, "deconnecter() " + serverUri + " " + clientId);
        try
        {
            IMqttToken disconToken = mqttAndroidClient.disconnect();
            disconToken.setActionCallback(new IMqttActionListener()
            {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.d(TAG, "onSuccess() : " + serverUri + " " + clientId);
                    connecte = false;
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

    public boolean estConnecte()
    {
        Log.w(TAG,"estConnecte() " + mqttAndroidClient.isConnected() + "" + connecte);

        //return mqttAndroidClient.isConnected();
        return connecte;
    }
}
