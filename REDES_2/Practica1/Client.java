import javax.swing.JFileChooser;
import java.util.ArrayList;
import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args){
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			System.out.printf("Escriba la direccion del servidor: ");
	        String host = reader.readLine();
	        System.out.printf("Escriba el puerto: ");
	        int port = Integer.parseInt(reader.readLine());

	        Socket server = new Socket(host, port);

	        System.out.println("Ingresa el tamanio de buffer");
			int buffSize = Integer.parseInt(reader.readLine());
			server.setSendBufferSize(buffSize);
			server.setReceiveBufferSize(buffSize);

	        DataOutputStream dos = new DataOutputStream(server.getOutputStream());
	        dos.writeInt(buffSize); //Envio el tamaño del buffer

			System.out.println("Desea habilitar el algoritmo de Nagle? [s/n]");
			char enabled = (char) reader.read();
			boolean nagle = false;
			if (enabled == 's'){
				System.out.println("Nagle habilitado");
				nagle = true;
			}else{
				System.out.println("Nagle inhabilitado");
				nagle = false;
			}
			server.setTcpNoDelay(nagle);
			dos.writeBoolean(nagle); //Envio la opcion de Nagle

			System.out.println("Seleccione los archivos a enviar");
			File[] files = null;
			JFileChooser chooser = new JFileChooser();
			chooser.setMultiSelectionEnabled(true);
			int res = chooser.showOpenDialog(null);
			if(res == JFileChooser.APPROVE_OPTION){
				files = chooser.getSelectedFiles();
				dos.writeInt(files.length); //Envio la cantidad de archivos		
			}else{
				dos.close();
				server.close();
				System.exit(1);
			}

			for(int i = 0; i < files.length; i++){
				byte[] buff = new byte[buffSize];
				String filePath = files[i].getAbsolutePath();
				
				String name = files[i].getName();
				dos.writeUTF(name); //Envio el nombre del archivo
				dos.flush();
				
				long size = files[i].length();
				dos.writeLong(size); //Envio el tamaño del archivo
				dos.flush();
				
				System.out.println("Enviando: "+name+", "+size+" bytes");
				DataInputStream dis = new DataInputStream(new FileInputStream(filePath));
				long sent = 0;
	            int percent, n;

	            while (sent < size){
	                 n = dis.read(buff);
	                 dos.writeInt(n);
	                 dos.flush();
	                 dos.write(buff,0,n);
	                 dos.flush();
	                 sent = sent + n;
	                 percent = (int)(sent*100/size);
	                 System.out.print("Enviado: "+percent+"%\r");
	             }//While

	            System.out.print("\n\nArchivo "+name+" enviado");
                dis.close();
			}//Terminamos con todos los archivos
			dos.close();
			server.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
}