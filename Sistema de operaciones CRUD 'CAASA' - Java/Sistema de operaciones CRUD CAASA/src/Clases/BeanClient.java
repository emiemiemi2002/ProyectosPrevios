package Clases;

import java.sql.Date;

/**
 *
 * @author 
 */
public class BeanClient {
    //Atributos
    private long id_client;
    private long id_domicilio; 
    private String nomb_client;
    private String appat_client;
    private String apmat_client;
    private String tel_client;
    private String cel_client;
    private String rfc_client;
    private String curp_client;
    private Date fechnac_client;

    //Constructor
    public BeanClient(long id_client, long id_domicilio, String nomb_client, String appat_client, String apmat_client, String tel_client, String cel_client, String rfc_client, String curp_client, Date fechnac_client) {
        this.id_client = id_client;
        this.id_domicilio = id_domicilio; 
        this.nomb_client = nomb_client;
        this.appat_client = appat_client;
        this.apmat_client = apmat_client;
        this.tel_client = tel_client;
        this.cel_client = cel_client;
        this.rfc_client = rfc_client;
        this.curp_client = curp_client;
        this.fechnac_client = fechnac_client;
    }
    
    //Constructor #2 (Solo con PK)
    public BeanClient(long id_client){
        this.id_client=id_client;
    }

    //Constructor #3
    public BeanClient(String rfc_client, String curp_client) {
        this.rfc_client=rfc_client;
        this.curp_client=curp_client;
    }
    
    //Constructor #4
    public BeanClient(long id_client, String nomb_client){
        this.id_client=id_client;
        this.nomb_client=nomb_client;
    }
    
    //Constructor #5
    public BeanClient(long id_client, String appat_client, String cadena){
        this.id_client=id_client;
        this.appat_client=appat_client;
    }
    
    //Constructor #6
    public BeanClient(long id_client, String apmat_client, String cadena, String cadena2){
        this.id_client=id_client;
        this.apmat_client=apmat_client;
    }
    
    //Constructor #7
    public BeanClient(long id_client, String tel_client, String cadena, String cadena2, String cadena3){
        this.id_client=id_client;
        this.tel_client=tel_client;
    }
    
    //Constructor #8
    public BeanClient(long id_client, String cel_client, String cadena, String cadena2, String cadena3, String cadena4){
        this.id_client=id_client;
        this.cel_client=cel_client;
    }
    
    //Constructor #9
    public BeanClient(long id_client, Date fechnac_client){
        this.id_client=id_client;
        this.fechnac_client=fechnac_client;
    }
    
    //Constructor #10
    public BeanClient(long id_client, long id_domicilio){
        this.id_client=id_client;
        this.id_domicilio=id_domicilio;
    }

    //Get's
    public long getId_client() {
        return id_client;
    }
    
    public long getId_domicilio(){
        return id_domicilio;
    }

    public String getNomb_client() {
        return nomb_client;
    }

    public String getAppat_client() {
        return appat_client;
    }

    public String getApmat_client() {
        return apmat_client;
    }

    public String getTel_client() {
        return tel_client;
    }

    public String getCel_client() {
        return cel_client;
    }

    public String getRfc_client() {
        return rfc_client;
    }

    public String getCurp_client() {
        return curp_client;
    }

    public Date getFechnac_client() {
        return fechnac_client;
    }

    //Set's
    public void setId_client(long id_client) {
        this.id_client = id_client;
    }
    
    public void setId_domicilio(long id_domicilio) {
        this.id_domicilio = id_domicilio;
    }

    public void setNomb_client(String nomb_client) {
        this.nomb_client = nomb_client;
    }

    public void setAppat_client(String appat_client) {
        this.appat_client = appat_client;
    }

    public void setApmat_client(String apmat_client) {
        this.apmat_client = apmat_client;
    }

    public void setTel_client(String tel_client) {
        this.tel_client = tel_client;
    }

    public void setCel_client(String cel_client) {
        this.cel_client = cel_client;
    }

    public void setRfc_client(String rfc_client) {
        this.rfc_client = rfc_client;
    }

    public void setCurp_client(String curp_client) {
        this.curp_client = curp_client;
    }

    public void setFechnac_client(Date fechnac_client) {
        this.fechnac_client = fechnac_client;
    }
}
