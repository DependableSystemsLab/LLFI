package application;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Class for reading in files from the gui/config folder.
 * @author phil
 *
 */
public class ConfigReader {
	private final static String CONFIG_PATH = Controller.llfibuildPath
			+ "gui/config/";

	private final static String customInstruction_list_PATH = CONFIG_PATH
			+ "customInstruction_list.txt";
	private final static String customRegister_list_PATH = CONFIG_PATH
			+ "customRegister_list.txt";
	private final static String customSoftwareFault_list_PATH = CONFIG_PATH
			+ "customSoftwareFault_list.txt";
	private final static String fault_type_PATH = CONFIG_PATH
			+ "fault_type.txt";
	private final static String instruction_list_PATH = CONFIG_PATH
			+ "instruction_list.txt";
	private final static String register_list_PATH = CONFIG_PATH
			+ "register_list.txt";

	private List<String> customInstruction;
	private List<String> customRegister;
	private List<String> customSoftwareFault;
	private List<String> faultType;
	private List<String> instruction;
	private List<String> register;

	public ConfigReader() {
		customInstruction = readFileIntoList(customInstruction_list_PATH);
		customRegister = readFileIntoList(customRegister_list_PATH);
		customSoftwareFault = readFileIntoList(customSoftwareFault_list_PATH);
		faultType = readFileIntoList(fault_type_PATH);
		instruction = readFileIntoList(instruction_list_PATH);
		register = readFileIntoList(register_list_PATH);
	}

	public List<String> getCustomInstruction() {
		return new ArrayList<String>(customInstruction);
	}

	public List<String> getCustomRegister() {
		return new ArrayList<String>(customRegister);
	}

	public List<String> getCustomSoftwareFault() {
		return new ArrayList<String>(customSoftwareFault);
	}

	public List<String> getFaultType() {
		return new ArrayList<String>(faultType);
	}

	public List<String> getInstruction() {
		return new ArrayList<String>(instruction);
	}

	public List<String> getRegister() {
		return new ArrayList<String>(register);
	}

	private List<String> readFileIntoList(String path) {
		BufferedReader reader;
		String line;
		List<String> list = new ArrayList<String>();
		try {
			reader = new BufferedReader(new FileReader(path));
			list = new ArrayList<String>();
			while ((line = reader.readLine()) != null) {
				list.add(line);
			}
			reader.close();
		} catch (IOException e) {
			System.err.println("ERROR: Unable to read " + path);
			e.printStackTrace();
		}
		return list;
	}
}
