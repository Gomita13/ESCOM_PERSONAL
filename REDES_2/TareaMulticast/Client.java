import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args){
		try{
			InetAddress GROUP = InetAddress.getByName("230.1.1.1");
			int PORT = 9000;
			MulticastSocket service = new MulticastSocket(PORT);
			service.setTimeToLive(0);
			service.joinGroup(GROUP);
			Thread msgsService = new Thread(new MsgsService(2000,service,PORT,GROUP));
			msgsService.start();
			String message = "Hola, soy "+args[0];
			byte[] buffer = message.getBytes();
			while(true){
				DatagramPacket sendPack = new DatagramPacket(buffer,buffer.length,GROUP,PORT);
				service.send(sendPack);
				Thread.sleep(3000);
			}
		}catch(Exception err){
			System.out.println("EROR (Client.main)");
			err.printStackTrace();
		}
	}
}

class MsgsService implements Runnable {
	
	int BUFF_SIZE;
	MulticastSocket service;
	int PORT;
	InetAddress GROUP;

	public MsgsService(int buffSize, MulticastSocket service, int port, InetAddress group){
		this.BUFF_SIZE = buffSize;
		this.service = service;
		this.PORT = port;
		this.GROUP = group;
	}

	@Override
	public void run(){
		try{
			while(true){
				byte[] buffer = new byte[BUFF_SIZE];
				DatagramPacket recPack = new DatagramPacket(buffer,buffer.length,GROUP,PORT);
				service.receive(recPack);
				System.out.println(new String(buffer,0,recPack.getLength(),"UTF-8"));
			}
		}catch(Exception e){
			System.out.println("ERROR (MsgsService.run)");
			e.printStackTrace();
		}
	}
}