import java.awt.BorderLayout;
import java.awt.Container;
import java.io.File;

import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JFrame;

import net.claribole.zgrviewer.ZGRPanelViewer;


public class ZGRPanelViewerTest 
{
	public static void main(String[] args) 
	{
		String fileName = "src/main/resources/example_graph/graph.dot";
		
		File graphFile = new File(fileName);
		
		ZGRPanelViewer zgrPanel = new ZGRPanelViewer();
		
		zgrPanel.loadFile(graphFile);
		
		JFrame jFrame = new JFrame();
		Container contentPane = jFrame.getContentPane();
		
		contentPane.add(zgrPanel.getPanel());
		
		JComponent glassPane = zgrPanel.getGlassPane();
		
		JCheckBox jCheckBox = new JCheckBox("Test");
		
		contentPane.add(jCheckBox, BorderLayout.EAST);
		
		jFrame.setGlassPane(glassPane);
		
		jFrame.setSize(800, 800);

		jFrame.setVisible(true);
		
		try {
			Thread.sleep(30000);
		} catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
	}
	
}
