package Clases;

/**
 *
 * @author 
 */
public class BeanDomicilio {
    //Atributos
    private long id_domicilio;
    private String ciudadmun_domicilio;
    private String cp_domicilio;
    private String colonia_domicilio;
    private String calle_domicilio;
    private int next_domicilio;
    private int nint_domicilio;
    
    //Constructor
    public BeanDomicilio(long id_domicilio, String ciudadmun_domicilio, String cp_domicilio, String colonia_domicilio, String calle_domicilio, int next_domicilio, int nint_domicilio) {
        this.id_domicilio = id_domicilio;
        this.ciudadmun_domicilio = ciudadmun_domicilio;
        this.cp_domicilio = cp_domicilio;
        this.colonia_domicilio = colonia_domicilio;
        this.calle_domicilio = calle_domicilio;
        this.next_domicilio = next_domicilio;
        this.nint_domicilio = nint_domicilio;
    }
    
    //Constructor #2 (Solo con PK)
    public BeanDomicilio(long id_domicilio){
        this.id_domicilio=id_domicilio;
    }
    
    //Constructor #3
    public BeanDomicilio(long id_domicilio, String ciudadmun_domicilio){
        this.id_domicilio=id_domicilio;
        this.ciudadmun_domicilio=ciudadmun_domicilio;
    }
    
    //Constructor #4
    public BeanDomicilio(long id_domicilio, String cp_domicilio, String cadena){
        this.id_domicilio=id_domicilio;
        this.cp_domicilio=cp_domicilio;
    }
    
    //Constructor #5
    public BeanDomicilio(long id_domicilio, String colonia_domicilio, String cadena, String cadena2){
        this.id_domicilio=id_domicilio;
        this.colonia_domicilio=colonia_domicilio;
    }
    
    //Constructor #6
    public BeanDomicilio(long id_domicilio, String calle_domicilio, String cadena, String cadena2, String cadena3){
        this.id_domicilio=id_domicilio;
        this.calle_domicilio=calle_domicilio;
    }
    
    //Constructor #7
    public BeanDomicilio(long id_domicilio, int nint_domicilio){
        this.id_domicilio=id_domicilio;
        this.nint_domicilio=nint_domicilio;
    }
    
    //Constructor #8
    public BeanDomicilio(long id_domicilio, int next_domicilio, String cadena){
        this.id_domicilio=id_domicilio;
        this.next_domicilio=next_domicilio;
    }

    //Get's
    public long getId_domicilio() {
        return id_domicilio;
    }

    public String getCiudadmun_domicilio() {
        return ciudadmun_domicilio;
    }

    public String getCp_domicilio() {
        return cp_domicilio;
    }

    public String getColonia_domicilio() {
        return colonia_domicilio;
    }

    public String getCalle_domicilio() {
        return calle_domicilio;
    }

    public int getNext_domicilio() {
        return next_domicilio;
    }

    public int getNint_domicilio() {
        return nint_domicilio;
    }

    //Set's
    public void setId_domicilio(long id_domicilio) {
        this.id_domicilio = id_domicilio;
    }

    public void setCiudadmun_domicilio(String ciudadmun_domicilio) {
        this.ciudadmun_domicilio = ciudadmun_domicilio;
    }

    public void setCp_domicilio(String cp_domicilio) {
        this.cp_domicilio = cp_domicilio;
    }

    public void setColonia_domicilio(String colonia_domicilio) {
        this.colonia_domicilio = colonia_domicilio;
    }

    public void setCalle_domicilio(String calle_domicilio) {
        this.calle_domicilio = calle_domicilio;
    }

    public void setNext_domicilio(int next_domicilio) {
        this.next_domicilio = next_domicilio;
    }

    public void setNint_domicilio(int nint_domicilio) {
        this.nint_domicilio = nint_domicilio;
    }
}
