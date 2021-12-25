import java.net.*;
import java.io.*;

public class Server {
    public static void main(String[] args){
        try{
            ServerSocket myServer = new ServerSocket(7000);
            System.out.println("Servidor iniciado en el puerto 7000");
            while(true){
                Socket client = myServer.accept();
                System.out.println("Conexion establecida con el cliente "+client.getInetAddress()+":"+client.getPort());
                
                DataInputStream dis = new DataInputStream(client.getInputStream());
                
                int buffSize = dis.readInt(); //Recibo tamaño buffer
                System.out.println("El tamanio del buffer es: "+buffSize);
                client.setSendBufferSize(buffSize);
                client.setReceiveBufferSize(buffSize);

                boolean nagle = dis.readBoolean(); //Recibo opcion Nagle
                client.setTcpNoDelay(nagle);
                if(nagle){
                    System.out.println("El algoritmo de Nagle esta habilitado");
                }else{
                    System.out.println("El algoritmo de Nagle esta deshabilitado");
                }

                int quant = dis.readInt(); //Recibo cantidad de archivos
                System.out.println("La cantidad de archivos es: "+quant);
                
                byte[] buff = new byte[buffSize];

                for(int i = 0; i < quant; i++){
                    try {        
                        String fileName = dis.readUTF();
                        System.out.println("Recibiendo el archivo: "+fileName);
                        long fileSize = dis.readLong();
                        DataOutputStream dos = new DataOutputStream(new FileOutputStream(fileName));
                        long recieved = 0;
                        int n, percent;
                        while (recieved < fileSize){
                            n = dis.readInt();
                            n = dis.read(buff,0,n);
                            dos.write(buff,0,n);
                            dos.flush();
                            recieved = recieved + n;
                            percent = (int)(recieved*100/fileSize);
                            System.out.print("Recibido "+percent+"% \r");
                        }
                        System.out.println("\n"+fileName+" recibido.");
                        dos.close(); 
                        Thread.sleep(100);               
                    } catch(Exception err) {
                        err.printStackTrace();
                        continue;
                    }
                }
                client.close();
                dis.close();
            }//ciclo infinito
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }
}
