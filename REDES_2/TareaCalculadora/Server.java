import java.rmi.*;
import java.rmi.registry.Registry;
import javax.swing.*;
import java.rmi.server.UnicastRemoteObject;

public class Server implements Calculator{

    public Server(){}

    @Override
    public double add(double a, double b) throws RemoteException {
        System.out.println("Server: "+a+"+"+b);
        return a+b;
    }

    @Override
    public double subs(double a, double b) throws RemoteException {
        System.out.println("Server: "+a+"-"+b);
        return a-b;
    }

    @Override 
    public double mult(double a, double b) throws RemoteException{
        System.out.println("Server: "+a+"*"+b);
        return a*b;
    }

    @Override
    public double div(double a, double b) throws RemoteException {
        System.out.println("Server: "+a+"/"+b);
        return a/b;
    }

    @Override
    public double mod(double a, double b) throws RemoteException {
        System.out.println("Server: "+a+"%"+b);
        return a%b;
    }

    public static void main(String[] args) {
        try {
            Registry r = java.rmi.registry.LocateRegistry.createRegistry(1099);
            Server obj = new Server();
            System.setProperty("rmi.server.hostname","127.0.0.1");
            Calculator stub = (Calculator) UnicastRemoteObject.exportObject(obj,0);
            r.bind("Calculator",stub);
            System.out.println("Servidor listo");
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Hubo un error en el servidor: " + e, "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
