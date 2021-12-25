import java.net.*;
import java.io.*;
public class Client {
    public static void main(String[] args){
        try{
            DatagramSocket cl = new DatagramSocket();
            System.out.print("Cliente iniciado, escriba un mensaje de saludo:");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String mensaje = br.readLine();
            byte[] b = mensaje.getBytes();
            String dst = "127.0.0.1";
            int pto = 2000;
            DatagramPacket p = new DatagramPacket(b,b.length,InetAddress.getByName(dst),pto);
            cl.send(p);
            System.out.println("Esperando una respuesta...");
            DatagramPacket p2 = new DatagramPacket(new byte[2000],2000,InetAddress.getByName(dst),pto);
            cl.receive(p2);
            String msj = new String(p2.getData(),0,p2.getLength());
            System.out.println("Respuesta: "+ msj);
            cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }//main
}
