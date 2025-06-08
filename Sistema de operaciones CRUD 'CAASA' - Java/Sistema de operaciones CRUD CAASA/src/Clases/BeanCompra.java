package Clases;

import java.sql.Date;
import java.sql.Time;

/**
 *
 * @author 
 */
public class BeanCompra {
    //Atributos
    private long id_compr;
    private long id_client;
    private long nserie_auto;
    private int id_asesor;
    private int id_formapago;
    private int id_planpago;
    private Date fech_compr;
    private Time hora_compr;
    private double monto_compr;
    
    //Constructor
    public BeanCompra(long id_compr, long id_client, long nserie_auto, int id_asesor, int id_formapago, int id_planpago, Date fech_compr, Time hora_compr, double monto_compr) {
        this.id_compr = id_compr;
        this.id_client = id_client;
        this.nserie_auto = nserie_auto;
        this.id_asesor = id_asesor;
        this.id_formapago = id_formapago;
        this.id_planpago = id_planpago;
        this.fech_compr = fech_compr;
        this.hora_compr = hora_compr;
        this.monto_compr = monto_compr;
    }
    
    //Constructor #2
    public BeanCompra(long id_compr, long id_client){
        this.id_compr=id_compr;
        this.id_client=id_client;
    }
    
    //Constructor #2
    public BeanCompra(long id_compr, long nserie_auto, String cadena){
        this.id_compr=id_compr;
        this.nserie_auto=nserie_auto;
    }
    
    //Constructor #3
    public BeanCompra(long id_compr, int id_asesor){
        this.id_compr=id_compr;
        this.id_asesor=id_asesor;
    }
    
    //Constructor #4
    public BeanCompra(long id_compr, int id_formapago, String cadena){
        this.id_compr=id_compr;
        this.id_formapago=id_formapago;
    }
    
    //Constructor #5
    public BeanCompra(long id_compr, int id_planpago, String cadena, String cadena2){
        this.id_compr=id_compr;
        this.id_planpago=id_planpago;
    }
    
    //Constructor #6
    public BeanCompra(long id_compr, Date fech_compr){
        this.id_compr=id_compr;
        this.fech_compr=fech_compr;
    }
    
    //Constructor #7
    public BeanCompra(long id_compr, Time hora_compr){
        this.id_compr=id_compr;
        this.hora_compr=hora_compr;
    }
    
    //Constructor #8
    public BeanCompra(long id_compr, double monto_compr){
        this.id_compr=id_compr;
        this.monto_compr=monto_compr;
    }

    //Get's
    public long getId_compr() {
        return id_compr;
    }

    public long getId_client() {
        return id_client;
    }

    public long getNserie_auto() {
        return nserie_auto;
    }

    public int getId_asesor() {
        return id_asesor;
    }

    public int getId_formapago() {
        return id_formapago;
    }

    public int getId_planpago() {
        return id_planpago;
    }

    public Date getFech_compr() {
        return fech_compr;
    }

    public Time getHora_compr() {
        return hora_compr;
    }

    public double getMonto_compr() {
        return monto_compr;
    }

    //Set's
    public void setId_compr(long id_compr) {
        this.id_compr = id_compr;
    }

    public void setId_client(long id_client) {
        this.id_client = id_client;
    }

    public void setNserie_auto(long nserie_auto) {
        this.nserie_auto = nserie_auto;
    }

    public void setId_asesor(int id_asesor) {
        this.id_asesor = id_asesor;
    }

    public void setId_formapago(int id_formapago) {
        this.id_formapago = id_formapago;
    }

    public void setId_planpago(int id_planpago) {
        this.id_planpago = id_planpago;
    }

    public void setFech_compr(Date fech_compr) {
        this.fech_compr = fech_compr;
    }

    public void setHora_compr(Time hora_compr) {
        this.hora_compr = hora_compr;
    }

    public void setMonto_compr(double monto_compr) {
        this.monto_compr = monto_compr;
    }
}
