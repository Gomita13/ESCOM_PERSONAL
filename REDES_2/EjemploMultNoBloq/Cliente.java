import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.util.Collections;
import java.util.Enumeration;
import java.util.Iterator;

public class Cliente {
    
    public static void main(String[] args){
        int pto=2000;
        String hhost="230.0.0.1";
        SocketAddress remote=null;
        try{
            try{
                remote = new InetSocketAddress(hhost, pto);
            }catch(Exception e){
                e.printStackTrace();
            }//catch
            Enumeration<NetworkInterface> nets = NetworkInterface.getNetworkInterfaces();
            for (NetworkInterface netint : Collections.list(nets))
                displayInterfaceInformation(netint);
            NetworkInterface ni = NetworkInterface.getByName("wlan1");
            DatagramChannel cl =DatagramChannel.open(StandardProtocolFamily.INET);
            cl.setOption(StandardSocketOptions.SO_REUSEADDR, true);
            cl.setOption(StandardSocketOptions.IP_MULTICAST_IF, ni);
            cl.configureBlocking(false);
            Selector sel = Selector.open();
            cl.register(sel, SelectionKey.OP_READ|SelectionKey.OP_WRITE);
            InetAddress group = InetAddress.getByName("230.0.0.1");
            cl.join(group, ni);
            ByteBuffer b = ByteBuffer.allocate(4);
            int n=0;
            while(n<100){
                sel.select();
                Iterator<SelectionKey>it = sel.selectedKeys().iterator();
                while(it.hasNext()){
                    SelectionKey k = (SelectionKey)it.next();
                    it.remove();
                    if(k.isWritable()){
                        DatagramChannel ch = (DatagramChannel)k.channel();
                        b.clear();
                        b.putInt(n++);
                        b.flip();
                        ch.send(b, remote);
                        continue;
                    }else if(k.isReadable()){
                        DatagramChannel ch = (DatagramChannel)k.channel();
                        b.clear();
                        SocketAddress emisor = ch.receive(b);
                        b.flip();
                        InetSocketAddress d = (InetSocketAddress)emisor;
                        System.out.println("Datagrama recibido desde "+ d.getAddress()+":"+d.getPort());
                        System.out.println("Dato: "+b.getInt());
                        continue;
                    }
                }//while
            }//while
            cl.close();
            System.out.println("Termina envio de datagramas");
        }catch(Exception e){
            e.printStackTrace();
        }//catch
    }//main
}
