package Clases;

//Librerías
import java.sql.*;
import javax.swing.JOptionPane;

/**
 *
 * @author Emiliano Espinoza Perales
 */
public class Conexion_BD_CAASA {
    //Objetos
    private Connection objcon = null;

    //Constructor
    public Conexion_BD_CAASA() {
    }
    
    //Método "conectar"
    public Connection conectar(){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            objcon=DriverManager.getConnection("jdbc:mysql://localhost/caasa?user=root&password=");
            System.out.println("Se ha conectado a la base de datos...");
        }catch(ClassNotFoundException cnfe){
            JOptionPane.showMessageDialog(null, "Ha ocurrido una excepción: "+cnfe.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }catch(SQLException sqle){
            JOptionPane.showMessageDialog(null, "Ha ocurrido una excepción: "+sqle.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
        return objcon;
    }
    
    //Método "desconectar"
    public void desconectar(Connection objcon){
        try{
            if(objcon!=null){
                objcon.close();
                System.out.println("Conexión cerrada!");
            }
            objcon=null;
        }catch(SQLException sqle2){
            JOptionPane.showMessageDialog(null, "Ha ocurrido una excepción: "+sqle2.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }//Cierre del método desconectar
}
