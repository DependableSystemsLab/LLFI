package application;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.URL;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.ResourceBundle;

import javax.swing.plaf.basic.BasicSplitPaneUI.KeyboardEndHandler;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.DragEvent;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import application.Controller;

public class FaultInjectionController implements Initializable{
	
	@FXML
	private TextField noOfRunsText;
	@FXML
	private TextField fiRegIndex;
	@FXML
	private TextField fiBitText;
	@FXML
	private TextField randomSeed;
	@FXML
	private Label fiIndexLabel;
	@FXML
	private Slider fiIndexSlider;
	@FXML
	private Label fiCycleLabel;
	@FXML
	private Slider fiCycleSlider;
	@FXML
	private ComboBox faulInjectionTypeCombo;
	@FXML
	private Label runCountLabel;
	private String noOfRuns;
	private String fiType;
	private String fiCycle;
	private String fiIndex;
	private ArrayList<String> faultTypeList;
	private ArrayList<String> fileNameLists;
	private ArrayList<String> resultList;
	private String fiBit;
	private boolean errorFlag;
	private String indexBound;
	FileReader inputFile;
	String str;
	String line;
	String subStr[];
	String fiTypefault;
	int index;
	int cycle;
	int regIndex;
	int bit;
	String status;
	String result;
	public String currentFolderName;
	public int runCount = 0;
	
