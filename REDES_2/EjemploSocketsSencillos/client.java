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
			String message = serverReader.readLine();
			System.out.print("\nRecibimos un mensaje desde el servidor\nMensaje: "+message+"\n");
			reader.close();
			serverReader.close();
			mySocket.close();
		} catch(Exception err) {
			err.printStackTrace();
		}
	}
}