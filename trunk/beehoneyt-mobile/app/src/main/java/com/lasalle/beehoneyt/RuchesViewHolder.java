package com.lasalle.beehoneyt;

import android.content.Intent;
import android.view.View;
import android.widget.TextView;

import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;

import de.hdodenhof.circleimageview.CircleImageView;


public class RuchesViewHolder extends RecyclerView.ViewHolder{

    private static final String TAG = "RuchesViewHolder";

    final TextView nom;
    final TextView info;
    final TextView poids;
    CircleImageView image;
    CardView cardview;
    private Ruche ruche;


    public RuchesViewHolder(final View itemView) {
        super(itemView);

        image = itemView.findViewById(R.id.circle_image);
        nom = ((TextView) itemView.findViewById(R.id.nom));
        info = ((TextView) itemView.findViewById(R.id.info));
        poids = ((TextView) itemView.findViewById(R.id.poids));

        cardview= itemView.findViewById(R.id.card_view);
    }


    public void afficher(Ruche ruche)
    {
        this.ruche = ruche;

        nom.setText(ruche.getNom());
        info.setText(ruche.getInfos());
        poids.setText(ruche.getPoids() + " Kg");
    }
}
