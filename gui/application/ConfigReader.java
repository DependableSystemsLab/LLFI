package application;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;

/**
 * Class for reading the GUI config file from gui/gui_config.yaml
 * @author phil
 *
 */
public class ConfigReader {
	private final static String CONFIG_PATH = Controller.llfibuildPath
			+ "gui/gui_config.yaml";

	private List<String> customInstruction;
	private List<String> customRegister;
	private List<String> customSoftwareFault;
	private List<String> faultType;
	private List<String> instruction;
	private List<String> register;

	@SuppressWarnings("unchecked")
	public ConfigReader() {
		Yaml y = new Yaml();
		Map<String, Object> config = null;
		try {
			config = (Map<String, Object>) y.load(new FileInputStream(CONFIG_PATH));
		} catch (FileNotFoundException e) {
			System.err.println("GUI Config file (" + CONFIG_PATH + ") not found!");
			e.printStackTrace();
		}
		
		if (config.get("custom_instructions") == null) {
			customInstruction = new ArrayList<String>();
		} else {
			customInstruction = (List<String>) config.get("custom_instructions");
		}
		if (config.get("custom_registers") == null) {
			customRegister = new ArrayList<String>();
		} else {
			customRegister = (List<String>) config.get("custom_registers");
		}
		if (config.get("custom_software_faults") == null) {
			customSoftwareFault = new ArrayList<String>();
		} else {
			customSoftwareFault = (List<String>) config.get("custom_software_faults");
		}
		
		faultType = (List<String>) config.get("fault_type");
		instruction = (List<String>) config.get("instructions");
		register = (List<String>) config.get("registers");
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
}
