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
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
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
import javafx.scene.control.Slider;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
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
private TableView<ResultTable> resultTable;
@FXML
private TableColumn<ResultTable,Integer> tFiRun;
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
private CategoryAxis xAxis;
@FXML
private NumberAxis yAxis;
@FXML
private BarChart<Integer, String> resultSummary;
@FXML
private Label UploadLabel;

@FXML
private Button instrumentButton;
@FXML
private Button profilingButton;
@FXML
private Button injectfaultButton;
@FXML
private TextArea errorTextArea;
@FXML 
private TextArea programInputText;
XYChart.Series<Integer, String> series = new XYChart.Series<Integer,String>();
static public String currentProgramFolder;
static public String llfibuildPath=null;
static public String currentFileName;


public ArrayList<String> fileNameLists = new ArrayList<>();
public ArrayList<String> registerList = new ArrayList<>();
private ArrayList<String> resultFileNameLists;
private ArrayList<String> resultErrorFileNameLists;
private ArrayList<String> resultOutputFileNameLists;
private ArrayList<String> resultList;
private String indexBound;
private String cycleBound;
public int runCount = 0;
public int flag = 0;
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
private List<List<String>> FileLists;
private List<String> fileContent;
private int fileCount = 0;
private boolean errorFlag;
private LinkedHashMap<String, List<String>> fileSelecMap = new LinkedHashMap<>();
static public List<String> errorString;
static public String inputString;

