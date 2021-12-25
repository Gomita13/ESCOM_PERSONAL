import javax.swing.*;
import javax.swing.text.html.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class ChatGUI extends JFrame implements ActionListener{

	private static JEditorPane pnMsgs;
	private JScrollPane scpMsgs;
	private JPanel pnlUsers;
	private JTextArea txtMsg;
	private JButton btnSend, btnExit;
	private static volatile String aux;
	private JLabel lblUsers;
	private JList<String> lstUsers;
	private static DefaultListModel<String> model = new DefaultListModel<>();
	static String userName;
	private static Chat chat;
	static boolean active = true;
	Thread messageService;
	private String privado = "";
	private HTMLEditorKit kit = new HTMLEditorKit();

	public ChatGUI(){
		//Construimos la interfaz
		pnMsgs = new JEditorPane();
		pnMsgs.setBounds(15,15,750,600);
		pnMsgs.setEditable(false);
		pnMsgs.setContentType("text/html");
		pnMsgs.setEditorKit(kit);
		pnMsgs.setBorder(BorderFactory.createEmptyBorder());

		StyleSheet style = kit.getStyleSheet();
		style.addRule("body{background-color:rgb(80,51,91);color:white;font-family:Helvetica,sans-serif;font-size:14px}");
		style.addRule(".msg{color:rgb(255,154,0)}");
		style.addRule(".join{color:rgb(10,255,0)}");
		style.addRule(".lft{color:rgb(201,0,255)}");
		style.addRule(".priv{color:rgb(255,0,0)}");

		scpMsgs = new JScrollPane(pnMsgs);
		scpMsgs.setBounds(15,15,750,600);
		scpMsgs.setBorder(BorderFactory.createEmptyBorder());

        pnlUsers = new JPanel();
        pnlUsers.setBounds(790,15,165,600);
        pnlUsers.setBackground(new Color(162,71,82));
        pnlUsers.setLayout(null);

        lblUsers = new JLabel("Usuarios online",SwingConstants.CENTER);
        lblUsers.setBounds(0,0,165,40);
        lblUsers.setForeground(new Color(255,154,0));
        lblUsers.setFont(new Font("Consolas",Font.BOLD,18));

        lstUsers = new JList(model);
        lstUsers.addListSelectionListener(new ListSelectionListener(){
        	@Override
        	public void valueChanged(ListSelectionEvent event){
        		sendToUser(event);
        	}
        });
        lstUsers.setBounds(0,40,165,570);
        lstUsers.setFont(new Font("Consolas",Font.BOLD,16));
        lstUsers.setBackground(new Color(92,39,129));
        lstUsers.setForeground(new Color(255,154,0));

        pnlUsers.add(lblUsers);
        pnlUsers.add(lstUsers);

        txtMsg = new JTextArea();
        txtMsg.setBounds(15,630,750,105);
        txtMsg.setBackground(new Color(60,9,50));
        txtMsg.setFont(new Font("Arial",Font.BOLD,16));
        txtMsg.setForeground(new Color(255,255,255));

        btnSend = new JButton("Enviar");
        btnSend.setBounds(793,635,160,45);
        btnSend.setBackground(new Color(10,255,0));
        btnSend.setFont(new Font("Arial",Font.BOLD,16));
        btnSend.setBorder(BorderFactory.createEmptyBorder());
        btnSend.addActionListener(this);

        btnExit = new JButton("Salir");
        btnExit.setBounds(793,690,160,45);
        btnExit.setBackground(new Color(201,0,255));
        btnExit.setBorder(BorderFactory.createEmptyBorder());
        btnExit.setFont(new Font("Arial",Font.BOLD,16));
        btnExit.addActionListener(this);

        aux = "";

        messageService = new Thread(new ReadMessages());
        messageService.start();
		//Propiedades de la ventana
		this.add(scpMsgs);
		this.add(pnlUsers);
		this.add(txtMsg);
		this.add(btnSend);
		this.add(btnExit);
		this.setSize(1000,800);
		this.setTitle("Chat: "+userName);
		this.setLocationRelativeTo(null);
		this.setLayout(null);
		this.setResizable(false);
		this.getContentPane().setBackground(new Color(65,17,95));
		this.addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e){
                closeChat();
            }
        });
		this.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == btnExit){
			closeChat();
		}else{
			if(!privado.equals("")){ //Si hay un usuario destino
				chat.sendMessage(privado+txtMsg.getText());
				lstUsers.clearSelection();
				privado = "";
			}else{
				chat.sendMessage("<msj><"+userName+">"+txtMsg.getText());
			}
			txtMsg.setText("");
		}
	}

	private void sendToUser(ListSelectionEvent event){
		String userDest = (String)lstUsers.getSelectedValue();
		privado = "<privado><"+userName+"><"+userDest+">";
	}

	public static String readMessage(){
		return chat.receiveMessage();
	}

	public static void addMessage(String message){
		aux = aux + message + "<br>";
		pnMsgs.setText(aux);
	}

	public static void sendName(){
		chat.sendMessage("<online><"+userName+">");
	}

	public static void addOnlineUser(String userName){
		if(!model.contains(userName)){
			model.addElement(userName);
		}
	}

	public static void removeOnlineUser(String userName){
		model.removeElement(userName);
	}

	private void closeChat(){
		active = false;
		chat.exitChat(userName);
		System.exit(0);
	}

	public static void main(String[] args){
		userName = JOptionPane.showInputDialog("Ingresa tu nombre de usuario");
		chat = new Chat(userName);
		new ChatGUI();
	}
}

