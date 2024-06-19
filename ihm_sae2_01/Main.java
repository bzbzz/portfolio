package application;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Main extends Application
{
    private static FenImprim fImprim;
    private static FenListeRes fListeRes;
    private FenSalle fSalle;
    
    public static void main(String[] args)
    {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception
    {
        fSalle = new FenSalle();
        fSalle.initModality(Modality.APPLICATION_MODAL);
        fSalle.show();
        
        fListeRes = new FenListeRes();
        fListeRes.initModality(Modality.APPLICATION_MODAL);

        fImprim = new FenImprim();
        fImprim.initModality(Modality.APPLICATION_MODAL);
    }

    public static void afficherFenImprim(Reservation res)
    {
        fImprim.afficher(res);
        fImprim.show();
    }

    public static void fermerFenImprim()
    {
        fImprim.close();
    }
    
    public static void afficherListRes()
    {
    	fListeRes.show();
    }
    
    public static void fermerFenListeRes()
    {
    	fListeRes.close();
    }

    public static void fermerAppli()
    {
        System.exit(0);
    }
    
    
}