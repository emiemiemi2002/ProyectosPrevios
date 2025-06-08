package Clases;

/**
 *
 * @author 
 */
public class ModeloAuto {
    //Atributo
    private int id_modelauto;
    private int id_marca;
    private String model_auto;
    private String año_auto;

    //Constructor
    public ModeloAuto(int id_modelauto, int id_marca, String model_auto, String año_auto) {
        this.id_modelauto = id_modelauto;
        this.id_marca = id_marca;
        this.model_auto = model_auto;
        this.año_auto = año_auto;
    }

    //Get's
    public int getId_modelauto() {
        return id_modelauto;
    }

    public int getId_marca() {
        return id_marca;
    }

    public String getModel_auto() {
        return model_auto;
    }

    public String getAño_auto() {
        return año_auto;
    }

    //Set's
    public void setId_modelauto(int id_modelauto) {
        this.id_modelauto = id_modelauto;
    }

    public void setId_marca(int id_marca) {
        this.id_marca = id_marca;
    }

    public void setModel_auto(String model_auto) {
        this.model_auto = model_auto;
    }

    public void setAño_auto(String año_auto) {
        this.año_auto = año_auto;
    }
}
