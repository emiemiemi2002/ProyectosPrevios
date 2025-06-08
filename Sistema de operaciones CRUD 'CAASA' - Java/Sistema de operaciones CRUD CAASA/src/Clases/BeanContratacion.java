package Clases;

import java.sql.Date;
import java.sql.Time;

/**
 *
 * @author
 */
public class BeanContratacion {
    //Atributos
    private long id_contrat;
    private long id_client;
    private long nserie_auto;
    private long id_serv;
    private int id_formapago;
    private int id_planpago;
    private Date fech_contrat;
    private Time hora_contrat;
    private double monto_contrat;
    
    //Constructor
    public BeanContratacion(long id_contrat, long id_client, long nserie_auto, long id_serv, int id_formapago, int id_planpago, Date fech_contrat, Time hora_contrat, double monto_contrat) {
        this.id_contrat = id_contrat;
        this.id_client = id_client;
        this.nserie_auto = nserie_auto;
        this.id_serv = id_serv;
        this.id_formapago = id_formapago;
        this.id_planpago = id_planpago;
        this.fech_contrat = fech_contrat;
        this.hora_contrat = hora_contrat;
        this.monto_contrat = monto_contrat;
    }
    
    //Constructor #2
    public BeanContratacion(long id_contrat, long id_client){
        this.id_contrat=id_contrat;
        this.id_client=id_client;
    }
    
    //Constructor #3
    public BeanContratacion(long id_contrat, long nserie_auto, String cadena){
        this.id_contrat=id_contrat;
        this.nserie_auto=nserie_auto;
    }
    
    //Constructor #4
    public BeanContratacion(long id_contrat, long id_serv, String cadena, String cadena2){
        this.id_contrat=id_contrat;
        this.id_serv=id_serv;
    }
    
    //Constructor #5
    public BeanContratacion(long id_contrat, int id_formapago){
        this.id_contrat=id_contrat;
        this.id_formapago=id_formapago;
    }
    
    //Constructor #6
    public BeanContratacion(long id_contrat, int id_planpago, String cadena){
        this.id_contrat=id_contrat;
        this.id_planpago=id_planpago;
    }
    
    //Constructor #7
    public BeanContratacion(long id_contrat, Date fech_contrat){
        this.id_contrat=id_contrat;
        this.fech_contrat=fech_contrat;
    }
    
    //Constructor #8
    public BeanContratacion(long id_contrat, Time hora_contrat){
        this.id_contrat=id_contrat;
        this.hora_contrat=hora_contrat;
    }
    
    //Constructor #9
    public BeanContratacion(long id_contrat, double monto_contrat){
        this.id_contrat=id_contrat;
        this.monto_contrat=monto_contrat;
    }

    //Get's
    public long getId_contrat() {
        return id_contrat;
    }

    public long getId_client() {
        return id_client;
    }

    public long getNserie_auto() {
        return nserie_auto;
    }

    public long getId_serv() {
        return id_serv;
    }

    public int getId_formapago() {
        return id_formapago;
    }

    public int getId_planpago() {
        return id_planpago;
    }

    public Date getFech_contrat() {
        return fech_contrat;
    }

    public Time getHora_contrat() {
        return hora_contrat;
    }

    public double getMonto_contrat() {
        return monto_contrat;
    }

    //Set's
    public void setId_contrat(long id_contrat) {
        this.id_contrat = id_contrat;
    }

    public void setId_client(long id_client) {
        this.id_client = id_client;
    }

    public void setNserie_auto(long nserie_auto) {
        this.nserie_auto = nserie_auto;
    }

    public void setId_serv(long id_serv) {
        this.id_serv = id_serv;
    }

    public void setId_formapago(int id_formapago) {
        this.id_formapago = id_formapago;
    }

    public void setId_planpago(int id_planpago) {
        this.id_planpago = id_planpago;
    }

    public void setFech_contrat(Date fech_contrat) {
        this.fech_contrat = fech_contrat;
    }

    public void setHora_contrat(Time hora_contrat) {
        this.hora_contrat = hora_contrat;
    }

    public void setMonto_contrat(double monto_contrat) {
        this.monto_contrat = monto_contrat;
    }
}
