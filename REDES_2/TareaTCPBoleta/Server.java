import java.net.*;
import java.io.*;

public class Server {
	public static void main(String [] args){
		try {
			ServerSocket myServer = new ServerSocket(9000);
			System.out.println("Servidor iniciado en el puerto 9000");
			while(true){
				Socket client = myServer.accept();
				DataInputStream dis = new DataInputStream(client.getInputStream());
				DataOutputStream dos = new DataOutputStream(client.getOutputStream());

				long boleta = dis.readLong();
				System.out.println("Boleta: "+boleta);

				String nombre = dis.readUTF();
				System.out.println("Nombre: "+nombre);

				int edad = dis.readInt();
				System.out.println("Edad: "+edad);

				long tamanio = 5;
				System.out.println("Tamanio enviado: "+tamanio);
				dos.writeLong(tamanio);
				dos.flush();
				
				byte[] bytes = new byte[]{1,2,3,4,5};
				dos.write(bytes);
				
				double valor = 10;
				System.out.println("Valor enviado: "+valor);
				dos.writeDouble(valor);
				dos.flush();

				double valorrt = dis.readDouble();
				System.out.println("Valor recibido: "+valorrt);

				boolean resultado = true;
				dos.writeBoolean(resultado);
				dos.flush();

				dis.close();
				dos.close();
				client.close();
			}
		} catch(Exception err){
			err.printStackTrace();
		}
	} 
}