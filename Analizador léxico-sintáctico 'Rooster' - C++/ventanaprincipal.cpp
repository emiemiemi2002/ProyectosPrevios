#include "ventanaprincipal.h"
#include "./ui_ventanaprincipal.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <QDebug>

#include <QVector>
#include <QString>
#include <stack>

#include <QIcon>
#include <QColor>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHeaderView>
#include <QCoreApplication>

using namespace std;

//Constructor
VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    //Setear tamaño predeterminado de ventana (sin resize)
    this->setFixedSize(1200,660);
    ui->centralwidget->setFixedSize(1200,660);
    //ícono
    QIcon icon("C:\\Users\\Propietario\\Documents\\Qt Projects\\Rooster\\Recursos\\Icono_Rooster.png");
    this->setWindowIcon(icon);
    //Elementos
    ui->btn_ANALIZAR->setEnabled(false);
    ui->btn_Limpiar->setEnabled(false);
    ui->btn_Guardar->setEnabled(false);
}

//Destructor
VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

/* Variables globales----------------------------------
 * 1.- Ruta de archivo leído
 * 2.- Pila de ejecución (análisis sintáctico)
 * 3.- Matriz de tokens (salida de análisis léxico)
 * 4.- Pila de símbolos (tipos de id's declarados)
 * 5.- Pila de símbolos (id's declarados)
 * 6.- Pila de tipos (analisis semántico)
 * 7.- Pila de operadores (analisis semántico)
 * 8.- Copia de pila de tipos (analisis semántico)
 * 9.- Copia de pila de operadores (analisis semántico)
 */
QString ruta;
stack<int> pilaX;
QVector<QVector<QString>> matriz_tokenid;
stack<QString> pilaSimbolos;
stack<QString> pilaSimbolos2;
stack<QString> pila_tipos;
stack<QString> pila_operadores;
stack<QString> copila_tipos;
stack<QString> copila_operadores;

// Eventos: al dar click en botón 'ANALIZAR'
void VentanaPrincipal::on_btn_ANALIZAR_clicked()
{
    //
    ui->lW_Tokens->clear();
    ui->lW_ErroresTokens->clear();
    ui->lW_MsjSintaxis->clear();
    ui->lW_MsjErrSintaxis->clear();
    ui->lW_MsjErrSemantic->clear();
    ui->lW_ContPilasSemantic->clear();

    ui->tW_VisualCuadrup->clear();
    ui->lW_ContPilasGCI->clear();
    //Limpiar contenido de estructuras de datos
    matriz_tokenid.clear();
    //Analizar léxico
    AnalizarLex();
    //Analizar sintáxis
    if(!matriz_tokenid.isEmpty()){
        AnalizarSintax();
    }
}

// Eventos: al dar click en botón 'Abrir archivo...'
void VentanaPrincipal::on_btn_AbrirArchivo_clicked()
{
    // Variables
    string rutastr;
    string contenido_linea;
    ruta=obtenerRutaArchivo();
    rutastr=ruta.toStdString();

    ifstream archivo(rutastr);
    // Condicional
    if(archivo.is_open()){
        // Mensaje de éxito
        cout << "El archivo fue abierto!" << endl;
        // Limpiar editor de texto
        ui->editorTextoArchivo->clear();
        // Añadir contenido de .txt al editor de texto
        while(getline(archivo,contenido_linea)){
            QString contenidolinea = QString::fromStdString(contenido_linea);
            ui->editorTextoArchivo->insertPlainText(contenidolinea+"\n");
        }
        // Activar botones
        ui->btn_ANALIZAR->setEnabled(true);
        ui->btn_Limpiar->setEnabled(true);
        ui->btn_Guardar->setEnabled(false);
        //
        archivo.close();
    }else{
        // Mensaje de error
        QMessageBox::critical(this, "Mensaje", "No se abrió ningún archivo.");
    }
}

// Eventos: al dar click en botón 'Guardar'
void VentanaPrincipal::on_btn_Guardar_clicked()
{
// Obtener contenido del editor de texto
    QString contenidoeditor = ui->editorTextoArchivo->toPlainText();
    // Condicionales según contenido de QString 'ruta'
    if(!ruta.isEmpty()){
        //
        QFile archivo(ruta);

        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream strm(&archivo);
            strm << contenidoeditor;
            archivo.close();
            QMessageBox::information(this, "Mensaje", "Éxito!");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para escritura.");
        }
    } else {
        //
        QString dir = QFileDialog::getExistingDirectory(this, tr("Seleccionar Directorio"), QDir::homePath());

        if (!dir.isEmpty()) {
            //Ingresar nombre del archivo
            QString rutarch = QDir(dir).filePath("nombre_archivo.rst");
            QFile arch(rutarch);

            if (arch.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream strm2(&arch);
                strm2 << contenidoeditor;
                arch.close();
                QMessageBox::information(this, "Mensaje", "Éxito!");
            } else {
                QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para escritura.");
            }
        } else {
            QMessageBox::information(this, "Mensaje", "No se seleccionó algún directorio.");
        }
    }
}

// Eventos: al dar click en botón 'Limpiar'
void VentanaPrincipal::on_btn_Limpiar_clicked()
{
    //Limpiar editor de texto
    ui->editorTextoArchivo->setText("");
    //Limpiar listas
    ui->lW_Tokens->clear();
    ui->lW_ErroresTokens->clear();
    ui->lW_MsjSintaxis->clear();
    ui->lW_MsjErrSintaxis->clear();
    ui->lW_MsjErrSemantic->clear();
    ui->lW_ContPilasSemantic->clear();
    //Limpiar tabla
    ui->tW_VisualCuadrup->clear();
}

// Eventos: al dar click en botón 'Salir'
void VentanaPrincipal::on_btn_Salir_clicked()
{
    //
    QString texto_editor = ui->editorTextoArchivo->toPlainText();
    QMessageBox::StandardButton respuesta;
    // Condicionales para determinar el mensaje mostrado
    if (!texto_editor.isEmpty()) {
        respuesta=QMessageBox::warning(this, "Advertencia", "¿Está seguro que desea salir sin guardar los cambios?...", QMessageBox::Yes | QMessageBox::No);
        // Condicionales según respuesta
        if (respuesta == QMessageBox::Yes) {
            close();
        } else if (respuesta == QMessageBox::No) {

        }
    } else {
        respuesta=QMessageBox::question(this, "Confirmación", "¿Está seguro que desea salir?...", QMessageBox::Yes | QMessageBox::No);
        // Condicionales según respuesta
        if (respuesta == QMessageBox::Yes) {
            close();
        } else if (respuesta == QMessageBox::No) {

        }
    }
}

// Función: Seleccionar archivo y obtener ruta
QString VentanaPrincipal::obtenerRutaArchivo(){
    // Abrir la ventana para seleccionar un archivo y obtener la ruta
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Seleccione un archivo...", "", "Archivos de texto (*.rst)");
    return rutaArchivo;
}

//Función 'Leer_Caracter()'
char VentanaPrincipal::Leer_Caracter(char*& puntero){
    char caracter = *puntero;  // Obtener el carácter actual apuntado por el puntero
    puntero++;
    return caracter;
}

//Función 'Leer_CarAnt()'
char VentanaPrincipal::Leer_CarAnt(char*& puntero){
    puntero--;
    char caracter = *puntero;
    puntero++;
    return caracter;
}

//Función 'Leer_CarPost()'
char VentanaPrincipal::Leer_CarPost(char*& puntero){
    puntero++;
    char caracter = *puntero;
    puntero--;
    return caracter;
}

// Función: Relacionar caracter con columna
int VentanaPrincipal::relacionarC(char c){
    //
    if(c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f'||c=='g'||c=='h'||c=='i'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'){
        return 0;
    }
    if(c=='A'||c=='B'||c=='C'||c=='D'||c=='F'||c=='G'||c=='H'||c=='I'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'){
        return 1;
    }
    if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){
        return 3;
    }
    //
    switch (c) {
    case '_':
        return 2;
        break;
    case '.':
        return 4;
        break;
    case 'E':
        return 5;
        break;
    case '+':
        return 6;
        break;
    case '-':
        return 7;
        break;
    case '/':
        return 9;
        break;
    case '*':
        return 10;
        break;
    case '=':
        return 11;
        break;
    case '%':
        return 12;
        break;
    case '&':
        return 13;
        break;
    case '!':
        return 14;
        break;
    case '|':
        return 15;
        break;
    case '<':
        return 16;
        break;
    case '>':
        return 17;
        break;
    case '{':
        return 18;
        break;
    case '}':
        return 19;
        break;
    case ',':
        return 20;
        break;
    case ':':
        return 21;
        break;
    case ';':
        return 22;
        break;
    case '[':
        return 23;
        break;
    case ']':
        return 24;
        break;
    case '(':
        return 25;
        break;
    case ')':
        return 26;
        break;
    case '\n':
        return 27;
        break;
    case '\t':
        return 28;
        break;
    case '\b':
        return 29;
        break;
    case '#':
        return 30;
        break;
    case '"':
        return 31;
        break;
    case '\'':
        return 32;
        break;
    default:
        return 8;
        break;
    }
}

// Función: Estado terminal de error
QString VentanaPrincipal::estadoError(int e){
    QString estadoerr="";
    //
    switch (e) {
    case 500:
        estadoerr="500: Valor flotante esperaba dígitos.";
        break;
    case 501:
        estadoerr="501: Para la notación científica esperaba dígito o +|-.";
        break;
    case 502:
        estadoerr="502: Para la notación científica esperaba dígito.";
        break;
    case 503:
        estadoerr="503: Operador AND icompleto.";
        break;
    case 504:
        estadoerr="504: Operador OR incompleto.";
        break;
    case 505:
        estadoerr="505: Constante caracter vacía.";
        break;
    case 506:
        estadoerr="506: Elemento no esperado/no reconocido.";
        break;
    case 507:
        estadoerr="507: Comilla terminal faltante.";
        break;
    default:
        break;
    }
    return estadoerr;
}

// Función: Estado terminal de aceptación
QString VentanaPrincipal::estadoToken(int e){
    QString estadoac="";
    //
    switch(e){
    case 100:
        estadoac="100: PALABRA RESERVADA.";
        break;
    case 101:
        estadoac="101: IDENTIFICADOR.";
        break;
    case 102:
        estadoac="102: NÚMERO ENTERO.";
        break;
    case 103:
        estadoac="103: NÚMERO REAL.";
        break;
    case 104:
        estadoac="104: NÚMERO CON NOTACIÓN CIENTÍFICA.";
        break;
    case 105:
        estadoac="105: SIGNO SUMA.";
        break;
    case 106:
        estadoac="106: SIGNO RESTA.";
        break;
    case 107:
        estadoac="107: SIGNO MULTIPLICACIÓN.";
        break;
    case 108:
        estadoac="108: SIGNO DIVISIÓN.";
        break;
    case 109:
        estadoac="109: ASIGNACIÓN.";
        break;
    case 110:
        estadoac="110: IGUAL.";
        break;
    case 111:
        estadoac="111: MENOR.";
        break;
    case 112:
        estadoac="112: MENOR O IGUAL.";
        break;
    case 113:
        estadoac="113: MAYOR.";
        break;
    case 114:
        estadoac="114: MAYOR O IGUAL.";
        break;
    case 115:
        estadoac="115: DIFERENTE.";
        break;
    case 116:
        estadoac="116: NOT.";
        break;
    case 117:
        estadoac="117: AND.";
        break;
    case 118:
        estadoac="118: OR.";
        break;
    case 119:
        estadoac="119: PARÉNTESIS QUE ABRE.";
        break;
    case 120:
        estadoac="120: PARÉNTESIS QUE CIERRA.";
        break;
    case 121:
        estadoac="121: CORCHETE QUE ABRE.";
        break;
    case 122:
        estadoac="122: CORCHETE QUE CIERRA.";
        break;
    case 123:
        estadoac="123: PUNTO Y COMA.";
        break;
    case 124:
        estadoac="124: COMA.";
        break;
    case 125:
        estadoac="125: CONSTANTE CARACTER.";
        break;
    case 126:
        estadoac="126: CONSTANTE STRING.";
        break;
    case 127:
        estadoac="127: COMENTARIO DE LÍNEA.";
        break;
    case 128:
        estadoac="128: INCREMENTO UNARIO.";
        break;
    case 129:
        estadoac="129: SUMA Y ASIGNA.";
        break;
    case 130:
        estadoac="130: RESTA UNARIA.";
        break;
    case 131:
        estadoac="131: RESTA Y ASIGNA.";
        break;
    case 132:
        estadoac="132: LLAVE QUE CIERRA.";
        break;
    case 133:
        estadoac="133: LLAVE QUE ABRE.";
        break;
    case 134:
        estadoac="134: MÓDULO.";
        break;
    case 135:
        estadoac="135: DOS PUNTOS.";
        break;
    default:
        break;
    }

    return estadoac;
}

