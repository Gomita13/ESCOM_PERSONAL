import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args){
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Ingresa la direccion del servidor: ");
			String host = reader.readLine();
			System.out.println("Ingresa el puerto: ");
			int port = Integer.parseInt(reader.readLine());
			Socket server = new Socket(host,port);

			DataInputStream dis = new DataInputStream(server.getInputStream());
			DataOutputStream dos = new DataOutputStream(server.getOutputStream());

			System.out.println("Ingresa la boleta: ");
			long boleta = Long.parseLong(reader.readLine());
			dos.writeLong(boleta);
			dos.flush();

			System.out.println("Ingresa el nombre: ");
			String nombre = reader.readLine();
			dos.writeUTF(nombre);
			dos.flush();

			System.out.println("Ingresa la edad: ");
			int edad = Integer.parseInt(reader.readLine());
			dos.writeInt(edad);
			dos.flush();

			long tamanio = dis.readLong();
			System.out.println("Me va a llegar un array de tamanioo: "+tamanio);
			byte[] arr = new byte[(int)tamanio];
			dis.read(arr,0,(int) tamanio);
			System.out.println("Recibo los bytes");

			double valor = dis.readDouble();
			System.out.println("Valor obtenido: "+valor+"\nRetornando...");
			dos.writeDouble(valor);

			boolean resultado = dis.readBoolean();
			if(resultado){
				System.out.println("Boolean true");
			}else{
				System.out.println("Boolean false");
			}

			dis.close();
			dos.close();
			server.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
}