class ReadMessages implements Runnable {
	
	String message;

	ReadMessages(){}

	@Override
	public void run(){
		while(ChatGUI.active){
			message = ChatGUI.readMessage();
			if(!message.equalsIgnoreCase(" ")){
				//<inicio> Juan
				//<msj><Juan> Hola
				message = message.replace("<","");
				String[] params = message.split(">");
				switch(params[0]){
					case "inicio":
						ChatGUI.addMessage("<b class='join'> "+params[1]+"</b> ha entrado al chat");
						if(!params[1].equals(ChatGUI.userName)){ 
							// Si no se trata de mi, voy a enviar mi nombre para que lo registren
							ChatGUI.sendName();
							//Como se conecto alguien nuevo, lo agrego a mi lista
							ChatGUI.addOnlineUser(params[1]);
						}
					break;
					case "msj":
						params[2] = params[2].replace(":)","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/risa.png>");
						params[2] = params[2].replace(":o","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/amor.png>");
						params[2] = params[2].replace(":s","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/enojo.png>");
						params[2] = params[2].replace("_loco_","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/loco.gif>");
						params[2] = params[2].replace("_homero_","<img src=http://tusimagenesde.com/wp-content/uploads/2015/01/gifs-animados-5.gif>");
						ChatGUI.addMessage("<b class='msg'> "+params[1]+":</b> "+params[2]);
					break;
					case "privado":
						if(params[2].equals(ChatGUI.userName)){ //Si el mensaje es para mi, muestramelo
							params[3] = params[3].replace(":)","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/risa.png>");
							params[3] = params[3].replace(":o","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/amor.png>");
							params[3] = params[3].replace(":s","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/enojo.png>");
							params[3] = params[3].replace("_loco_","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/loco.gif>");
							params[3] = params[3].replace("_homero_","<img src=http://tusimagenesde.com/wp-content/uploads/2015/01/gifs-animados-5.gif>");
							ChatGUI.addMessage("<b class='priv'> "+params[1]+" (para ti):</b> "+params[3]);	
						}else if(params[1].equals(ChatGUI.userName)){//Si el mensaje lo envie yo
							params[3] = params[3].replace(":)","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/risa.png>");
							params[3] = params[3].replace(":o","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/amor.png>");
							params[3] = params[3].replace(":s","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/enojo.png>");
							params[3] = params[3].replace("_loco_","<img src=file:///D:/Documents/Programs/Java/Redes2/Practica2/loco.gif>");
							params[3] = params[3].replace("_homero_","<img src=http://tusimagenesde.com/wp-content/uploads/2015/01/gifs-animados-5.gif>");
							ChatGUI.addMessage("<b class='priv'> Enviaste a "+params[2]+":</b> "+params[3]);	
						}
					break;
					case "fin":
						ChatGUI.addMessage("<b class='lft'> "+params[1]+"</b> ha salido del grupo");
						ChatGUI.removeOnlineUser(params[1]);
					break;
					case "online": //Me estan enviando los usuarios que hay en la sala
						if(!params[1].equals(ChatGUI.userName)){ //No puedo mandarme mensajes privados
							ChatGUI.addOnlineUser(params[1]);
						}
					break;
				}
			}
		}
	}
}