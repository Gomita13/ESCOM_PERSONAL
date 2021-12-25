import java.net.*;
import java.io.*;

public class Server {
	public static void main(String [] args){
		try{
			
			int PORT = 2000;
			DatagramSocket server = new DatagramSocket(PORT);
			System.out.println("Servidor iniciado en el puerto "+PORT);
			InetAddress LOCAL_HOST = InetAddress.getByName("127.0.0.1");
			int clientPort = PORT;
			int TAM = 20;

			while(true){
				StringBuffer msgBuff = new StringBuffer();	
				int msgLength = TAM; //Inicializamos para entrar al while
				int offset = 0;
				byte[] msgBytes = new byte[TAM];
				//Recibimos el mensaje
				while(msgLength >= TAM){
					//Vamos a recibir paquetes de 20 bytes hasta que llegue el ultimo tramo
					DatagramPacket receivePacket = new DatagramPacket(msgBytes,msgBytes.length);
					server.receive(receivePacket);
					String data = new String(receivePacket.getData(),0,receivePacket.getLength());
					System.out.println(data);
					msgBuff.insert(offset,data);
					offset += msgLength;
					msgLength = receivePacket.getLength();
					clientPort = receivePacket.getPort();
				}

				//Preparamos y enviamos la respuesta
				String eco = "Eco " + msgBuff.toString();
				byte[] bytes = eco.getBytes();

				System.out.println("Vamos a enviar: "+eco);
				msgBytes = eco.getBytes();
				offset = 0;
				int buffLength = msgBytes.length - offset;
				
				while(buffLength > 0){
					if(buffLength < TAM){
						DatagramPacket sendPacket = new DatagramPacket(msgBytes,offset,buffLength,LOCAL_HOST,clientPort);
						server.send(sendPacket);
						buffLength = 0; //Salimos
					}else{
						DatagramPacket sendPacket = new DatagramPacket(msgBytes,offset,buffLength,LOCAL_HOST,clientPort);
						server.send(sendPacket);
						offset += TAM;
						buffLength = msgBytes.length - offset;	
					}
				}

				System.out.println("Respuesta enviada...");
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}