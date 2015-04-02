package application;


import java.util.List;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.ResourceBundle;
import java.util.concurrent.TimeUnit;
import java.util.Comparator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.sun.glass.ui.View;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Cursor;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.Slider;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.CheckBoxTableCell;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TableCell;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.util.Callback;
import javafx.stage.FileChooser;
import javafx.stage.DirectoryChooser;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import application.InstrumentController;
import javafx.stage.Stage;
import javafx.event.ActionEvent;  
import javafx.event.EventHandler;
public class Controller implements Initializable {

	@FXML
	private Button compiletoIrButton;
	@FXML
	private TextArea programTextArea;
	@FXML
	private ListView fileList;
	@FXML
	ObservableList<String> items;
	@FXML
	private TableView<Table> profilingTable;
	@FXML
	private TableColumn<Table,Integer> indexCount;
	@FXML
	private TableColumn<Table,Integer> cycleCount;
	@FXML
	private TableColumn<Table, String> failureType;
	@FXML
	private TableView<ResultTable> resultTable;
	@FXML
	private TableColumn<ResultTable,Integer> tFiRun;
	@FXML
	private TableColumn<ResultTable,String> failureClass;
	@FXML
	private TableColumn<ResultTable,String> failureMode;
	@FXML
	private TableColumn<ResultTable,String> functionName;
	@FXML
	private TableColumn<ResultTable,String> tFiType;
	@FXML
	private TableColumn<ResultTable,Integer> tFiIndex;
	@FXML
	private TableColumn<ResultTable,Integer> tFiCycle;
	@FXML
	private TableColumn<ResultTable,Integer> tFiRegIndex;
	@FXML
	private TableColumn<ResultTable,Integer> tFiBit;
	@FXML
	private TableColumn<ResultTable,String> tFiSdc;
	@FXML
	private TableColumn<ResultTable,String> tFiStatus;
	@FXML
	private TableColumn<ResultTable,String> tFiResult;
	@FXML
	private TableColumn<ResultTable,Boolean> tFiTrace;
	@FXML
	private CategoryAxis xAxis;
	@FXML
	private NumberAxis yAxis;
	@FXML
	private BarChart<Integer, String> resultSummary;
	@FXML
	private Label UploadLabel;
	@FXML
	private CheckBox showTraceOutputText;
	@FXML
	private Button instrumentButton;
	@FXML
	private Button profilingButton;
	@FXML
	private Button injectfaultButton;
	@FXML
	private Button runtimeButton;
	@FXML
	private Button tracegraphButton;
	@FXML
	private TextArea errorTextArea;
	@FXML
	private TextArea consoleTextArea;
	@FXML 
	private TextArea programInputText;
	@FXML 
	private Tab profilingTab;
	@FXML 
	private Tab faultStatus;
	@FXML 
	private Tab faultSummaryTab;
	@FXML 
	private Tab errorTab;
	@FXML 
	private Tab consoleTab;
	@FXML 
	private TabPane tabBottom;
	@FXML
	private ProgressBar progressBar;
	@FXML 
	private ProgressIndicator indicator;
	@FXML
	private ProgressBar progressBar1;
	@FXML
	private ProgressIndicator progressIndicator;
	XYChart.Series<Integer, String> series = new XYChart.Series<Integer,String>();
	static public String currentProgramFolder;
	static public String llfibuildPath=null;
	static public String zgrviewerPath =null;
	static public String psViewer=null;
	static public String currentFileName;
	public boolean checkFlag = true;
	public boolean indexStates =false;
	static public List<String> console;
	static public File currentFilePath=null;


	public ArrayList<String> fileNameLists = new ArrayList<>();
	public ArrayList<String> CompiledllFileNameLists = new ArrayList<>();
	public ArrayList<String> registerList = new ArrayList<>();
	private ArrayList<String> resultFileNameLists;
	private ArrayList<String> resultErrorFileNameLists;
	private ArrayList<String> resultOutputFileNameLists;
	private ArrayList<String> resultList;
	private ArrayList<String> TraceFileNameLists;
	private ArrayList<String> TraceDiffReportFileNameLists;

	private String indexBound;
	private String cycleBound;
	public int runCount = 0;
	public int totalRunCount = 0;
	public int currentCount = 0;
	/**
	 * Flag that fault injection is complete.
	 */
	public int faultInjectionCompleted = 0;
	public int crashedCount = 0;
	public int hangedCount = 0;
	public int sdcCount = 0;
	FileReader inputFile;
	FileReader errorFile;
	String str;
	String line;
	String subStr[];
	String fiTypefault;
	int index;@FXML
	int cycle;
	int regIndex;
	int bit;
	String status = "";
	String result ="";
	String sdc = "";
	Boolean trace = false;
	private List<List<String>> FileLists;
	private List<String> fileContent;
	private int fileCount = 0;
	private boolean errorFlag;
	private LinkedHashMap<String, List<String>> fileSelecMap = new LinkedHashMap<>();
	static public List<String> errorString = new ArrayList<String>();
	static public String inputString;

	public ArrayList<String> rowCount = new ArrayList<>();
	@FXML
	ObservableList<ResultTable> data1 =  FXCollections.observableArrayList() ;
	@FXML
	ObservableList<Table> data = FXCollections.observableArrayList();
	@FXML
	ObservableList<String> row = FXCollections.observableArrayList();
	public ArrayList<String> parameter = new ArrayList<>();
	
	// #SFIT
	/**
	 * Indicates whether we are doing hardware fault or software fault injection. This affects 
	 * how certain options/results are displayed, as well as how the input.yaml is generated.
	 */
	static public boolean isHardwareInjection = true;
	/**
	 * Only affects software fault injection. This is true when we are selecting more than 1
	 * software fault and the batch mode script will be called instead.
	 */
	static public boolean isBatchMode = false;
	static public List<String> selectedSoftwareFailures;
	static public ComboBox<String> fiResultDisplay;
	
	static public ConfigReader configReader;
	