	@FXML
	ObservableList<String> items;
	@FXML
	private void onClickAddRunOption(ActionEvent event){
		currentFolderName = Controller.currentProgramFolder;
		FileReader inputFile;
		String line;
		String fileContent = "";
		boolean runFlag = false;
		 
		try{
			inputFile = new FileReader(currentFolderName+"/input.yaml");
			
			
			if(runCount == 0)
			{
				BufferedReader bufferReader = new BufferedReader(inputFile);
			    while ((line = bufferReader.readLine()) != null)   {
		      	if(line.contains("runOption:"))
		      	{	runFlag = true;
			        break;
		      	}
		      	else
		      	{
		      		fileContent+=line+"\n";
		      	}
		      	
		        }
			    
			    File yamlFile = new File(currentFolderName+"/input.yaml");
		        FileOutputStream is = new FileOutputStream(yamlFile);
		        OutputStreamWriter osw = new OutputStreamWriter(is);    
		        Writer w = new BufferedWriter(osw);
		        w.write(fileContent);
			    if(runFlag)
			    {
			    	w.write("runOption:");
			    	runFlag = false;
			    }
			    	
			    else
			    	w.write("\nrunOption:");
			    
					w.write("\n    - run:");
					w.write("\n        numOfRuns: "+noOfRunsText.getText());
					w.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
					
					if(!fiRegIndex.getText().equalsIgnoreCase(""))
					w.write("\n        fi_reg_index: "+fiRegIndex.getText());
				
					if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
					w.write("\n        fi_cycle: "+fiCycleLabel.getText());
					
					if(!fiBitText.getText().equalsIgnoreCase(""))
					{
						w.write("\n        fi_bit: "+fiBitText.getText());
						if(fiRegIndex.getText().equalsIgnoreCase(""))
							w.write("\n        fi_reg_index: "+"0");
						if(fiCycleLabel.getText().equalsIgnoreCase("0"))
							w.write("\n        fi_cycle: "+fiCycleLabel.getText());
						if(fiIndexLabel.getText().equalsIgnoreCase("0"))
							w.write("\n        fi_index: "+fiIndexLabel.getText());
					
					}
				
					if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
					w.write("\n        fi_index: "+fiIndexLabel.getText());
					if(!randomSeed.getText().equalsIgnoreCase(""))
					w.write("\n        fi_random_seed: "+randomSeed.getText());
					w.close();
			    
			    
			    
			    
			    
			}
			else
			{

		    	FileWriter injectWrite = new FileWriter(currentFolderName+"/input.yaml",true);
		    	//injectWrite.write("\n\nrunOption:");
				injectWrite.write("\n\n    - run:");
				injectWrite.write("\n        numOfRuns: "+noOfRunsText.getText());
				injectWrite.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
				
				if(!fiRegIndex.getText().equalsIgnoreCase(""))
				injectWrite.write("\n        fi_reg_index: "+fiRegIndex.getText());
			
				if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
				injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
				
				if(!fiBitText.getText().equalsIgnoreCase(""))
				{
					injectWrite.write("\n        fi_bit: "+fiBitText.getText());
					if(fiRegIndex.getText().equalsIgnoreCase(""))
						injectWrite.write("\n        fi_reg_index: "+"0");
					if(fiCycleLabel.getText().equalsIgnoreCase("0"))
						injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
					if(fiIndexLabel.getText().equalsIgnoreCase("0"))
						injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
				
				}
			
				if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
				injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
				if(!randomSeed.getText().equalsIgnoreCase(""))
				injectWrite.write("\n        fi_random_seed: "+randomSeed.getText());
				injectWrite.close();
			}
			
			runCount++;
			runCountLabel.setText(runCount+" Run Option Added");
			
			noOfRunsText.setText("");
			faulInjectionTypeCombo.setValue("--Select--");
			fiRegIndex.setText("");
			fiRegIndex.setPromptText("null");
			fiBitText.setText("");
			fiBitText.setPromptText("null");
			randomSeed.setText("");
			randomSeed.setPromptText("null");
			fiCycleLabel.setText("0");
			fiIndexLabel.setText("0");
			fiIndexSlider.setValue(0);
			fiCycleSlider.setValue(0);
		}
		catch (IOException e) {
	        System.err.println("Exception Occured in writing to the input.yaml file");
	    }
		
	}
	@FXML
	private void onClickFaultInjection(ActionEvent event) {
		Parent root;
		try{
			 ObservableList<ResultTable> data;
			 final File folder = new File(Controller.currentProgramFolder+"/llfi/llfi_stat_output");
			 if(folder.exists())
			  deleteFilesInFolder(folder);
			  final File errorFolder = new File(Controller.currentProgramFolder+"/llfi/error_output");
			  if(errorFolder.exists())
			  deleteFilesInFolder(errorFolder);
			//runCount++;
			//faultCount.setVisible(true);
			//faultCount.setText("No.Of Fault Injections Added: "+runCount);
			
		    ProcessBuilder p = new ProcessBuilder("/bin/tcsh","-c",Controller.llfibuildPath+"bin/injectfault "+Controller.currentProgramFolder+"/llfi/"+Controller.currentProgramFolder+"-faultinjection.exe "+Controller.inputString);
		    
		    p.redirectErrorStream(true);
		    Process pr = p.start();
			BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
		    String line1;
		    while ((line1 = in1.readLine()) != null) {
		    	Controller.errorString.add(line1+"\n");
		    	if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
		    		errorFlag= true;
		    	
		        
		    }
		    pr.waitFor();
		   in1.close();
		   
		   
		   /*
		   root = FXMLLoader.load(getClass().getClassLoader().getResource("application/InjectFaultResult.fxml"));
	        Stage stage = new Stage();
	        stage.setTitle("Profiling");
	        stage.setScene(new Scene(root, 400, 100));
	        stage.show();*/
	        
		   //controller.flag =1;
		  // controller.onGeneratingResultTable();
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
				  Controller.errorString = new ArrayList<>();
				  Node  source = (Node)  event.getSource(); 
				  Stage stage  = (Stage) source.getScene().getWindow();
				  stage.close();
			  }
		  
	     
	      
			
		    
			
		}
		catch (IOException e) {
	        System.err.println("Problem writing to the file statsTest.txt");
	    } catch (InterruptedException e) {
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
	private void onChangeIndexSlider(MouseEvent e){
		
		int slideValue = (int)Math.round(fiIndexSlider.getValue());
		
		fiIndexLabel.setText(String.valueOf(slideValue));
	}
	
	@FXML
	private void onChangeRegIndexSlider(MouseEvent e){
		
		int slideValue1 = (int)Math.round(fiCycleSlider.getValue());
		
		fiCycleLabel.setText(String.valueOf(slideValue1));
	}
	
	@FXML
	private void checkForNumberRuns(KeyEvent event){
		String regex = "\\d+";
		if(noOfRunsText.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			noOfRunsText.setText("");
		}
	}
	
	@FXML
	private void checkForNumberRegister(KeyEvent event){
		String regex = "\\d+";
		if(fiRegIndex.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			fiRegIndex.setText("");
		}
	}
	@FXML
	private void checkForNumberBit(KeyEvent event){
		String regex = "\\d+";
		if(fiBitText.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			fiBitText.setText("");
		}
	}
	@FXML
	private void checkForNumberSeed(KeyEvent event){
		String regex = "\\d+";
		if(randomSeed.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			randomSeed.setText("");
		}
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		FileReader inputFile;
		try{
		inputFile = new FileReader("llfi.stat.totalindex.txt");
		BufferedReader bufferReader = new BufferedReader(inputFile);
        
       
        String line;
        
        while ((line = bufferReader.readLine()) != null)   {
        	indexBound = line.split("=")[1];
        	
        }
        bufferReader.close();
        fiIndexSlider.setMax(Double.parseDouble(indexBound));
        fiIndexSlider.setMajorTickUnit(Double.parseDouble(indexBound));
        //regCombo.getItems().removeAll(true);
        
        inputFile = new FileReader("llfi.stat.prof.txt");
		bufferReader = new BufferedReader(inputFile);
        
       
        while ((line = bufferReader.readLine()) != null)   {
        	if(line.contains("="))
        	indexBound = line.split("=")[1];
        	
        }
        bufferReader.close();
        fiCycleSlider.setMax(Double.parseDouble(indexBound));
        fiCycleSlider.setMajorTickUnit(Double.parseDouble(indexBound));
        
        inputFile = new FileReader("fault_type.txt");
		bufferReader = new BufferedReader(inputFile);
        
		faultTypeList = new ArrayList<String>();
       // String line;
        
        while ((line = bufferReader.readLine()) != null)   {
        	faultTypeList.add(line);
        	
        }
        bufferReader.close();
        items =FXCollections.observableArrayList (faultTypeList);
        //regCombo.getItems().removeAll(true);
        faulInjectionTypeCombo.setItems(items);
        faulInjectionTypeCombo.setPromptText("-- Select --");
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    // TODO
	}

}
