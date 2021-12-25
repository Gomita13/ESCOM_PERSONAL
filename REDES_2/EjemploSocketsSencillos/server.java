import java.net.*;
import java.io.*;

public class server {

	private static int PORT = 1234;

	public static void main (String[] args) {
		try {
			ServerSocket myServer = new ServerSocket(PORT);
			System.out.println("Servidor iniciado en el puerto "+PORT+", esperando conexion");
			while (true) {
				Socket mySocket = myServer.accept();
				System.out.println("Conexion establecida");
				String message = "Hola clipetes";
				PrintWriter prntWtr = new PrintWriter(new OutputStreamWriter(mySocket.getOutputStream()));
				prntWtr.println(message);
				prntWtr.flush();
				prntWtr.close();
				mySocket.close();
			}
		} catch (Exception err) {
			err.printStackTrace();
		}
	}
}