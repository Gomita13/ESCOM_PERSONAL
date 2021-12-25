import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
//import Suma.*;
	
public class Servidor implements Suma {
	
    static int result;

    public Servidor() {
        result = 0;
    }

    public int suma(int a, int b) {
	   result = a+b;
       return result;
    }
    
    public static void main(String args[]) {
	try {
               //puerto default del rmiregistry
               java.rmi.registry.LocateRegistry.createRegistry(1099); 
               System.out.println("RMI registro listo.");
	} catch (Exception e) {
               System.out.println("Excepcion RMI del registry:");
                e.printStackTrace();
           }//catch
	try {
                Thread hilo = new Thread(new Prueba());
                hilo.start();
                System.setProperty("java.rmi.server.codebase","file:/c:/Temp/Suma/");
                Servidor obj = new Servidor();
                Suma stub = (Suma) UnicastRemoteObject.exportObject(obj, 0);
                // Ligamos el objeto remoto en el registro
                Registry registry = LocateRegistry.getRegistry();
                registry.bind("Suma", stub);

                System.err.println("Servidor listo...");
	} catch (Exception e) {
	    System.err.println("Excepción del servidor: " + e.toString());
	    e.printStackTrace();
	}
    }
}

class Prueba implements Runnable {

    public Prueba(){

    }

    @Override
    public void run(){
        try{
            while(true){
                System.out.println(Servidor.result);
                Thread.sleep(5000);
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

}