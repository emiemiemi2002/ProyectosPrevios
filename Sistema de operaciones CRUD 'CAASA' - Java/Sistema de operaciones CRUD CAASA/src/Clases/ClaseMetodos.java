//Paquete
package Clases;

//Librerías
import java.sql.*;

/**
 *
 * @author Propietario
 */
public class ClaseMetodos {

    //Método probar una transacción
    public void transaccInsertSelect(Connection vconexion, Conexion_BD_CAASA objclasecon){
        //PS's
        PreparedStatement insertarModelo, insertarColor, actualizarModelo, eliminarColor, eliminarAuto;
        //Sentencias de operaciones y consultas
        String sentenciaModelo="INSERT INTO modelo VALUES (?,?,?,?)"; 
        String sentenciaColor="INSERT INTO color VALUES (?,?,?)"; 
        String sentenciaUpdateModelo="UPDATE modelo SET año_auto = ? WHERE id_modelauto = ?";
        String sentenciaEliminarColor="DELETE FROM color WHERE id_color = ?";
        String sentenciaEliminarAuto="DELETE FROM automovil WHERE nserie_auto = ?";
        String consulta1="SELECT id_modelauto, model_auto, año_auto FROM modelo";
        String consulta2="SELECT color, tono_color FROM color";
        String consulta3="SELECT * FROM automovil";
        //Statement y ResultSet de consulta
        Statement stm, stm2, stm3;
        ResultSet rs, rs2, rs3;
        //Arreglos de información de registros Modelo y Color a insertar
        int [] ids_modelos = {15874963,16589324};
        int [] ids_marcas = {56312,54231};
        String [] noms_modelos = {"Renegade","Focus"};
        String [] años_modelos = {"2021","2020"};
        
        int [] ids_colores = {19862,47563};
        String [] noms_colores = {"Rosa","Rojo"};
        String [] noms_tonos = {"Neon","Carmesí"};
        //ID's de registros de Modelo y Color a actualizar y eliminar respectivamente | Dato a actualizar de modelo
        int id_mdlaupdate=13256945, id_clraelim=99854;
        String newaño_mdl="2010";
        long nserie_autaelim=1236547899856743L;
        //Variable de iteraciones de primer ciclo
        int iteraciones=ids_modelos.length;
        //Bloque try-catch
        try{
            //prepareStatement's
            insertarModelo=vconexion.prepareStatement(sentenciaModelo);
            insertarColor=vconexion.prepareStatement(sentenciaColor);
            actualizarModelo=vconexion.prepareStatement(sentenciaUpdateModelo);
            eliminarColor=vconexion.prepareStatement(sentenciaEliminarColor);
            eliminarAuto=vconexion.prepareStatement(sentenciaEliminarAuto);
            //Desactivar la autoconfirmación 
            vconexion.setAutoCommit(false);
            //Ciclo para inserciones
            for(int e=0;e<iteraciones;e++){
                insertarModelo.setInt(1,ids_modelos[e]);
                insertarModelo.setInt(2,ids_marcas[e]);
                insertarModelo.setString(3,noms_modelos[e]);
                insertarModelo.setString(4,años_modelos[e]);
                insertarModelo.executeUpdate();
                insertarColor.setInt(1,ids_colores[e]);
                insertarColor.setString(2,noms_colores[e]);
                insertarColor.setString(3,noms_tonos[e]);
                insertarColor.executeUpdate();
                vconexion.commit();
            }
            //Desactivar la autoconfirmación 
            vconexion.setAutoCommit(false);
            //Actualización y eliminacion
            for(int n=0;n<1;n++){
                actualizarModelo.setString(1, newaño_mdl);
                actualizarModelo.setInt(2, id_mdlaupdate);
                actualizarModelo.executeUpdate();
                eliminarColor.setInt(1, id_clraelim);
                eliminarColor.executeUpdate();
                eliminarAuto.setLong(1, nserie_autaelim);
                eliminarAuto.executeUpdate();
                vconexion.commit();
            }
            vconexion.setAutoCommit(true);
            insertarModelo.close();
            insertarColor.close();
            actualizarModelo.close();
            eliminarColor.close();
            eliminarAuto.close();
            //Consultas
            stm=vconexion.createStatement();
            rs=stm.executeQuery(consulta1);
            
            stm2=vconexion.createStatement();
            rs2=stm.executeQuery(consulta2);
            
            stm3=vconexion.createStatement();
            rs3=stm.executeQuery(consulta3);
            //
            while(rs.next()){
                int idmdlaut = rs.getInt("id_modelauto");
                String mdlaut = rs.getString("model_auto");
                String añaut = rs.getString("año_auto");
                System.out.println(idmdlaut+"  |  "+mdlaut+"  |  "+añaut);
            }
            while(rs2.next()){
                String colorclr = rs2.getString("color");
                String tonoclr = rs2.getString("tono_color");
                System.out.println(colorclr+"  |  "+tonoclr);
            }
            while(rs3.next()){
                
            }
            
            stm.close();
            stm2.close();
            stm3.close();
            //Desconectar
            objclasecon.desconectar(vconexion);
        }catch(SQLException vex){
            System.err.println("SQLException: "+vex.getMessage());
            if(vconexion!=null){
                try{
                    System.err.print("A la transacción se le va a aplicar ");
                    System.err.println("un rollback...");
                    vconexion.rollback();
                }catch(SQLException vex2){
                    System.err.print("SQLException: ");
                    System.err.println(vex2.getMessage());
                }
            }
        }
    }
}