public ArrayList<String> rowCount = new ArrayList<>();
@FXML
ObservableList<ResultTable> data1 =  FXCollections.observableArrayList() ;
@FXML
ObservableList<Table> data = FXCollections.observableArrayList();
@FXML
ObservableList<String> row = FXCollections.observableArrayList();
public ArrayList<String> parameter = new ArrayList<>();
@FXML
private void onClickProfiling(ActionEvent event){
	Parent root;
	FileReader inputFile;
	ProcessBuilder p;
	try{
		inputString = programInputText.getText();
		programInputText.setEditable(false);
		errorString = new ArrayList<>();
		//System.out.println("inputString;"+inputString);
		
			p = new ProcessBuilder("/bin/tcsh","-c",llfibuildPath+"bin/profile "+currentProgramFolder+"/llfi/"+currentProgramFolder+"-profiling.exe "+inputString);
		
		
	    
	    p.redirectErrorStream(true);
	    Process pr = p.start();
		BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
	    String line1;
	    while ((line1 = in1.readLine()) != null) {
	    	//System.out.printl
	    	errorString.add(line1+"\n");
	    	if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
	    		errorFlag= true;
	    	
	    }
	    pr.waitFor();
	    in1.close();
	  
	    inputFile = new FileReader("llfi.stat.totalindex.txt");
		BufferedReader bufferReader = new BufferedReader(inputFile);
      
		
        String line;
      
        while ((line = bufferReader.readLine()) != null)   {
      	indexBound = line.split("=")[1];
      	
        }
      
      bufferReader.close();
      inputFile = new FileReader("llfi.stat.prof.txt");
		bufferReader = new BufferedReader(inputFile);
      
     
      while ((line = bufferReader.readLine()) != null)   {
      	if(line.contains("="))
      		cycleBound = line.split("=")[1];
      	
      }
     
      bufferReader.close();
      
      ObservableList<Table> data =
              FXCollections.observableArrayList(
              new Table(Integer.parseInt(indexBound),Integer.parseInt(cycleBound)));
      
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
           injectfaultButton.setDisable(false);
       }
	    
        
        //profilingButton.setDisable(true);
        
	    
	    
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
public void onClickInjectFaultOkHandler(ActionEvent event){
	
}
@FXML
public void onGeneratingResultTable(){
	try{
		sdcCount = 0;
		data1 =  FXCollections.observableArrayList() ;
		resultList = new ArrayList<String>();
		final File folder = new File(currentProgramFolder+"/llfi/llfi_stat_output");
		listFilesForFolder(folder);
		final File errorFolder = new File(currentProgramFolder+"/llfi/error_output");
		listFilesForErrorFolder(errorFolder);
		final File outputFolder = new File(currentProgramFolder+"/llfi/std_output");
		listFilesForOtputFolder(outputFolder);
		runCount = 0;
		for(int i = 0; i < resultFileNameLists.size();i++)                                

		   {
			if(resultFileNameLists.get(i).contains("trace"))
			{
				
			}
			else
			{
				resultList = new ArrayList<String>();
				runCount++;
				                              
	     
				inputFile = new FileReader(currentProgramFolder+"/llfi/llfi_stat_output/"+resultFileNameLists.get(i));
				BufferedReader bufferReader = new BufferedReader(inputFile);
				  while ((line = bufferReader.readLine()) != null)   {
					  
					  str = line.split(":")[1];
					  
					  subStr = str.split(",");
					  for(int j = 0; j < subStr.length;j++)
					  {
						 
						  resultList.add(subStr[j].split("=")[1]);
						 
					  }
				      	
				      }
				  
				  if(resultErrorFileNameLists.size()>0){
					  for(int k = 0;k< resultErrorFileNameLists.size();k++)
					  {
						  
						  if(resultErrorFileNameLists.get(k).contains(resultFileNameLists.get(i).substring(28, 31)))
						  {
							  result = "";
							  status = "Injected";
							  errorFile = new FileReader(currentProgramFolder+"/llfi/error_output/"+resultErrorFileNameLists.get(k));
							  BufferedReader bufferReader1 = new BufferedReader(errorFile);
							  while ((line = bufferReader1.readLine()) != null)   {
								 
									  
								  
								  result = result+line+";";
							      	
							      }
							  bufferReader1.close();
							  break;
							  
						  }
						  else
						  {
							  status = "Not Injected ";
							  result ="Nil";
						  }
					  }
					 
						 
					  
				  }
				  else
				  {
					  status = "Not Injected ";
					  result ="Nil";
				  }
				  if(resultOutputFileNameLists.size()>0)
				  {
					  FileReader baseline = new FileReader(currentProgramFolder+"/llfi/baseline/golden_std_output");
					  BufferedReader bufferReader1 = new BufferedReader(baseline);
					  String stdValue="";
					  String progValue="";
					  while ((line = bufferReader1.readLine()) != null)   {
							 
						  stdValue += line;						      	
					      }
					  
					  bufferReader1.close();
					  for(int k = 0;k< resultOutputFileNameLists.size();k++)
					  {
						  
						  if(resultOutputFileNameLists.get(k).contains(resultFileNameLists.get(i).substring(28, 31)))
						  {
							  FileReader progOutputFile= new FileReader(currentProgramFolder+"/llfi/std_output/"+resultOutputFileNameLists.get(k));
							  BufferedReader bufferReader2 = new BufferedReader(progOutputFile);
							  while ((line = bufferReader2.readLine()) != null)   {
									 
								  progValue += line;						      	
							      }
							  
							  bufferReader2.close();
							  if(stdValue.equalsIgnoreCase(progValue))
							  {
								  sdc = "Not Occured";
							  }
							  else
							  {
								  sdcCount++;
								  sdc = "Occured";
							  }
						  }
					  }
				  }
				  else
				  {
					  sdc = "NA";
				  }
				  
				  data1.add(new ResultTable(runCount,resultList.get(0),Integer.parseInt(resultList.get(1)),Integer.parseInt(resultList.get(2)),
	            		  Integer.parseInt(resultList.get(3)),Integer.parseInt(resultList.get(4)),sdc,
	    				  status,result));
				 
				  bufferReader.close();
			}
			
			
		   }
		tFiRun.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>("noOfRuns"));
	    tFiType.setCellValueFactory(new PropertyValueFactory<ResultTable, String>("FaultInjectionType"));
	    tFiIndex.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>("index"));
	    tFiCycle.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>("cycle"));
	    tFiRegIndex.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>("regIndex"));
	    tFiBit.setCellValueFactory(new PropertyValueFactory<ResultTable, Integer>("bit"));
	    tFiSdc.setCellValueFactory(new PropertyValueFactory<ResultTable, String>("sdc"));
	    tFiStatus.setCellValueFactory(new PropertyValueFactory<ResultTable, String>("status"));
	    tFiResult.setCellValueFactory(new PropertyValueFactory<ResultTable, String>("result"));
	    resultTable.setItems(data1);
	 
	}
	catch(IOException e)
	{
		e.printStackTrace();
		 System.out.println(e.getMessage());
	}
	
	
}

