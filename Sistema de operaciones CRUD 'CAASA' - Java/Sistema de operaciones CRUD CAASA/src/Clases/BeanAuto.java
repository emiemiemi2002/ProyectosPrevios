package Clases;

/**
 *
 * @author 
 */
public class BeanAuto {
    //Atributos 
    private long nserie_auto;
    private int id_modelauto;
    private int id_color;
    private double precio_auto;
    private String estado_auto;
    private String disp_auto;

    //Constructor
    public BeanAuto(long nserie_auto, int id_modelauto, int id_color, double precio_auto, String estado_auto, String disp_auto) {
        this.nserie_auto = nserie_auto;
        this.id_modelauto = id_modelauto;
        this.id_color = id_color;
        this.precio_auto = precio_auto;
        this.estado_auto = estado_auto;
        this.disp_auto = disp_auto;
    }
    
    //Constructor #2 (Solo con PK)
    public BeanAuto(long nserie_auto){
        this.nserie_auto=nserie_auto;
    }
    
    //Get's
    public long getNserie_auto() {
        return nserie_auto;
    }

    public int getId_modelauto() {
        return id_modelauto;
    }

    public int getId_color() {
        return id_color;
    }

    public double getPrecio_auto() {
        return precio_auto;
    }

    public String getEstado_auto() {
        return estado_auto;
    }

    public String getDisp_auto() {
        return disp_auto;
    }

    //Set's
    public void setNserie_auto(long nserie_auto) {
        this.nserie_auto = nserie_auto;
    }

    public void setId_modelauto(int id_modelauto) {
        this.id_modelauto = id_modelauto;
    }

    public void setId_color(int id_color) {
        this.id_color = id_color;
    }

    public void setPrecio_auto(double precio_auto) {
        this.precio_auto = precio_auto;
    }

    public void setEstado_auto(String estado_auto) {
        this.estado_auto = estado_auto;
    }

    public void setDisp_auto(String disp_auto) {
        this.disp_auto = disp_auto;
    }
}
