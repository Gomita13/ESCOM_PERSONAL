import java.net.*;
import java.io.*;

public class Server {
	public static void main(String[] args){
		try{
			DatagramSocket server = new DatagramSocket(2000);
			System.out.println("Servidor iniciado en el puerto 2000");
			for(;;){
				DatagramPacket pack = new DatagramPacket(new byte[2000],2000);
				server.receive(pack);
				System.out.println("Datagrama recibido desde: "+pack.getAddress()+":"+pack.getPort());
				String msg = new String(pack.getData(),0,pack.getLength());
				System.out.println("Mensaje: "+msg);
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
}