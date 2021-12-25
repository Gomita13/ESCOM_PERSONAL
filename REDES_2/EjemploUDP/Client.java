import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args){
		try {
			DatagramSocket client = new DatagramSocket();
			System.out.println("Cliente iniciado, escriba un mensaje:");
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String msg = reader.readLine();
			byte[] b = msg.getBytes();
			int port = 2000;
			DatagramPacket pack = new DatagramPacket(b,b.length,InetAddress.getByName("127.0.0.1"),port);
			client.send(pack);
			client.close();
		} catch(Exception e) {
			e.printStackTrace();
		}	
	}
}