package application;

import javafx.beans.property.SimpleStringProperty;

public class Reservation {
    private final SimpleStringProperty nom = new SimpleStringProperty();
    private final SimpleStringProperty ville = new SimpleStringProperty();
    private final SimpleStringProperty num = new SimpleStringProperty();

    private final SimpleStringProperty prenom = new SimpleStringProperty();
    private final SimpleStringProperty date = new SimpleStringProperty();
    private final SimpleStringProperty heure = new SimpleStringProperty();
    private final SimpleStringProperty tarif = new SimpleStringProperty();
    private final SimpleStringProperty artiste = new SimpleStringProperty();

    Reservation(String cNom, String cVille, String cNum, String cPrenom, String cDate, String cHeure, String cTarif, String cArtiste)
    {
        this.nom.setValue(cNom);
        this.ville.setValue(cVille);
        this.num.setValue(cNum);
     
        this.prenom.setValue(cPrenom);
        this.date.setValue(cDate);
        this.heure.setValue(cHeure);
        this.tarif.setValue(cTarif);
        this.artiste.setValue(cArtiste);
    }

    public String getNom()
    {
        return nom.get();
    }

    public void setnom(String cNom)
    {
        nom.set(cNom);
    }
    
    public SimpleStringProperty getNomProperty()
    {
        return nom;
    }
    
    public String getVille()
    {
        return ville.get();
    }

    public void setVille(String cVille)
    {
        ville.set(cVille);
    }

    public SimpleStringProperty getVilleProperty()
    {
        return ville;
    }
    
    public String getNum()
    {
        return num.get();
    }

    public void setNum(String fName)
    {
        num.set(fName);
    }
    
    public SimpleStringProperty getNumProperty()
    {
        return num;
    }

    public String getPrenom()
    {
        return prenom.get();
    }

    public void setPrenom(String cPrenom)
    {
        prenom.set(cPrenom);
    }

    public SimpleStringProperty getPrenomProperty()
    {
        return prenom;
    }

    public String getDate()
    {
        return date.get();
    }

    public void setDate(String cDate)
    {
        date.set(cDate);
    }

    public SimpleStringProperty getDateProperty()
    {
        return date;
    }

    public String getHeure()
    {
        return heure.get();
    }

    public void setHeure(String cHeure)
    {
        heure.set(cHeure);
    }

    public SimpleStringProperty getHeureProperty()
    {
        return heure;
    }

    public String getTarif()
    {
        return tarif.get();
    }

    public void setTarif(String cTarif)
    {
        tarif.set(cTarif);
    }

    public SimpleStringProperty getTarifProperty()
    {
        return tarif;
    }

    public String getArtiste()
    {
        return artiste.get();
    }

    public void setArtiste(String cArtiste)
    {
        artiste.set(cArtiste);
    }

    public SimpleStringProperty getArtisteProperty()
    {
        return artiste;
    }
}
