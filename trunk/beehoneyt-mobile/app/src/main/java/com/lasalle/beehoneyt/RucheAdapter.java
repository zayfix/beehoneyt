package com.lasalle.beehoneyt;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.ContextThemeWrapper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.io.Serializable;
import java.lang.reflect.Array;
import java.util.List;


public class RucheAdapter extends RecyclerView.Adapter<RuchesViewHolder>
{
    private static final String TAG = "RucheAdapter";
    private  Context mContext;
    private List<Ruche> ruches = null;

    public RucheAdapter(Context context, List<Ruche> ruches)
    {
        if(ruches != null)
        {
            this.ruches = ruches;
            mContext = context;
        }
    }

    @Override
    public RuchesViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType)
    {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.ruche, parent, false);
        return new RuchesViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RuchesViewHolder holder, final int position)
    {
        Log.d(TAG, "onBindViewHolder: appel.");

        final Ruche ruche = ruches.get(position);
        holder.afficher(ruche);

        holder.cardview.setOnClickListener(new View.OnClickListener(){
            @Override
            public  void onClick(View view) {
                Log.d(TAG, "onClick: click sur : " + ruche);
                Toast.makeText(mContext, ruche.getNom(), Toast.LENGTH_SHORT).show();

                Intent intent = new Intent(mContext, RucheActivity.class);
                intent.putExtra("Ruche", (Serializable) ruche);
                mContext.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount()
    {
        if(ruches != null)
            return ruches.size();
        return 0;
    }

}
