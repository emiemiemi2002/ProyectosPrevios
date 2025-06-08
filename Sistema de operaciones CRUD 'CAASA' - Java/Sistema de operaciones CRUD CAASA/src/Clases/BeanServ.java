package Clases;

/**
 *
 * @author 
 */
public class BeanServ {
    //Atributos 
    private long id_serv;
    private String accion_serv;
    private String component_serv;
    private double precio_serv;
    private String disp_serv;
    private int id_tiposerv;
    private int id_periodoserv;
    
    //Constructor 
    public BeanServ(long id_serv, String accion_serv, String component_serv, double precio_serv, String disp_serv, int id_tiposerv, int id_periodoserv) {
        this.id_serv = id_serv;
        this.accion_serv = accion_serv;
        this.component_serv = component_serv;
        this.precio_serv = precio_serv;
        this.disp_serv = disp_serv;
        this.id_tiposerv = id_tiposerv;
        this.id_periodoserv = id_periodoserv;
    }
    
    //Constructor #2 (Solo con PK)
    public BeanServ(long id_serv){
        this.id_serv=id_serv;
    }

    //Get's
    public long getId_serv() {
        return id_serv;
    }

    public String getAccion_serv() {
        return accion_serv;
    }

    public String getComponent_serv() {
        return component_serv;
    }

    public double getPrecio_serv() {
        return precio_serv;
    }

    public String getDisp_serv() {
        return disp_serv;
    }

    public int getId_tiposerv() {
        return id_tiposerv;
    }

    public int getId_periodoserv() {
        return id_periodoserv;
    }
    
    //Set's
    public void setId_serv(long id_serv) {
        this.id_serv = id_serv;
    }

    public void setAccion_serv(String accion_serv) {
        this.accion_serv = accion_serv;
    }

    public void setComponent_serv(String component_serv) {
        this.component_serv = component_serv;
    }

    public void setPrecio_serv(double precio_serv) {
        this.precio_serv = precio_serv;
    }

    public void setDisp_serv(String disp_serv) {
        this.disp_serv = disp_serv;
    }

    public void setId_tiposerv(int id_tiposerv) {
        this.id_tiposerv = id_tiposerv;
    }

    public void setId_periodoserv(int id_periodoserv) {
        this.id_periodoserv = id_periodoserv;
    }
}
