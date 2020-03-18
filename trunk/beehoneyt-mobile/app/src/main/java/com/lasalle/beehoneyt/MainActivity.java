package com.lasalle.beehoneyt;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.os.Bundle;
import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @file MainActivity.java
 * @brief Déclaration de la classe MainActivity
 * @author Ethan VILLESSECHE
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
        Log.d(TAG, "onCreate: started");

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

        recupererRuches();
    }

    /**
     * @brief Méthode pour récupérer les ruches
     *
     * @fn MainActivity::recupererRuches()
     */
    private void recupererRuches()
    {
        List<Ruche> listeRuches = Arrays.asList(
                new Ruche("Ruche_Alexis", "Alexis", 1148),
                new Ruche("ruche_1", "Simulateur", 1122),
                new Ruche("ruche_2", "Simulateur", 475),
                new Ruche("ruche_3", "Simulateur", 570)
        );

        ruches.clear();
        for(int i = 0; i < listeRuches.size(); i++)
        {
            ruches.add(listeRuches.get(i));
        }

        rafraichir(ruches);
    }

    /**
     * @brief Méthode pour rafraîchir la liste des ruches connues
     *
     * @fn MainActivity::rafraichir(List<Ruche> ruches)
     */
    private void rafraichir(List<Ruche> ruches)
    {
        swipeRefreshLayout.setRefreshing(false);
        adapter.notifyDataSetChanged();
    }
}
