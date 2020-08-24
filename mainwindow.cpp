#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Restaurantes abertos");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------
// Click no botão OK
//--------------------
void MainWindow::on_pushButton_OK_clicked()
{
    QMessageBox msgBox;

    ui->listWidget->clear();

    // Procura pelo arquivo na pasta de debug do Qt
    QString arquivo = QCoreApplication::applicationDirPath() + "/restaurant-hours.csv";

    QString hora = ui->timeEdit->text();

    // Chama o método que vai processar o arquivo com os dados dos restaurantes passando também a hora para consulta
    QStringList lista = availableHours(arquivo, hora);

    // Se retornou algum restaurante, monta lista
    if(lista.count())
    {
        for(int i=0;i<lista.count();i++)
        {
            ui->listWidget->addItem(lista.at(i));
        }
    }
    else
    {
        msgBox.setWindowTitle("Aviso");
        msgBox.setText("Nenhum restaurante encontrado.");
        msgBox.exec();
    }
}

//------------------------------------------------------------
// Método que recebe o arquivo com os dados dos restaurantes
// e a hora pedida para consulta
//------------------------------------------------------------
QStringList MainWindow::availableHours(QString arquivo, QString hora)
{
    QStringList lista;
    QStringList dados;
    QString linha, restaurante, horaFaixa, horaAbre, horaFecha;
    QTime qt_horaConsulta, qt_horaAbre, qt_horaFecha;
    int ind = 0;

    // Seta a hora para consulta a partir do timeEdit
    qt_horaConsulta = QTime::fromString(hora);

    // Prepara para ler o arquivo com os dados dos restaurantes
    QFile file(arquivo);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Erro", "Problemas com o arquivo: " + file.errorString());
        return lista;
    }

    QTextStream in(&file);
    linha = in.readLine(); // Le e despreza a primeira linha do arquivo (os títulos)
    do // Le as próximas linhas
    {
        linha = in.readLine(); // Le linha de cada restaurante

        if(!linha.isNull())
        {
            // Pega os dados da linha
            restaurante = linha.split(',').at(0);
            horaFaixa = linha.split(',').at(1);
            horaAbre = horaFaixa.split('-').at(0);
            horaFecha = horaFaixa.split('-').at(1);

            // Retira as aspas e troca : por .
            restaurante = restaurante.mid(1,restaurante.length()-2);
            horaAbre = horaAbre.mid(1, horaAbre.length());
            horaAbre = horaAbre.replace(horaAbre.indexOf(':'),1,'.');
            horaFecha = horaFecha.mid(0, horaFecha.length()-1);
            horaFecha = horaFecha.replace(horaFecha.indexOf(':'),1,'.');

            // Transforma os horários para QTime
            if(horaAbre.length() == 5)  // Formato hh.mm
            {
                qt_horaAbre = QTime::fromString(horaAbre, "hh.mm");
                horaAbre = qt_horaAbre.toString("hh.mm");
            }
            else                        // Formato h.mm
            {
                qt_horaAbre = QTime::fromString(horaAbre, "h.mm");
                horaAbre = qt_horaAbre.toString("h.mm");
            }

            if(horaFecha.length() == 5) // Formato hh.mm
            {
                qt_horaFecha = QTime::fromString(horaFecha, "hh.mm");
                horaFecha = qt_horaFecha.toString("hh.mm");
            }
            else                        // Formato h.mm
            {
                qt_horaFecha = QTime::fromString(horaFecha, "h.m");
                horaFecha = qt_horaFecha.toString("h.m");
            }

            // Verifica se horário pedido está na faixa deste restaurante
            if(qt_horaConsulta.operator>=(qt_horaAbre) && qt_horaConsulta.operator<=(qt_horaFecha))
            {
                //lista.insert(ind++, restaurante + "-" + horaAbre + "-" + horaFecha);
                lista.insert(ind++, restaurante);
            }
        }
    }while(!linha.isNull());

    file.close();

    return lista;
}
