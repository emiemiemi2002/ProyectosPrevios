package Clases;

/**
 *
 * @author 
 */
public class BeanAsesor {
    //Atributos
    private int id_asesor;
    private String nomb_asesor;
    private String appat_asesor;
    private String apmat_asesor;
    private String tel_asesor;
    private String cel_asesor;
    private String email_asesor;

    //Constructor
    public BeanAsesor(int id_asesor, String nomb_asesor, String appat_asesor, String apmat_asesor, String tel_asesor, String cel_asesor, String email_asesor) {
        this.id_asesor = id_asesor;
        this.nomb_asesor = nomb_asesor;
        this.appat_asesor = appat_asesor;
        this.apmat_asesor = apmat_asesor;
        this.tel_asesor = tel_asesor;
        this.cel_asesor = cel_asesor;
        this.email_asesor = email_asesor;
    }
    
    //Constructor #2 (Solo con PK)
    public BeanAsesor(int id_asesor){
        this.id_asesor=id_asesor;
    }
    
    //Constructor #3 
    public BeanAsesor(String email_asesor){
        this.email_asesor=email_asesor;
    }

    //Get's
    public int getId_asesor() {
        return id_asesor;
    }

    public String getNomb_asesor() {
        return nomb_asesor;
    }

    public String getAppat_asesor() {
        return appat_asesor;
    }

    public String getApmat_asesor() {
        return apmat_asesor;
    }

    public String getTel_asesor() {
        return tel_asesor;
    }

    public String getCel_asesor() {
        return cel_asesor;
    }

    public String getEmail_asesor() {
        return email_asesor;
    }
    
    //Set's
    public void setId_asesor(int id_asesor) {
        this.id_asesor = id_asesor;
    }

    public void setNomb_asesor(String nomb_asesor) {
        this.nomb_asesor = nomb_asesor;
    }

    public void setAppat_asesor(String appat_asesor) {
        this.appat_asesor = appat_asesor;
    }

    public void setApmat_asesor(String apmat_asesor) {
        this.apmat_asesor = apmat_asesor;
    }

    public void setTel_asesor(String tel_asesor) {
        this.tel_asesor = tel_asesor;
    }

    public void setCel_asesor(String cel_asesor) {
        this.cel_asesor = cel_asesor;
    }

    public void setEmail_asesor(String email_asesor) {
        this.email_asesor = email_asesor;
    }
}
