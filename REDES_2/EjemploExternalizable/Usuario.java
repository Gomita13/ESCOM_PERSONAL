import java.io.*;
import java.util.*;
class Usuario implements Externalizable{
    private String usuario;
    private String password;
    public Usuario(){
        System.out.println("Creando usuario vacio");
    }
    Usuario(String u, String p){
        System.out.println("Creando usuario ("+u+","+p+")");
        usuario = u;
        password = p;
    }
    public void writeExternal(ObjectOutput out) throws IOException{
        System.out.println("Usuario.writeExternal");
        //Explicitamente indicamos cuales son los atributos a almacenar
        out.writeObject(usuario);
    }
public void readExternal(ObjectInput in) 
            throws IOException, ClassNotFoundException{
        System.out.println("Usuario.readExternal");
        //Explicitamente indicamos cuales son los atributos a recuperar
        usuario = (String)in.readObject();
    }
    
    public void muestraUsuario(){
        String cad = "Usuario: "+usuario+" Password: ";
        if (password == null)
            cad = cad + "No disponible";
        else
            cad = cad + password;
        System.out.println(cad);
    }
}
class ListaUsuarios implements Serializable{
    private LinkedList lista = new LinkedList();
    int valor;
    ListaUsuarios(String[] usuarios, String[] passwords){
        for(int i =0; i < usuarios.length; i++)
            lista.add(new Usuario(usuarios[i],passwords[i]));
    }
    public void muestraUsuario(){
        ListIterator li = lista.listIterator();
        Usuario u;   
        while(li.hasNext()){
            u = (Usuario) li.next();
            u.muestraUsuario();
        }
    }
}
