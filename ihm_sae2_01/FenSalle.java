package application;

import java.io.IOException;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class FenSalle extends Stage {
	private static final int BUTTON_PADDING = 8;
	private static final int NUM_BUTTON_LINES = 15;
	private static final int BUTTONS_PER_LINE = 22;

	public FenSalle() throws IOException
	{
		// EN-TETE
		HBox enTete = new HBox();
		enTete.setAlignment(Pos.CENTER);
		ImageView logo = new ImageView("/logo.png");
		logo.setFitHeight(100);
		logo.setFitWidth(100);
		Label titre = new Label("PLAN DE LA SALLE");
		titre.setStyle("-fx-font-size: 50;" + "-fx-font-weight: bold;" + "-fx-text-fill: #000000");
		enTete.getChildren().addAll(logo, titre);
		enTete.setPadding(new Insets(10, 10, 10, 10));
		enTete.setSpacing(10);
		enTete.setStyle("-fx-background-color: #bbbbbb");
		
		
		// GRID (Plan de la salle)
		GridPane grid = new GridPane();
		grid.setPadding(new Insets(BUTTON_PADDING));
		grid.setHgap(BUTTON_PADDING);
		grid.setVgap(BUTTON_PADDING);

		for (int r = 0; r < NUM_BUTTON_LINES; r++) {
			for (int c = 0; c < BUTTONS_PER_LINE; c++) {
				int number = NUM_BUTTON_LINES * r + c;
				Button button = new Button(String.valueOf(number));
				configButton(button);
				res(button, c, r);
				grid.add(button, c, r);
			}
		}

		//grid.setGridLinesVisible(true);
		grid.setStyle("-fx-border-color: #cccccc;" + "-fx-border-width: 2;" + "-fx-background-color: #dddddd");
		grid.setAlignment(Pos.CENTER);

		// Add a button to close the window
		Button closeButton = new Button("Fermer");
		closeButton.setOnAction(e -> Main.fermerAppli());
		closeButton.setPrefSize(140, 80);
		closeButton.setCancelButton(true);
		
		// Add a button to show the list of reservations
		Button listButton = new Button("Liste des réservations");
		listButton.setOnAction(e -> Main.afficherListRes());
		listButton.setPrefSize(160, 80);
		listButton.setDefaultButton(true);
		
		HBox footer = new HBox();
		footer.setAlignment(Pos.CENTER);
		footer.setPadding(new Insets(10, 10, 10, 10));
		footer.setSpacing(650);
		footer.getChildren().addAll(listButton, closeButton);
		footer.setStyle("-fx-background-color: #cccccc");

		
		
		VBox mainBox = new VBox(enTete, grid, footer);
		mainBox.setAlignment(Pos.CENTER);
		Scene scene = new Scene(mainBox);
		this.setScene(scene);
		this.setTitle("Plan de la salle");
		this.setWidth(1200);
		this.setHeight(800);
	}

	private void configButton(Button button) {
		button.setPrefSize(35, 35);
		button.setStyle("-fx-font-size: 10;" + "-fx-background-color: #74B72E;" + "-fx-border-color: #000000");
		button.setOnAction(e -> {
			if (button.getStyle().equals("-fx-font-size: 10;" + "-fx-background-color: #74B72E;" + "-fx-border-color: #000000")) {
				button.setStyle("-fx-font-size: 10;" + "-fx-background-color: #b72e74;" + "-fx-border-color: #000000");
			} else {
				button.setStyle("-fx-font-size: 10;" + "-fx-background-color: #74B72E;" + "-fx-border-color: #000000");
			}	
		});
	}
	
	private void res(Button button, int c, int r) {
		if (c == 21 && ( r == 4 || r == 5  || r == 6 || r == 7)) {
			button.setStyle("-fx-font-size: 10;" + "-fx-background-color: #b72e74;" + "-fx-border-color: #000000");
		}
	}
}
