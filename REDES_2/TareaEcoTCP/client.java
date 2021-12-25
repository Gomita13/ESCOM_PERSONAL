import java.net.*;
import java.io.*;

public class client {
	public static void main (String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Escriba la direccion del servidor: ");
			String host = reader.readLine();
			System.out.println("Escriba el puerto: ");
			int port = Integer.parseInt(reader.readLine());

			Socket mySocket = new Socket(host,port);
			BufferedReader serverReader = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
			PrintWriter serverPrint	= new PrintWriter(new OutputStreamWriter(mySocket.getOutputStream()));

			System.out.println("Escriba el mensaje que desea enviar: ");
			String message = reader.readLine();
			
			serverPrint.println(message);
			serverPrint.flush();

			System.out.println("Recibimos un mensaje del servidor: ");
			message = serverReader.readLine();
			System.out.println("Mensaje: "+message);

			reader.close();
			serverReader.close();
			serverPrint.close();
			mySocket.close();
		} catch(Exception err) {
			err.printStackTrace();
		}
	}
}