@FXML
private void generateFaultSummaryGraph(){
	//resultSummary.setVisible(true);
	int faultCount =0;
	hangedCount = 0;
	crashedCount = 0;
	try{
	resultList = new ArrayList<String>();
	final File folder = new File(currentProgramFolder+"/llfi/llfi_stat_output");
	
	listFilesForFolder(folder);
	final File errorFolder = new File(currentProgramFolder+"/llfi/error_output");
	listFilesForErrorFolder(errorFolder);
	for(int k = 0;k< resultErrorFileNameLists.size();k++)
	   {
		errorFile = new FileReader(currentProgramFolder+"/llfi/error_output/"+resultErrorFileNameLists.get(k));
		  BufferedReader bufferReader1 = new BufferedReader(errorFile);
		  while ((line = bufferReader1.readLine()) != null)   {
			  if(line.contains("crashed"))
				  crashedCount++;
			  else if(line.contains("hanged"))
				  hangedCount++;
		  }
	   }
	
	
	
	String[] params = {"Faults Injected","Crashed","Hanged","SDC"};                               

    // Convert it to a list and add it to our ObservableList of months.
   // row.addAll(Arrays.asList(params));
    
   
	//row = FXCollections.observableArrayList(parameter);
	xAxis.setLabel("Parameters");
	yAxis.setLabel("Total.No.Of.Fault Injections");
	xAxis.setCategories(FXCollections.<String>observableArrayList(Arrays.asList(params)));
	xAxis.setAutoRanging(false);
	xAxis.invalidateRange(Arrays.asList(params));
	
	yAxis.setAutoRanging(false);
	yAxis.setLowerBound(0);
	if(resultFileNameLists.size()>0)
	{
		faultCount =0;
		for(int i = 0;i <resultFileNameLists.size();i++)
		{
			if(resultFileNameLists.get(i).contains("trace"))
			{
				
			}
			else
			{
				faultCount++;
			}
		}
	}
	yAxis.setUpperBound(faultCount);
	yAxis.setTickUnit(1);
	
	 series = new XYChart.Series<Integer,String>();
	 XYChart.Data<Integer, String> faultData = new XYChart.Data<Integer,String>(resultErrorFileNameLists.size(),"Faults Injected");
     series.getData().add(faultData);
     
     
     faultData = new XYChart.Data<Integer,String>(crashedCount,"Crashed");
     series.getData().add(faultData);
     
     faultData = new XYChart.Data<Integer,String>(hangedCount,"Hanged");
     series.getData().add(faultData);
     
     faultData = new XYChart.Data<Integer,String>(sdcCount,"SDC");
     series.getData().add(faultData);
	
	// XYChart.Series<String, Integer> series = createMonthDataSeries(monthCounter);
     resultSummary.getData().add(series);
     

	}catch(IOException e)
	{
		e.printStackTrace();
		 System.out.println(e.getMessage());
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
public void listFilesForFolder(final File folder) {
	resultFileNameLists = new ArrayList<String>();
    for (final File fileEntry : folder.listFiles()) {
    	
        if (fileEntry.isDirectory()) {
            listFilesForFolder(fileEntry);
        } else {
           
            resultFileNameLists.add(fileEntry.getName());
        }
    }
}

@FXML
private void onClickCompileToIr(ActionEvent event){
	Parent root;
	try{
		
		String cmd = "echo $llfibuild";
		//System.out.println(System.getenv());
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
        String command = llfibuildPath+"tools/compiletoIR --readable -o "+currentProgramFolder+"/"+currentProgramFolder+".ll "+currentProgramFolder+"/"+currentFileName;
        
		Process p = Runtime.getRuntime().exec(command);
		BufferedReader in1 = new BufferedReader(new InputStreamReader(p.getErrorStream()));
		errorTextArea.clear();
		errorString = new ArrayList<>();
	    while ((line = in1.readLine()) != null) {
	    	
	    	errorString.add(line+"\n");
	       
	    }
		in1.close();
	    p.waitFor();
	   
	    p.destroy();
	    
	    if(errorString.size()==0)
	    {
	    	root = FXMLLoader.load(getClass().getClassLoader().getResource("application/compileToIR.fxml"));
	        Stage stage = new Stage();
	        stage.setTitle("Compiling To IR Result");
	        stage.setScene(new Scene(root, 500, 150));
	        stage.show();
	        //compiletoIrButton.setDisable(true);
	        instrumentButton.setDisable(false);
	        
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
	
	
}

@FXML
private void onClickInstrument(ActionEvent event) {
	 Parent root;
     try {
    	 
         root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Instrument.fxml"));
         Stage stage = new Stage();
         stage.setTitle("Instrument");
         stage.setScene(new Scene(root, 742, 569));
         stage.show();
         
         //instrumentButton.setDisable(true);
         profilingButton.setDisable(false);
     } catch (IOException e) {
         e.printStackTrace();
     }
}


	 

@FXML
private void onClickInjectFault(ActionEvent event) {
	 Parent root;
     try {
         root = FXMLLoader.load(getClass().getClassLoader().getResource("application/Profiling.fxml"));
         Stage stage = new Stage();
         stage.setTitle("Fault Injection");
         stage.setScene(new Scene(root, 600, 500));
         stage.show();
          flag = 1;
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

private static void configureFileChooser(
        final FileChooser fileChooser) {      
            
            fileChooser.getExtensionFilters().addAll(
               
                new FileChooser.ExtensionFilter("C", "*.c"),
                new FileChooser.ExtensionFilter("CPP", "*.cpp")
            );
    }
private void openFile(File file) {
    try{
    	fileContent = new ArrayList<>();
    	Path path = file.toPath();
        
        String fileInfo =path.toString();
        
        FileReader inputFile = new FileReader(fileInfo);
        BufferedReader bufferReader = new BufferedReader(inputFile);
        
        String fileName = path.getFileName().toString();
        fileNameLists.add(fileName);
        items =FXCollections.observableArrayList (fileNameLists);
        fileList.setItems(items);
        //Variable to hold the one line data
        String line;
       
        String folderName = fileName.split("\\.")[0];
       
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
        	programTextArea.clear();
        	 //System.out.println("Hello");
        	currentProgramFolder = folderName;
        	
        	currentFileName = fileName;
        	for(int i = 0 ; i < fileContent.size(); i++)
        	{
        		
        		programTextArea.appendText(fileContent.get(i));
        	}
        	 compiletoIrButton.setDisable(false);
        	 instrumentButton.setDisable(true);
        	 profilingButton.setDisable(true);
        	 injectfaultButton.setDisable(true);
        	
        }
        
        fileCount++;
        UploadLabel.setVisible(false);
        compiletoIrButton.setDisable(false);
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
	compiletoIrButton.setDisable(false);
	 instrumentButton.setDisable(true);
	 profilingButton.setDisable(true);
	 injectfaultButton.setDisable(true);
	
}
@FXML
private void onTabChange(){
	
	if(flag == 1 && errorString.size() == 0 )
	{
		programInputText.setEditable(true);
		onGeneratingResultTable();
		generateFaultSummaryGraph();
		flag = 0;
	}
	errorTextArea.clear();
	if(errorString.size()>0)
	{
		for(int i = 0; i < errorString.size();i++){
			//System.out.println("TAB -"+errorString.get(i));
			errorTextArea.appendText(errorString.get(i)+"\n");
		}
	}
	
	
		
	
}



@Override
public void initialize(URL url, ResourceBundle rb) {
	
	
	 
    // TODO
}    
}