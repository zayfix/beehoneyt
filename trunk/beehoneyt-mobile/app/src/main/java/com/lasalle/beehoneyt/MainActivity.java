package com.lasalle.beehoneyt;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    
    private static final int NB_RUCHE = 5;

    private RecyclerView recyclerView; // la vue
    private RecyclerView.Adapter adapter; // l'adaptateur
    private RecyclerView.LayoutManager layoutManager; // le gestionnaire de mise en page
    private List<Ruche> ruches = new ArrayList<>();
    private SwipeRefreshLayout swipeRefreshLayout;

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
                recupererDonnees();
            }
        });

        recyclerView = (RecyclerView) findViewById(R.id.listeRuche);
        recyclerView.setHasFixedSize(true);

        layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);

        adapter = new RucheAdapter(this, ruches);
        recyclerView.setAdapter(adapter);

        recupererDonnees();
    }

    private void recupererDonnees() {
        final int nb = NB_RUCHE;
        List<Ruche> tous = Arrays.asList(
                new Ruche("Simu", "Alexis", 1148),
                new Ruche("Ruche_2", "Aleksander Aamodt", 1122),
                new Ruche("Ruche_3", "Henrik", 475),
                new Ruche("Ruche_4", "Aamodt", 570),
                new Ruche("Ruche_5", "Thomas", 465)
        );

        ruches.clear();
        for(int i =0; i < nb; i++)
        {
            ruches.add(tous.get(i));
        }

        rafraichir(ruches);
    }

    private void rafraichir(List<Ruche> ruches)
    {
        swipeRefreshLayout.setRefreshing(false);
        adapter.notifyDataSetChanged();
    }

}