	// making later changes to how states are kept
	public CurrentState cs = new CurrentState(State.IMPORT_FILE);
	
	
	@FXML
	private void onClickProfiling(ActionEvent event){
		Parent root;
		FileReader inputFile;
		ProcessBuilder p;
		errorFlag = false;
		try{
			tabBottom.getSelectionModel().select(profilingTab);

			console = new ArrayList<String>();


			inputString = programInputText.getText();
			//programInputText.setEditable(false);
			errorString = new ArrayList<>();
			//System.out.println("inputString;"+inputString);
			
			// #SFIT
			String execName;
			if (!Controller.isBatchMode) {
				execName = "bin/profile " + currentProgramFolder+"/llfi/" + currentProgramFolder + "-profiling.exe " + inputString;
			} else {
				// #SFIT 
				// call batch instrument instead if we have more than 1 software fault
				execName = "bin/batchProfile " + currentProgramFolder + "/" + currentProgramFolder
								+ ".ll " + inputString;
			}

			p = new ProcessBuilder("/bin/tcsh","-c",llfibuildPath + execName);
			console.add("$ "+llfibuildPath + execName);

			p.redirectErrorStream(true);
			Process pr = p.start();
			BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
			String line1;
			while ((line1 = in1.readLine()) != null) {
				//System.out.printl
				console.add(line1);
				errorString.add(line1+"\n");
				if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
					errorFlag= true;

			}
			pr.waitFor();
			in1.close();
			
			// gets the number of index
			inputFile = new FileReader(currentProgramFolder
					+ "/llfi.stat.totalindex.txt");
			BufferedReader bufferReader = new BufferedReader(inputFile);
			String line;
			while ((line = bufferReader.readLine()) != null) {
				indexBound = line.split("=")[1];
			}
			bufferReader.close();

			// #SFIT
			// if we are doing multiple software failure injection, we have to 
			// get all the different cycles for each failure
			ArrayList<Table> profileResult = new ArrayList<Table>();
			int num = isBatchMode ? selectedSoftwareFailures.size() : 1;
			for (int i = 0; i < num; i++) {
				String failureName;
				if (isHardwareInjection) {
					failureName = "Hardware Fault(s)";
				} else {
					failureName = selectedSoftwareFailures.get(i);
				}
				if (!isBatchMode) {
					inputFile = new FileReader(currentProgramFolder
							+ "/llfi.stat.prof.txt");
				} else {
					inputFile = new FileReader(currentProgramFolder + "/llfi-"
							+ selectedSoftwareFailures.get(i) + "/llfi.stat.prof.txt");
				}
				bufferReader = new BufferedReader(inputFile);
				while ((line = bufferReader.readLine()) != null) {
					if (line.contains("="))
						cycleBound = line.split("=")[1];
				}
				bufferReader.close();
				
				profileResult.add(new Table(failureName, Integer.parseInt(indexBound), 
						Integer.parseInt(cycleBound)));
			}
			
			ObservableList<Table> data = FXCollections.observableArrayList(profileResult);
			
			failureType.setCellValueFactory(new PropertyValueFactory<Table, String>("failureType"));
			indexCount.setCellValueFactory(new PropertyValueFactory<Table, Integer>("noIndex"));
			cycleCount.setCellValueFactory(new PropertyValueFactory<Table, Integer>("noCycles"));
			
			profilingTable.setItems(data);
			
			if(errorFlag == true)
			{
				errorFlag = false;
				Node  source = (Node)  event.getSource(); 
				Stage stage  = (Stage) source.getScene().getWindow();
				stage.close();

				root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ErrorDisplay.fxml"));
				stage = new Stage();
				stage.setTitle("Error");
				stage.setScene(new Scene(root, 450, 100));
				stage.show();
			}
			else
			{
				errorString = new ArrayList<>();
				root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Profile.fxml"));
				Stage stage = new Stage();                               

				stage.setTitle("Profiling");
				stage.setScene(new Scene(root, 400, 100));
				stage.show();
				runtimeButton.setDisable(false);
				tracegraphButton.setDisable(true);
				showTraceOutputText.setVisible(false);
				if(InstrumentController.selectProfileFlag == true || InstrumentController.existingInputFileFlag ==true)
					injectfaultButton.setDisable(false);
				else
					injectfaultButton.setDisable(true);
			}
			
			//Display index file in Text area
			//Clear the Text area
			programTextArea.clear();
			// Clear fileContent
			fileContent = new ArrayList<>();
			FileReader indexFile = new FileReader(currentProgramFolder + "/" + currentProgramFolder + "-llfi_displayIndex.ll");
			bufferReader = new BufferedReader(indexFile);
			//Read file contents
			while ((line = bufferReader.readLine()) != null)   {
				fileContent.add(line+"\n");      
			}

			// Write file contents to Text Area
			for(int i = 0 ; i < fileContent.size(); i++)
			{

				programTextArea.appendText(fileContent.get(i));
			}




		}
		catch(IOException e){
			e.printStackTrace();  
			System.out.println(e);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println(e.getMessage());
		}


	}

