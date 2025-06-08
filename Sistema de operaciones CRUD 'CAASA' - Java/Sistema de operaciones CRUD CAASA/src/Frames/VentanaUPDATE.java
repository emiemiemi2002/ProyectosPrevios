package Frames;

//Imports
import javax.swing.ImageIcon;
import Clases.*;
import java.sql.*;
import javax.swing.JOptionPane;

/**
 *
 * @author Propietario
 */
public class VentanaUPDATE extends javax.swing.JFrame {

    //Vars/Objs
    Conexion_BD_CAASA obclasecon=new Conexion_BD_CAASA();
    Connection vcon=obclasecon.conectar();
    
    /**
     * Creates new form VentanaUPDATE
     */
    public VentanaUPDATE() {
        initComponents();
        //Icono de la ventana
        ImageIcon icon=new ImageIcon("C:\\Users\\Propietario\\Desktop\\Trabajos - Semestre 8\\Gestión de Proyectos de Software\\NBP\\Sistema de operaciones CRUD CAASA\\src\\Imagenes\\lcaasa.jpg");
        this.setIconImage(icon.getImage());  
        
        //Elementos combos
        //cboSeleccTabla----------------------
        cboSeleccTabla.addItem("...");
        cboSeleccTabla.addItem("Cliente");
        cboSeleccTabla.addItem("Domicilio");
        cboSeleccTabla.addItem("Compra");
        cboSeleccTabla.addItem("Contratación");
        cboSeleccTabla.setSelectedIndex(0);
        //1 Cliente
        cbo_CamposCliente.addItem("...");
        cbo_CamposCliente.addItem("nomb_client");
        cbo_CamposCliente.addItem("appat_client");
        cbo_CamposCliente.addItem("apmat_client");
        cbo_CamposCliente.addItem("tel_client");
        cbo_CamposCliente.addItem("cel_client");
        cbo_CamposCliente.addItem("fechnac_client");
        cbo_CamposCliente.addItem("id_domicilio"); 
        cbo_CamposCliente.setSelectedIndex(0);
        //2 Domicilio
        cbo_CamposDomicilio.addItem("...");
        cbo_CamposDomicilio.addItem("ciudadmun_domicilio");
        cbo_CamposDomicilio.addItem("cp_domicilio");
        cbo_CamposDomicilio.addItem("colonia_domicilio");
        cbo_CamposDomicilio.addItem("calle_domicilio");
        cbo_CamposDomicilio.addItem("nint_domicilio");
        cbo_CamposDomicilio.addItem("next_domicilio");
        cbo_CamposDomicilio.setSelectedIndex(0); 
        //3 Compra
        cbo_CamposCompra.addItem("...");
        cbo_CamposCompra.addItem("id_client");
        cbo_CamposCompra.addItem("nserie_auto");
        cbo_CamposCompra.addItem("id_asesor");
        cbo_CamposCompra.addItem("id_formapago");
        cbo_CamposCompra.addItem("id_planpago");
        cbo_CamposCompra.addItem("fech_compr");
        cbo_CamposCompra.addItem("hora_compr");
        cbo_CamposCompra.addItem("monto_compr");
        cbo_CamposCompra.setSelectedIndex(0);
        //4 Contratacion
        cbo_CamposContratacion.addItem("...");
        cbo_CamposContratacion.addItem("id_client");
        cbo_CamposContratacion.addItem("nserie_auto");
        cbo_CamposContratacion.addItem("id_serv");
        cbo_CamposContratacion.addItem("id_formapago");
        cbo_CamposContratacion.addItem("id_planpago");
        cbo_CamposContratacion.addItem("fech_contrat");
        cbo_CamposContratacion.addItem("hora_contrat");
        cbo_CamposContratacion.addItem("monto_contrat");
        cbo_CamposContratacion.setSelectedIndex(0);
        
        //
        txtf_LlaveCliente.setDocument(new LengthRestrictedDocument(11));
        txtf_LlaveDomicilio.setDocument(new LengthRestrictedDocument(11));
        txtf_LlaveCompra.setDocument(new LengthRestrictedDocument(12));
        txtf_LlaveContratacion.setDocument(new LengthRestrictedDocument(12));
        
        //Desactivar componentes de paneles
        //1
        pnl_UpdCliente.setEnabled(false);
        lbl_SeleccCampo.setEnabled(false);
        cbo_CamposCliente.setEnabled(false);
        cbo_SelecVExistenteCliente.setEnabled(false); 
        lbl_IngresarLlave.setEnabled(false);
        txtf_LlaveCliente.setEnabled(false);
        lbl_IngresarNVCliente.setEnabled(false);
        txtf_NVCliente.setEnabled(false);
        btn_ActNVCliente.setEnabled(false);
        //2
        pnl_UpdDomicilio.setEnabled(false);
        lbl_SeleccCampo2.setEnabled(false);
        cbo_CamposDomicilio.setEnabled(false);
        lbl_IngresarLlave2.setEnabled(false);
        txtf_LlaveDomicilio.setEnabled(false);
        lbl_IngresarNVDom.setEnabled(false);
        txtf_NVDomicilio.setEnabled(false);
        btn_ActNVDomicilio.setEnabled(false);
        //3
        pnl_UpdCompra.setEnabled(false);
        lbl_SeleccCampo3.setEnabled(false);
        cbo_CamposCompra.setEnabled(false);
        lbl_IngresarLlave3.setEnabled(false);
        txtf_LlaveCompra.setEnabled(false);
        lbl_IngresarNVComp.setEnabled(false);
        txtf_NVCompra.setEnabled(false);
        cbo_SelecVExistenteCompr.setEnabled(false);
        btn_ActNVCompra.setEnabled(false);
        //4
        pnl_UpdContratacion.setEnabled(false);
        lbl_SeleccCampo4.setEnabled(false);
        cbo_CamposContratacion.setEnabled(false);
        lbl_IngresarLlave4.setEnabled(false);
        txtf_LlaveContratacion.setEnabled(false);
        lbl_IngresarNVContr.setEnabled(false);
        txtf_NVContratacion.setEnabled(false);
        cbo_SelecVExistenteContr.setEnabled(false);
        btn_ActNVContratacion.setEnabled(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        pnl_UpdCliente = new javax.swing.JPanel();
        txtf_NVCliente = new javax.swing.JTextField();
        txtf_LlaveCliente = new javax.swing.JTextField();
        lbl_IngresarNVCliente = new javax.swing.JLabel();
        lbl_SeleccCampo = new javax.swing.JLabel();
        lbl_IngresarLlave = new javax.swing.JLabel();
        btn_ActNVCliente = new javax.swing.JButton();
        cbo_CamposCliente = new javax.swing.JComboBox<>();
        cbo_SelecVExistenteCliente = new javax.swing.JComboBox<>();
        pnl_UpdDomicilio = new javax.swing.JPanel();
        btn_ActNVDomicilio = new javax.swing.JButton();
        lbl_SeleccCampo2 = new javax.swing.JLabel();
        lbl_IngresarLlave2 = new javax.swing.JLabel();
        lbl_IngresarNVDom = new javax.swing.JLabel();
        cbo_CamposDomicilio = new javax.swing.JComboBox<>();
        txtf_NVDomicilio = new javax.swing.JTextField();
        txtf_LlaveDomicilio = new javax.swing.JTextField();
        pnl_UpdCompra = new javax.swing.JPanel();
        cbo_SelecVExistenteCompr = new javax.swing.JComboBox<>();
        cbo_CamposCompra = new javax.swing.JComboBox<>();
        btn_ActNVCompra = new javax.swing.JButton();
        lbl_SeleccCampo3 = new javax.swing.JLabel();
        lbl_IngresarLlave3 = new javax.swing.JLabel();
        lbl_IngresarNVComp = new javax.swing.JLabel();
        txtf_NVCompra = new javax.swing.JTextField();
        txtf_LlaveCompra = new javax.swing.JTextField();
        pnl_UpdContratacion = new javax.swing.JPanel();
        cbo_SelecVExistenteContr = new javax.swing.JComboBox<>();
        cbo_CamposContratacion = new javax.swing.JComboBox<>();
        btn_ActNVContratacion = new javax.swing.JButton();
        lbl_SeleccCampo4 = new javax.swing.JLabel();
        lbl_IngresarLlave4 = new javax.swing.JLabel();
        lbl_IngresarNVContr = new javax.swing.JLabel();
        txtf_NVContratacion = new javax.swing.JTextField();
        txtf_LlaveContratacion = new javax.swing.JTextField();
        cboSeleccTabla = new javax.swing.JComboBox<>();
        lbl_SeleccTab = new javax.swing.JLabel();
        lbl_fondo = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Actualice registros");
        setResizable(false);

        jPanel1.setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        lbl_IngresarNVCliente.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarNVCliente.setText(">Nuevo valor del campo:");

        lbl_SeleccCampo.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_SeleccCampo.setText(">Elija el campo del registro a actualizar:");

        lbl_IngresarLlave.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarLlave.setText(">Ingrese el valor de la PK del registro:");

        btn_ActNVCliente.setBackground(new java.awt.Color(255, 51, 51));
        btn_ActNVCliente.setFont(new java.awt.Font("Impact", 0, 18)); // NOI18N
        btn_ActNVCliente.setText("ACTUALIZAR");
        btn_ActNVCliente.setToolTipText("Insertar registro en la tabla seleccionada.");
        btn_ActNVCliente.setBorderPainted(false);
        btn_ActNVCliente.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_ActNVClienteActionPerformed(evt);
            }
        });

        cbo_CamposCliente.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbo_CamposClienteActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout pnl_UpdClienteLayout = new javax.swing.GroupLayout(pnl_UpdCliente);
        pnl_UpdCliente.setLayout(pnl_UpdClienteLayout);
        pnl_UpdClienteLayout.setHorizontalGroup(
            pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdClienteLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(pnl_UpdClienteLayout.createSequentialGroup()
                        .addComponent(lbl_SeleccCampo, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_CamposCliente, javax.swing.GroupLayout.PREFERRED_SIZE, 170, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(pnl_UpdClienteLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarLlave, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtf_LlaveCliente)))
                .addGroup(pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdClienteLayout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(lbl_IngresarNVCliente)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(txtf_NVCliente, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_SelecVExistenteCliente, 0, 159, Short.MAX_VALUE)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdClienteLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(btn_ActNVCliente, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(84, 84, 84))))
        );
        pnl_UpdClienteLayout.setVerticalGroup(
            pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdClienteLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(lbl_SeleccCampo)
                    .addComponent(cbo_CamposCliente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(lbl_IngresarNVCliente)
                    .addComponent(txtf_NVCliente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(cbo_SelecVExistenteCliente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(pnl_UpdClienteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn_ActNVCliente, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(txtf_LlaveCliente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(lbl_IngresarLlave))
                .addContainerGap(13, Short.MAX_VALUE))
        );

        jPanel1.add(pnl_UpdCliente, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 220, 1020, 85));

        btn_ActNVDomicilio.setBackground(new java.awt.Color(255, 51, 51));
        btn_ActNVDomicilio.setFont(new java.awt.Font("Impact", 0, 18)); // NOI18N
        btn_ActNVDomicilio.setText("ACTUALIZAR");
        btn_ActNVDomicilio.setToolTipText("Insertar registro en la tabla seleccionada.");
        btn_ActNVDomicilio.setBorderPainted(false);
        btn_ActNVDomicilio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_ActNVDomicilioActionPerformed(evt);
            }
        });

        lbl_SeleccCampo2.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_SeleccCampo2.setText(">Elija el campo del registro a actualizar:");

        lbl_IngresarLlave2.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarLlave2.setText(">Ingrese el valor de la PK del registro:");

        lbl_IngresarNVDom.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarNVDom.setText(">Nuevo valor del campo:");

        cbo_CamposDomicilio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbo_CamposDomicilioActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout pnl_UpdDomicilioLayout = new javax.swing.GroupLayout(pnl_UpdDomicilio);
        pnl_UpdDomicilio.setLayout(pnl_UpdDomicilioLayout);
        pnl_UpdDomicilioLayout.setHorizontalGroup(
            pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addComponent(lbl_SeleccCampo2, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_CamposDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, 170, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarLlave2, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtf_LlaveDomicilio)))
                .addGroup(pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(lbl_IngresarNVDom)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(txtf_NVDomicilio)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addGap(18, 320, Short.MAX_VALUE)
                        .addComponent(btn_ActNVDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(83, 83, 83))))
        );
        pnl_UpdDomicilioLayout.setVerticalGroup(
            pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addGap(40, 40, 40)
                        .addComponent(btn_ActNVDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(pnl_UpdDomicilioLayout.createSequentialGroup()
                        .addGroup(pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lbl_SeleccCampo2)
                            .addComponent(cbo_CamposDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(lbl_IngresarNVDom)
                            .addComponent(txtf_NVDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(pnl_UpdDomicilioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lbl_IngresarLlave2)
                            .addComponent(txtf_LlaveDomicilio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(9, Short.MAX_VALUE))
        );

        jPanel1.add(pnl_UpdDomicilio, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 310, 1020, 85));

        cbo_CamposCompra.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbo_CamposCompraActionPerformed(evt);
            }
        });

        btn_ActNVCompra.setBackground(new java.awt.Color(255, 51, 51));
        btn_ActNVCompra.setFont(new java.awt.Font("Impact", 0, 18)); // NOI18N
        btn_ActNVCompra.setText("ACTUALIZAR");
        btn_ActNVCompra.setToolTipText("Insertar registro en la tabla seleccionada.");
        btn_ActNVCompra.setBorderPainted(false);
        btn_ActNVCompra.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_ActNVCompraActionPerformed(evt);
            }
        });

        lbl_SeleccCampo3.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_SeleccCampo3.setText(">Elija el campo del registro a actualizar:");

        lbl_IngresarLlave3.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarLlave3.setText(">Ingrese el valor de la PK del registro:");

        lbl_IngresarNVComp.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarNVComp.setText(">Nuevo valor del campo:");

        javax.swing.GroupLayout pnl_UpdCompraLayout = new javax.swing.GroupLayout(pnl_UpdCompra);
        pnl_UpdCompra.setLayout(pnl_UpdCompraLayout);
        pnl_UpdCompraLayout.setHorizontalGroup(
            pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                        .addComponent(lbl_SeleccCampo3, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_CamposCompra, 0, 171, Short.MAX_VALUE))
                    .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarLlave3, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtf_LlaveCompra)))
                .addGap(18, 18, 18)
                .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdCompraLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarNVComp)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(txtf_NVCompra, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_SelecVExistenteCompr, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdCompraLayout.createSequentialGroup()
                        .addComponent(btn_ActNVCompra, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(84, 84, 84))))
        );
        pnl_UpdCompraLayout.setVerticalGroup(
            pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                        .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(cbo_SelecVExistenteCompr, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(txtf_NVCompra, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(lbl_IngresarNVComp))
                        .addGap(18, 18, 18)
                        .addComponent(btn_ActNVCompra, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(pnl_UpdCompraLayout.createSequentialGroup()
                        .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lbl_SeleccCampo3)
                            .addComponent(cbo_CamposCompra, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(pnl_UpdCompraLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(txtf_LlaveCompra, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(lbl_IngresarLlave3))))
                .addContainerGap(7, Short.MAX_VALUE))
        );

        jPanel1.add(pnl_UpdCompra, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 410, 1020, 85));

        cbo_CamposContratacion.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbo_CamposContratacionActionPerformed(evt);
            }
        });

        btn_ActNVContratacion.setBackground(new java.awt.Color(255, 51, 51));
        btn_ActNVContratacion.setFont(new java.awt.Font("Impact", 0, 18)); // NOI18N
        btn_ActNVContratacion.setText("ACTUALIZAR");
        btn_ActNVContratacion.setToolTipText("Insertar registro en la tabla seleccionada.");
        btn_ActNVContratacion.setBorderPainted(false);
        btn_ActNVContratacion.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_ActNVContratacionActionPerformed(evt);
            }
        });

        lbl_SeleccCampo4.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_SeleccCampo4.setText(">Elija el campo del registro a actualizar:");

        lbl_IngresarLlave4.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarLlave4.setText(">Ingrese el valor de la PK del registro:");

        lbl_IngresarNVContr.setFont(new java.awt.Font("Segoe UI Semibold", 0, 16)); // NOI18N
        lbl_IngresarNVContr.setText(">Nuevo valor del campo:");

        javax.swing.GroupLayout pnl_UpdContratacionLayout = new javax.swing.GroupLayout(pnl_UpdContratacion);
        pnl_UpdContratacion.setLayout(pnl_UpdContratacionLayout);
        pnl_UpdContratacionLayout.setHorizontalGroup(
            pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                        .addComponent(lbl_SeleccCampo4, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_CamposContratacion, 0, 171, Short.MAX_VALUE))
                    .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarLlave4, javax.swing.GroupLayout.PREFERRED_SIZE, 295, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtf_LlaveContratacion)))
                .addGap(18, 18, 18)
                .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdContratacionLayout.createSequentialGroup()
                        .addComponent(lbl_IngresarNVContr)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(txtf_NVContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(cbo_SelecVExistenteContr, javax.swing.GroupLayout.PREFERRED_SIZE, 158, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_UpdContratacionLayout.createSequentialGroup()
                        .addComponent(btn_ActNVContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(84, 84, 84))))
        );
        pnl_UpdContratacionLayout.setVerticalGroup(
            pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                        .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(cbo_SelecVExistenteContr, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(txtf_NVContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(lbl_IngresarNVContr))
                        .addGap(18, 18, 18)
                        .addComponent(btn_ActNVContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(pnl_UpdContratacionLayout.createSequentialGroup()
                        .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lbl_SeleccCampo4)
                            .addComponent(cbo_CamposContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(pnl_UpdContratacionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lbl_IngresarLlave4)
                            .addComponent(txtf_LlaveContratacion, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(7, Short.MAX_VALUE))
        );

        jPanel1.add(pnl_UpdContratacion, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 500, 1020, 85));

        cboSeleccTabla.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cboSeleccTablaActionPerformed(evt);
            }
        });
        jPanel1.add(cboSeleccTabla, new org.netbeans.lib.awtextra.AbsoluteConstraints(590, 180, 170, 30));

        lbl_SeleccTab.setFont(new java.awt.Font("Malgun Gothic", 1, 20)); // NOI18N
        lbl_SeleccTab.setText("•Seleccione la tabla en la que desea actualizar registros:");
        jPanel1.add(lbl_SeleccTab, new org.netbeans.lib.awtextra.AbsoluteConstraints(40, 180, 540, 30));

        lbl_fondo.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lbl_fondo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Imagenes/bck.png"))); // NOI18N
        jPanel1.add(lbl_fondo, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 1045, 600));

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 1045, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 600, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btn_ActNVClienteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_ActNVClienteActionPerformed
        //Variables
        String str_campoamod, str_primarykey, str_newvalcampo, str_newvalexistcampo;
        long valor_primarykey, valor_iddomic;
        Date valor_fechnac;
        
        str_campoamod=cbo_CamposCliente.getSelectedItem().toString();
        str_primarykey=txtf_LlaveCliente.getText();
        valor_primarykey=Long.parseLong(str_primarykey);
        str_newvalcampo=txtf_NVCliente.getText();
        
        if(str_campoamod.equals("nomb_client")){
            BeanClient bclient_nomb=new BeanClient(valor_primarykey,str_newvalcampo); 
            this.actualizarCliente("nomb_client", bclient_nomb);
        }else if(str_campoamod.equals("appat_client")){
            BeanClient bclient_appat=new BeanClient(valor_primarykey,str_newvalcampo,"");
            this.actualizarCliente("appat_client", bclient_appat);
        }else if(str_campoamod.equals("apmat_client")){
            BeanClient bclient_apmat=new BeanClient(valor_primarykey,str_newvalcampo,"","");
            this.actualizarCliente("apmat_client", bclient_apmat);
        }else if(str_campoamod.equals("tel_client")){
            BeanClient bclient_tel=new BeanClient(valor_primarykey,str_newvalcampo,"","","");
            this.actualizarCliente("tel_client", bclient_tel);
        }else if(str_campoamod.equals("cel_client")){
            BeanClient bclient_cel=new BeanClient(valor_primarykey,str_newvalcampo,"","","","");
            this.actualizarCliente("cel_client", bclient_cel);
        }else if(str_campoamod.equals("fechnac_client")){
            valor_fechnac=Date.valueOf(str_newvalcampo);
            BeanClient bclient_fechnac=new BeanClient(valor_primarykey,valor_fechnac);
            this.actualizarCliente("fechnac_client", bclient_fechnac);
        }else if(str_campoamod.equals("id_domicilio")){
            str_newvalexistcampo=cbo_SelecVExistenteCliente.getSelectedItem().toString();
            valor_iddomic=Long.parseLong(str_newvalexistcampo); 
            BeanClient bclient_iddomic=new BeanClient(valor_primarykey,valor_iddomic);
            this.actualizarCliente("id_domicilio", bclient_iddomic);
        }
    }//GEN-LAST:event_btn_ActNVClienteActionPerformed

    private void btn_ActNVDomicilioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_ActNVDomicilioActionPerformed
        //Variables
        String str_campomodif, str_pk, str_nuevovalcampo;
        long valor_pk;
        int valor_next, valor_nint;
        
        str_campomodif=cbo_CamposDomicilio.getSelectedItem().toString();
        str_pk=txtf_LlaveDomicilio.getText();
        str_nuevovalcampo=txtf_NVDomicilio.getText();
        valor_pk=Long.parseLong(str_pk);
        
        if(str_campomodif.equals("ciudadmun_domicilio")){
            BeanDomicilio bdom_ciudmun=new BeanDomicilio(valor_pk,str_nuevovalcampo);
            this.actualizarDomicilio("ciudadmun_domicilio", bdom_ciudmun);
        }else if(str_campomodif.equals("cp_domicilio")){
            BeanDomicilio bdom_cp=new BeanDomicilio(valor_pk,str_nuevovalcampo,"");
            this.actualizarDomicilio("cp_domicilio", bdom_cp);
        }else if(str_campomodif.equals("colonia_domicilio")){
            BeanDomicilio bdom_col=new BeanDomicilio(valor_pk,str_nuevovalcampo,"","");
            this.actualizarDomicilio("colonia_domicilio", bdom_col);
        }else if(str_campomodif.equals("calle_domicilio")){
            BeanDomicilio bdom_calle=new BeanDomicilio(valor_pk,str_nuevovalcampo,"","","");
            this.actualizarDomicilio("calle_domicilio", bdom_calle);
        }else if(str_campomodif.equals("nint_domicilio")){
            valor_nint=Integer.parseInt(str_nuevovalcampo);
            BeanDomicilio bdom_nint=new BeanDomicilio(valor_pk,valor_nint);
            this.actualizarDomicilio("nint_domicilio", bdom_nint); 
        }else if(str_campomodif.equals("next_domicilio")){ 
            valor_next=Integer.parseInt(str_nuevovalcampo);
            BeanDomicilio bdom_next=new BeanDomicilio(valor_pk,valor_next,"");
            this.actualizarDomicilio("next_domicilio", bdom_next);
        }
    }//GEN-LAST:event_btn_ActNVDomicilioActionPerformed

    private void btn_ActNVCompraActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_ActNVCompraActionPerformed
        //Variables
        String str_cmpamod, str_primaryk, str_newvcmp;
        Long valor_primaryk, valor_idcli, valor_nserie;
        int valor_idases, valor_idformp, valor_idplanp;
        Date valor_fechcomp;
        Time valor_horacomp;
        double valor_monto; 
        
        
        str_cmpamod=cbo_CamposCompra.getSelectedItem().toString();
        str_primaryk=txtf_LlaveCompra.getText();
        if(str_cmpamod.equals("id_client") || str_cmpamod.equals("nserie_auto") || str_cmpamod.equals("id_asesor") || str_cmpamod.equals("id_formapago") || str_cmpamod.equals("id_planpago")){
            str_newvcmp=cbo_SelecVExistenteCompr.getSelectedItem().toString();
        }else{
            str_newvcmp=txtf_NVCompra.getText();
        }
        valor_primaryk=Long.parseLong(str_primaryk);
        
        
        if(str_cmpamod.equals("id_client")){
            valor_idcli=Long.parseLong(str_newvcmp);
            BeanCompra bcom_idcli=new BeanCompra(valor_primaryk,valor_idcli);
            this.actualizarCompra("id_client", bcom_idcli); 
        }else if(str_cmpamod.equals("nserie_auto")){
            valor_nserie=Long.parseLong(str_newvcmp);
            BeanCompra bcom_nserie=new BeanCompra(valor_primaryk,valor_nserie,"");
            this.actualizarCompra("nserie_auto", bcom_nserie); 
        }else if(str_cmpamod.equals("id_asesor")){
            valor_idases=Integer.parseInt(str_newvcmp);
            BeanCompra bcom_idases=new BeanCompra(valor_primaryk,valor_idases);
            this.actualizarCompra("id_asesor", bcom_idases); 
        }else if(str_cmpamod.equals("id_formapago")){
            valor_idformp=Integer.parseInt(str_newvcmp);
            BeanCompra bcom_idformp=new BeanCompra(valor_primaryk,valor_idformp,"");
            this.actualizarCompra("id_formapago", bcom_idformp);
        }else if(str_cmpamod.equals("id_planpago")){
            valor_idplanp=Integer.parseInt(str_newvcmp); 
            BeanCompra bcom_idplanp=new BeanCompra(valor_primaryk,valor_idplanp,"","");
            this.actualizarCompra("id_planpago", bcom_idplanp); 
        }else if(str_cmpamod.equals("fech_compr")){
            valor_fechcomp=Date.valueOf(str_newvcmp);
            BeanCompra bcom_fechcomp=new BeanCompra(valor_primaryk,valor_fechcomp);
            this.actualizarCompra("fech_compr", bcom_fechcomp); 
        }else if(str_cmpamod.equals("hora_compr")){
            valor_horacomp=Time.valueOf(str_newvcmp); 
            BeanCompra bcom_horacomp=new BeanCompra(valor_primaryk,valor_horacomp);
            this.actualizarCompra("hora_compr", bcom_horacomp); 
        }else if(str_cmpamod.equals("monto_compr")){
            valor_monto=Double.parseDouble(str_newvcmp);
            BeanCompra bcom_montocomp=new BeanCompra(valor_primaryk,valor_monto);
            this.actualizarCompra("monto_compr", bcom_montocomp); 
        } 
    }//GEN-LAST:event_btn_ActNVCompraActionPerformed

    private void btn_ActNVContratacionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_ActNVContratacionActionPerformed
        //Variables
        String strn_campomodif, strn_pkey, str_nuevalorcamp;
        Long valor_pkey, valor_idclien, valor_nseri, valor_idserv;
        int valor_idformap, valor_idplanp;
        Date valor_fechcontr;
        Time valor_horacontr;
        double valor_montocontr;
        
        strn_campomodif=cbo_CamposContratacion.getSelectedItem().toString();
        strn_pkey=txtf_LlaveContratacion.getText();
        valor_pkey=Long.parseLong(strn_pkey);
        if(strn_campomodif.equals("id_client") || strn_campomodif.equals("nserie_auto") || strn_campomodif.equals("id_serv") || strn_campomodif.equals("id_formapago") || strn_campomodif.equals("id_planpago")){
            str_nuevalorcamp=cbo_SelecVExistenteContr.getSelectedItem().toString();
        }else{
            str_nuevalorcamp=txtf_NVContratacion.getText();
        }
        
        if(strn_campomodif.equals("id_client")){
            valor_idclien=Long.parseLong(str_nuevalorcamp);
            BeanContratacion bcont_idcli=new BeanContratacion(valor_pkey,valor_idclien);
            this.actualizarContratacion("id_client", bcont_idcli);       
            
        }else if(strn_campomodif.equals("nserie_auto")){
            valor_nseri=Long.parseLong(str_nuevalorcamp);
            BeanContratacion bcont_nseri=new BeanContratacion(valor_pkey,valor_nseri,"");
            this.actualizarContratacion("nserie_auto", bcont_nseri); 
            
        }else if(strn_campomodif.equals("id_serv")){
            valor_idserv=Long.parseLong(str_nuevalorcamp);
            BeanContratacion bcont_idserv=new BeanContratacion(valor_pkey,valor_idserv,"",""); 
            this.actualizarContratacion("id_serv", bcont_idserv); 
            
        }else if(strn_campomodif.equals("id_formapago")){
            valor_idformap=Integer.parseInt(str_nuevalorcamp);
            BeanContratacion bcont_idformp=new BeanContratacion(valor_pkey,valor_idformap);
            this.actualizarContratacion("id_formapago", bcont_idformp); 
            
        }else if(strn_campomodif.equals("id_planpago")){
            valor_idplanp=Integer.parseInt(str_nuevalorcamp);
            BeanContratacion bcont_idplanp=new BeanContratacion(valor_pkey,valor_idplanp,"");
            this.actualizarContratacion("id_planpago", bcont_idplanp); 
            
        }else if(strn_campomodif.equals("fech_contrat")){
            valor_fechcontr=Date.valueOf(str_nuevalorcamp);
            BeanContratacion bcont_fechcont=new BeanContratacion(valor_pkey,valor_fechcontr);
            this.actualizarContratacion("fech_contrat", bcont_fechcont); 
            
        }else if(strn_campomodif.equals("hora_contrat")){
            valor_horacontr=Time.valueOf(str_nuevalorcamp); 
            BeanContratacion bcont_horacont=new BeanContratacion(valor_pkey,valor_horacontr);
            this.actualizarContratacion("hora_contrat", bcont_horacont); 
            
        }else if(strn_campomodif.equals("monto_contrat")){
            valor_montocontr=Double.parseDouble(str_nuevalorcamp); 
            BeanContratacion bcont_montocont=new BeanContratacion(valor_pkey,valor_montocontr);
            this.actualizarContratacion("monto_contrat", bcont_montocont); 
            
        } 
    }//GEN-LAST:event_btn_ActNVContratacionActionPerformed

    private void cboSeleccTablaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cboSeleccTablaActionPerformed
        //Condicionales dependiendo de la tabla seleccionada en el ComboBox
        switch(cboSeleccTabla.getSelectedIndex()){
            case 0://-----------------------------------------------------------
            //1
            pnl_UpdCliente.setEnabled(false);
            lbl_SeleccCampo.setEnabled(false);
            cbo_CamposCliente.setEnabled(false);
            cbo_SelecVExistenteCliente.setEnabled(false); 
            lbl_IngresarLlave.setEnabled(false);
            txtf_LlaveCliente.setText("");
            txtf_LlaveCliente.setEnabled(false);
            lbl_IngresarNVCliente.setEnabled(false);
            txtf_NVCliente.setText("");
            txtf_NVCliente.setEnabled(false);
            btn_ActNVCliente.setEnabled(false);
            //2
            pnl_UpdDomicilio.setEnabled(false);
            lbl_SeleccCampo2.setEnabled(false);
            cbo_CamposDomicilio.setEnabled(false);
            lbl_IngresarLlave2.setEnabled(false);
            txtf_LlaveDomicilio.setText("");
            txtf_LlaveDomicilio.setEnabled(false);
            lbl_IngresarNVDom.setEnabled(false);
            txtf_NVDomicilio.setText("");
            txtf_NVDomicilio.setEnabled(false);
            btn_ActNVDomicilio.setEnabled(false);
            //3
            pnl_UpdCompra.setEnabled(false);
            lbl_SeleccCampo3.setEnabled(false);
            cbo_CamposCompra.setEnabled(false);
            lbl_IngresarLlave3.setEnabled(false);
            txtf_LlaveCompra.setText("");
            txtf_LlaveCompra.setEnabled(false);
            lbl_IngresarNVComp.setEnabled(false);
            txtf_NVCompra.setText("");
            txtf_NVCompra.setEnabled(false);
            cbo_SelecVExistenteCompr.setEnabled(false);
            btn_ActNVCompra.setEnabled(false);
            //4
            pnl_UpdContratacion.setEnabled(false);
            lbl_SeleccCampo4.setEnabled(false);
            cbo_CamposContratacion.setEnabled(false);
            lbl_IngresarLlave4.setEnabled(false);
            txtf_LlaveContratacion.setText("");
            txtf_LlaveContratacion.setEnabled(false);
            lbl_IngresarNVContr.setEnabled(false);
            txtf_NVContratacion.setText("");
            txtf_NVContratacion.setEnabled(false);
            cbo_SelecVExistenteContr.setEnabled(false);
            btn_ActNVContratacion.setEnabled(false);
                break;
            case 1:
            //1
            pnl_UpdCliente.setEnabled(true);
            lbl_SeleccCampo.setEnabled(true);
            cbo_CamposCliente.setEnabled(true);
            cbo_CamposCliente.setSelectedIndex(0);
            lbl_IngresarLlave.setEnabled(true);
            txtf_LlaveCliente.setEnabled(true);
            txtf_LlaveCliente.setText("");
            lbl_IngresarNVCliente.setEnabled(true);
            txtf_NVCliente.setEnabled(true);
            txtf_NVCliente.setText("");
            cbo_SelecVExistenteCliente.setEnabled(true); 
            //cbo_SelecVExistenteCliente.setSelectedIndex(0); 
            btn_ActNVCliente.setEnabled(false);
            //2
            pnl_UpdDomicilio.setEnabled(false);
            lbl_SeleccCampo2.setEnabled(false);
            cbo_CamposDomicilio.setEnabled(false);
            lbl_IngresarLlave2.setEnabled(false);
            txtf_LlaveDomicilio.setEnabled(false);
            lbl_IngresarNVDom.setEnabled(false);
            txtf_NVDomicilio.setEnabled(false);
            btn_ActNVDomicilio.setEnabled(false);
            //3
            pnl_UpdCompra.setEnabled(false);
            lbl_SeleccCampo3.setEnabled(false);
            cbo_CamposCompra.setEnabled(false);
            lbl_IngresarLlave3.setEnabled(false);
            txtf_LlaveCompra.setEnabled(false);
            lbl_IngresarNVComp.setEnabled(false);
            txtf_NVCompra.setEnabled(false);
            cbo_SelecVExistenteCompr.setEnabled(false);
            btn_ActNVCompra.setEnabled(false);
            //4
            pnl_UpdContratacion.setEnabled(false);
            lbl_SeleccCampo4.setEnabled(false);
            cbo_CamposContratacion.setEnabled(false);
            lbl_IngresarLlave4.setEnabled(false);
            txtf_LlaveContratacion.setEnabled(false);
            lbl_IngresarNVContr.setEnabled(false);
            txtf_NVContratacion.setEnabled(false);
            cbo_SelecVExistenteContr.setEnabled(false);
            btn_ActNVContratacion.setEnabled(false);
            //
            cbo_CamposCliente.setSelectedIndex(0);
            cbo_CamposDomicilio.setSelectedIndex(0);
            cbo_CamposCompra.setSelectedIndex(0);
            cbo_CamposContratacion.setSelectedIndex(0);
                break;
            case 2:
            //1
            pnl_UpdCliente.setEnabled(false);
            lbl_SeleccCampo.setEnabled(false);
            cbo_CamposCliente.setEnabled(false);
            cbo_SelecVExistenteCliente.setEnabled(false); 
            lbl_IngresarLlave.setEnabled(false);
            txtf_LlaveCliente.setEnabled(false);
            lbl_IngresarNVCliente.setEnabled(false);
            txtf_NVCliente.setEnabled(false);
            btn_ActNVCliente.setEnabled(false);
            //2
            pnl_UpdDomicilio.setEnabled(true);
            lbl_SeleccCampo2.setEnabled(true);
            cbo_CamposDomicilio.setEnabled(true);
            cbo_CamposDomicilio.setSelectedIndex(0);
            lbl_IngresarLlave2.setEnabled(true);
            txtf_LlaveDomicilio.setEnabled(true);
            txtf_LlaveDomicilio.setText("");
            lbl_IngresarNVDom.setEnabled(true);
            txtf_NVDomicilio.setEnabled(true);
            txtf_NVDomicilio.setText("");
            btn_ActNVDomicilio.setEnabled(false);
            //3
            pnl_UpdCompra.setEnabled(false);
            lbl_SeleccCampo3.setEnabled(false);
            cbo_CamposCompra.setEnabled(false);
            lbl_IngresarLlave3.setEnabled(false);
            txtf_LlaveCompra.setEnabled(false);
            lbl_IngresarNVComp.setEnabled(false);
            txtf_NVCompra.setEnabled(false);
            cbo_SelecVExistenteCompr.setEnabled(false);
            btn_ActNVCompra.setEnabled(false);
            //4
            pnl_UpdContratacion.setEnabled(false);
            lbl_SeleccCampo4.setEnabled(false);
            cbo_CamposContratacion.setEnabled(false);
            lbl_IngresarLlave4.setEnabled(false);
            txtf_LlaveContratacion.setEnabled(false);
            lbl_IngresarNVContr.setEnabled(false);
            txtf_NVContratacion.setEnabled(false);
            cbo_SelecVExistenteContr.setEnabled(false);
            btn_ActNVContratacion.setEnabled(false);
            //
            cbo_CamposCliente.setSelectedIndex(0);
            cbo_CamposDomicilio.setSelectedIndex(0);
            cbo_CamposCompra.setSelectedIndex(0);
            cbo_CamposContratacion.setSelectedIndex(0);
                break;
            case 3:
            //1
            pnl_UpdCliente.setEnabled(false);
            lbl_SeleccCampo.setEnabled(false);
            cbo_CamposCliente.setEnabled(false);
            cbo_SelecVExistenteCliente.setEnabled(false); 
            lbl_IngresarLlave.setEnabled(false);
            txtf_LlaveCliente.setEnabled(false);
            lbl_IngresarNVCliente.setEnabled(false);
            txtf_NVCliente.setEnabled(false);
            btn_ActNVCliente.setEnabled(false);
            //2
            pnl_UpdDomicilio.setEnabled(false);
            lbl_SeleccCampo2.setEnabled(false);
            cbo_CamposDomicilio.setEnabled(false);
            lbl_IngresarLlave2.setEnabled(false);
            txtf_LlaveDomicilio.setEnabled(false);
            lbl_IngresarNVDom.setEnabled(false);
            txtf_NVDomicilio.setEnabled(false);
            btn_ActNVDomicilio.setEnabled(false);
            //3
            pnl_UpdCompra.setEnabled(true);
            lbl_SeleccCampo3.setEnabled(true);
            cbo_CamposCompra.setEnabled(true);
            cbo_CamposCompra.setSelectedIndex(0);
            lbl_IngresarLlave3.setEnabled(true);
            txtf_LlaveCompra.setEnabled(true);
            txtf_LlaveCompra.setText("");
            lbl_IngresarNVComp.setEnabled(true);
            txtf_NVCompra.setEnabled(true);
            txtf_NVCompra.setText("");
            cbo_SelecVExistenteCompr.setEnabled(true);
            btn_ActNVCompra.setEnabled(false);
            //4
            pnl_UpdContratacion.setEnabled(false);
            lbl_SeleccCampo4.setEnabled(false);
            cbo_CamposContratacion.setEnabled(false);
            lbl_IngresarLlave4.setEnabled(false);
            txtf_LlaveContratacion.setEnabled(false);
            lbl_IngresarNVContr.setEnabled(false);
            txtf_NVContratacion.setEnabled(false);
            cbo_SelecVExistenteContr.setEnabled(false);
            btn_ActNVContratacion.setEnabled(false);
            //
            cbo_CamposCliente.setSelectedIndex(0);
            cbo_CamposDomicilio.setSelectedIndex(0);
            cbo_CamposCompra.setSelectedIndex(0);
            cbo_CamposContratacion.setSelectedIndex(0);
                break;
            case 4:
            //1
            pnl_UpdCliente.setEnabled(false);
            lbl_SeleccCampo.setEnabled(false);
            cbo_CamposCliente.setEnabled(false);
            cbo_SelecVExistenteCliente.setEnabled(false); 
            lbl_IngresarLlave.setEnabled(false);
            txtf_LlaveCliente.setEnabled(false);
            lbl_IngresarNVCliente.setEnabled(false);
            txtf_NVCliente.setEnabled(false);
            btn_ActNVCliente.setEnabled(false);
            //2
            pnl_UpdDomicilio.setEnabled(false);
            lbl_SeleccCampo2.setEnabled(false);
            cbo_CamposDomicilio.setEnabled(false);
            lbl_IngresarLlave2.setEnabled(false);
            txtf_LlaveDomicilio.setEnabled(false);
            lbl_IngresarNVDom.setEnabled(false);
            txtf_NVDomicilio.setEnabled(false);
            btn_ActNVDomicilio.setEnabled(false);
            //3
            pnl_UpdCompra.setEnabled(false);
            lbl_SeleccCampo3.setEnabled(false);
            cbo_CamposCompra.setEnabled(false);
            lbl_IngresarLlave3.setEnabled(false);
            txtf_LlaveCompra.setEnabled(false);
            lbl_IngresarNVComp.setEnabled(false);
            txtf_NVCompra.setEnabled(false);
            cbo_SelecVExistenteCompr.setEnabled(false);
            btn_ActNVCompra.setEnabled(false);
            //4
            pnl_UpdContratacion.setEnabled(true);
            lbl_SeleccCampo4.setEnabled(true);
            cbo_CamposContratacion.setEnabled(true);
            cbo_CamposContratacion.setSelectedIndex(0);
            lbl_IngresarLlave4.setEnabled(true);
            txtf_LlaveContratacion.setEnabled(true);
            txtf_LlaveContratacion.setText("");
            lbl_IngresarNVContr.setEnabled(true);
            txtf_NVContratacion.setEnabled(true);
            txtf_NVContratacion.setText("");
            cbo_SelecVExistenteContr.setEnabled(true);
            btn_ActNVContratacion.setEnabled(false);
            //
            cbo_CamposCliente.setSelectedIndex(0);
            cbo_CamposDomicilio.setSelectedIndex(0);
            cbo_CamposCompra.setSelectedIndex(0);
            cbo_CamposContratacion.setSelectedIndex(0);
                break;
            default:
                break;
        }
    }//GEN-LAST:event_cboSeleccTablaActionPerformed

    private void cbo_CamposClienteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbo_CamposClienteActionPerformed
        //
        switch(cbo_CamposCliente.getSelectedIndex()){
            case 0:
                //
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(false); 
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(0));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false); 
                btn_ActNVCliente.setEnabled(false);
                break;
            case 1://Nombre
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true); 
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(25));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false); 
                btn_ActNVCliente.setEnabled(true);
                break;
            case 2://ApPat
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(15));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false);
                btn_ActNVCliente.setEnabled(true);
                break;
            case 3://ApMat
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(15));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false);
                btn_ActNVCliente.setEnabled(true);
                break;
            case 4://Tel
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(7));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false);
                btn_ActNVCliente.setEnabled(true);
                break;
            case 5://Cel
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(12));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false);
                btn_ActNVCliente.setEnabled(true);
                break;
            case 6://FechNac
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setDocument(new LengthRestrictedDocument(10));
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(false);
                btn_ActNVCliente.setEnabled(true);
                break;
            case 7://IdDom
                txtf_LlaveCliente.setText("");
                txtf_LlaveCliente.setEnabled(true);
                txtf_NVCliente.setText("");
                txtf_NVCliente.setEnabled(false); 
                cbo_SelecVExistenteCliente.removeAllItems();
                cbo_SelecVExistenteCliente.setEnabled(true);
                this.valoresExistentesCliente();
                btn_ActNVCliente.setEnabled(true);
                break;
            default:
                break;
        }
    }//GEN-LAST:event_cbo_CamposClienteActionPerformed

    private void cbo_CamposCompraActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbo_CamposCompraActionPerformed
        //
        switch(cbo_CamposCompra.getSelectedIndex()){
            case 0:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(false);
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(false);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(false); 
                break;
            case 1:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(true);
                this.valoresExistentesCompra("id_client","cliente");
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 2:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(true);
                this.valoresExistentesCompra("nserie_auto","automovil");
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 3:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(true);
                this.valoresExistentesCompra("id_asesor","asesor");
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 4:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(true);
                this.valoresExistentesCompra("id_formapago","forma_pago");
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 5:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(true);
                this.valoresExistentesCompra("id_planpago","plan_pago");
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(false);
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 6:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(false);
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(true);
                txtf_NVCompra.setDocument(new LengthRestrictedDocument(10));
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 7:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(false);
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(true);
                txtf_NVCompra.setDocument(new LengthRestrictedDocument(8));
                btn_ActNVCompra.setEnabled(true); 
                break;
            case 8:
                cbo_SelecVExistenteCompr.removeAllItems();
                cbo_SelecVExistenteCompr.setEnabled(false);
                txtf_LlaveCompra.setText("");
                txtf_LlaveCompra.setEnabled(true);
                txtf_NVCompra.setText("");
                txtf_NVCompra.setEnabled(true);
                txtf_NVCompra.setDocument(new LengthRestrictedDocument(10));
                btn_ActNVCompra.setEnabled(true); 
                break;
            default:
                break;
        }
    }//GEN-LAST:event_cbo_CamposCompraActionPerformed

    private void cbo_CamposContratacionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbo_CamposContratacionActionPerformed
        //
        switch(cbo_CamposContratacion.getSelectedIndex()){
            case 0:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(false);
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(false); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(false);
                break;
            case 1:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(true);
                this.valoresExistentesContratacion("id_client","cliente");
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 2:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(true);
                this.valoresExistentesContratacion("nserie_auto","automovil");
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 3:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(true);
                this.valoresExistentesContratacion("id_serv","servicio");
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 4:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(true);
                this.valoresExistentesContratacion("id_formapago","forma_pago");
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 5:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(true);
                this.valoresExistentesContratacion("id_planpago","plan_pago");
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true); 
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(false);
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 6:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(false);
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true);
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(true);
                txtf_NVContratacion.setDocument(new LengthRestrictedDocument(10));
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 7:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(false);
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true);
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(true);
                txtf_NVContratacion.setDocument(new LengthRestrictedDocument(8));
                btn_ActNVContratacion.setEnabled(true);
                break;
            case 8:
                cbo_SelecVExistenteContr.removeAllItems();
                cbo_SelecVExistenteContr.setEnabled(false);
                txtf_LlaveContratacion.setText("");
                txtf_LlaveContratacion.setEnabled(true);
                txtf_NVContratacion.setText("");
                txtf_NVContratacion.setEnabled(true);
                txtf_NVContratacion.setDocument(new LengthRestrictedDocument(8));
                btn_ActNVContratacion.setEnabled(true);
                break;
            default:
                break;
        }
    }//GEN-LAST:event_cbo_CamposContratacionActionPerformed

    private void cbo_CamposDomicilioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbo_CamposDomicilioActionPerformed
        //
        switch(cbo_CamposDomicilio.getSelectedIndex()){
            case 0:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(false); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(0));
                btn_ActNVDomicilio.setEnabled(false);
                break;
            case 1:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(25));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            case 2:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(5));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            case 3:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(25));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            case 4:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(25));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            case 5:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(2));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            case 6:
                txtf_LlaveDomicilio.setText("");
                txtf_LlaveDomicilio.setEnabled(true); 
                txtf_NVDomicilio.setText("");
                txtf_NVDomicilio.setDocument(new LengthRestrictedDocument(3));
                btn_ActNVDomicilio.setEnabled(true);
                break;
            default:
                break;
        }
    }//GEN-LAST:event_cbo_CamposDomicilioActionPerformed

    //Métodos de actualización/UPDATE
    //--------------------------
    public void actualizarCliente(String campoC, BeanClient beanC){
        try{
            PreparedStatement ps=vcon.prepareStatement("UPDATE cliente SET "+campoC+" = ? WHERE id_client = ?");
            if(campoC=="nomb_client"){
                ps.setString(1, beanC.getNomb_client());
            }else if(campoC=="appat_client"){
                ps.setString(1, beanC.getAppat_client());
            }else if(campoC=="apmat_client"){
                ps.setString(1, beanC.getApmat_client());
            }else if(campoC=="tel_client"){
                ps.setString(1, beanC.getTel_client());
            }else if(campoC=="cel_client"){
                ps.setString(1, beanC.getCel_client());
            }else if(campoC=="fechnac_client"){
                ps.setDate(1, beanC.getFechnac_client());
            }else if(campoC=="id_domicilio"){
                ps.setLong(1, beanC.getId_domicilio());
            }
            //
            ps.setLong(2, beanC.getId_client());
            int aff_rows=ps.executeUpdate();
            JOptionPane.showMessageDialog(this, "¡Operación exitosa en 'Cliente'!, filas afectadas: "+aff_rows, "Mensaje", JOptionPane.INFORMATION_MESSAGE);
        }catch(SQLException sqlex){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    //--------------------------
    public void actualizarDomicilio(String campoD, BeanDomicilio beanD){
        try{
            PreparedStatement ps1=vcon.prepareStatement("UPDATE domicilio SET "+campoD+" = ? WHERE id_domicilio = ?");
            if(campoD=="ciudadmun_domicilio"){
                ps1.setString(1, beanD.getCiudadmun_domicilio());
            }else if(campoD=="cp_domicilio"){
                ps1.setString(1, beanD.getCp_domicilio());
            }else if(campoD=="colonia_domicilio"){
                ps1.setString(1, beanD.getColonia_domicilio());
            }else if(campoD=="calle_domicilio"){
                ps1.setString(1, beanD.getCalle_domicilio());
            }else if(campoD=="nint_domicilio"){
                ps1.setInt(1, beanD.getNint_domicilio());
            }else if(campoD=="next_domicilio"){
                ps1.setInt(1, beanD.getNext_domicilio());
            }
            //
            ps1.setLong(2, beanD.getId_domicilio());
            int aff_rows1=ps1.executeUpdate();
            JOptionPane.showMessageDialog(this, "¡Operación exitosa en 'Domicilio'!, filas afectadas: "+aff_rows1, "Mensaje", JOptionPane.INFORMATION_MESSAGE);
        }catch(SQLException sqlex1){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex1.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    //--------------------------
    public void actualizarCompra(String campoCompr, BeanCompra beanCompr){
        try{
            PreparedStatement ps2=vcon.prepareStatement("UPDATE compra SET "+campoCompr+" = ? WHERE id_compr = ?");
            if(campoCompr=="id_client"){
                ps2.setLong(1, beanCompr.getId_client());
            }else if(campoCompr=="nserie_auto"){
                ps2.setLong(1, beanCompr.getNserie_auto());
            }else if(campoCompr=="id_asesor"){
                ps2.setInt(1, beanCompr.getId_asesor());
            }else if(campoCompr=="id_formapago"){
                ps2.setInt(1, beanCompr.getId_formapago());
            }else if(campoCompr=="id_planpago"){
                ps2.setInt(1, beanCompr.getId_planpago());
            }else if(campoCompr=="fech_compr"){
                ps2.setDate(1, beanCompr.getFech_compr());
            }else if(campoCompr=="hora_compr"){
                ps2.setTime(1, beanCompr.getHora_compr());
            }else if(campoCompr=="monto_compr"){
                ps2.setDouble(1, beanCompr.getMonto_compr());
            }
            //
            ps2.setLong(2, beanCompr.getId_compr());
            int aff_rows2=ps2.executeUpdate();
            JOptionPane.showMessageDialog(this, "¡Operación exitosa en 'Compra'!, filas afectadas: "+aff_rows2, "Mensaje", JOptionPane.INFORMATION_MESSAGE);
        }catch(SQLException sqlex2){
             JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex2.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    //--------------------------
    public void actualizarContratacion(String campoContra, BeanContratacion beanContra){
        try{
            PreparedStatement ps3=vcon.prepareStatement("UPDATE contratacion SET "+campoContra+" = ? WHERE id_contrat = ?");
            if(campoContra=="id_client"){
                ps3.setLong(1, beanContra.getId_client());
            }else if(campoContra=="nserie_auto"){
                ps3.setLong(1, beanContra.getNserie_auto());
            }else if(campoContra=="id_serv"){
                ps3.setLong(1, beanContra.getId_serv());
            }else if(campoContra=="id_formapago"){
                ps3.setInt(1, beanContra.getId_formapago());
            }else if(campoContra=="id_planpago"){
                ps3.setInt(1, beanContra.getId_planpago());
            }else if(campoContra=="fech_contrat"){
                ps3.setDate(1, beanContra.getFech_contrat());
            }else if(campoContra=="hora_contrat"){
                ps3.setTime(1, beanContra.getHora_contrat());
            }else if(campoContra=="monto_contrat"){
                ps3.setDouble(1, beanContra.getMonto_contrat());
            }
            //
            ps3.setLong(2, beanContra.getId_contrat());
            int aff_rows3=ps3.executeUpdate();
            JOptionPane.showMessageDialog(this, "¡Operación exitosa en 'Contratacion'!, filas afectadas: "+aff_rows3, "Mensaje", JOptionPane.INFORMATION_MESSAGE);
        }catch(SQLException sqlex3){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex3.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    //Obtener PK's Compra
    public void valoresExistentesCompra(String campofk, String tabla){
        //Variables
        ResultSet rs;
        Statement stm;
        String sentenciaSQL="SELECT "+campofk+" FROM "+tabla;
        //try-catch
        try{
            stm=vcon.createStatement();
            rs=stm.executeQuery(sentenciaSQL);
            //
            if(campofk.equals("id_client") || campofk.equals("nserie_auto")){
                while(rs.next()){
                cbo_SelecVExistenteCompr.addItem(""+rs.getLong(1)+"");
                }
            }else if(campofk.equals("id_asesor") || campofk.equals("id_formapago") || campofk.equals("id_planpago")){
                while(rs.next()){
                cbo_SelecVExistenteCompr.addItem(""+rs.getInt(1)+"");
                }
            }
        }catch(SQLException sqlex4){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex4.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    //Obtener PK's Contratacion
    public void valoresExistentesContratacion(String campofk, String tabla){
        //Variables
        ResultSet rs;
        Statement stm;
        String sentenciaSQL="SELECT "+campofk+" FROM "+tabla;
        //try-catch
        try{
            stm=vcon.createStatement();
            rs=stm.executeQuery(sentenciaSQL);
            //
            if(campofk.equals("id_client") || campofk.equals("nserie_auto") || campofk.equals("id_serv")){
                while(rs.next()){
                cbo_SelecVExistenteContr.addItem(""+rs.getLong(1)+"");
                }
            }else if(campofk.equals("id_formapago") || campofk.equals("id_planpago")){
                while(rs.next()){
                cbo_SelecVExistenteContr.addItem(""+rs.getInt(1)+"");
                }
            }
        }catch(SQLException sqlex5){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex5.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    //Obtener PK's Cliente
    public void valoresExistentesCliente(){
        //Variables
        ResultSet rs;
        Statement stm;
        String sentenciaSQL="SELECT id_domicilio FROM domicilio";
        //try-catch
        try{
            stm=vcon.createStatement();
            rs=stm.executeQuery(sentenciaSQL);
            //
            while(rs.next()){
                cbo_SelecVExistenteCliente.addItem(""+rs.getLong(1)+"");
            }
        }catch(SQLException sqlex6){
            JOptionPane.showMessageDialog(this, "Ha ocurrido una excepción: "+sqlex6.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(VentanaUPDATE.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(VentanaUPDATE.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(VentanaUPDATE.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(VentanaUPDATE.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new VentanaUPDATE().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btn_ActNVCliente;
    private javax.swing.JButton btn_ActNVCompra;
    private javax.swing.JButton btn_ActNVContratacion;
    private javax.swing.JButton btn_ActNVDomicilio;
    private javax.swing.JComboBox<String> cboSeleccTabla;
    private javax.swing.JComboBox<String> cbo_CamposCliente;
    private javax.swing.JComboBox<String> cbo_CamposCompra;
    private javax.swing.JComboBox<String> cbo_CamposContratacion;
    private javax.swing.JComboBox<String> cbo_CamposDomicilio;
    private javax.swing.JComboBox<String> cbo_SelecVExistenteCliente;
    private javax.swing.JComboBox<String> cbo_SelecVExistenteCompr;
    private javax.swing.JComboBox<String> cbo_SelecVExistenteContr;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JLabel lbl_IngresarLlave;
    private javax.swing.JLabel lbl_IngresarLlave2;
    private javax.swing.JLabel lbl_IngresarLlave3;
    private javax.swing.JLabel lbl_IngresarLlave4;
    private javax.swing.JLabel lbl_IngresarNVCliente;
    private javax.swing.JLabel lbl_IngresarNVComp;
    private javax.swing.JLabel lbl_IngresarNVContr;
    private javax.swing.JLabel lbl_IngresarNVDom;
    private javax.swing.JLabel lbl_SeleccCampo;
    private javax.swing.JLabel lbl_SeleccCampo2;
    private javax.swing.JLabel lbl_SeleccCampo3;
    private javax.swing.JLabel lbl_SeleccCampo4;
    private javax.swing.JLabel lbl_SeleccTab;
    private javax.swing.JLabel lbl_fondo;
    private javax.swing.JPanel pnl_UpdCliente;
    private javax.swing.JPanel pnl_UpdCompra;
    private javax.swing.JPanel pnl_UpdContratacion;
    private javax.swing.JPanel pnl_UpdDomicilio;
    private javax.swing.JTextField txtf_LlaveCliente;
    private javax.swing.JTextField txtf_LlaveCompra;
    private javax.swing.JTextField txtf_LlaveContratacion;
    private javax.swing.JTextField txtf_LlaveDomicilio;
    private javax.swing.JTextField txtf_NVCliente;
    private javax.swing.JTextField txtf_NVCompra;
    private javax.swing.JTextField txtf_NVContratacion;
    private javax.swing.JTextField txtf_NVDomicilio;
    // End of variables declaration//GEN-END:variables
}
