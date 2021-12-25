import java.net.*;
import java.io.*;

public class Client {
	public static void main(String [] args){
		try {

			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			InetAddress LOCAL_HOST = InetAddress.getByName("127.0.0.1");
			int PORT = 2000;
			byte[] buffer = new byte[20];
			int TAM = 20;

			DatagramSocket client = new DatagramSocket();
			
			System.out.println("Cliente iniciado\nEscriba un mensaje para el servidor:");
			String msg = reader.readLine();

			if((msg.length()%TAM) == 0){
				msg = msg + " ";
			}

			byte[] msgBytes = msg.getBytes();

			
			int offset = 0;
			int buffLength = msgBytes.length - offset;
			while(buffLength > 0){
				if(buffLength < TAM){
					DatagramPacket sendPacket = new DatagramPacket(msgBytes,offset,buffLength,LOCAL_HOST,PORT);
					client.send(sendPacket);
					buffLength = 0; //Salimos
				}else{
					DatagramPacket sendPacket = new DatagramPacket(msgBytes,offset,buffLength,LOCAL_HOST,PORT);
					client.send(sendPacket);
					offset += TAM;
					buffLength = msgBytes.length - offset;	
				}
			}

			System.out.println("Esperando una respuesta...");

			//Recibimos un packet
			StringBuffer msgBuff = new StringBuffer();	
			int msgLength = TAM; //Inicializamos para entrar al while
			offset = 0;
			//Recibimos el mensaje
			while(msgLength >= TAM){
				//Vamos a recibir paquetes de 20 bytes hasta que llegue el ultimo tramo
				DatagramPacket receivePacket = new DatagramPacket(buffer,buffer.length);
				client.receive(receivePacket);
				String data = new String(receivePacket.getData(),0,receivePacket.getLength());
				msgBuff.insert(offset,data);
				offset += msgLength;
				msgLength = receivePacket.getLength();
			}

			System.out.println("Recibo este mensaje: "+msgBuff);

		} catch(Exception e) {
			e.printStackTrace();
		}
	}
}