	@FXML
	public void onClickActualFaultInjection(ActionEvent event)
	{
		Parent root;
		try{
			tabBottom.getSelectionModel().select(profilingTab);
			faultInjectionCompleted = 1; 
			ObservableList<ResultTable> data;
			
			// read output folder(s), if exist delete them
			final File folder = new File(currentProgramFolder+"/llfi/llfi_stat_output");
			if(folder.exists())
				deleteFilesInFolder(folder);
			final File errorFolder = new File(currentProgramFolder+"/llfi/error_output");
			if(errorFolder.exists())
				deleteFilesInFolder(errorFolder);

			//if(new File(currentProgramFolder+"/llfi/std_output").exists());
			// {
			final File outputFolder = new File(currentProgramFolder+"/llfi/std_output");
			if(outputFolder.exists())
				deleteFilesInFolder(outputFolder);
			// }
			
			// runs ProgressBarController.java
			root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ProgressWindow.fxml"));
			Stage stage = new Stage();                               

			stage.setTitle("Fault Injection");
			stage.setScene(new Scene(root, 440, 118));
			stage.show();
		}
		catch (IOException e) {

			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	public void deleteFilesInFolder(final File folder) {
		//resultFileNameLists = new ArrayList<String>();
		for (final File fileEntry : folder.listFiles()) {

			if (fileEntry.isDirectory()) {
				deleteFilesInFolder(fileEntry);
			} else {
				fileEntry.delete();
			}
		}
	}

	@FXML
	public void onClickInjectFaultOkHandler(ActionEvent event){


	}

	/**
	 * Generates the 'Fault Injection Status' tab
	 */
	@FXML
	public void onGeneratingResultTable() {
		try {
			sdcCount = 0;
			runCount = 0;
			data1 = FXCollections.observableArrayList();
			
			// Generate trace_report_output folder to hold TraceDiffReport files
			ProcessBuilder deleteTraceReportFolder = new ProcessBuilder(
					"/bin/tcsh", "-c", "rm -rf "
							+ Controller.currentProgramFolder
							+ "/llfi/trace_report_output");
			deleteTraceReportFolder.start().waitFor();

			ProcessBuilder makeTraceReportFolder = new ProcessBuilder(
					"/bin/tcsh", "-c", "mkdir -p " 
							+ Controller.currentProgramFolder
							+ "/llfi/trace_report_output");
			makeTraceReportFolder.start().waitFor();
			
			
			// #SFIT
			// get the fault the display
			// if we are doing single injection this does not matter
			String selectedFault = fiResultDisplay.getSelectionModel().getSelectedItem();
			
			// for batch mode, if the user selected all we need to loop through all the 
			// inner folders
			int faultFolderNum;
			if (isBatchMode && selectedFault == "All") {
				faultFolderNum = selectedSoftwareFailures.size();
			} else {
				faultFolderNum = 1;
			}
			
			// loop through each inner folder when doing batch injection
			for (int it = 0; it < faultFolderNum; it++) {
				/**
				 * Name of TraceDiff files needs to change if we are doing batch mode
				 * as we are copying all the TraceDiff files to one location ("llfi/trace_report_output")
				 */
				String diff;
				String fault;
				// fault name changes through each loop iteration
				if (isBatchMode && selectedFault == "All") {
					fault = selectedSoftwareFailures.get(it);
					diff = fault + "-";
				} else {
					fault = selectedFault;
					diff = "";
				}
				
				// changes path accordingly if we are doing batch software injection
				String folderPath, errorFolderPath, outputFolderPath, goldenStdOutputPath, statTraceProfPath;
				if (!isBatchMode) {
					folderPath = currentProgramFolder
							+ "/llfi/llfi_stat_output/";
					errorFolderPath = currentProgramFolder
							+ "/llfi/error_output/";
					outputFolderPath = currentProgramFolder 
							+ "/llfi/std_output/";
					goldenStdOutputPath = currentProgramFolder
							+ "/llfi/baseline/golden_std_output";
					statTraceProfPath = Controller.currentProgramFolder
							+ "/llfi/baseline/llfi.stat.trace.prof.txt";
				} else {
					folderPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/llfi_stat_output/";
					errorFolderPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/error_output/";
					outputFolderPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/std_output/";
					goldenStdOutputPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/baseline/golden_std_output";
					statTraceProfPath = Controller.currentProgramFolder + "/llfi-" + fault
							+ "/llfi/baseline/llfi.stat.trace.prof.txt";
				}
				
				listFilesForFolder(new File(folderPath));
				listFilesForErrorFolder(new File(errorFolderPath));
				listFilesForOtputFolder(new File(outputFolderPath));
	
				for (int i = 0; i < resultFileNameLists.size(); i++) {
					// get run_config and run_number from the file name
					String fileName = resultFileNameLists.get(i);
					String[] split = fileName.split("\\.");
					String runNum = split[split.length - 2];
					/**
					 * Used for generating the 'TraceDiffReportFile'
					 * as well as finding it later. Get the last 8 character
					 * of fileName as that is the run_config# - run#
					 */
					String traceDiffName = diff + "TraceDiffReportFile."
							+ runNum + ".txt";
					if (fileName.contains("trace")) {
						// Generate diff report file using tracediff
						ProcessBuilder DiffFile = new ProcessBuilder("/bin/tcsh",
								"-c", Controller.llfibuildPath + "tools/tracediff '"
										+ statTraceProfPath
										+ "' '" + folderPath
										+ fileName + "' > './"
										+ Controller.currentProgramFolder
										+ "/llfi/trace_report_output/" + traceDiffName + "'");
						DiffFile.redirectErrorStream(true).start().waitFor();
						continue;
					} 
					resultList = new ArrayList<String>();
					runCount++;
	
					inputFile = new FileReader(folderPath + fileName);
					BufferedReader bufferReader = new BufferedReader(inputFile);
					while ((line = bufferReader.readLine()) != null) {
						str = line.split(":")[1];
	
						subStr = str.split(",");
						for (int j = 0; j < subStr.length; j++) {
							resultList.add(subStr[j].split("=")[1]);
						}
					}
					bufferReader.close();
					
					if (resultErrorFileNameLists.size() > 0) {
						for (int k = 0; k < resultErrorFileNameLists.size(); k++) {
							if (resultErrorFileNameLists
									.get(k)
									.substring(14)
									.equalsIgnoreCase(
											resultFileNameLists.get(i)
													.substring(28).split("\\.")[0])) {
								result = "";
								status = "Injected";
								errorFile = new FileReader(errorFolderPath
										+ resultErrorFileNameLists.get(k));
								BufferedReader bufferReader1 = new BufferedReader(
										errorFile);
								while ((line = bufferReader1.readLine()) != null) {
									result = result + line + ";";
								}
								bufferReader1.close();
								break;
							} else {
								status = "Not Injected ";
								result = "Nil";
							}
						}
					} else {
						status = "Not Injected ";
						result = "Nil";
					}
	
					boolean tmpFlag = false;
					if (resultOutputFileNameLists.size() > 0) {
						for (int k = 0; k < resultOutputFileNameLists.size(); k++) {
							for (int l = 0; l < resultErrorFileNameLists.size(); l++) {
								if ((resultErrorFileNameLists.get(l).substring(14)
										.equalsIgnoreCase(resultFileNameLists
												.get(i).substring(28).split("\\.")[0]))) {
									sdc = "Not Occured";
									tmpFlag = true;
									break;
								}
							}
	
							if (tmpFlag) {
								break;
							}
	
							if (!resultOutputFileNameLists
									.get(k)
									.substring(19)
									.equalsIgnoreCase(
											resultFileNameLists.get(i)
													.substring(28).split("\\.")[0])) {
								continue;
							}
	
							// i dont think the code below does anything 
							ProcessBuilder p1 = new ProcessBuilder("/bin/tcsh",
									"-c", "echo $COMPARE");
							p1.redirectErrorStream(true);
							Process pr1 = p1.start();
							BufferedReader in2 = new BufferedReader(
									new InputStreamReader(pr1.getInputStream()));
							String line1;
							String comparePath = null;
							while ((line1 = in2.readLine()) != null) {
								Controller.errorString.add(line1 + "\n");
								if (line1.contains("error")
										|| line1.contains("Error")
										|| line1.contains("ERROR")
										|| line1.contains("Undefined variable")) {
									errorFlag = true;
								} else {
									comparePath = line1;
								}
							}
							pr1.waitFor();
							in2.close();
	
							// I dont think the if below ever runs, only the else ever runs
							if (comparePath != null) {
								ProcessBuilder p2 = new ProcessBuilder("/bin/tcsh",
										"-c", "sh " + comparePath + " '"
												+ goldenStdOutputPath + "' '"
												+ outputFolderPath
												+ resultOutputFileNameLists.get(k) + "'");
	
								p2.redirectErrorStream(true);
								Process pr2 = p2.start();
								BufferedReader in3 = new BufferedReader(
										new InputStreamReader(pr2.getInputStream()));
	
								while ((line1 = in3.readLine()) != null) {
	
									Controller.errorString.add(line1 + "\n");
									if (line1.contains("error")
											|| line1.contains("Error")
											|| line1.contains("ERROR")) {
										errorFlag = true;
									} else {
										if (line1.equalsIgnoreCase("Not Identical")) {
											sdc = "Not Occured";
										} else {
											sdcCount++;
											sdc = "Occured";
											status = "Injected";
										}
									}
								}
								pr2.waitFor();
								in3.close();
							} else {
								// #SFIT
								// '(' and ')' need to be escaped or encapsulated in a '...'
								// eg. diff 'factorial/llfi-CPUHog(Res)/llfi/baseline/golden_std_output' 'factorial/llfi-CPUHog(Res)/llfi/std_output/std_outputfile-run-0-1'
								// or it wont work in a diff
								String cmd = "diff '" + goldenStdOutputPath + "' '"
										+ outputFolderPath
										+ resultOutputFileNameLists.get(k) + "'";
								ProcessBuilder p3 = new ProcessBuilder("/bin/tcsh",
										"-c", cmd);
								p3.redirectErrorStream(true);
								Process pr3 = p3.start();
								BufferedReader in4 = new BufferedReader(
										new InputStreamReader(pr3.getInputStream()));
								if ((line1 = in4.readLine()) == null) {
									sdc = "Not Occured";
									status = "Injected";
								} else {
									while ((line1 = in4.readLine()) != null) {
										Controller.errorString.add(line1 + "\n");
										if (line1.contains("error")
												|| line1.contains("Error")
												|| line1.contains("ERROR")) {
											errorFlag = true;
										} else {
											sdcCount++;
											sdc = "Occured";
											status = "Injected";
											break;
										}
									}
								}
								pr3.waitFor();
								in4.close();
							}
						}
					} else {
						sdc = "NA";
					}
	
					trace = false;
					data1.add(new ResultTable(runCount, resultList.get(0), Integer
							.parseInt(resultList.get(1)), Integer
							.parseInt(resultList.get(2)), Integer
							.parseInt(resultList.get(4)), sdc, status, result,
							trace, traceDiffName));
				}
			}

			tFiRun.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>(
					"noOfRuns"));
			tFiType.setCellValueFactory(new PropertyValueFactory<ResultTable, String>(
					"FaultInjectionType"));
			tFiIndex.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>(
					"index"));
			tFiCycle.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>(
					"cycle"));
			tFiBit.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>(
					"bit"));
			tFiSdc.setCellValueFactory(new PropertyValueFactory<ResultTable, String>(
					"sdc"));
			tFiStatus
					.setCellValueFactory(new PropertyValueFactory<ResultTable, String>(
							"status"));
			tFiResult
					.setCellValueFactory(new PropertyValueFactory<ResultTable, String>(
							"result"));
			tFiTrace.setCellValueFactory(new PropertyValueFactory<ResultTable, Boolean>(
					"trace"));
			tFiTrace.setCellFactory(new Callback<TableColumn<ResultTable, Boolean>, TableCell<ResultTable, Boolean>>() {
				public TableCell<ResultTable, Boolean> call(
						TableColumn<ResultTable, Boolean> p) {
					return new CheckBoxTableCell<ResultTable, Boolean>();
				}
			});
			tFiTrace.setEditable(true);

			resultTable.setItems(data1);
			resultTable.setEditable(true);
			tracegraphButton.setDisable(false);
			showTraceOutputText.setVisible(true);

