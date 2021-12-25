import java.rmi.*;

public interface Calculator extends Remote {
    public double add(double a, double b) throws RemoteException;
    public double subs(double a, double b) throws RemoteException;
    public double mult(double a, double b) throws RemoteException;
    public double div(double a, double b) throws RemoteException;
    public double mod(double a, double b) throws RemoteException;
}