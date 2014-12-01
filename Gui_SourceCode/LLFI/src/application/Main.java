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
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;

public class Main extends Application{

    static public String LLFI_BUILD_ROOT = "";

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

            final Parameters params = getParameters();
            final List<String> parameters = params.getRaw();
            LLFI_BUILD_ROOT = !parameters.isEmpty() ? parameters.get(0)+"/" : Paths.get("").toAbsolutePath().toString()+"/../";
            System.out.println("Current LLFI_BUILD_ROOT path is: " + LLFI_BUILD_ROOT);
            Controller.llfibuildPath = LLFI_BUILD_ROOT;

			primaryStage.setScene(new Scene(root));
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
