#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grafo.hpp"
#include "trie.hpp"
#include <QGraphicsScene>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_txtOrigem_textChanged(const QString &arg1);
    void on_listOrigem_itemClicked(QListWidgetItem *item);
    void on_txtDestino_textChanged(const QString &arg1);
    void on_listDestino_itemClicked(QListWidgetItem *item);
    void on_btnCalcular_clicked();

private:
    Ui::MainWindow *ui;

    //estruturas de dados
    Grafo *cidade;
    Trie *autocomplete;

    //mapa
    QGraphicsScene *cena;

    //var. de controle de estado
    long long idOrigem = -1;
    long long idDestino = -1;

    //metodos
    void carregarDados();
    void configurarInterface();
    void carregarTrie(const std::string &caminho);
    void desenharMapaBase();

    // elem. graficos para desenhar camino
    QGraphicsEllipseItem *marcadorOrigem = nullptr;
    QGraphicsEllipseItem *marcadorDestino = nullptr;
    std::vector<QGraphicsLineItem*> linhasRotaAtiva;

    // funções de desenhar caminho
    void desenharMarcador(long long id, bool isOrigem);
    void limparRota();

};
#endif // MAINWINDOW_H
