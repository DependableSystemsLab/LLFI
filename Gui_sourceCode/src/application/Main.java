package application;
	
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.fxml.FXMLLoader;

import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;

public class Main extends Application{
	@Override
	public void start(Stage primaryStage) {
		try {
			//BorderPane root = new BorderPane();
			//Scene scene = new Scene(root,400,400);
			//scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			//primaryStage.setScene(scene);
			Parent root = FXMLLoader.load(getClass().getResource("Sample.fxml"));
			//primaryStage.setResizable(false);
			//primaryStage.initStyle(StageStyle.UTILITY);
			primaryStage.setTitle("LLFI");
			primaryStage.setScene(new Scene(root));
			primaryStage.show();
			
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
	
		//File yamlFile = new File("C:\\Nithya\\sample_files\\input.txt");
		launch(args);
	}
}
