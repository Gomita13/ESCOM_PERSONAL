import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class GUI extends JFrame implements ActionListener{
	
	private String[] symbols = {"<-","C","%","+","7","8","9","-","4","5","6","*","1","2","3","/","0",".","S","="};
	private JButton[] buttons;
	private JLabel lblRes;
	private int padding = 10, x = padding, y = 100;
	private double a = 0, b = 0;
	private char operation = ' ';
	private String text;
	private Calculator stub; 

	public GUI(){

		buttons = new JButton[symbols.length];

		for(int i = 0; i < symbols.length; i++){
			buttons[i] = new JButton(symbols[i]);	
			buttons[i].setBounds(x,y,50,50);
			x = x + 50 + padding;
			if(x == 250) {
				y = y + 50 + padding;
				x = padding;
			}
			buttons[i].setFont(new Font("Arial", Font.BOLD, 17));
			buttons[i].addActionListener(this);
			buttons[i].setBackground(new Color(181,182,228));
			this.add(buttons[i]);
		}

		buttons[0].setBackground(new Color(79,67,174));
		buttons[0].setForeground(Color.WHITE);
		buttons[1].setBackground(new Color(79,67,174));
		buttons[1].setForeground(Color.WHITE);
		buttons[2].setBackground(new Color(79,67,174));
		buttons[2].setForeground(Color.WHITE);
		buttons[3].setBackground(new Color(79,67,174));
		buttons[3].setForeground(Color.WHITE);
		buttons[7].setBackground(new Color(79,67,174));
		buttons[7].setForeground(Color.WHITE);
		buttons[11].setBackground(new Color(79,67,174));
		buttons[11].setForeground(Color.WHITE);
		buttons[15].setBackground(new Color(79,67,174));
		buttons[15].setForeground(Color.WHITE);
		buttons[17].setBackground(new Color(79,67,174));
		buttons[17].setForeground(Color.WHITE);
		buttons[18].setBackground(new Color(79,67,174));
		buttons[18].setForeground(Color.WHITE);
		buttons[19].setBackground(new Color(79,67,174));
		buttons[19].setForeground(Color.WHITE);

		lblRes = new JLabel("",SwingConstants.RIGHT);
		lblRes.setBounds(10,20,230,60);
		lblRes.setOpaque(true);
		lblRes.setFont(new Font("Calculator",Font.BOLD,20));
		lblRes.setBackground(new Color(147,161,74));

		initRMI("127.0.0.1");

		this.getContentPane().setBackground(new Color(206,201,204));
		this.add(lblRes);
		this.setLayout(null);
		this.setSize(270,450);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent event){
		String button = ((JButton) event.getSource()).getText();
		if(isNumber(button) || button.equalsIgnoreCase(".")){
			text = lblRes.getText();
			text = text + button;
			lblRes.setText(text);
		}else if (button.equalsIgnoreCase("S")){
			text = lblRes.getText();
			if(text.charAt(0) == '-'){
				text = text.substring(1,text.length());
				text = "+"+text;
			}else{
				text = "-" + text;
			}
			lblRes.setText(text);
		}else if (button.equalsIgnoreCase("C")){
			a = 0; b = 0; lblRes.setText("");
		}else if (button.equalsIgnoreCase("<-")){
			text = lblRes.getText();
			text = text.substring(0,text.length()-1);
			lblRes.setText(text);
		}else if(button.equalsIgnoreCase("=")){
			b = Double.parseDouble(lblRes.getText());
			calculate(a,b,operation);
		}else{
			a = Double.parseDouble(lblRes.getText());
			operation = button.charAt(0);
			lblRes.setText(""); //Esperando otro numero
		}
	}	

	private boolean isNumber(String value){
		try{
			double n = Double.parseDouble(value);
			return true;
		}catch(NumberFormatException e){
			return false;
		}
	}

	private void calculate(double a, double b, char op){
		try{
			double res = 0;
			switch(op){
				case '+':
					res = stub.add(a,b);
				break;
				case '-':
					res = stub.subs(a,b);
				break;
				case '*':
					res = stub.mult(a,b);
				break;
				case '/':
					res = stub.div(a,b);
				break;
				case '%':
					res = stub.mod(a,b);
				break;
			}
			lblRes.setText(String.valueOf(res));
			return;
		}catch(Exception e){
			System.out.println("ERROR (GUI.calculate): ");
			e.printStackTrace();
		}
	}

	private void initRMI(String host){
		try{
			Registry reg = LocateRegistry.getRegistry(host);
			this.stub = (Calculator) reg.lookup("Calculator");
			return;
		}catch(Exception e){
			System.out.println("ERROR (GUI.initRMI): ");
			e.printStackTrace();
		}
	}

	public static void main(String args[]){
		new GUI();
	}

}