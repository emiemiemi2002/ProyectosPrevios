#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <stack>

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaPrincipal; }
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

    QString obtenerRutaArchivo();

    char Leer_Caracter(char*& puntero);

    char Leer_CarAnt(char*& puntero);

    char Leer_CarPost(char*& puntero);

    int relacionarC(char c);

    QString estadoToken(int e);

    QString estadoError(int e);

    void AnalizarLex();

    int columnaTerminal(int e);

    int filaNoTerminal(int e);

    void insertarDerivacion(int prod);

    int relacionarT(QString t);

    void AnalizarSintax();

    QString xToString(int x);

    QString verifTiposOps(QString op1, QString op2, QString operador);

    QString obtenerTipoId(QString id);

    QString topMenosUnoStr(std::stack<QString>& pilastr);

    int topMenosUnoInt(std::stack<int>& pilaint);

    bool idYaDeclarado(QString newid);

    void Rellenar(int direccion, int valor, QVector<QVector<QString>>& matriz);

private slots:
    void on_btn_ANALIZAR_clicked();

    void on_btn_AbrirArchivo_clicked();

    void on_btn_Guardar_clicked();

    void on_btn_Limpiar_clicked();

    void on_btn_Salir_clicked();

    void on_editorTextoArchivo_textChanged();

private:
    Ui::VentanaPrincipal *ui;
};
#endif // VENTANAPRINCIPAL_H