//Funciones/Métodos para análisis sintáctico, semántico y generación de código--------------------------------------------------------------------

//Función: RELLENAR
void VentanaPrincipal::Rellenar(int direccion, int valor, QVector<QVector<QString>>& matriz){
    //
    QString valorstr=QString::number(valor);
    int dir=direccion-1;
    int col=4;
    //
    if(dir>=0 && dir<matriz.size()){
        matriz[dir].insert(col,valorstr);
    }else{
        cout << ">ERROR: La direccion de la fila a rellenar NO es valida." << endl;
    }
}

//Función: Verificar si el identificador leído durante la declaración de variables ya fue declarado anteriormente.
bool VentanaPrincipal::idYaDeclarado(QString newid){
    //
    stack<QString> pilaTemp = pilaSimbolos2;

    //
    while(!pilaTemp.empty()){
        if(pilaTemp.top().compare(newid)==0){
            return true;
        }
        pilaTemp.pop();
    }

    return false;
}

//Función: Obtener el elemento del top-1 de una pila de enteros.
int VentanaPrincipal::topMenosUnoInt(std::stack<int>& pilaint){
    //
    int elemento;
    //
    if(pilaint.size()>=2){
        stack<int> pilaTemp=pilaint;
        pilaTemp.pop();
        elemento=pilaTemp.top();
    }else{
        //Valor que representa error
        elemento=-1;
    }
    //
    return elemento;
}

//Función: Obtener el elemento del top-1 de una pila de strings.
QString VentanaPrincipal::topMenosUnoStr(std::stack<QString>& pilastr){
    //
    QString elemento;
    //
    if(pilastr.size()>=2){
        stack<QString> pilaTemp=pilastr;
        pilaTemp.pop();
        elemento=pilaTemp.top();
    }else{
        elemento="ERROR, pila con elementos insuficientes.";
    }
    //
    return elemento;
}

//Función: Obtener el tipo de un indentificador/variable de 'pilaSimbolos'.
QString VentanaPrincipal::obtenerTipoId(QString id){
    //Variables
    int posicion=-1;
    int indice=0;
    QString resultado;

    //
    stack<QString> pilaTemp=pilaSimbolos2;
    //Iterar sobre copia de 'pilaSimbolos2' para encontrar la posición del id...
    while(!pilaTemp.empty()){
        if(pilaTemp.top()==id){
            posicion = indice;
            break;
        }
        pilaTemp.pop();
        indice++;
    }

    //Condicionales
    if(posicion!=-1){
        //
        stack<QString> pilaTemp2=pilaSimbolos;
        int contador=0;
        //Obtener el tipo en la posición encontrada previamente...
        while(!pilaTemp2.empty() && contador<posicion){
            pilaTemp2.pop();
            contador++;
        }
        //
        if(contador==posicion){
            resultado=pilaTemp2.top();
        }else{
            cout << "No se encontró la posición específica." << endl;
        }
    }else{
        resultado="ERROR, id no declarado.";
    }

    //
    return resultado;
}

