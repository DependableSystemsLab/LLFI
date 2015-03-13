package application;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import application.Controller;

@Deprecated
public class TraceController implements Initializable{

	@FXML 
	private TextField profileNameText;


	@FXML
	private void onClickTraceHandler(ActionEvent event){



		Node  source = (Node)  event.getSource(); 
		Stage stage  = (Stage) source.getScene().getWindow();
		stage.close();
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		// TODO

	}
}