			// Header CheckBox for select all
			HBox box = new HBox();
			Label text = new Label("Trace");
			CheckBox cb = new CheckBox();
			cb.setUserData(this.tFiTrace);
			cb.setText("Select All");
			cb.setOnAction(handleSelectAllCheckbox());
			box.getChildren().addAll(text, cb);
			box.setSpacing(5);
			this.tFiTrace.setGraphic(box);
		} catch (IOException e) {
			System.err.println("ERROR: ioexception");
			e.printStackTrace();
		} catch (InterruptedException e) {
			System.err.println("ERROR: interrupted");
			e.printStackTrace();
		}
	}
	
	private EventHandler<ActionEvent> handleSelectAllCheckbox() {  
		return new EventHandler<ActionEvent>() {  
			@Override  
			public void handle(ActionEvent event) {  
				CheckBox cb = (CheckBox) event.getSource();  
				TableColumn column = (TableColumn) cb.getUserData();  
				if(cb.isSelected())
				{
					for (ResultTable resultTableRow : resultTable.getItems())
					{
						resultTableRow.setTrace(true);
					}
				}
				else
				{
					for (ResultTable resultTableRow : resultTable.getItems())
					{
						resultTableRow.setTrace(false);
					}
				}
			}  
		};  
	}
	
	/**
	 * Clicking "TraceGraph" on the GUI runs this function.
	 * @param event - Click event
	 */
	@FXML
	private void onClickGenerateTraceGraph(ActionEvent event) {
		Parent root;
		try {
			// Generate Trace Union file
			final File TraceDiffReportFolder = new File(currentProgramFolder + "/llfi/trace_report_output");
			FileListofTraceReportFolder(TraceDiffReportFolder);

			//Delete old UnitedDiffReportFile.txt, TraceGraph.dot, and TraceGraph.ps files
			File UnitedDiffReportFile = new File(currentProgramFolder + "/llfi/trace_report_output/UnionedDiffReportFile.txt");
			if(UnitedDiffReportFile.exists()) {
				delete(UnitedDiffReportFile);
			}
			
			File TraceGraphDot = new File(currentProgramFolder + "/llfi/trace_report_output/TraceGraph.dot");
			if(TraceGraphDot.exists()) {
				delete(TraceGraphDot);
			}
			
			File TraceGraphPs = new File(currentProgramFolder + "/llfi/trace_report_output/TraceGraph.ps");
			if(TraceGraphPs.exists()) {
				delete(TraceGraphPs);
			}

			String TraceUnionCmd = Controller.llfibuildPath + "tools/traceunion";
			int found = 0;
			String traceFileName = "";
			for (ResultTable resultTableRow : resultTable.getItems()) {
				// if checkBox is ticked, then use this file
				if (resultTableRow.getTrace() == true) {
					for (int i = 0; i < TraceDiffReportFileNameLists.size(); i++) {
						// see if trace file exist (trace file does not exist if the fault injection
						// caused the program to crash)
						traceFileName = TraceDiffReportFileNameLists.get(i);
						System.out.println(traceFileName + " " + resultTableRow.getTraceFileName());
						if (resultTableRow.getTraceFileName().equals(traceFileName)) {
							TraceUnionCmd += " './"
									+ Controller.currentProgramFolder
									+ "/llfi/trace_report_output/" + traceFileName
									+ "'";
							found++;
							break;
						}
					}
				}
			}

			TraceUnionCmd += "> ./" + Controller.currentProgramFolder
					+ "/llfi/trace_report_output/UnionedDiffReportFile.txt";
			if (found > 1) {
				ProcessBuilder UnionTraceDiffReportFile = new ProcessBuilder(
						"/bin/tcsh", "-c", TraceUnionCmd);
				UnionTraceDiffReportFile.redirectErrorStream(true).start()
						.waitFor();

				// Generate .dot graph file using traceontograph
				ProcessBuilder TraceGraph = new ProcessBuilder(
						"/bin/tcsh",
						"-c",
						Controller.llfibuildPath
								+ "tools/traceontograph "
								+ Controller.currentProgramFolder
								+ "/llfi/trace_report_output/UnionedDiffReportFile.txt"
								+ " " + currentProgramFolder
								+ "/llfi.stat.graph.dot" + " > ./"
								+ Controller.currentProgramFolder
								+ "/llfi/trace_report_output/TraceGraph.dot");
				TraceGraph.redirectErrorStream(true).start().waitFor();
			} else if (found == 1) {
				// Generate .dot graph file using traceontograph
				ProcessBuilder TraceGraph = new ProcessBuilder("/bin/tcsh",
						"-c", Controller.llfibuildPath
								+ "tools/traceontograph '"
								+ Controller.currentProgramFolder
								+ "/llfi/trace_report_output/" + traceFileName
								+ "' " + currentProgramFolder
								+ "/llfi.stat.graph.dot" + " > ./"
								+ Controller.currentProgramFolder
								+ "/llfi/trace_report_output/TraceGraph.dot");
				TraceGraph.redirectErrorStream(true).start().waitFor();
			} else { // found == 0
				// When cannot find trace files, inform users about the error.
				root = FXMLLoader.load(getClass().getClassLoader().getResource(
						"application/TracingErrorDisplay.fxml"));
				Stage stage = new Stage();

				stage.setTitle("Error");
				stage.setScene(new Scene(root, 500, 118));
				stage.show();
				return;
			}
			
			//If show traceoutput text box is selected, find the file opener then open the tracefile
			String fileOpener = "";
			if (showTraceOutputText.isSelected() && found != 0) {
				String osName = System.getProperty("os.name").toLowerCase();
				if (osName.indexOf("mac") >= 0) {
					fileOpener = "open ";
				} else if (osName.indexOf("nux") >= 0) {
					fileOpener = "xdg-open ";
				} else if (osName.indexOf("solaris") >= 0) {
					fileOpener = "xdg-open ";
				}
				
				String fileName = fileOpener + "'" + Controller.currentProgramFolder + "/llfi/trace_report_output/";
				if (found > 1) {
					fileName += "UnionedDiffReportFile.txt'";
				} else {
					fileName += traceFileName + "'";
				}
				ProcessBuilder openFile = new ProcessBuilder("/bin/tcsh", "-c", fileName);
				openFile.redirectErrorStream(true).start();
			}

			// Covert traceontograph to pdf format using Graphviz
			ProcessBuilder ConvertToPs = new  ProcessBuilder("/bin/tcsh","-c","dot -Tps "+Controller.currentProgramFolder+"/llfi/trace_report_output/TraceGraph.dot -o "+Controller.currentProgramFolder+"/llfi/trace_report_output/TraceGraph.ps");
			ConvertToPs.redirectErrorStream(true);
			ConvertToPs.start().waitFor();
			
			// if zgrviewer path has not been set/not installed, we will open the pdf instead
			if (zgrviewerPath.contains("Undefined")) {
				// Test system before opening the graph
				String psOpenner ="";
				boolean psError = true;
				String psErrorMessage ="";
				String checkExe ="";
				String osName = System.getProperty("os.name").toLowerCase();
				if (osName.indexOf("mac") >= 0) {
					// The current os is mac, use to view ps file
					psOpenner = "open ";
					psError = false;
					checkExe = "open -h > /dev/null 2>&1";
				} else if (osName.indexOf("nux") >= 0) {
					// The current os is linux, use xdg-open to view ps file
					psOpenner = "xdg-open ";
					checkExe = "xdg-open --help > /dev/null";
					psError = false;
				} else if (osName.indexOf("solaris") >= 0) {
					// The current os is solaris, use xdg-open to view ps file
					psOpenner = "xdg-open ";
					psError = false;
					checkExe = "xdg-open --help > /dev/null";
				} else {
					// Other OS, display error message when trying to open os file
					psError = true;
				}

				if (!psError) {
					try {
						Runtime rt = Runtime.getRuntime();
						Process proc = rt.exec(checkExe);
						psError = false;
					} catch (IOException e) {
						//e.printStackTrace();  
						//System.out.println(e);
						psError =true;
					}
				}
				
				// If user specified a psViewer in environment variable, use the defined ps file viewer.
				//kenneth
				if (!psViewer.contains("Undefined variable")) {
					psError = false;
					psOpenner = psViewer + " ";
				}
				
				if (psError) {
					try {
						root = FXMLLoader.load(getClass().getClassLoader().getResource("application/TraceOpenError.fxml"));
						Stage stage = new Stage();
						stage.setTitle("Error");
						stage.setScene(new Scene(root, 650, 100));
						stage.show();
					} catch (IOException e) {
						e.printStackTrace();
						System.out.println(e);
					}
				} else {
					//Open the trace graph file
					ProcessBuilder openGraph = new  ProcessBuilder("/bin/tcsh","-c",psOpenner+Controller.currentProgramFolder+"/llfi/trace_report_output/TraceGraph.ps");
					openGraph.redirectErrorStream(true);
					openGraph.start().waitFor();
				}
			} else {
				ProcessBuilder openGraph = new  ProcessBuilder("/bin/tcsh","-c",zgrviewerPath+"run.sh "+Controller.currentProgramFolder+"/llfi/trace_report_output/TraceGraph.dot");
				openGraph.redirectErrorStream(true).start();
			}
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		} catch (InterruptedException e) {
			System.out.println(e);
			e.printStackTrace();
		}
	}
	
	/**
	 * Generates the 'Fault Summary' tab
	 */
	@FXML
	private void generateFaultSummaryGraph() {
		// sets all counts to zero
		int faultCount = 0;
		hangedCount = 0;
		crashedCount = 0;
		resultList = new ArrayList<String>(); // this is not used here?
		
		try {
			// #SFIT
			// get the fault the display
			// if we are doing single injection this does not matter
			String selectedFault = fiResultDisplay.getSelectionModel().getSelectedItem();
			
			// for batch mode, if the user selected all we need to loop through all the 
			// inner folders
			int faultFolderNum;
			if (isBatchMode && selectedFault == "All") {
				faultFolderNum = selectedSoftwareFailures.size();
			} else {
				faultFolderNum = 1;
			}
			
			// loop through each inner folder when doing batch injection
			for (int it = 0; it < faultFolderNum; it++) {
				String errorFolderPath;
				String folderPath;
				String fault;
				
				// are we in batch mode or single?
				if (isBatchMode && selectedFault == "All") {
					fault = selectedSoftwareFailures.get(it);
				} else {
					fault = selectedFault;
				}
				
				// go into inner folder if we are in batch mode
				if (!isBatchMode) {
					folderPath = currentProgramFolder
							+ "/llfi/llfi_stat_output/";
					errorFolderPath = currentProgramFolder
							+ "/llfi/error_output/";
				} else {
					folderPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/llfi_stat_output/";
					errorFolderPath = currentProgramFolder + "/llfi-" + fault
							+ "/llfi/error_output/";
				}
				
				// list out the files in these folder in a member variable
				listFilesForFolder(new File(folderPath));
				listFilesForErrorFolder(new File(errorFolderPath));
				
				// read all files from error folder for 'crashed' or 'hanged'
				for (int k = 0; k < resultErrorFileNameLists.size(); k++) {
					errorFile = new FileReader(errorFolderPath
							+ resultErrorFileNameLists.get(k));
					BufferedReader bufferReader1 = new BufferedReader(errorFile);
					while ((line = bufferReader1.readLine()) != null) {
						if (line.contains("crashed")) {
							crashedCount++;
						} else if (line.contains("hanged")) {
							hangedCount++;
						}
					}
				}
				
				// get fault count
				if (resultFileNameLists.size() > 0) {
					for (int i = 0; i < resultFileNameLists.size(); i++) {
						if (resultFileNameLists.get(i).contains("trace")) {

						} else {
							faultCount++;
						}
					}
				}
			} 

			String[] params = { "Crashed", "Hanged", "SDC" };

			// Convert it to a list and add iUTILITYt to our ObservableList of
			// months.
			resultSummary.getData().clear();

			xAxis.setLabel("Parameters");
			yAxis.setLabel("Total.No.Of.Fault Injections");
			xAxis.setCategories(FXCollections
					.<String> observableArrayList(Arrays.asList(params)));
			xAxis.setAutoRanging(false);
			xAxis.invalidateRange(Arrays.asList(params));

			yAxis.setAutoRanging(false);
			yAxis.setLowerBound(0);
			
			yAxis.setUpperBound(faultCount);
			yAxis.setTickUnit(1);

			series = new XYChart.Series<Integer, String>();

			XYChart.Data<Integer, String> faultData = new XYChart.Data<Integer, String>(
					crashedCount, "Crashed");
			series.getData().add(faultData);

			faultData = new XYChart.Data<Integer, String>(hangedCount, "Hanged");
			series.getData().add(faultData);

			faultData = new XYChart.Data<Integer, String>(sdcCount, "SDC");
			series.getData().add(faultData);

			resultSummary.getData().add(series);

		} catch (IOException e) {
			System.err.println("ERROR: cannot generate Fault Summary!");
			e.printStackTrace();
		}
	}

	public void listFilesForErrorFolder(final File folder) {

		resultErrorFileNameLists = new ArrayList<String>();
		for (final File fileEntry : folder.listFiles()) {                                

			if (fileEntry.isDirectory()) {
				listFilesForErrorFolder(fileEntry);
			} else {
				resultErrorFileNameLists.add(fileEntry.getName());
			}
		}
		//System.out.println(line1);

	}
	public void listFilesForOtputFolder(final File folder) {
		resultOutputFileNameLists = new ArrayList<String>();
		for (final File fileEntry : folder.listFiles()) {                                

			if (fileEntry.isDirectory()) {
				listFilesForErrorFolder(fileEntry);
			} else {
				resultOutputFileNameLists.add(fileEntry.getName());
			}
		}
		//System.out.println(line1);

	}

	public void FileListofTraceReportFolder(final File folder) {
		TraceDiffReportFileNameLists = new ArrayList<String>();
		for (final File fileEntry : folder.listFiles()) {                                

			if (fileEntry.isDirectory()) {
				listFilesForErrorFolder(fileEntry);
			} else {
				TraceDiffReportFileNameLists.add(fileEntry.getName());
			}
		}
		//System.out.println(line1);

	}

	public void listFilesForFolder(final File folder) {
		resultFileNameLists = new ArrayList<String>();
		File[] files =folder.listFiles();
		Arrays.sort(files, new FileNameComparator());
		for (final File fileEntry : files) {
			if (fileEntry.isDirectory()) {
				listFilesForFolder(fileEntry);
			} else {

				resultFileNameLists.add(fileEntry.getName());
			}
		}
	}
	Pattern splitter = Pattern.compile("(\\d+|\\D+)");
	public class FileNameComparator implements Comparator
	{
		public int compare(Object o1, Object o2)
		{
			// I deliberately use the Java 1.4 syntax, 
			// all this can be improved with 1.5's generics
			String s1 = o1.toString(), s2 = o2.toString();
			// We split each string as runs of number/non-number strings
			ArrayList sa1 = split(s1);
			ArrayList sa2 = split(s2);
			// Nothing or different structure
			if (sa1.size() == 0 || sa1.size() != sa2.size())
			{
				// Just compare the original strings
				return s1.compareTo(s2);
			}
			int i = 0;
			String si1 = "";
			String si2 = "";
			// Compare beginning of string
			for (; i < sa1.size(); i++)
			{
				si1 = (String)sa1.get(i);
				si2 = (String)sa2.get(i);
				if (!si1.equals(si2))
					break;  // Until we find a difference
			}
			// No difference found?
			if (i == sa1.size())
				return 0; // Same strings!

			// Try to convert the different run of characters to number
			int val1, val2;
			try
			{
				val1 = Integer.parseInt(si1);
				val2 = Integer.parseInt(si2);
			}
			catch (NumberFormatException e)
			{
				return s1.compareTo(s2);  // Strings differ on a non-number
			}

			// Compare remainder of string
			for (i++; i < sa1.size(); i++)
			{
				si1 = (String)sa1.get(i);
				si2 = (String)sa2.get(i);
				if (!si1.equals(si2))
				{
					return s1.compareTo(s2);  // Strings differ
				}
			}

			// Here, the strings differ only on a number
			return val1 < val2 ? -1 : 1;
		}

		ArrayList split(String s)
		{
			ArrayList r = new ArrayList();
			Matcher matcher = splitter.matcher(s);
			while (matcher.find())
			{
				String m = matcher.group(1);
				r.add(m);
			}
			return r;
		}
	}

	@FXML
	private void onClickCompileToIr(ActionEvent event){
		Parent root;	
		try{
			boolean flag =false;
			console = new ArrayList<String>();
			tabBottom.getSelectionModel().select(profilingTab);
			String cmd = "echo $llfibuild";
			//System.out.println(System.getenv());
			// Delete the old .ll file
			ProcessBuilder deleteCmd = new  ProcessBuilder("/bin/tcsh","-c","rm " + currentProgramFolder+"/"+currentFileName+".ll");
			Process delete = deleteCmd.start();
			delete.waitFor();
			delete.destroy();
			
			if (currentFileName.equals("Makefile"))
			{
				String command = "make";
				File folder = currentFilePath;
				try {
					Process p = Runtime.getRuntime().exec(command,null,folder);;
					BufferedReader in1 = new BufferedReader(new InputStreamReader(p.getErrorStream()));
					errorTextArea.clear();
					errorString = new ArrayList<>();
					while ((line = in1.readLine()) != null) {
						console.add(line+"\n");
						errorString.add(line+"\n");
					}
					in1.close();
					p.waitFor();


					p.destroy();
				}
				catch (Exception e)
				{
					System.out.println(e);
				}
			}
			else
			{
				String command = llfibuildPath+"tools/compiletoIR --debug --readable -o "+currentProgramFolder+"/"+currentProgramFolder+".ll  "+currentProgramFolder+"/"+currentFileName;
				console.add("$ "+command+"\n");
				Process p = Runtime.getRuntime().exec(command);
				BufferedReader in1 = new BufferedReader(new InputStreamReader(p.getErrorStream()));
				errorTextArea.clear();
				errorString = new ArrayList<>();
				while ((line = in1.readLine()) != null) {
					console.add(line+"\n");
					errorString.add(line+"\n");

				}
				in1.close();
				p.waitFor();

				p.destroy();
			}

			if(errorString.size()==0)
			{
				root = FXMLLoader.load(getClass().getClassLoader().getResource("application/compileToIR.fxml"));
				Stage stage = new Stage();
				stage.setTitle("Compiling To IR Result");
				stage.setScene(new Scene(root, 500, 150));
				stage.show();



				// Clear fileContent
				fileContent = new ArrayList<>();
				String line;
				FileReader inputFile = new FileReader(currentProgramFolder+"/"+currentProgramFolder+".ll");
				BufferedReader bufferReader = new BufferedReader(inputFile);
				//Read file contents
				while ((line = bufferReader.readLine()) != null)   {
					fileContent.add(line+"\n");      
				}
				
				//Clear the Text area
				programTextArea.clear();
				// Write file contents to Text Area
				for(int i = 0 ; i < fileContent.size(); i++)
				{

					programTextArea.appendText(fileContent.get(i));
				}
				File file = new File(currentProgramFolder+"/"+currentProgramFolder+".ll");
				Path path = file.toPath();
				String fileName = path.getFileName().toString();
				for(int n =0;n<fileNameLists.size();n++)
				{
					if(fileNameLists.get(n).equalsIgnoreCase(fileName))
					{
						fileNameLists.remove(n);
						fileNameLists.add(fileName);
						flag =true;
						break;
					}
					else
					{

					}
				}
				if(!flag)
				{
					fileNameLists.add(fileName);
					flag = false;
				}
				items =FXCollections.observableArrayList (fileNameLists);
				fileList.setItems(items);
				fileSelecMap.put(fileName, fileContent);
				//Add file name to compiledfileNameList
				CompiledllFileNameLists.add(currentProgramFolder+".c");
				instrumentButton.setDisable(false);
				profilingButton.setDisable(true);
				runtimeButton.setDisable(true);
				injectfaultButton.setDisable(true);
				tracegraphButton.setDisable(true);
				showTraceOutputText.setVisible(false);


			}
			else
			{
				root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ErrorDisplay.fxml"));
				Stage stage = new Stage();
				stage.setTitle("Error");
				stage.setScene(new Scene(root, 450, 100));
				stage.show();
			}





			// System.out.println(line1);

		}
		catch(IOException e){
			e.printStackTrace();  
			System.out.println(e);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println(e.getMessage());
		}

		// #SFIT
		// find out which software faults are applicable (which one can be injected)
		// and dump it into <folder>/llfi.applicable.software.failures.txt
		String cmd = Controller.llfibuildPath 
				+ "bin/SoftwareFailureAutoScan --no_input_yaml " 
				+ currentProgramFolder + "/" + currentProgramFolder + ".ll";
		ProcessBuilder softwareFailureAutoScan = new ProcessBuilder("/bin/tcsh", "-c", cmd);
		Process p;
		try {
			p = softwareFailureAutoScan.start();
			p.waitFor();
			
			// route the output of the process to the GUI's console
			console.add("\n$ " + cmd);
			BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			while ((line = in.readLine()) != null) {
				console.add(line);
			}
			in.close();
		} catch (IOException | InterruptedException e) {
			System.err.println("ERROR: SoftwareFailureAutoScan failed!");
			e.printStackTrace();
		} 
	}
	@FXML
	private void onClickOkHandler(ActionEvent event){


		Node  source = (Node)  event.getSource(); 
		Stage stage  = (Stage) source.getScene().getWindow();
		stage.close();
	}
	@FXML
	private void onClickInstrument(ActionEvent event) {
		Parent root;
		try {
			indexStates=false;
			tabBottom.getSelectionModel().select(profilingTab);
			root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Instrument.fxml"));
			Stage stage = new Stage();
			stage.setTitle("Instrument");
			stage.setScene(new Scene(root, 742, 569));
			stage.show();

			//instrumentButton.setDisable(true);




			profilingButton.setDisable(false);
			runtimeButton.setDisable(true);
			injectfaultButton.setDisable(true);
			tracegraphButton.setDisable(true);
			showTraceOutputText.setVisible(false);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}




	@FXML
	private void onClickInjectFault(ActionEvent event) {
		Parent root;
		try {

			tabBottom.getSelectionModel().select(profilingTab);
			root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Profiling.fxml"));
			Stage stage = new Stage();
			stage.setTitle("Fault Injection");
			stage.setScene(new Scene(root, 600, 500));
			stage.show();
			//flag = 1;

			/*if(errorFlag == true)
          {
       	   errorFlag = false;
   			  Node  source = (Node)  event.getSource(); 
   			   stage  = (Stage) source.getScene().getWindow();
   			  stage.close();

   			  root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ErrorDisplay.fxml"));
   		        stage = new Stage();
   		        stage.setTitle("Error");
   		        stage.setScene(new Scene(root, 450, 100));
   		        stage.show();
          }
          else
          {
       	   errorString = new ArrayList<>();
       	   root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Profile.fxml"));
              Stage stage = new Stage();                               

              stage.setTitle("Profiling");
              stage.setScene(new Scene(root, 400, 100));
              stage.show();

          }*/
			injectfaultButton.setDisable(false);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	@FXML
	private void onClickOpenFile(ActionEvent event) {
		Parent root;
		fileCount=0;
		Stage stage = new Stage();
		FileChooser fileChooser = new FileChooser();
		fileChooser.setTitle("Open Resource File");
		configureFileChooser(fileChooser); 
		List<File> list = fileChooser.showOpenMultipleDialog(stage);
		if (list != null) {
			for (File file : list) {
				openFile(file);
			}
		}


	}

	@FXML
	private void onClickOpenProject(ActionEvent event) {
		Parent root;
		fileCount=0;
		Stage stage = new Stage();
		DirectoryChooser dirChooser = new DirectoryChooser();
		dirChooser.setTitle("Open Project Folder");
		File folder = dirChooser.showDialog(stage);
		if (folder != null) {
			System.out.println(folder);
			currentFilePath	= folder.getAbsoluteFile();
			//currentProgramFolder = currentFilePath.getAbsolutePath();
			System.out.println("currentProgramFolder: " + folder);
	
			String command = llfibuildPath+"tools/GenerateMakefile --readable --all -o " + folder + "/" + folder.getName() + ".ll";			
			try {			
				System.out.println(command);				
				Process p = Runtime.getRuntime().exec(command,null,folder);;
				p.waitFor();
				p.destroy();
			}
			catch(Exception e)
			{
				System.out.println(e);
			}
			File[] list = folder.listFiles();

			for (File file : list) {
			    String ext = getFileExtension(file);
			    System.out.println(file.getName());
			    if (file.getName().equals("Makefile"))
			    {			
				openFile(file);
				System.out.println("Absolute Path: " + file.getAbsolutePath());
			    }
			    else if (ext.equals("c") || ext.equals("cpp") ) {
				openFile(file);
			    }
			}
		}


	}

	private static String getFileExtension(File file) {
		String fileName = file.getName();
		if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
		return fileName.substring(fileName.lastIndexOf(".")+1);
		else return "";
    	}

	private static void configureFileChooser(
			final FileChooser fileChooser) {      

		fileChooser.getExtensionFilters().addAll(

				new FileChooser.ExtensionFilter("C", "*.c"),
				new FileChooser.ExtensionFilter("CPP", "*.cpp"),
				new FileChooser.ExtensionFilter("ll", "*.ll")
				);
	}
	public static void delete(File file)
			throws IOException{

		if(file.isDirectory()){

			//directory is empty, then delete it
			if(file.list().length==0){

				file.delete();


			}else{

				//list all the directory contents
				String files[] = file.list();

				for (String temp : files) {
					//construct the file structure
					File fileDelete = new File(file, temp);

					//recursive delete
					delete(fileDelete);
				}

				//check the directory again, if empty then delete it
				if(file.list().length==0){
					file.delete();

				}
			}

		}else{
			//if file, then delete it
			file.delete();

		}
	}
	private void openFile(File file) {
		try{
			
			boolean flag =false;
			fileContent = new ArrayList<>();
			Path path = file.toPath().toAbsolutePath();
			String fileInfo =path.toString(); 
			FileReader inputFile = new FileReader(fileInfo);
			BufferedReader bufferReader = new BufferedReader(inputFile);

			String fileName = path.getFileName().toString();
			for(int n =0;n<fileNameLists.size();n++)
			{
				if(fileNameLists.get(n).equalsIgnoreCase(fileName))
				{
					fileNameLists.remove(n);
					fileNameLists.add(fileName);
					flag =true;
					break;
				}
				else
				{

				}
			}
			if(!flag)
			{
				fileNameLists.add(fileName);
				flag = false;
			}

			items =FXCollections.observableArrayList (fileNameLists);
			fileList.setItems(items);
			//Variable to hold the one line data
			String line;
			
			//Variable to hold the folder name.
			String folderName;
			boolean Makefile = false;	
			
			if (fileName.equals("Makefile"))
			{
				folderName = file.getAbsolutePath().split("Makefile")[0]; 
				Makefile = true;
			}
			else
			{
				folderName = fileName.split("\\.")[0];
			}

			File  theDirectory = new File(folderName);
			if(theDirectory.exists() && !Makefile)
			{
				delete(theDirectory);

			}

			new File(folderName).mkdir();
			// programTextArea.clear();
			// Read file line by line and print on the console

			while ((line = bufferReader.readLine()) != null)   {
				fileContent.add(line+"\n");
			}
			File actualFile = new File(folderName+"/"+fileName);
			BufferedWriter outputFile = new BufferedWriter(new FileWriter(actualFile));
			for(int i = 0 ; i < fileContent.size(); i++)
			{
				outputFile.write(fileContent.get(i));
			}
			outputFile.close();
			fileSelecMap.put(fileName, fileContent);
			if(fileCount == 0)
			{
				data = FXCollections.observableArrayList();
				profilingTable.setItems(data);
				data1=FXCollections.observableArrayList();
				resultTable.setItems(data1);
				resultSummary.getData().clear();
				//resultSummary.setVisible(false);
				/*series = new XYChart.Series<Integer,String>();

        		resultSummary.getData().add(series);*/
				currentProgramFolder = folderName;
				//fileList.sgetSelectionModel().select(currentFileName);
				currentFileName = fileName;

				for(int i = 0 ; i < fileContent.size(); i++)
				{
					// ProgramTextArea displays the files contents in GUI text console. 

					programTextArea.appendText(fileContent.get(i));
				}
				if(fileName.equals("Makefile") || fileName.split("\\.")[1].equalsIgnoreCase("ll"))
				{

					compiletoIrButton.setDisable(true);
					instrumentButton.setDisable(false);
					profilingButton.setDisable(true);
					runtimeButton.setDisable(true);
					injectfaultButton.setDisable(true);

				}
				else
				{

					compiletoIrButton.setDisable(false);
					instrumentButton.setDisable(true);
					profilingButton.setDisable(true);
					runtimeButton.setDisable(true);
					injectfaultButton.setDisable(true);
				}

			}

			fileCount++;
			UploadLabel.setVisible(false);
			// compiletoIrButton.setDisable(false);
			bufferReader.close();
		}catch(IOException e){
			System.out.println("Error while reading file line by line:" 
					+ e.getMessage());                      
		}    
	}
	@FXML
	private void onFileSelection(MouseEvent event){
		
		fileContent = new ArrayList<>();
		data = FXCollections.observableArrayList();
		profilingTable.setItems(data);
		data1=FXCollections.observableArrayList();
		resultTable.setItems(data1);
		resultSummary.getData().clear();
		//programInputText.setEditable(true);
		//resultSummary.setVisible(false);
		/*series = new XYChart.Series<Integer,String>();
	resultSummary.getData().add(series);*/
		String selectedFile = fileList.getSelectionModel().getSelectedItem().toString();
		currentProgramFolder = selectedFile.split("\\.")[0];
		currentFileName = selectedFile;
		fileContent = fileSelecMap.get(selectedFile);
		programTextArea.clear();
		for(int i = 0 ; i < fileContent.size(); i++)
		{

			programTextArea.appendText(fileContent.get(i));
		}

		if(!currentFileName.equals("Makefile") && currentFileName.split("\\.")[1].equalsIgnoreCase("ll"))
		{

			compiletoIrButton.setDisable(true);
			instrumentButton.setDisable(false);
			profilingButton.setDisable(true);
			runtimeButton.setDisable(true);
			injectfaultButton.setDisable(true);
		}
		else
		{


			compiletoIrButton.setDisable(false);
			instrumentButton.setDisable(true);
			profilingButton.setDisable(true);
			runtimeButton.setDisable(true);
			injectfaultButton.setDisable(true);
		}


	}
	@FXML
	private void onTabChange(){
		if(faultStatus.isSelected() || faultSummaryTab.isSelected())
		{
			generateInjectionResult(false);
		}
		else if(errorTab.isSelected())
		{
			errorTextArea.clear();

			if(errorString.size()>0)
			{
				for(int i = 0; i < errorString.size();i++){
					//System.out.println("TAB -"+errorString.get(i));
					errorTextArea.appendText(errorString.get(i)+"\n");
				}
			}
		}
		else if(consoleTab.isSelected())
		{
			consoleTextArea.clear();
			if(console.size()>0)
			{
				for(int i = 0; i < console.size();i++){
					//System.out.println("TAB -"+errorString.get(i));
					consoleTextArea.appendText(console.get(i)+"\n");
				}
			}
		}





	}



	@Override
	public void initialize(URL url, ResourceBundle rb) {
		try{
			//progressBar.setVisible(false);
			File f = new File("."); // current directory

			File[] files = f.listFiles();
			int i;
			boolean signFalg = false;
			ProcessBuilder p1 = new ProcessBuilder("/bin/tcsh","-c","echo $llfibuild");

			p1.redirectErrorStream(true);
			Process pr1 = p1.start();
			BufferedReader in = new BufferedReader(new InputStreamReader(pr1.getInputStream()));
			String line;
			while ((line = in.readLine()) != null) {

				llfibuildPath = line;
			}
			pr1.waitFor();
			pr1.destroy();
			in.close();



			ProcessBuilder p2 = new ProcessBuilder("/bin/tcsh","-c","echo $psViewer");

			p2.redirectErrorStream(true);
			Process pr2 = p2.start();
			BufferedReader in2 = new BufferedReader(new InputStreamReader(pr2.getInputStream()));
			while ((line = in2.readLine()) != null) {

				psViewer = line;
			}
			pr2.waitFor();
			pr2.destroy();
			in2.close();
			
			
			ProcessBuilder p3 = new ProcessBuilder("/bin/tcsh","-c","echo $zgrviewer");

			p3.redirectErrorStream(true);
			Process pr3 = p3.start();
			BufferedReader in3 = new BufferedReader(new InputStreamReader(pr3.getInputStream()));

			while ((line = in3.readLine()) != null) {

				zgrviewerPath = line;
			}
			pr3.waitFor();
			pr3.destroy();
			in3.close();
			
			/*for (final File fileEntry : files) {
	    	fileContent = new ArrayList<>();
	        if (fileEntry.isDirectory()) {
	        	i = 0;ProcessBuilder p1 = new ProcessBuilder("/bin/tcsh","-c","echo $llfibuild");

	    p1.redirectErrorStream(true);
	    Process pr1 = p1.start();
		BufferedReader in = new BufferedReader(new InputStreamReader(pr1.getInputStream()));
	    String line;
	    while ((line = in.readLine()) != null) {

	        llfibuildPath = line;
	    }
	    pr1.waitFor();
	    pr1.destroy();
		in.close();



	        		FileReader actualFile = new FileReader(fileEntry.getName()+"/"+fileEntry.getName()+".c");
	                BufferedReader inputFile = new BufferedReader(actualFile);
	                while ((line = inputFile.readLine()) != null)   {
	                    fileContent.add(line+"\n");

	                }

	                inputFile.close();
	                fileSelecMap.put(fileEntry.getName()+".c", fileContent);
	                fileNameLists.add(fileEntry.getName()+".c");
	                items =FXCollections.observableArrayList (fileNameLists);
	                fileList.setItems(items);
	                if(i == 0 && signFalg == false)
		        	{
	                	//fileList.getSelectionModel().select(0);
	                	signFalg = true;
	                	//System.out.println("inside if");
		        		currentProgramFolder = fileEntry.getName();
		        		currentFileName = fileEntry.getName()+".c";
		        		programTextArea.clear();
		        		for(int j = 0 ; j < fileContent.size(); j++)
		        		{

		        			programTextArea.appendText(fileContent.get(j));
		        		}
		        		compiletoIrButton.setDisable(false);
		        		 instrumentButton.setDisable(true);
		        		 profilingButton.setDisable(true);
		        		 runtimeButton.setDisable(true);
		        		 injectfaultButton.setDisable(true);
		        		PProcessBuilder p1 = new ProcessBuilder("/bin/tcsh","-c","echo $llfibuild");

	    p1.redirectErrorStream(true);
	    Process pr1 = p1.start();
		BufferedReader in = new BufferedReader(new InputStreamReader(pr1.getInputStream()));
	    String line;
	    while ((line = in.readLine()) != null) {

	        llfibuildPath = line;
	    }
	    pr1.waitFor();
	    pr1.destroy();
		in.close();rocessBuilder p1 = new ProcessBuilder("/bin/tcsh","-c","echo $llfibuild");

	    p1.redirectErrorStream(true);
	    Process pr1 = p1.start();
		BufferedReader in = new BufferedReader(new InputStreamReader(pr1.getInputStream()));
	    String line;
	    while ((line = in.readLine()) != null) {

	        llfibuildPath = line;
	    }
	    pr1.waitFor();
	    pr1.destroy();
		in.close();
		        	}

	                i++;

	        } else {


	        }

	 for (final File fileEntry : files) {
	    	fileContent = new ArrayList<>();
	        if (fileEntry.isDirectory()) {
	        	i = 0;



	        		FileReader actualFile = new FileReader(fileEntry.getName()+"/"+fileEntry.getName()+".c");
	                BufferedReader inputFile = new BufferedReader(actualFile);
	                while ((line = inputFile.readLine()) != null)   {
	                    fileContent.add(line+"\n");

	                }

	                inputFile.close();
	                fileSelecMap.put(fileEntry.getName()+".c", fileContent);
	                fileNameLists.add(fileEntry.getName()+".c");
	                items =FXCollections.observableArrayList (fileNameLists);
	                fileList.setItems(items);
	                if(i == 0 && signFalg == false)
		        	{
	                	//fileList.getSelectionModel().select(0);
	                	signFalg = true;
	                	//System.out.println("inside if");
		        		currentProgramFolder = fileEntry.getName();
		        		currentFileName = fileEntry.getName()+".c";
		        		programTextArea.clear();
		        		for(int j = 0 ; j < fileContent.size(); j++)
		        		{

		        			programTextArea.appendText(fileContent.get(j));
		        		}
		        		compiletoIrButton.setDisable(false);
		        		 instrumentButton.setDisable(true);
		        		 profilingButton.setDisable(true);
		     compiletoIrButton.setDisable(false);
	 instrumentButton.setDisable(true);
	 profilingButton.setDisable(true);
	 runtimeButton.setDisable(true);
	 injectfaultButton.setDisable(true);   		 runtimeButton.setDisable(true);
		        		 injectfaultButton.setDisable(true);

		        	}

	                i++;

	        } else {


	        }

	    }   }*/
		}
		catch(IOException e)
		{
			System.out.println(e);
		}catch(InterruptedException e)
		{
			System.out.println(e);
		}
		
		configReader = new ConfigReader();

		// #SFIT
		fiResultDisplay.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>(){
			@Override
			public void changed(ObservableValue<? extends String> observable,
					String oldValue, String newValue) {
				if (oldValue == null || newValue == null) {
					return;
				}
				if (!oldValue.equals(newValue)) {
					generateInjectionResult(true);
				}
			}
		});
		// so that the user can't play with with UNTIL
		// they have selected batch mode
		fiResultDisplay.setVisible(false);
	}
	
	/**
	 * Updates the 'Fault Injection Status' and the 'Fault Summary' tab
	 * with the output data from the injection.
	 * @param forceUpdate - forces the two tab to update, even if nothing has changed
	 */
	private void generateInjectionResult(boolean forceUpdate) {
		if (faultInjectionCompleted == 1 || forceUpdate) {
			onGeneratingResultTable();
			generateFaultSummaryGraph();
			faultInjectionCompleted = 0;
		} 
	}
	
	public class CurrentState {
		public CurrentState(State s) {
			changeStateTo(s);
		}
		
		public void changeStateTo(State s) {
			switch (s) {
			case COMPILE_COMPLETED:
				break;
			case IMPORT_FILE:
				break;
			case IMPORT_FILE_COMPLETED:
				break;
			case INJECT_FAULT_COMPLETED:
				break;
			case INSTRUMENT_COMPLETED:
				break;
			case PROFILING_COMPLETED:
				break;
			case RUNTIME_OPTIONS_COMPLETED:
				break;
			default:
				break;
			}
		}
	}
	
	public enum State {
		IMPORT_FILE,
		IMPORT_FILE_COMPLETED,
		COMPILE_COMPLETED,
		INSTRUMENT_COMPLETED,
		PROFILING_COMPLETED,
		RUNTIME_OPTIONS_COMPLETED,
		INJECT_FAULT_COMPLETED;
	}
}