//Función: Verificar si operando #1 y operando #2 son tipos permitidos en una operación determinada.
QString VentanaPrincipal::verifTiposOps(QString op1, QString op2, QString operador){
    QString tipores;
    int fila;
    int columna;
    //Matriz de comprobación de tipos en operaciones
    string matriz_tipos[15][5]={
        {"int","float","int","bool","X"},
        {"float","float","float","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"float","float","float","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","bool"},
        {"X","X","X","bool","X"},
        {"X","X","X","bool","X"}
    };

    //Obtener fila
    if((op1.compare("int")==0) && (op2.compare("int")==0)){
        fila=0;
    }else if((op1.compare("int")==0 && op2.compare("float")==0) || (op1.compare("float")==0 && op2.compare("int")==0)){
        fila=1;
    }else if((op1.compare("int")==0 && op2.compare("char")==0) || (op1.compare("char")==0 && op2.compare("int")==0)){
        fila=2;
    }else if((op1.compare("int")==0 && op2.compare("bool")==0) || (op1.compare("bool")==0 && op2.compare("int")==0)){
        fila=3;
    }else if((op1.compare("int")==0 && op2.compare("string")==0) || (op1.compare("string")==0 && op2.compare("int")==0)){
        fila=4;
    }else if((op1.compare("float")==0) && (op2.compare("float")==0)){
        fila=5;
    }else if((op1.compare("float")==0 && op2.compare("char")==0) || (op1.compare("char")==0 && op2.compare("float")==0)){
        fila=6;
    }else if((op1.compare("float")==0 && op2.compare("bool")==0) || (op1.compare("bool")==0 && op2.compare("float")==0)){
        fila=7;
    }else if((op1.compare("float")==0 && op2.compare("string")==0) || (op1.compare("string")==0 && op2.compare("float")==0)){
        fila=8;
    }else if((op1.compare("char")==0) && (op2.compare("char")==0)){
        fila=9;
    }else if((op1.compare("char")==0 && op2.compare("bool")==0) || (op1.compare("bool")==0 && op2.compare("char")==0)){
        fila=10;
    }else if((op1.compare("char")==0 && op2.compare("string")==0) || (op1.compare("string")==0 && op2.compare("char")==0)){
        fila=11;
    }else if((op1.compare("bool")==0) && (op2.compare("bool")==0)){
        fila=12;
    }else if((op1.compare("bool")==0 && op2.compare("string")==0) || (op1.compare("string")==0 && op2.compare("bool")==0)){
        fila=13;
    }else if((op1.compare("string")==0) && (op2.compare("string")==0)){
        fila=14;
    }

    //Obtener columna
    if((operador.compare("+")==0) || (operador.compare("-")==0) || (operador.compare("*")==0)){
        columna=0;
    }else if(operador.compare("/")==0){
        columna=1;
    }else if(operador.compare("%")==0){
        columna=2;
    }else if(operador.compare("==")==0){
        columna=3;
    }else if((operador.compare("&&")==0) || (operador.compare("||")==0)){
        columna=4;
    }

    tipores=QString::fromStdString(matriz_tipos[fila][columna]);

    return tipores;
}

//Función: Convertir valor numérico de pila de ejec. a token o prod.
QString VentanaPrincipal::xToString(int x){
    QString cadenax="";

    switch(x){
    case 100:
        cadenax="PROGRAM";
        break;
    case 101:
        cadenax="A";
        break;
    case 102:
        cadenax="B";
        break;
    case 103:
        cadenax="TIPO";
        break;
    case 104:
        cadenax="OPREL";
        break;
    case 105:
        cadenax="EC";
        break;
    case 106:
        cadenax="ES";
        break;
    case 107:
        cadenax="E";
        break;
    case 108:
        cadenax="E'";
        break;
    case 109:
        cadenax="PRINCIPAL";
        break;
    case 110:
        cadenax="DIM";
        break;
    case 111:
        cadenax="C";
        break;
    case 112:
        cadenax="C'";
        break;
    case 113:
        cadenax="IDDIM";
        break;
    case 114:
        cadenax="D";
        break;
    case 115:
        cadenax="DECLARA";
        break;
    case 116:
        cadenax="F";
        break;
    case 117:
        cadenax="F'";
        break;
    case 118:
        cadenax="ESTWHILE";
        break;
    case 119:
        cadenax="ESTLOOP";
        break;
    case 120:
        cadenax="ASIG";
        break;
    case 121:
        cadenax="G";
        break;
    case 122:
        cadenax="ESTREAD";
        break;
    case 123:
        cadenax="H";
        break;
    case 124:
        cadenax="H'";
        break;
    case 125:
        cadenax="ESTFOR";
        break;
    case 126:
        cadenax="ESTDO";
        break;
    case 127:
        cadenax="DIMASIG";
        break;
    case 128:
        cadenax="ESTASIG";
        break;
    case 129:
        cadenax="ESTIF";
        break;
    case 130:
        cadenax="J";
        break;
    case 131:
        cadenax="K";
        break;
    case 132:
        cadenax="ESTWRITE";
        break;
    case 133:
        cadenax="I";
        break;
    case 134:
        cadenax="I'";
        break;
    case 135:
        cadenax="TERM";
        break;
    case 136:
        cadenax="TERM'";
        break;
    case 137:
        cadenax="FACT";
        break;
    case 138:
        cadenax="EXPR";
        break;
    case 139:
        cadenax="EXPR'";
        break;
    case 140:
        cadenax="EXPR2";
        break;
    case 141:
        cadenax="EXPR2'";
        break;
    case 142:
        cadenax="EXPR3";
        break;
    case 143:
        cadenax="L";
        break;
    case 144:
        cadenax="EXPR4";
        break;
    case 145:
        cadenax="M";
        break;
    case 146:
        cadenax="EXPR5";
        break;
    case 147:
        cadenax="EXPR5'";
        break;
    case 1000:
        cadenax="lib";
        break;
    case 1001:
        cadenax="id";
        break;
    case 1002:
        cadenax=";";
        break;
    case 1003:
        cadenax="class";
        break;
    case 1004:
        cadenax="{";
        break;
    case 1005:
        cadenax="}";
        break;
    case 1006:
        cadenax="int";
        break;
    case 1007:
        cadenax="float";
        break;
    case 1008:
        cadenax="char";
        break;
    case 1009:
        cadenax="bool";
        break;
    case 1010:
        cadenax="string";
        break;
    case 1011:
        cadenax="break";
        break;
    case 1012:
        cadenax="def";
        break;
    case 1013:
        cadenax=",";
        break;
    case 1014:
        cadenax="of";
        break;
    case 1015:
        cadenax="[";
        break;
    case 1016:
        cadenax="]";
        break;
    case 1017:
        cadenax="main";
        break;
    case 1018:
        cadenax="(";
        break;
    case 1019:
        cadenax=")";
        break;
    case 1020:
        cadenax="input";
        break;
    case 1021:
        cadenax="output";
        break;
    case 1022:
        cadenax="while";
        break;
    case 1023:
        cadenax=":";
        break;
    case 1024:
        cadenax="for";
        break;
    case 1025:
        cadenax="=";
        break;
    case 1026:
        cadenax="to";
        break;
    case 1027:
        cadenax="loop";
        break;
    case 1028:
        cadenax="do";
        break;
    case 1029:
        cadenax="eval";
        break;
    case 1030:
        cadenax="if";
        break;
    case 1031:
        cadenax="elseif";
        break;
    case 1032:
        cadenax="else";
        break;
    case 1033:
        cadenax="||";
        break;
    case 1034:
        cadenax="&&";
        break;
    case 1035:
        cadenax="==";
        break;
    case 1036:
        cadenax="!=";
        break;
    case 1037:
        cadenax="<";
        break;
    case 1038:
        cadenax="<=";
        break;
    case 1039:
        cadenax=">";
        break;
    case 1040:
        cadenax=">=";
        break;
    case 1041:
        cadenax="!";
        break;
    case 1042:
        cadenax="+";
        break;
    case 1043:
        cadenax="-";
        break;
    case 1044:
        cadenax="*";
        break;
    case 1045:
        cadenax="/";
        break;
    case 1046:
        cadenax="%";
        break;
    case 1047:
        cadenax="cteentera";
        break;
    case 1048:
        cadenax="ctereal";
        break;
    case 1049:
        cadenax="ctenotacion";
        break;
    case 1050:
        cadenax="ctecaracter";
        break;
    case 1051:
        cadenax="ctestring";
        break;
    case 2000:
        cadenax="$";
        break;
    default:
        break;
    }

    return cadenax;
}

// Función: Relacionar terminal con columna de matriz------------
int VentanaPrincipal::columnaTerminal(int e){
    int numeroColumna=0;

    switch(e){
    case 1000:
        numeroColumna=0;
        break;
    case 1001:
        numeroColumna=1;
        break;
    case 1002:
        numeroColumna=2;
        break;
    case 1003:
        numeroColumna=3;
        break;
    case 1004:
        numeroColumna=4;
        break;
    case 1005:
        numeroColumna=5;
        break;
    case 1006:
        numeroColumna=6;
        break;
    case 1007:
        numeroColumna=7;
        break;
    case 1008:
        numeroColumna=8;
        break;
    case 1009:
        numeroColumna=9;
        break;
    case 1010:
        numeroColumna=10;
        break;
    case 1011:
        numeroColumna=11;
        break;
    case 1012:
        numeroColumna=12;
        break;
    case 1013:
        numeroColumna=13;
        break;
    case 1014:
        numeroColumna=14;
        break;
    case 1015:
        numeroColumna=15;
        break;
    case 1016:
        numeroColumna=16;
        break;
    case 1017:
        numeroColumna=17;
        break;
    case 1018:
        numeroColumna=18;
        break;
    case 1019:
        numeroColumna=19;
        break;
    case 1020:
        numeroColumna=20;
        break;
    case 1021:
        numeroColumna=21;
        break;
    case 1022:
        numeroColumna=22;
        break;
    case 1023:
        numeroColumna=23;
        break;
    case 1024:
        numeroColumna=24;
        break;
    case 1025:
        numeroColumna=25;
        break;
    case 1026:
        numeroColumna=26;
        break;
    case 1027:
        numeroColumna=27;
        break;
    case 1028:
        numeroColumna=28;
        break;
    case 1029:
        numeroColumna=29;
        break;
    case 1030:
        numeroColumna=30;
        break;
    case 1031:
        numeroColumna=31;
        break;
    case 1032:
        numeroColumna=32;
        break;
    case 1033:
        numeroColumna=33;
        break;
    case 1034:
        numeroColumna=34;
        break;
    case 1035:
        numeroColumna=35;
        break;
    case 1036:
        numeroColumna=36;
        break;
    case 1037:
        numeroColumna=37;
        break;
    case 1038:
        numeroColumna=38;
        break;
    case 1039:
        numeroColumna=39;
        break;
    case 1040:
        numeroColumna=40;
        break;
    case 1041:
        numeroColumna=41;
        break;
    case 1042:
        numeroColumna=42;
        break;
    case 1043:
        numeroColumna=43;
        break;
    case 1044:
        numeroColumna=44;
        break;
    case 1045:
        numeroColumna=45;
        break;
    case 1046:
        numeroColumna=46;
        break;
    case 1047:
        numeroColumna=47;
        break;
    case 1048:
        numeroColumna=48;
        break;
    case 1049:
        numeroColumna=49;
        break;
    case 1050:
        numeroColumna=50;
        break;
    case 1051:
        numeroColumna=51;
        break;
    case 2000:
        numeroColumna=52;
        break;
    default:
        break;
    }

    return numeroColumna;
}

// Función: Relacionar no-terminal con fila de matriz------------
int VentanaPrincipal::filaNoTerminal(int e){
    int numeroFila=0;

    switch(e){
    case 100:
        numeroFila=0;
        break;
    case 101:
        numeroFila=1;
        break;
    case 102:
        numeroFila=2;
        break;
    case 103:
        numeroFila=3;
        break;
    case 104:
        numeroFila=4;
        break;
    case 105:
        numeroFila=5;
        break;
    case 106:
        numeroFila=6;
        break;
    case 107:
        numeroFila=7;
        break;
    case 108:
        numeroFila=8;
        break;
    case 109:
        numeroFila=9;
        break;
    case 110:
        numeroFila=10;
        break;
    case 111:
        numeroFila=11;
        break;
    case 112:
        numeroFila=12;
        break;
    case 113:
        numeroFila=13;
        break;
    case 114:
        numeroFila=14;
        break;
    case 115:
        numeroFila=15;
        break;
    case 116:
        numeroFila=16;
        break;
    case 117:
        numeroFila=17;
        break;
    case 118:
        numeroFila=18;
        break;
    case 119:
        numeroFila=19;
        break;
    case 120:
        numeroFila=20;
        break;
    case 121:
        numeroFila=21;
        break;
    case 122:
        numeroFila=22;
        break;
    case 123:
        numeroFila=23;
        break;
    case 124:
        numeroFila=24;
        break;
    case 125:
        numeroFila=25;
        break;
    case 126:
        numeroFila=26;
        break;
    case 127:
        numeroFila=27;
        break;
    case 128:
        numeroFila=28;
        break;
    case 129:
        numeroFila=29;
        break;
    case 130:
        numeroFila=30;
        break;
    case 131:
        numeroFila=31;
        break;
    case 132:
        numeroFila=32;
        break;
    case 133:
        numeroFila=33;
        break;
    case 134:
        numeroFila=34;
        break;
    case 135:
        numeroFila=35;
        break;
    case 136:
        numeroFila=36;
        break;
    case 137:
        numeroFila=37;
        break;
    case 138:
        numeroFila=38;
        break;
    case 139:
        numeroFila=39;
        break;
    case 140:
        numeroFila=40;
        break;
    case 141:
        numeroFila=41;
        break;
    case 142:
        numeroFila=42;
        break;
    case 143:
        numeroFila=43;
        break;
    case 144:
        numeroFila=44;
        break;
    case 145:
        numeroFila=45;
        break;
    case 146:
        numeroFila=46;
        break;
    case 147:
        numeroFila=47;
        break;
    default:
        break;
    }

    return numeroFila;
}

// Función: Insertar derivación de producción en la pila (si no deriva a Ɛ)------------
void VentanaPrincipal::insertarDerivacion(int prod){
    switch (prod) {
    case 1:
        pilaX.push(102);
        pilaX.push(101);
        break;
    case 2:
        pilaX.push(101);
        pilaX.push(1002);
        pilaX.push(1001);
        pilaX.push(1000);
        break;
    case 4:
        pilaX.push(1005);
        pilaX.push(109);
        pilaX.push(115);
        pilaX.push(1004);
        pilaX.push(1001);
        pilaX.push(1003);
        break;
    case 6:
        pilaX.push(115);
        pilaX.push(103);
        pilaX.push(1014);
        pilaX.push(116);
        pilaX.push(1012);
        break;
    case 7:
        pilaX.push(117);
        pilaX.push(113);
        break;
    case 8:
        pilaX.push(116);
        pilaX.push(1013);
        break;
    case 10:
        pilaX.push(114);
        pilaX.push(1001);
        break;
    case 12:
        pilaX.push(110);
        break;
    case 13:
        pilaX.push(1016);
        pilaX.push(111);
        pilaX.push(1015);
        break;
    case 14:
        pilaX.push(112);
        pilaX.push(1047);
        break;
    case 15:
        pilaX.push(111);
        pilaX.push(1013);
        break;
    case 17:
        pilaX.push(1006);
        break;
    case 18:
        pilaX.push(1007);
        break;
    case 19:
        pilaX.push(1008);
        break;
    case 20:
        pilaX.push(1009);
        break;
    case 21:
        pilaX.push(1010);
        break;
    case 22:
        pilaX.push(1005);
        pilaX.push(107);
        pilaX.push(1004);
        pilaX.push(1019);
        pilaX.push(1018);
        pilaX.push(1017);
        break;
    case 23:
        pilaX.push(108);
        pilaX.push(106);
        break;
    case 24:
        pilaX.push(108);
        pilaX.push(105);
        break;
    case 25:
        pilaX.push(107);
        break;
    case 27:
        pilaX.push(1005);
        pilaX.push(107);
        pilaX.push(1004);
        break;
    case 28:
        pilaX.push(1002);
        pilaX.push(128);
        break;
    case 29:
        pilaX.push(1002);
        pilaX.push(129);
        break;
    case 30:
        pilaX.push(1002);
        pilaX.push(118);
        break;
    case 31:
        pilaX.push(1002);
        pilaX.push(126);
        break;
    case 32:
        pilaX.push(1002);
        pilaX.push(122);
        break;
    case 33:
        pilaX.push(1002);
        pilaX.push(132);
        break;
    case 34:
        pilaX.push(1002);
        pilaX.push(119);
        break;
    case 35:
        pilaX.push(1002);
        pilaX.push(125);
        break;
    case 36:
        pilaX.push(1002);
        pilaX.push(1011);
        break;
    case 38:
        pilaX.push(138);
        pilaX.push(1025);
        pilaX.push(120);
        break;
    case 39:
        pilaX.push(121);
        pilaX.push(1001);
        break;
    case 41:
        pilaX.push(127);
        break;
    case 42:
        pilaX.push(1016);
        pilaX.push(133);
        pilaX.push(1015);
        break;
    case 43:
        pilaX.push(1019);
        pilaX.push(123);
        pilaX.push(1018);
        pilaX.push(1020);
        break;
    case 44:
        pilaX.push(124);
        pilaX.push(1001);
        break;
    case 45:
        pilaX.push(123);
        pilaX.push(1013);
        break;
    case 47:
        pilaX.push(1019);
        pilaX.push(133);
        pilaX.push(1018);
        pilaX.push(1021);
        break;
    case 48:
        pilaX.push(134);
        pilaX.push(138);
        break;
    case 49:
        pilaX.push(133);
        pilaX.push(1013);
        break;
    case 51:
        pilaX.push(107);
        pilaX.push(1023);
        pilaX.push(138);
        pilaX.push(1022);
        break;
    case 52:
        pilaX.push(107);
        pilaX.push(1023);
        pilaX.push(138);
        pilaX.push(1026);
        pilaX.push(138);
        pilaX.push(1025);
        pilaX.push(1001);
        pilaX.push(1024);
        break;
    case 53:
        pilaX.push(107);
        pilaX.push(1027);
        break;
    case 54:
        pilaX.push(1019);
        pilaX.push(138);
        pilaX.push(1018);
        pilaX.push(1029);
        pilaX.push(107);
        pilaX.push(1028);
        break;
    case 55:
        pilaX.push(131);
        pilaX.push(130);
        pilaX.push(107);
        pilaX.push(1023);
        pilaX.push(138);
        pilaX.push(1030);
        break;
    case 56:
        pilaX.push(130);
        pilaX.push(107);
        pilaX.push(1023);
        pilaX.push(138);
        pilaX.push(1031);
        break;
    case 58:
        pilaX.push(107);
        pilaX.push(1023);
        pilaX.push(1032);
        break;
    case 60:
        pilaX.push(1035);
        break;
    case 61:
        pilaX.push(1036);
        break;
    case 62:
        pilaX.push(1037);
        break;
    case 63:
        pilaX.push(1038);
        break;
    case 64:
        pilaX.push(1039);
        break;
    case 65:
        pilaX.push(1040);
        break;
    case 66:
        pilaX.push(139);
        pilaX.push(140);
        break;
    case 67:
        pilaX.push(138);
        pilaX.push(1033);
        break;
    case 69:
        pilaX.push(141);
        pilaX.push(142);
        break;
    case 70:
        pilaX.push(140);
        pilaX.push(1034);
        break;
    case 72:
        pilaX.push(144);
        pilaX.push(143);
        break;
    case 74:
        pilaX.push(1041);
        break;
    case 75:
        pilaX.push(145);
        pilaX.push(146);
        break;
    case 76:
        pilaX.push(146);
        pilaX.push(104);
        break;
    case 78:
        pilaX.push(147);
        pilaX.push(135);
        break;
    case 79:
        pilaX.push(146);
        pilaX.push(1042);
        break;
    case 80:
        pilaX.push(146);
        pilaX.push(1043);
        break;
    case 82:
        pilaX.push(136);
        pilaX.push(137);
        break;
    case 83:
        pilaX.push(135);
        pilaX.push(1044);
        break;
    case 84:
        pilaX.push(135);
        pilaX.push(1045);
        break;
    case 85:
        pilaX.push(135);
        pilaX.push(1046);
        break;
    case 87:
        pilaX.push(120);
        break;
    case 88:
        pilaX.push(1047);
        break;
    case 89:
        pilaX.push(1048);
        break;
    case 90:
        pilaX.push(1049);
        break;
    case 91:
        pilaX.push(1050);
        break;
    case 92:
        pilaX.push(1051);
        break;
    case 93:
        pilaX.push(1019);
        pilaX.push(138);
        pilaX.push(1018);
        break;
    default:
        break;
    }
}

// Función: Relacionar token------------
int VentanaPrincipal::relacionarT(QString t){
    int numeroToken=0;

    if(t=="lib"){
        numeroToken=1000;
    }else if(t==";"){
        numeroToken=1002;
    }else if(t=="class"){
        numeroToken=1003;
    }else if(t=="{"){
        numeroToken=1004;
    }else if(t=="}"){
        numeroToken=1005;
    }else if(t=="int"){
        numeroToken=1006;
    }else if(t=="float"){
        numeroToken=1007;
    }else if(t=="char"){
        numeroToken=1008;
    }else if(t=="bool"){
        numeroToken=1009;
    }else if(t=="string"){
        numeroToken=1010;
    }else if(t=="break"){
        numeroToken=1011;
    }else if(t=="def"){
        numeroToken=1012;
    }else if(t==","){
        numeroToken=1013;
    }else if(t=="of"){
        numeroToken=1014;
    }else if(t=="["){
        numeroToken=1015;
    }else if(t=="]"){
        numeroToken=1016;
    }else if(t=="main"){
        numeroToken=1017;
    }else if(t=="("){
        numeroToken=1018;
    }else if(t==")"){
        numeroToken=1019;
    }else if(t=="input"){
        numeroToken=1020;
    }else if(t=="output"){
        numeroToken=1021;
    }else if(t=="while"){
        numeroToken=1022;
    }else if(t==":"){
        numeroToken=1023;
    }else if(t=="for"){
        numeroToken=1024;
    }else if(t=="="){
        numeroToken=1025;
    }else if(t=="to"){
        numeroToken=1026;
    }else if(t=="loop"){
        numeroToken=1027;
    }else if(t=="do"){
        numeroToken=1028;
    }else if(t=="eval"){
        numeroToken=1029;
    }else if(t=="if"){
        numeroToken=1030;
    }else if(t=="elseif"){
        numeroToken=1031;
    }else if(t=="else"){
        numeroToken=1032;
    }else if(t=="||"){
        numeroToken=1033;
    }else if(t=="&&"){
        numeroToken=1034;
    }else if(t=="=="){
        numeroToken=1035;
    }else if(t=="!="){
        numeroToken=1036;
    }else if(t=="<"){
        numeroToken=1037;
    }else if(t=="<="){
        numeroToken=1038;
    }else if(t==">"){
        numeroToken=1039;
    }else if(t==">="){
        numeroToken=1040;
    }else if(t=="!"){
        numeroToken=1041;
    }else if(t=="+"){
        numeroToken=1042;
    }else if(t=="-"){
        numeroToken=1043;
    }else if(t=="*"){
        numeroToken=1044;
    }else if(t=="/"){
        numeroToken=1045;
    }else if(t=="%"){
        numeroToken=1046;
    }else if(t=="$"){
        numeroToken=2000;
    }else{
        /*
         * Si el string es diferente a todos los anteriores(es una constante/identificador, no es un token "fijo"), buscar en matriz 'token,identificacion'
         * el token igual al del argumento y obtener su "identificacion" en la segunda columna en la misma fila.
         *
        */
        //Variables
        int columnaABuscar=0;
        QString edoTkn;

        //Ciclo de busqueda
        for(int fila=0;fila<matriz_tokenid.size();fila++){
            if(matriz_tokenid[fila][columnaABuscar]==t){
                edoTkn=matriz_tokenid[fila][1];
                break;
            }
        }

        //
        if(edoTkn=="102: NÚMERO ENTERO."){
            numeroToken=1047;
        }else if(edoTkn=="103: NÚMERO REAL."){
            numeroToken=1048;
        }else if(edoTkn=="104: NÚMERO CON NOTACIÓN CIENTÍFICA."){
            numeroToken=1049;
        }else if(edoTkn=="125: CONSTANTE CARACTER."){
            numeroToken=1050;
        }else if(edoTkn=="126: CONSTANTE STRING."){
            numeroToken=1051;
        }else if(edoTkn=="101: IDENTIFICADOR."){
            numeroToken=1001;
        }
    }

    return numeroToken;

}

// Función: Analizar sintaxis
void VentanaPrincipal::AnalizarSintax(){
    // Matriz predictiva
    int matrizPredictiva[48][53]={
        {1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
        {2,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,17,18,19,20,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,60,61,62,63,64,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,28,37,-1,37,37,-1,-1,-1,-1,-1,36,-1,-1,-1,-1,-1,-1,-1,-1,32,33,30,-1,35,-1,-1,34,31,37,29,37,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,23,23,-1,24,23,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,23,23,23,-1,23,-1,-1,23,23,23,23,23,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,25,26,-1,25,26,-1,-1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,25,25,25,-1,25,-1,-1,25,25,26,25,26,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,-1,-1,-1,-1,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,41,40,-1,-1,40,-1,-1,-1,40,-1,40,40,-1,-1,-1,-1,-1,-1,40,40,40,40,40,40,40,40,-1,40,40,40,40,40,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,42,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,59,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,48,48,48,48,48,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,50,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,82,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,82,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,82,82,82,82,82,-1},
        {-1,-1,86,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,-1,-1,86,-1,-1,86,-1,-1,-1,86,-1,-1,86,-1,-1,-1,-1,-1,-1,86,86,86,86,86,86,86,86,-1,86,86,83,84,85,-1,-1,-1,-1,-1,-1},
        {-1,87,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,93,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,88,89,90,91,92,-1},
        {-1,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,-1,-1,-1,-1,-1,66,66,66,66,66,-1},
        {-1,-1,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,68,-1,-1,68,-1,-1,68,-1,-1,-1,68,-1,-1,68,-1,-1,-1,-1,-1,-1,67,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,69,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,69,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,69,-1,-1,-1,-1,-1,69,69,69,69,69,-1},
        {-1,-1,71,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71,-1,-1,71,-1,-1,71,-1,-1,-1,71,-1,-1,71,-1,-1,-1,-1,-1,-1,71,70,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,72,72,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,72,-1,-1,72,-1,72,72,-1,-1,-1,72,-1,-1,72,-1,-1,-1,-1,-1,-1,72,72,-1,-1,-1,-1,-1,-1,72,-1,-1,-1,-1,-1,72,72,72,72,72,-1},
        {-1,73,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,73,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74,-1,-1,-1,-1,-1,73,73,73,73,73,-1},
        {-1,75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,75,75,75,75,-1},
        {-1,-1,77,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,77,-1,-1,77,-1,-1,77,-1,-1,-1,77,-1,-1,77,-1,-1,-1,-1,-1,-1,77,77,76,76,76,76,76,76,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,78,78,78,78,-1},
        {-1,-1,81,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,81,-1,-1,81,-1,-1,81,-1,-1,-1,81,-1,-1,81,-1,-1,-1,-1,-1,-1,81,81,81,81,81,81,81,81,-1,79,80,-1,-1,-1,-1,-1,-1,-1,-1,-1}
    };

    // Vaciar pila "de ejecución" e insertar $ y primer no-terminal de producciones
    while (!pilaX.empty()) {
        pilaX.pop();
    }
    pilaX.push(2000);
    pilaX.push(100);

    //Vaciar contenido de otras pilas
    while (!pilaSimbolos.empty()) {
        pilaSimbolos.pop();
    }
    while (!pilaSimbolos2.empty()) {
        pilaSimbolos2.pop();
    }
    while (!pila_tipos.empty()) {
        pila_tipos.pop();
    }
    while (!pila_operadores.empty()) {
        pila_operadores.pop();
    }
    while (!copila_tipos.empty()) {
        copila_tipos.pop();
    }
    while (!copila_operadores.empty()) {
        copila_operadores.pop();
    }

    // Variables para valores de X y nexttoken
    int valorX;
    QString valorX2;
    QString NT;
    QString LT;
    int valorNT2;

    // Iterador para recorrer filas de matriz de tokens
    QVector<QVector<QString>>::iterator iterador=matriz_tokenid.begin();
    // Bandera para verificar contenido de 'pilaX'
    bool bandContPila;

    // Contador de posición de variables/ids en declaración
    int contadorPosVar=1;
    // Bandera de nuevo token de entrada
    bool bandNuevaEntrada;

    // Banderas de estatutos
    bool bandDeclara;
    bool bandAsignacion=false;
    bool bandExpresion;
    bool bandDoEval;
    bool bandIf;
    bool bandFor;
    bool bandWhile;
    bool bandErrSemantAsig=false;
    bool bandErrSintac=false;

    // Estructuras y variables para generación de cuádruplos
    QVector<QVector<QString>> matriz_cuadruplos;
    QVector<QVector<QString>> matriz_estbandera;
    stack<QString> pila_operandos;
    stack<QString> pila_operadoresgc;
    stack<int> pila_saltos;
    stack<QString> copila_operandos;
    stack<QString> copila_operadoresgc;
    stack<int> copila_saltos;
    int cont_cuadruplo=1;
    int cont_nores=1;

    // Ciclo de ejecución
    do {
        // Valor de X (int)
        valorX=pilaX.top();
        // Valor de X (QString)
        valorX2.clear();
        valorX2=xToString(valorX);
        cout << "Valor actual de X: " << valorX2.toStdString() << endl;
        // Valor de nexttoken (QString)
        NT=(*iterador)[0];
        cout << "Valor actual de nexttoken: " << NT.toStdString() << endl;
        // Valor de nexttoken (int)
        valorNT2=relacionarT(NT);
        // Línea de token
        LT=(*iterador)[2];

        //CONSTRUCCIÓN DE TABLA DE SÍMBOLOS------------------------------------------------------------------------------------------------
        // Si se lee '{'...
        if((bandNuevaEntrada==true) && (valorNT2==1004)){
            // Obtener el token posterior al de la entrada
            ++iterador;
            QString ST=(*iterador)[0];
            int valorST2=relacionarT(ST);
            --iterador;
            // Si el token posterior es 'def', es el primer '{' del programa, y se supone que existe una declaración de variables...
            if(valorST2==1012){
                bandDeclara=true;
            }
            // Bandera de nueva entrada de token se pone en falso porque ya fue comprobado una vez.
            bandNuevaEntrada=false;
        }
        // Mientras bandDeclara==true...
        if((bandNuevaEntrada==true) && (bandDeclara==true)){
            // Obtener identificación de token (qué es)
            QString IdNT=(*iterador)[1];
            // Si se lee un identificador...
            if(IdNT.compare("101: IDENTIFICADOR.")==0){
                //
                bool verificar_newid=idYaDeclarado(NT);
                //
                if(verificar_newid==true){
                    QString msj_erroridyadec=">ERROR: El identificador '"+NT+"' ya había sido declarado anteriormente.";
                    ui->lW_MsjErrSemantic->addItem(msj_erroridyadec);
                }else{
                    // Almacenar dirección en la pila
                    QString dirvar="1,"+QString::number(contadorPosVar);
                    pilaSimbolos.push(dirvar);
                    // Almacenar identificador en 'pilaSimbolos2'
                    pilaSimbolos2.push(NT);
                    // Aumentar posición
                    contadorPosVar++;
                }
            }
            // Si se lee una palabra reservada (correspondiente a un tipo)...
            if((IdNT.compare("100: PALABRA RESERVADA.")==0) && (valorNT2>=1006 && valorNT2<=1010)){
                // Contador
                int contador_direcciones=0;
                // Remover elementos de la pila que contengan "1," (que son consecutivos), y reemplazarlos por el último token de tipo leído...
                while(pilaSimbolos.top().contains("1,")){
                    pilaSimbolos.pop();
                    contador_direcciones++;
                    // Si se remueven todos (ocurre con la primera línea de declaración)...
                    if(pilaSimbolos.empty()){
                        break;
                    }
                }
                // Introducir el último token de tipo leído en el número de posiciones de la pila que se removieron...
                for (int i = 0; i < contador_direcciones; ++i) {
                    pilaSimbolos.push(NT);
                }    
            }
            // Si se lee una palabra reservada (correspondiente a 'main')...
            if((IdNT.compare("100: PALABRA RESERVADA.")==0) && (valorNT2==1017)){
                bandDeclara=false;
            }
            //
            bandNuevaEntrada=false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------


        //RUTINAS DE ANÁLISIS SEMÁNTICO (y de generación de código intermedio para estatutos de asignación)--------------------------------
        // Establecer condicion a partir de la cual se está dentro de ESTASIG (si el valor del top de pilaX es <ESTASIG> y nexttoken es un id)...
        if((valorX==128) && (valorNT2==1001)){
            bandAsignacion=true;
            cout << "<BAND ASIG SE ESTABLECE EN TRUE>" << endl;
        }
        // Mientras bandAsignacion==true...
        if(bandAsignacion==true){
            // Si el valor del top de pilaX y nexttoken son ambos un id, una constante o paréntesis que cierra...
            if((valorX==1001 && valorNT2==1001) || (valorX==1047 && valorNT2==1047) || (valorX==1048 && valorNT2==1048) || (valorX==1049 && valorNT2==1049) || (valorX==1050 && valorNT2==1050) || (valorX==1051 && valorNT2==1051) || (valorX==1019 && valorNT2==1019)){
                //
                if(valorX==1001 && valorNT2==1001){
                    // Obtener tipo del identificador
                    QString tipoId=obtenerTipoId(NT);
                    //
                    if(tipoId.compare("ERROR, id no declarado.")==0){
                        QString msj_erroridnodec=">ERROR: El identificador '"+NT+"' no fue declarado. | Linea: "+LT;
                        ui->lW_MsjErrSemantic->addItem(msj_erroridnodec);
                        // ACCIÓN CORRECTIVA: Ingresar token de identificador a pila de símbolos con el tipo deseado (se propone 'int')
                        pilaSimbolos.push("int");
                        pilaSimbolos2.push(NT);
                        // Obtener tipo del identificador
                        QString tipoId2=obtenerTipoId(NT);
                        // Ingresar tipo obtenido a 'pila_tipos' y a su copia
                        pila_tipos.push(tipoId2);
                        copila_tipos.push(tipoId2);
                    }else{
                        // Ingresar tipo obtenido a 'pila_tipos' y a su copia
                        pila_tipos.push(tipoId);
                        copila_tipos.push(tipoId);
                    }

                    pila_operandos.push(NT);
                    copila_operandos.push(NT);
                }else if(valorX==1047 && valorNT2==1047){
                    //
                    pila_tipos.push("int");
                    copila_tipos.push("int");

                    pila_operandos.push(NT);
                    copila_operandos.push(NT);
                }else if((valorX==1048 && valorNT2==1048) || (valorX==1049 && valorNT2==1049)){
                    //
                    pila_tipos.push("float");
                    copila_tipos.push("float");

                    pila_operandos.push(NT);
                    copila_operandos.push(NT);
                }else if(valorX==1050 && valorNT2==1050){
                    //
                    pila_tipos.push("char");
                    copila_tipos.push("char");

                    pila_operandos.push(NT);
                    copila_operandos.push(NT);
                }else if(valorX==1051 && valorNT2==1051){
                    //
                    pila_tipos.push("string");
                    copila_tipos.push("string");

                    pila_operandos.push(NT);
                    copila_operandos.push(NT);
                }else if(valorX==1019 && valorNT2==1019){
                    if(pila_operadores.top().compare("MFF")==0){
                        //
                        pila_operadores.pop();
                    }
                    //
                    if(pila_operadoresgc.top().compare("MFF")==0){
                        //
                        pila_operadoresgc.pop();
                    }
                }

                // Obtener siguiente elemento
                ++iterador;
                QString ST=(*iterador)[0];
                int valorST2=relacionarT(ST);
                --iterador;

                if(valorST2==1025){// Si el token posterior es '='...

                }else{
                    // Obtener y verificar elemento del top de pila_operadores
                    QString top_pilaoperadores=pila_operadores.top();
                    if((top_pilaoperadores.compare("*")==0) || (top_pilaoperadores.compare("/")==0) || (top_pilaoperadores.compare("&&")==0) || (top_pilaoperadores.compare("%")==0)){
                        // Verificar tipos en operación
                        QString top_pilatipos=pila_tipos.top();
                        QString topmenosuno_pilatipos=topMenosUnoStr(pila_tipos);

                        QString tipo_resultop=verifTiposOps(topmenosuno_pilatipos,top_pilatipos,top_pilaoperadores);

                        // Condicionales según el tipo del resultado
                        if(tipo_resultop.compare("X")==0){
                            // MARCAR ERROR SEMÁNTICO Y APLICAR ACCIÓN CORRECTIVA
                            QString msj_errorsemantico=">ERROR: entre tipos ("+topmenosuno_pilatipos+top_pilaoperadores+top_pilatipos+"). | Linea: "+LT;
                            ui->lW_MsjErrSemantic->addItem(msj_errorsemantico);

                            pila_tipos.pop();
                            pila_tipos.pop();

                            // Se ingresa el tipo del posible resultado de la operación (se propone 'int')...
                            pila_tipos.push("int");
                            copila_tipos.push("int");

                            pila_operadores.pop();

                            //GEN CUÁDRUPLO
                            QString contstr=QString::number(cont_cuadruplo);
                            QString op2=pila_operandos.top();
                            pila_operandos.pop();
                            QString op1=pila_operandos.top();
                            pila_operandos.pop();
                            QString oper=pila_operadoresgc.top();
                            pila_operadoresgc.pop();
                            QString res="R"+QString::number(cont_nores);
                            pila_operandos.push(res);
                            copila_operandos.push(res);

                            QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                            matriz_cuadruplos.append(cuadruplo);

                            cont_cuadruplo++;
                            cont_nores++;
                        }else{
                            // "GENERAR OPERACIÓN"
                            pila_tipos.pop();
                            pila_tipos.pop();

                            // Se ingresa el tipo del resultado de la operación...
                            pila_tipos.push(tipo_resultop);
                            copila_tipos.push(tipo_resultop);

                            pila_operadores.pop();

                            //GEN CUÁDRUPLO
                            QString contstr=QString::number(cont_cuadruplo);
                            QString op2=pila_operandos.top();
                            pila_operandos.pop();
                            QString op1=pila_operandos.top();
                            pila_operandos.pop();
                            QString oper=pila_operadoresgc.top();
                            pila_operadoresgc.pop();
                            QString res="R"+QString::number(cont_nores);
                            pila_operandos.push(res);
                            copila_operandos.push(res);

                            QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                            matriz_cuadruplos.append(cuadruplo);

                            cont_cuadruplo++;
                            cont_nores++;
                        }
                    }
                    // Verificar si lo que sigue es '*','/','&&' o '%' para realizar siguiente acción...
                    if((valorST2==1044) || (valorST2==1045) || (valorST2==1034) || (valorST2==1046)){
                        //
                        pila_operadores.push(ST);
                        copila_operadores.push(ST);

                        pila_operadoresgc.push(ST);
                        copila_operadoresgc.push(ST);
                    }else{
                        // Obtener y verificar elemento del top de pila_operadores
                        QString top_pilaoperadores2=pila_operadores.top();
                        if((top_pilaoperadores2.compare("+")==0) || (top_pilaoperadores2.compare("-")==0) || (top_pilaoperadores2.compare("||")==0)){
                            // Verificar tipos en operación
                            QString top_pilatipos2=pila_tipos.top();
                            QString topmenosuno_pilatipos2=topMenosUnoStr(pila_tipos);

                            QString tipo_resultop2=verifTiposOps(topmenosuno_pilatipos2,top_pilatipos2,top_pilaoperadores2);

                            // Condicionales según el tipo del resultado
                            if(tipo_resultop2.compare("X")==0){
                                // MARCAR ERROR SEMÁNTICO Y APLICAR ACCIÓN CORRECTIVA
                                QString msj_errorsemantico2=">ERROR: entre tipos ("+topmenosuno_pilatipos2+top_pilaoperadores2+top_pilatipos2+"). | Linea: "+LT;
                                ui->lW_MsjErrSemantic->addItem(msj_errorsemantico2);

                                pila_tipos.pop();
                                pila_tipos.pop();

                                // Se ingresa el tipo del posible resultado de la operación (se propone 'int')...
                                pila_tipos.push("int");
                                copila_tipos.push("int");

                                pila_operadores.pop();

                                //GEN CUÁDRUPLO
                                QString contstr=QString::number(cont_cuadruplo);
                                QString op2=pila_operandos.top();
                                pila_operandos.pop();
                                QString op1=pila_operandos.top();
                                pila_operandos.pop();
                                QString oper=pila_operadoresgc.top();
                                pila_operadoresgc.pop();
                                QString res="R"+QString::number(cont_nores);
                                pila_operandos.push(res);
                                copila_operandos.push(res);

                                QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                                matriz_cuadruplos.append(cuadruplo);

                                cont_cuadruplo++;
                                cont_nores++;
                            }else{
                                // "GENERAR OPERACIÓN"
                                pila_tipos.pop();
                                pila_tipos.pop();

                                // Se ingresa el tipo del resultado de la operación...
                                pila_tipos.push(tipo_resultop2);
                                copila_tipos.push(tipo_resultop2);

                                pila_operadores.pop();

                                //GEN CUÁDRUPLO
                                QString contstr=QString::number(cont_cuadruplo);
                                QString op2=pila_operandos.top();
                                pila_operandos.pop();
                                QString op1=pila_operandos.top();
                                pila_operandos.pop();
                                QString oper=pila_operadoresgc.top();
                                pila_operadoresgc.pop();
                                QString res="R"+QString::number(cont_nores);
                                pila_operandos.push(res);
                                copila_operandos.push(res);

                                QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                                matriz_cuadruplos.append(cuadruplo);

                                cont_cuadruplo++;
                                cont_nores++;
                            }
                        }
                        // Verificar si lo que sigue es '+','-' o '||' para realizar siguiente acción...
                        if((valorST2==1042) || (valorST2==1043) || (valorST2==1033)){
                            //
                            pila_operadores.push(ST);
                            copila_operadores.push(ST);

                            pila_operadoresgc.push(ST);
                            copila_operadoresgc.push(ST);
                        }
                    }
                }
            }
            // Si el valor del top de pilaX y nexttoken son ambos '='...
            if((valorX==1025) && (valorNT2==1025)){
                //
                pila_operadores.push("=");
                copila_operadores.push("=");

                pila_operadoresgc.push("=");
                copila_operadoresgc.push("=");
            }
            // Si el valor del top de pilaX y nexttoken son ambos '('...
            if((valorX==1018) && (valorNT2==1018)){
                //
                pila_operadores.push("MFF");
                copila_operadores.push("MFF");

                pila_operadoresgc.push("MFF");
                copila_operadoresgc.push("MFF");
            }
            // Establecer condicion a partir de la cual se sale de ESTASIG (si el valor del top de pilaX es ';' y nexttoken es ';')...
            if((valorX==1002) && (valorNT2==1002)){
                bandAsignacion=false;
                cout << "<BAND ASIG SE ESTABLECE EN FALSE>" << endl;
                //
                if(pila_operadores.top().compare("=")==0){
                    //Obtener top y top-1 de pila_tipos y comprobar si son iguales
                    QString top_pilatipos=pila_tipos.top();
                    QString topmenosuno_pilatipos=topMenosUnoStr(pila_tipos);

                    if(top_pilatipos.compare(topmenosuno_pilatipos)==0){
                        // La operación es correcta...
                        pila_tipos.pop();
                        pila_tipos.pop();

                        pila_operadores.pop();

                        //GEN CUÁDRUPLO ASIGNACIÓN
                        QString contstr=QString::number(cont_cuadruplo);
                        QString res=pila_operandos.top();
                        pila_operandos.pop();
                        QString oper=pila_operadoresgc.top();
                        pila_operadoresgc.pop();
                        QString op1=pila_operandos.top();
                        pila_operandos.pop();

                        QVector<QString> cuadruploAsig = {contstr,oper,op1,"",res};
                        matriz_cuadruplos.append(cuadruploAsig);

                        cont_cuadruplo++;
                    }else{
                        // Marcar ERROR ENTRE TIPOS
                        QString msj_errorsemantico=">ERROR: entre tipos ("+topmenosuno_pilatipos+"≠"+top_pilatipos+"). | Linea: "+LT;
                        ui->lW_MsjErrSemantic->addItem(msj_errorsemantico);

                        pila_tipos.pop();
                        pila_tipos.pop();

                        pila_operadores.pop();

                        //
                        bandErrSemantAsig=true;
                    }
                }
                // IMPRIMIR PILAS DE ANÁLISIS SEMÁNTICO...
                QString strpila_tipos=copila_tipos.top();
                copila_tipos.pop();
                QString strpila_operadores=copila_operadores.top();
                copila_operadores.pop();
                //
                while(!copila_tipos.empty()){
                    strpila_tipos.prepend(copila_tipos.top()+" | ");
                    copila_tipos.pop();
                }
                while(!copila_operadores.empty()){
                    strpila_operadores.prepend(copila_operadores.top()+" | ");
                    copila_operadores.pop();
                }
                //
                strpila_tipos.prepend("P. TIPOS: | ");
                strpila_tipos.append(" |");
                ui->lW_ContPilasSemantic->addItem(strpila_tipos);
                strpila_operadores.prepend("P. OPERADORES: | ");
                strpila_operadores.append(" |");
                ui->lW_ContPilasSemantic->addItem(strpila_operadores);
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------

        //GENERACIÓN DE CUÁDRUPLOS PARA ESTATUTOS------------------------------------------------------------------------------------------
        // Establecer condicion a partir de la cual se está dentro de EXPR (si el valor del top de pilaX es <EXPR> y nexttoken es un id o una constante numérica)...
        if((valorX==138) && (valorNT2==1001 || valorNT2==1047 || valorNT2==1048 || valorNT2==1049) && (bandAsignacion==false)){
            bandExpresion=true;
            cout << "<BAND EXPR SE ESTABLECE EN TRUE>" << endl;
        }
        if(bandExpresion==true){
            // Si el valor del top de pilaX y nexttoken son ambos un id o una constante numérica...
            if((valorX==1001 && valorNT2==1001) || (valorX==1047 && valorNT2==1047) || (valorX==1048 && valorNT2==1048) || (valorX==1049 && valorNT2==1049)){
                //ACCIÓN #1 GEN
                pila_operandos.push(NT);
                copila_operandos.push(NT);

                // Obtener siguiente elemento
                ++iterador;
                QString ST=(*iterador)[0];
                int valorST2=relacionarT(ST);
                --iterador;

                // Verificar si lo que sigue es '==','!=','<','<=','>' o '>=' para realizar siguiente acción...
                if((valorST2==1035) || (valorST2==1036) || (valorST2==1037) || (valorST2==1038) || (valorST2==1039) || (valorST2==1040)){
                    //ACCIÓN #2 GEN
                    pila_operadoresgc.push(ST);
                    copila_operadoresgc.push(ST);
                }
            }
            // Establecer condicion a partir de la cual se sale de EXPR (dependiendo del estatuto en el cual se está)...
            if(bandDoEval==true){
                if(valorX==136 && valorNT2==1019){// (Si el valor del top de pilaX es 'TERM'' y nexttoken es ')')...
                    bandExpresion=false;
                    cout << "<BAND EXPR SE ESTABLECE EN FALSE>" << endl;
                }
            }
            if(bandIf==true){
                if(valorX==136 && valorNT2==1023){// (Si el valor del top de pilaX es 'TERM'' y nexttoken es ':')...
                    bandExpresion=false;
                    cout << "<BAND EXPR SE ESTABLECE EN FALSE>" << endl;
                    //ACCIÓN #6 GEN
                    QString contstr=QString::number(cont_cuadruplo);
                    QString op2=pila_operandos.top();
                    pila_operandos.pop();
                    QString op1=pila_operandos.top();
                    pila_operandos.pop();
                    QString oper=pila_operadoresgc.top();
                    pila_operadoresgc.pop();
                    QString res="R"+QString::number(cont_nores);
                    pila_operandos.push(res);
                    copila_operandos.push(res);

                    QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                    matriz_cuadruplos.append(cuadruplo);

                    cont_cuadruplo++;
                    cont_nores++;
                    //ACCIÓN #7 GEN
                    QString contstr2=QString::number(cont_cuadruplo);
                    QString top_pilaoperandos=pila_operandos.top();
                    pila_operandos.pop();

                    QVector<QString> cuadruploSF = {contstr2,"SF",top_pilaoperandos,"",""};
                    matriz_cuadruplos.append(cuadruploSF);
                    pila_saltos.push(cont_cuadruplo);
                    copila_saltos.push(cont_cuadruplo);

                    cont_cuadruplo++;
                }
            }
            if(bandWhile==true){
                if(valorX==136 && valorNT2==1023){// (Si el valor del top de pilaX es 'TERM'' y nexttoken es ':')...
                    bandExpresion=false;
                    cout << "<BAND EXPR SE ESTABLECE EN FALSE>" << endl;
                    //ACCIÓN #6 GEN
                    QString contstr=QString::number(cont_cuadruplo);
                    QString op2=pila_operandos.top();
                    pila_operandos.pop();
                    QString op1=pila_operandos.top();
                    pila_operandos.pop();
                    QString oper=pila_operadoresgc.top();
                    pila_operadoresgc.pop();
                    QString res="R"+QString::number(cont_nores);
                    pila_operandos.push(res);
                    copila_operandos.push(res);

                    QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                    matriz_cuadruplos.append(cuadruplo);

                    cont_cuadruplo++;
                    cont_nores++;
                }
            }
            if(bandFor==true){
                // (Si el valor del top de pilaX es 'TERM'' y nexttoken es 'to' o ':')...
                if(valorX==136 && valorNT2==1026){
                    bandExpresion=false;
                    cout << "<BAND EXPR SE ESTABLECE EN FALSE>" << endl;
                    //ACCIÓN #4 GEN
                    QString contstr=QString::number(cont_cuadruplo);
                    QString res=pila_operandos.top();
                    pila_operandos.pop();
                    QString op1=pila_operandos.top();
                    pila_operandos.pop();
                    QString oper=pila_operadoresgc.top();
                    pila_operadoresgc.pop();

                    QVector<QString> cuadruplo = {contstr,oper,op1,"",res};
                    matriz_cuadruplos.append(cuadruplo);

                    cont_cuadruplo++;
                }
                if(valorX==136 && valorNT2==1023){
                    bandExpresion=false;
                    cout << "<BAND EXPR SE ESTABLECE EN FALSE>" << endl;
                    //ACCIÓN #6 GEN
                    QString contstr=QString::number(cont_cuadruplo);
                    QString op2=pila_operandos.top();
                    pila_operandos.pop();
                    QString op1=pila_operandos.top();
                    pila_operandos.pop();
                    QString oper=">";
                    QString res="R"+QString::number(cont_nores);
                    pila_operandos.push(res);
                    copila_operandos.push(res);

                    QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                    matriz_cuadruplos.append(cuadruplo);

                    cont_cuadruplo++;
                    cont_nores++;
                }
            }
        }

        //ESTATUTO: while
        // Establecer condicion a partir de la cual se está dentro de ESTWHILE (si el valor del top de pilaX es <ESTWHILE> y nexttoken es while)...
        if((valorX==118) && (valorNT2==1022)){
            //Verificar si la bandera de algún estatuto está en true...
            if((bandDoEval==true) || (bandIf==true) || (bandFor==true) || (bandWhile==true)){
                //Comprobar cual bandera está en true, guardar su estado y ponerla en false
                if(bandDoEval==true){
                    QVector<QString> registrobandera = {"bandDoEval","true"};
                    matriz_estbandera.append(registrobandera);
                    bandDoEval=false;
                }else if(bandIf==true){
                    QVector<QString> registrobandera = {"bandIf","true"};
                    matriz_estbandera.append(registrobandera);
                    bandIf=false;
                }else if(bandFor==true){
                    QVector<QString> registrobandera = {"bandFor","true"};
                    matriz_estbandera.append(registrobandera);
                    bandFor=false;
                }else if(bandWhile==true){
                    QVector<QString> registrobandera = {"bandWhile","true"};
                    matriz_estbandera.append(registrobandera);
                    bandWhile=false;
                }
                //
                bandWhile=true;
                cout << "<BAND While SE ESTABLECE EN TRUE>" << endl;
            }else if((bandDoEval==false) && (bandIf==false) && (bandFor==false) && (bandWhile==false)){
                bandWhile=true;
                cout << "<BAND While SE ESTABLECE EN TRUE>" << endl;
            }
        }
        // Mientras bandWhile==true...
        if(bandWhile==true){
            // Si el valor del top de pilaX y 'nexttoken' son ambos while...
            if(valorX==1022 && valorNT2==1022){
                //ACCIÓN #5 GEN
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos :...
            if(valorX==1023 && valorNT2==1023){
                //ACCIÓN #7 GEN
                QString contstr=QString::number(cont_cuadruplo);
                QString top_pilaoperandos=pila_operandos.top();
                pila_operandos.pop();

                QVector<QString> cuadruploSF = {contstr,"SF",top_pilaoperandos,"",""};
                matriz_cuadruplos.append(cuadruploSF);
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);

                cont_cuadruplo++;
            }
            // Si el valor del top de pilaX y 'nexttoken' son E' y ; respectivamente...
            if(valorX==108 && valorNT2==1002){
                //ACCIÓN #8 GEN
                QString contstr=QString::number(cont_cuadruplo);
                QString topmeuno_pilasaltos=QString::number(topMenosUnoInt(pila_saltos));
                int top_pilasaltos=pila_saltos.top();

                QVector<QString> cuadruploSI = {contstr,"SI","","",topmeuno_pilasaltos};
                matriz_cuadruplos.append(cuadruploSI);

                cont_cuadruplo++;
                Rellenar(top_pilasaltos,cont_cuadruplo,matriz_cuadruplos);
                pila_saltos.pop();
                pila_saltos.pop();
                //Poner bandera de estatuto en false
                bandWhile=false;
                cout << "<BAND While SE ESTABLECE EN FALSE>" << endl;
                //Establecer la bandera del último registro de 'matriz_estbandera' en su estado anterior...
                if(!matriz_estbandera.isEmpty() && !matriz_estbandera.last().isEmpty()){
                    QString bandera = matriz_estbandera.last().first();
                    //
                    if(bandera=="bandDoEval"){
                        bandDoEval=true;
                        cout << "<BAND DoEval SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandIf"){
                        bandIf=true;
                        cout << "<BAND If SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandFor"){
                        bandFor=true;
                        cout << "<BAND For SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandWhile"){
                        bandWhile=true;
                        cout << "<BAND While SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }
                    //
                    matriz_estbandera.removeLast();
                }else{
                    //
                    cout << ">Mensaje: La matriz de banderas o su ultima fila estan vacias (no se estaba en un estatuto anidado)." << endl;
                }
            }
        }

        //ESTATUTO: if
        // Establecer condicion a partir de la cual se está dentro de ESTIF (si el valor del top de pilaX es <ESTIF> y nexttoken es if)...
        if((valorX==129) && (valorNT2==1030)){
            //Verificar si la bandera de algún estatuto está en true...
            if((bandDoEval==true) || (bandIf==true) || (bandFor==true) || (bandWhile==true)){
                //Comprobar cual bandera está en true, guardar su estado y ponerla en false
                if(bandDoEval==true){
                    QVector<QString> registrobandera = {"bandDoEval","true"};
                    matriz_estbandera.append(registrobandera);
                    bandDoEval=false;
                }else if(bandIf==true){
                    QVector<QString> registrobandera = {"bandIf","true"};
                    matriz_estbandera.append(registrobandera);
                    bandIf=false;
                }else if(bandFor==true){
                    QVector<QString> registrobandera = {"bandFor","true"};
                    matriz_estbandera.append(registrobandera);
                    bandFor=false;
                }else if(bandWhile==true){
                    QVector<QString> registrobandera = {"bandWhile","true"};
                    matriz_estbandera.append(registrobandera);
                    bandWhile=false;
                }
                //
                bandIf=true;
                cout << "<BAND If SE ESTABLECE EN TRUE>" << endl;
            }else if((bandDoEval==false) && (bandIf==false) && (bandFor==false) && (bandWhile==false)){
                bandIf=true;
                cout << "<BAND If SE ESTABLECE EN TRUE>" << endl;
            }
        }
        // Mientras bandIf==true...
        if(bandIf==true){
            // Si el valor del top de pilaX y 'nexttoken' son ambos if...
            if(valorX==1030 && valorNT2==1030){
                //ACCIÓN #5 GEN
                pila_operadoresgc.push("MFF");
                copila_operadoresgc.push("MFF");
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos else...
            if(valorX==1032 && valorNT2==1032){
                //ACCIÓN #8 GEN
                QString contstr=QString::number(cont_cuadruplo);
                int topmeuno_pilasaltos=pila_saltos.top(); //Top hasta este momento, que será top-1 para op. rellenar
                pila_saltos.pop();

                QVector<QString> cuadruploSI = {contstr,"SI","","",""};
                matriz_cuadruplos.append(cuadruploSI);
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);

                cont_cuadruplo++;
                Rellenar(topmeuno_pilasaltos,cont_cuadruplo,matriz_cuadruplos);
            }
            // Si el valor del top de pilaX y 'nexttoken' son E' y ; respectivamente...
            if(valorX==108 && valorNT2==1002){
                //ACCIÓN #9 GEN
                int top_pilasaltos=pila_saltos.top();
                pila_saltos.pop();

                Rellenar(top_pilasaltos,cont_cuadruplo,matriz_cuadruplos);
                //ACCIÓN #10 GEN
                QString top_pilaoperadores=pila_operadoresgc.top();
                if(top_pilaoperadores.compare("MFF")==0){
                    pila_operadoresgc.pop();
                }
                //Poner bandera de estatuto en false
                bandIf=false;
                cout << "<BAND If SE ESTABLECE EN FALSE>" << endl;
                //Establecer la bandera del último registro de 'matriz_estbandera' en su estado anterior...
                if(!matriz_estbandera.isEmpty() && !matriz_estbandera.last().isEmpty()){
                    QString bandera = matriz_estbandera.last().first();
                    //
                    if(bandera=="bandDoEval"){
                        bandDoEval=true;
                        cout << "<BAND DoEval SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandIf"){
                        bandIf=true;
                        cout << "<BAND If SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandFor"){
                        bandFor=true;
                        cout << "<BAND For SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandWhile"){
                        bandWhile=true;
                        cout << "<BAND While SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }
                    //
                    matriz_estbandera.removeLast();
                }else{
                    //
                    cout << ">Mensaje: La matriz de banderas o su ultima fila estan vacias (no se estaba en un estatuto anidado)." << endl;
                }
            }
        }

        //ESTATUTO: do-eval (repeat-until)
        // Establecer condicion a partir de la cual se está dentro de ESTDO (si el valor del top de pilaX es <ESTDO> y nexttoken es do)...
        if((valorX==126) && (valorNT2==1028)){
            //Verificar si la bandera de algún estatuto está en true...
            if((bandDoEval==true) || (bandIf==true) || (bandFor==true) || (bandWhile==true)){
                //Comprobar cual bandera está en true, guardar su estado y ponerla en false
                if(bandDoEval==true){
                    QVector<QString> registrobandera = {"bandDoEval","true"};
                    matriz_estbandera.append(registrobandera);
                    bandDoEval=false;
                }else if(bandIf==true){
                    QVector<QString> registrobandera = {"bandIf","true"};
                    matriz_estbandera.append(registrobandera);
                    bandIf=false;
                }else if(bandFor==true){
                    QVector<QString> registrobandera = {"bandFor","true"};
                    matriz_estbandera.append(registrobandera);
                    bandFor=false;
                }else if(bandWhile==true){
                    QVector<QString> registrobandera = {"bandWhile","true"};
                    matriz_estbandera.append(registrobandera);
                    bandWhile=false;
                }
                //
                bandDoEval=true;
                cout << "<BAND DoEval SE ESTABLECE EN TRUE>" << endl;
            }else if((bandDoEval==false) && (bandIf==false) && (bandFor==false) && (bandWhile==false)){
                bandDoEval=true;
                cout << "<BAND DoEval SE ESTABLECE EN TRUE>" << endl;
            }
        }
        // Mientras bandDoEval==true...
        if(bandDoEval==true){
            // Si el valor del top de pilaX y 'nexttoken' son ambos do...
            if(valorX==1028 && valorNT2==1028){
                //ACCIÓN #5 GEN
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos )...
            if(valorX==1019 && valorNT2==1019){
                //ACCIÓN #6 GEN
                QString contstr=QString::number(cont_cuadruplo);
                QString op2=pila_operandos.top();
                pila_operandos.pop();
                QString op1=pila_operandos.top();
                pila_operandos.pop();
                QString oper=pila_operadoresgc.top();
                pila_operadoresgc.pop();
                QString res="R"+QString::number(cont_nores);
                pila_operandos.push(res);
                copila_operandos.push(res);

                QVector<QString> cuadruplo = {contstr,oper,op1,op2,res};
                matriz_cuadruplos.append(cuadruplo);

                cont_cuadruplo++;
                cont_nores++;
                //
                QString contstr2=QString::number(cont_cuadruplo);
                QString top_pilaoperandos=pila_operandos.top();
                pila_operandos.pop();
                QString top_pilasaltos=QString::number(pila_saltos.top());
                pila_saltos.pop();

                QVector<QString> cuadruploSF = {contstr2,"SF",top_pilaoperandos,"",top_pilasaltos};
                matriz_cuadruplos.append(cuadruploSF);

                cont_cuadruplo++;
                //Poner bandera de estatuto en false
                bandDoEval=false;
                cout << "<BAND DoEval SE ESTABLECE EN FALSE>" << endl;
                //Establecer la bandera del último registro de 'matriz_estbandera' en su estado anterior...
                if(!matriz_estbandera.isEmpty() && !matriz_estbandera.last().isEmpty()){
                    QString bandera = matriz_estbandera.last().first();
                    //
                    if(bandera=="bandDoEval"){
                        bandDoEval=true;
                        cout << "<BAND DoEval SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandIf"){
                        bandIf=true;
                        cout << "<BAND If SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandFor"){
                        bandFor=true;
                        cout << "<BAND For SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandWhile"){
                        bandWhile=true;
                        cout << "<BAND While SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }
                    //
                    matriz_estbandera.removeLast();
                }else{
                    //
                    cout << ">Mensaje: La matriz de banderas o su ultima fila estan vacias (no se estaba en un estatuto anidado)." << endl;
                }
            }
        }

        //ESTATUTO: for
        // Establecer condicion a partir de la cual se está dentro de ESTFOR (si el valor del top de pilaX es <ESTFOR> y nexttoken es for)...
        if((valorX==125) && (valorNT2==1024)){
            //Verificar si la bandera de algún estatuto está en true...
            if((bandDoEval==true) || (bandIf==true) || (bandFor==true) || (bandWhile==true)){
                //Comprobar cual bandera está en true, guardar su estado y ponerla en false
                if(bandDoEval==true){
                    QVector<QString> registrobandera = {"bandDoEval","true"};
                    matriz_estbandera.append(registrobandera);
                    bandDoEval=false;
                }else if(bandIf==true){
                    QVector<QString> registrobandera = {"bandIf","true"};
                    matriz_estbandera.append(registrobandera);
                    bandIf=false;
                }else if(bandFor==true){
                    QVector<QString> registrobandera = {"bandFor","true"};
                    matriz_estbandera.append(registrobandera);
                    bandFor=false;
                }else if(bandWhile==true){
                    QVector<QString> registrobandera = {"bandWhile","true"};
                    matriz_estbandera.append(registrobandera);
                    bandWhile=false;
                }
                //
                bandFor=true;
                cout << "<BAND For SE ESTABLECE EN TRUE>" << endl;
            }else if((bandDoEval==false) && (bandIf==false) && (bandFor==false) && (bandWhile==false)){
                bandFor=true;
                cout << "<BAND For SE ESTABLECE EN TRUE>" << endl;
            }
        }
        // Mientras bandFor==true...
        if(bandFor==true){
            // Si el valor del top de pilaX y 'nexttoken' son ambos un id...
            if(valorX==1001 && valorNT2==1001){
                //ACCIÓN #1/#2 GEN
                pila_operandos.push(NT);
                copila_operandos.push(NT);
                pila_operandos.push(NT);
                copila_operandos.push(NT);
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos =...
            if(valorX==1025 && valorNT2==1025){
                //ACCIÓN #3 GEN
                pila_operadoresgc.push(NT);
                copila_operadoresgc.push(NT);
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos to...
            if(valorX==1026 && valorNT2==1026){
                //ACCIÓN #5 GEN
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);
            }
            // Si el valor del top de pilaX y 'nexttoken' son ambos :...
            if(valorX==1023 && valorNT2==1023){
                //ACCIÓN #7 GEN
                QString contstr=QString::number(cont_cuadruplo);
                QString top_pilaoperandos=pila_operandos.top();

                QVector<QString> cuadruploSV = {contstr,"SV",top_pilaoperandos,"",""};
                matriz_cuadruplos.append(cuadruploSV);
                pila_saltos.push(cont_cuadruplo);
                copila_saltos.push(cont_cuadruplo);

                cont_cuadruplo++;
                pila_operandos.pop();
            }
            // Si el valor del top de pilaX y 'nexttoken' son E' y ; respectivamente...
            if(valorX==108 && valorNT2==1002){
                //ACCIÓN #9 GEN
                QString contstr=QString::number(cont_cuadruplo);
                QString topmeuno_pilasaltos=QString::number(topMenosUnoInt(pila_saltos));
                int top_pilasaltos=pila_saltos.top();

                QVector<QString> cuadruploSI = {contstr,"SI","","",topmeuno_pilasaltos};
                matriz_cuadruplos.append(cuadruploSI);

                cont_cuadruplo++;
                Rellenar(top_pilasaltos,cont_cuadruplo,matriz_cuadruplos);
                pila_saltos.pop();
                pila_saltos.pop();
                //Poner bandera de estatuto en false
                bandFor=false;
                cout << "<BAND For SE ESTABLECE EN FALSE>" << endl;
                //Establecer la bandera del último registro de 'matriz_estbandera' en su estado anterior...
                if(!matriz_estbandera.isEmpty() && !matriz_estbandera.last().isEmpty()){
                    QString bandera = matriz_estbandera.last().first();
                    //
                    if(bandera=="bandDoEval"){
                        bandDoEval=true;
                        cout << "<BAND DoEval SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandIf"){
                        bandIf=true;
                        cout << "<BAND If SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandFor"){
                        bandFor=true;
                        cout << "<BAND For SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }else if(bandera=="bandWhile"){
                        bandWhile=true;
                        cout << "<BAND While SE ESTABLECE NUEVAMENTE EN TRUE>" << endl;
                    }
                    //
                    matriz_estbandera.removeLast();
                }else{
                    //
                    cout << ">Mensaje: La matriz de banderas o su ultima fila estan vacias (no se estaba en un estatuto anidado)." << endl;
                }
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------

        // Condicionales en base al valor de X (parte principal del análisis sintáctico)---------------------------------------------------
        if((valorX>=1000 && valorX<=1051) || valorX==2000){
            cout << "X es terminal: "+valorX2.toStdString() << endl;

            if((valorX==valorNT2) && (valorNT2==2000)){
                QString msj_stringacept="String de entrada ACEPTADO.";
                ui->lW_MsjSintaxis->addItem(msj_stringacept);
            }else{
                if((valorX==valorNT2) && (valorNT2!=2000)){
                    // Sacar a X de la pila
                    pilaX.pop();
                    // Incrementar iterador (remover a nexttoken de la entrada)
                    ++iterador;
                    bandNuevaEntrada=true;
                }else{
                    QString msj_error=">ERROR: Se esperaba: "+valorX2+".";
                    ui->lW_MsjErrSintaxis->addItem(msj_error);
                    //
                    ui->lW_MsjErrSemantic->clear();
                    ui->lW_ContPilasSemantic->clear();

                    bandErrSintac=true;
                    //
                    break;
                }
            }
        }else if(valorX>=100 && valorX<=147){
            cout << "X es NO terminal: "+valorX2.toStdString() << endl;

            // Obtener elemento de matriz predictiva
            int fila=filaNoTerminal(valorX);
            int columna=columnaTerminal(valorNT2);
            int produccion=matrizPredictiva[fila][columna];
            cout << "Produccion: " << produccion << endl;//Imprimir no. de produccion en consola

            if(produccion!=-1){
                // Sacar a X de la pila
                pilaX.pop();
                // Meter derivación de producción a la pila
                insertarDerivacion(produccion);
            }else{
                QString msj_error2=">ERROR: Se esperaba alguno de los First's de: "+valorX2+".";
                ui->lW_MsjErrSintaxis->addItem(msj_error2);
                //
                ui->lW_MsjErrSemantic->clear();
                ui->lW_ContPilasSemantic->clear();

                bandErrSintac=true;
                //
                break;
            }
        }
        bandContPila=pilaX.empty();
    }while ((valorNT2!=2000) && (bandContPila==false));

    cout << "SALE DE CICLO DE ANALISIS SINTACTICO/SEMANTICO Y GCI<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    if((bandErrSemantAsig==false && bandErrSintac==false) && !matriz_cuadruplos.isEmpty()){
        // Establecer el número de filas y columnas
        ui->tW_VisualCuadrup->setRowCount(matriz_cuadruplos.size());
        ui->tW_VisualCuadrup->setColumnCount(matriz_cuadruplos.isEmpty() ? 0 : matriz_cuadruplos[0].size());
        // Establecer los encabezados de las columnas
        QStringList encabezados;
        encabezados << "#" << "OPER" << "OP1" << "OP2" << "RES";
        ui->tW_VisualCuadrup->setHorizontalHeaderLabels(encabezados);
        // Rellenar la tabla con los datos de la matriz
        for (int row = 0; row < matriz_cuadruplos.size(); ++row) {
            for (int column = 0; column < matriz_cuadruplos[row].size(); ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(matriz_cuadruplos[row][column]);
                ui->tW_VisualCuadrup->setItem(row, column, item);
            }
        }
        //
        ui->tW_VisualCuadrup->verticalHeader()->setVisible(false);
        // Ajustar el tamaño de las columnas para que se ajusten al contenido
        ui->tW_VisualCuadrup->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //
        ui->tW_VisualCuadrup->show();
        // IMPRIMIR PILAS DE GCI...
        if(!copila_operandos.empty()){
            QString strpila_operandos=copila_operandos.top();
            copila_operandos.pop();
            while(!copila_operandos.empty()){
                strpila_operandos.prepend(copila_operandos.top()+" | ");
                copila_operandos.pop();
            }
            strpila_operandos.prepend("P. OPERANDOS: | ");
            strpila_operandos.append(" |");
            ui->lW_ContPilasGCI->addItem(strpila_operandos);
        }else{
            ui->lW_ContPilasGCI->addItem("P. OPERANDOS:");
        }

        if(!copila_operadoresgc.empty()){
            QString strpila_operadoresgc=copila_operadoresgc.top();
            copila_operadoresgc.pop();
            while(!copila_operadoresgc.empty()){
                strpila_operadoresgc.prepend(copila_operadoresgc.top()+" | ");
                copila_operadoresgc.pop();
            }
            strpila_operadoresgc.prepend("P. OPERADORES: | ");
            strpila_operadoresgc.append(" |");
            ui->lW_ContPilasGCI->addItem(strpila_operadoresgc);
        }else{
            ui->lW_ContPilasGCI->addItem("P. OPERADORES:");
        }

        if(!copila_saltos.empty()){
            QString strpila_saltos=QString::number(copila_saltos.top());
            copila_saltos.pop();
            while(!copila_saltos.empty()){
                strpila_saltos.prepend(QString::number(copila_saltos.top())+" | ");
                copila_saltos.pop();
            }
            strpila_saltos.prepend("P. SALTOS: | ");
            strpila_saltos.append(" |");
            ui->lW_ContPilasGCI->addItem(strpila_saltos);
        }else{
            ui->lW_ContPilasGCI->addItem("P. SALTOS:");
        }
    }else{
        cout << "Ocurrio un error sintactico/semantico, generacion de codigo intermedio fallida." << endl;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------

// Función: Analizar léxico
void VentanaPrincipal::AnalizarLex(){
    // Matriz de estados
    int matriz_estados[22][33] = {
        {1,2,506,3,506,506,20,21,506,108,107,9,134,13,12,14,10,11,133,132,124,135,123,121,122,119,120,0,0,0,19,17,15},
        {1,2,2,2,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
        {2,2,2,2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
        {102,102,102,3,4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
        {500,500,500,5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500},
        {103,103,103,5,103,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
        {501,501,501,8,501,501,7,7,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
        {502,502,502,8,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
        {104,104,104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
        {109,109,109,109,109,109,109,109,109,109,109,110,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109},
        {111,111,111,111,111,111,111,111,111,111,111,112,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111},
        {113,113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
        {116,116,116,116,116,116,116,116,116,116,116,115,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
        {503,503,503,503,503,503,503,503,503,503,503,503,503,117,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
        {504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,118,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
        {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,505},
        {507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,125},
        {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,17},
        {126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,17,126},
        {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,127,19,19,19,19,19},
        {105,105,105,105,105,105,128,105,105,105,105,129,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105},
        {106,106,106,106,106,106,106,130,106,106,106,131,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106}
    };
    //Variables
    int estado, columna;
    char caracter;

    int contador_cadena=0;
    int contador_paro=0;
    int contador_linea=1;//
    int contador_notoken=1;//

    bool band_apred=false;
    bool band_reserror=false;//

    QString token;//Cadena para almacenar caracteres (token)

    //Obtener texto de editor
    QString textoeditor=ui->editorTextoArchivo->toPlainText();
    string cad_textoeditor=textoeditor.toStdString();
    char cadena[cad_textoeditor.length()]{};
    strcpy(cadena, cad_textoeditor.c_str());
    cout << "CADENA LEIDA: <" << cadena << ">" << endl;
    cout << "TAMANO:" << strlen(cadena) << endl;

    char* ap_cadena=cadena;//Apuntador

    //Ciclo de analisis
    while(contador_cadena<=strlen(cadena)){
        estado=0;//Establecer estado en 0

        while(estado<=21){
            //Obtener caracter posterior al actual
            char caracter_post=Leer_CarPost(ap_cadena);
            cout << "CARACTER POST.:" << caracter_post << endl;

            if(band_apred==true){//
                if(caracter_post==' ' || caracter_post=='\n'){//
                    caracter=Leer_Caracter(ap_cadena);
                    cout << "Caracter leido:" << caracter << endl;

                    token.append(caracter);

                    columna=relacionarC(caracter);
                    cout << "Columna:" << columna << endl;

                    estado=matriz_estados[estado][columna];
                    cout << "Estado:" << estado << endl;

                    ap_cadena++;
                    cout << "AP INCREMENTA." << endl;

                    band_apred=false;
                }else if(caracter_post=='\0'){//
                    caracter=Leer_Caracter(ap_cadena);
                    cout << "Caracter leido:" << caracter << endl;

                    token.append(caracter);

                    columna=relacionarC(caracter);
                    cout << "Columna:" << columna << endl;

                    estado=matriz_estados[estado][columna];
                    cout << "Estado:" << estado << endl;

                    if(estado<=21){
                        //ELMENTO NO RECONOCIDO
                    }else{
                        ap_cadena++;
                        cout << "AP INCREMENTA." << endl;

                        if(token.size()==1){

                        }else{
                            token.chop(1);
                        }
                    }

                    band_apred=false;
                }else{//
                    caracter=Leer_Caracter(ap_cadena);
                    cout << "Caracter leido:" << caracter << endl;

                    token.append(caracter);

                    columna=relacionarC(caracter);
                    cout << "Columna:" << columna << endl;

                    estado=matriz_estados[estado][columna];
                    cout << "Estado:" << estado << endl;

                    if(estado<=21){

                    }else{
                        ap_cadena++;
                        cout << "AP INCREMENTA." << endl;

                        if(token.size()==1){

                        }else{
                            token.chop(1);
                        }
                    }

                    band_apred=false;
                }
            }else if(band_apred==false){//
                caracter=Leer_Caracter(ap_cadena);
                cout << "Caracter leido:" << caracter << endl;

                token.append(caracter);

                columna=relacionarC(caracter);
                cout << "Columna:" << columna << endl;

                estado=matriz_estados[estado][columna];
                cout << "Estado:" << estado << endl;

                if(estado<=21){

                }else{
                    //
                    if((caracter_post==' ' || caracter_post=='\n') && (estado>=500 && estado<=507)){
                        ap_cadena++;
                        cout << "AP INCREMENTA." << endl;
                    }

                    //
                    if(token.size()==1){

                    }else{
                        token.chop(1);
                    }
                }
            }
        }
        //Resultado según estado
        if(estado>=100 && estado<=135){//
            QString estadoresult=estadoToken(estado);

            //Crear fila con token analizado, ¿qué es? y no. de línea, para añadirla a la matriz
            QString linea = QString::number(contador_linea);
            QVector<QString> fila = {token,estadoresult,linea};
            matriz_tokenid.append(fila);

            //Imprimir token reconocido y vaciar QString que lo contiene
            cout << "TOKEN REC: <" << token.toStdString() << ">" << endl;
            token.clear();

            //Agregar qué token se reconoció a la lista
            QString notoken=QString::number(contador_notoken);
            ui->lW_Tokens->addItem(estadoresult+" | Token no. "+notoken+" | Linea: "+linea);
            contador_notoken++;

            //
            string estadors=estadoresult.toStdString();
            cout << "RECONOCIDO:" << estadors << endl;
            //

            //Aumentar contador_cadena e imprimir su valor
            contador_cadena = ap_cadena - cadena;
            cout << "VALOR CONTADOR:" << contador_cadena << endl;

            //Detener análisis
            if(contador_cadena==strlen(cadena)){
                contador_paro=contador_paro+1;
                if(contador_paro==1){
                    contador_cadena=contador_cadena+1;
                }

                if(contador_cadena>strlen(cadena)){
                    cout << "TERMINA ANALISIS LEXICO<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
                    //
                    if(band_reserror==true){
                        //Vaciar matriz de tokens
                        matriz_tokenid.clear();

                        if(matriz_tokenid.isEmpty()){
                            cout << ">Se detectaron tokens erroneos, por lo que se vacio la matriz." << endl;
                        }
                    }else{
                        QVector<QString> filafin = {"$","FIN",linea};
                        matriz_tokenid.append(filafin);
                        /*
                        for (const QString& elemento : filafin) {
                            std::cout << elemento.toStdString() << std::endl;
                        }*/
                    }
                }
            }

            //Regresar al caracter anterior que se identificó como "diferente" para detectar el último token.
            if(contador_cadena<(strlen(cadena)-1)){
                //Obtener el caracter anterior del arreglo de caracteres...
                char caracter_ant=Leer_CarAnt(ap_cadena);
                cout << "CARACTER ANTERIOR:" << caracter_ant << endl;

                //Condicionales
                if((caracter_ant==' ') || (caracter_ant=='\0') || (caracter_ant=='\n')){
                    if(caracter_ant=='\n'){
                        contador_linea++;
                    }
                }else{
                    ap_cadena--;
                    band_apred=true;
                    cout << "AP DECREMENTA." << endl;
                }
            }
        }else if(estado>=500 && estado<=507){//
            QString estadoresult2=estadoError(estado);
            band_reserror=true;//Hubo un tóken erróneo

            //
            string estadors2=estadoresult2.toStdString();
            cout << "TOKEN ERRONEO:" << estadors2 << endl;
            //

            //Limpiar QString con caracteres de token erróneo
            token.clear();

            //Agregar error de token a la lista
            QString notoken=QString::number(contador_notoken);
            QString linea = QString::number(contador_linea);
            ui->lW_ErroresTokens->addItem(estadoresult2+" | Token no. "+notoken+" | Linea: "+linea);
            contador_notoken++;

            //Aumentar contador_cadena e imprimir su valor
            contador_cadena = ap_cadena - cadena;
            cout << "VALOR CONTADOR:" << contador_cadena << endl;

            //Detener análisis
            if(contador_cadena==strlen(cadena)){
                contador_paro=contador_paro+1;
                if(contador_paro==1){
                    contador_cadena=contador_cadena+1;
                }

                if(contador_cadena>strlen(cadena)){
                    cout << "TERMINA ANALISIS LEXICO<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
                    //
                    //Vaciar matriz de tokens
                    matriz_tokenid.clear();

                    if(matriz_tokenid.isEmpty()){
                        cout << ">Se detectaron tokens erroneos, por lo que se vacio la matriz." << endl;
                    }
                }
            }

            //
            if(contador_cadena<=strlen(cadena)){
                //Obtener el caracter anterior del arreglo de caracteres...
                char caracter_ant=Leer_CarAnt(ap_cadena);
                cout << "CARACTER ANTERIOR:" << caracter_ant << endl;

                //Condicionales
                if(caracter_ant=='\n'){
                    contador_linea++;
                }else{

                }
            }
        }
    }
}

// Eventos: al modificar el texto en QTextEdit
void VentanaPrincipal::on_editorTextoArchivo_textChanged()
{
    QString texto_editor = ui->editorTextoArchivo->toPlainText();
    // Condicionales según contenido del editor
    if (!texto_editor.isEmpty()){
        //
        ui->btn_Guardar->setEnabled(true);
        ui->btn_Limpiar->setEnabled(true);
        ui->btn_ANALIZAR->setEnabled(true);
    } else {
        //
        ui->btn_Guardar->setEnabled(false);
        ui->btn_Limpiar->setEnabled(false);
        ui->btn_ANALIZAR->setEnabled(false);
    }
}
