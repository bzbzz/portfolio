package application;

import java.io.IOException;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class FenListeRes extends Stage {
    private TableView<Reservation> table = new TableView<Reservation>();
    private final ObservableList<Reservation> data
            = FXCollections.observableArrayList(
                    new Reservation("Nathan", "Pleuven", "270301", "Thuault", "27/09/24", "20h30", "Senior", "France Gall"),
                    new Reservation("Deonna", "Rennes", "160505", "Naicker", "16/09/24", "20h30", "Jeune", "Bon Entendeur"),
                    new Reservation("Eliott", "Saint-Brieuc", "120202", "Janot", "12/09/24", "20h30", "Abonné", "Mika"),
                    new Reservation("Nidhish", "Pondichéry", "300305", "Ramane", "30/09/24", "20h30", "Abonné", "Ed Sheeran")
            );

    public FenListeRes() throws IOException
    {
        Scene scene = new Scene(new Group());
        this.setScene(scene);
        this.setTitle("Réservations");
        this.setWidth(650);
        this.setHeight(600);

        final Label label = new Label("Liste des réservations");
        label.setFont(new Font("Arial", 20));

        table.setEditable(true);

        TableColumn nomCol = new TableColumn("Nom");
        nomCol.setMinWidth(200);
        nomCol.setCellValueFactory(
                new PropertyValueFactory<Reservation, String>("nom"));

        TableColumn villeCol = new TableColumn("Ville");
        villeCol.setMinWidth(200);
        villeCol.setCellValueFactory(
                new PropertyValueFactory<Reservation, String>("ville"));

        TableColumn numCol = new TableColumn("Numéro");
        numCol.setMinWidth(200);
        numCol.setCellValueFactory(
                new PropertyValueFactory<Reservation, String>("num"));

        FilteredList<Reservation> flReservation = new FilteredList(data, p -> true);//Pass the data to a filtered list
        table.setItems(flReservation);//Set the table's items using the filtered list
        table.getColumns().addAll(nomCol, villeCol, numCol);

        //Adding ChoiceBox and TextField here!
        ChoiceBox<String> choiceBox = new ChoiceBox();
        choiceBox.getItems().addAll("Nom", "Ville", "Numéro");
        choiceBox.setValue("Nom");

        TextField textField = new TextField();
        textField.setPromptText("Rechercher ici");
        textField.textProperty().addListener((obs, oldValue, newValue) -> {
            switch (choiceBox.getValue())//Switch on choiceBox value
            {
                case "Nom":
                    flReservation.setPredicate(p -> p.getNom().toLowerCase().contains(newValue.toLowerCase().trim()));//filter table by nom name
                    break;
                case "Ville":
                    flReservation.setPredicate(p -> p.getVille().toLowerCase().contains(newValue.toLowerCase().trim()));//filter table by last name
                    break;
                case "Numéro":
                    flReservation.setPredicate(p -> p.getNum().toLowerCase().contains(newValue.toLowerCase().trim()));//filter table by email
                    break;
            }
        });

        choiceBox.getSelectionModel().selectedItemProperty().addListener((obs, oldVal, newVal)
                -> {
            if (newVal != null) {
                textField.setText("");
            }
        });

        HBox hBox = new HBox(choiceBox, textField);//Add choiceBox and textField to hBox
        hBox.setAlignment(Pos.CENTER);//Center HBox
        // Add a close button
        Button closeButton = new Button("Fermer");
        closeButton.setOnAction(e -> Main.fermerFenListeRes());
        closeButton.setCancelButton(true);
        // Bouton pour imprimer
        Button imprimButton = new Button("Imprimer");
        imprimButton.setDefaultButton(true);
        // imprimButton is only active when a reservation is selected
        imprimButton.disableProperty().bind(table.getSelectionModel().selectedItemProperty().isNull());
        // When imprimButton is clicked, print the selected reservation
        imprimButton.setOnAction(e -> Main.afficherFenImprim(table.getSelectionModel().getSelectedItem()));

        // Add a Hbox
        HBox hBoxBoutons = new HBox();
        hBoxBoutons.getChildren().addAll(imprimButton, closeButton);
        hBoxBoutons.setSpacing(10);
        hBoxBoutons.setAlignment(Pos.CENTER_RIGHT);
        
        final VBox vbox = new VBox();
        vbox.setSpacing(5);
        vbox.setPadding(new Insets(10, 0, 0, 10));
        vbox.getChildren().addAll(label, table, hBox, hBoxBoutons);

        ((Group) scene.getRoot()).getChildren().addAll(vbox);
        
        this.setScene(scene);
    }
}
