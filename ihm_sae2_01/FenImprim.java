package application;

import java.io.IOException;

import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class FenImprim extends Stage {
     private Label prenom = new Label();
     private Label nom = new Label();
     private Label num = new Label();

     private Label date = new Label();
     private Label heure = new Label();
     private Label tarif = new Label();
     private Label artiste = new Label();

	public FenImprim() throws IOException {
          Scene scene = new Scene(new Group());
          this.setScene(scene);
          this.setTitle("Impression");
          this.setWidth(1200);
          this.setHeight(450);

          String textStyle = "-fx-font-size: 50;" + "-fx-font-weight: bold;" + "-fx-text-fill: #000000";
          prenom.setStyle(textStyle);
          nom.setStyle(textStyle);
          num.setStyle("-fx-font-size: 40; -fx-text-fill: #000000");
          tarif.setStyle("-fx-font-size: 40; -fx-text-fill: #000000");
          date.setStyle("-fx-font-size: 40; -fx-text-fill: #000000");
          heure.setStyle("-fx-font-size: 40; -fx-text-fill: #000000");
          artiste.setStyle(textStyle);

          ImageView codeBarre = new ImageView("/codeBarre.png");
          codeBarre.rotateProperty().set(-90);

          VBox infoClientBox = new VBox();
          infoClientBox.setAlignment(Pos.CENTER);
          infoClientBox.setSpacing(20);

          infoClientBox.getChildren().addAll(prenom, nom, tarif, num);

          VBox infoRepre = new VBox(artiste, date, heure);
          infoRepre.setAlignment(Pos.CENTER_RIGHT);
          infoRepre.setSpacing(20);

          HBox mainBox = new HBox(codeBarre, infoClientBox, infoRepre);
          mainBox.setSpacing(60);
          mainBox.setStyle("-fx-background-color: #FFFFFF");
          mainBox.setAlignment(Pos.CENTER_LEFT);
          scene.setRoot(mainBox);
     }

     public void afficher(Reservation res) {
          prenom.setText(res.getPrenom());
          nom.setText(res.getNom());
          num.setText(res.getNum());
          date.setText(res.getDate());
          heure.setText(res.getHeure());
          tarif.setText(res.getTarif());
          artiste.setText(res.getArtiste());
          System.out.println("Impression ... ");
     }
}
