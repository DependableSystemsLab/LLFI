package application;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import application.Controller;
import application.InputYaml.RuntimeOption;

/**
 * Does the fault injection as well as updating the progress bar
 */
public class ProgressBarController implements Initializable {

	private int totalRunCount = 0;
	private int currentCount = 0;
	
	@FXML
	private ProgressBar progressBar;
	@FXML
	private ProgressIndicator indicator;
	@FXML
	private TextField runText;

	@FXML
	private void onClickOkHandler(ActionEvent event) {
		Node source = (Node) event.getSource();
		Stage stage = (Stage) source.getScene().getWindow();
		stage.close();
	}

	@Override
	public void initialize(URL url, ResourceBundle rb) {
		InputYaml input = new InputYaml();
		input.load(new File(Controller.currentProgramFolder + "/input.yaml"));
		List<RuntimeOption> list = input.getRuntimeOptions();

		for (RuntimeOption r : list) {
			totalRunCount += r.numOfRuns;
		}

		// #SFIT
		if (Controller.isBatchMode) {
			totalRunCount *= Controller.selectedSoftwareFailures.size();
		}
		runText.setText(Integer.toString(totalRunCount));
		progressBar.setVisible(true);

		// do fault injection
		Task<Void> fi = new FaultInjection();
		progressBar.progressProperty().bind(fi.progressProperty());
		indicator.progressProperty().bind(fi.progressProperty());
		new Thread(fi).start();
	}
	
	private class FaultInjection extends Task<Void> {
		private boolean errorFlag;

		@Override
		protected Void call() {
			// resets the console
			Controller.console = new ArrayList<String>();
			Controller.errorString = new ArrayList<String>();

			// #SFIT
			// changes how injection is done if we are in batch mode
			String execName;
			if (!Controller.isBatchMode) {
				execName = "bin/injectfault " + Controller.currentProgramFolder
						+ "/llfi/" + Controller.currentProgramFolder
						+ "-faultinjection.exe " + Controller.inputString;
			} else {
				execName = "bin/batchInjectfault "
						+ Controller.currentProgramFolder + "/"
						+ Controller.currentProgramFolder + ".ll "
						+ Controller.inputString;
			}

			// add the log to the GUI console
			Controller.console.add("$ " + Controller.llfibuildPath + execName + "\n");
			Controller.errorString.add("$ " + Controller.llfibuildPath + execName + "\n");

			try {
				// start the fault injection script
				ProcessBuilder p = new ProcessBuilder("/bin/tcsh", "-c",
						Controller.llfibuildPath + execName);
				p.redirectErrorStream(true);
				Process pr = p.start();

				// get the output from the script
				BufferedReader in = new BufferedReader(new InputStreamReader(
						pr.getInputStream()));

				// read the output
				String line;
				while ((line = in.readLine()) != null) {
					// print line to GUI console and error log
					Controller.console.add(line);
					Controller.errorString.add(line);

					if (line.contains("error") || line.contains("Error")
							|| line.contains("ERROR")) {
						errorFlag = true;
					}
					
					// update progress bar
					if (line.contains("%")) {
						updateProgress(++currentCount, totalRunCount);
					}
				}

				// wait for process to finish
				pr.waitFor();
				in.close();
			} catch (IOException | InterruptedException e) {
				System.err.println("ERROR: Fault injection failed!");
				e.printStackTrace();
			}

			// run this in the main UI thread
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					if (errorFlag == true) {
						// display error
						try {
							Parent root = FXMLLoader.load(getClass()
									.getClassLoader().getResource(
											"application/ErrorDisplay.fxml"));
							Stage stage = new Stage();
							stage.setTitle("Error");
							stage.setScene(new Scene(root, 450, 100));
							stage.show();
						} catch (IOException e) {
							System.err
									.println("ERROR: ProgressBarController: unable to load ErrorDisplay.fxml");
							e.printStackTrace();
						}
					} else {
						// reset error log
						Controller.errorString = new ArrayList<>();
					}

				}
			});
			// finish
			return null;
		}
	}
}