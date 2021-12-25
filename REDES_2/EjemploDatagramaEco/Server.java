import java.net.*;
import java.io.*;
public class Server {
    public static void main(String[] args){
        try{
            DatagramSocket s = new DatagramSocket(2000);
            System.out.println("Servidor iniciado, esperando cliente");
            for(;;){
                DatagramPacket p = new DatagramPacket(new byte[2000],2000);
                s.receive(p);
                System.out.println("Datagrama recibido desde"+p.getAddress()+":"+p.getPort());
                String msj = new String(p.getData(),0,p.getLength());
                System.out.println("Con el mensaje:"+ msj);
                String resp = "Eco "+msj;
                byte[] resbts = resp.getBytes();
                DatagramPacket p2 = new DatagramPacket(resbts,resbts.length,p.getAddress(),p.getPort());
                s.send(p2);
                System.out.println("Mensaje enviado...");
            }//for
            //s.close()
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }//main
}
