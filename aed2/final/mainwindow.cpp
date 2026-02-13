#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cidade = new Grafo();
    autocomplete = new Trie();

    cena = new QGraphicsScene(this);
    ui->mapView->setScene(cena);


    carregarDados();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cidade;
    delete autocomplete;
}


//função para ler os arquivos json
void MainWindow::carregarDados(){
    qDebug() << "Lendo JSON...";

    // 1. Avisa o utilizador que está a carregar
    ui->txtResultado->setText("A carregar o mapa da cidade... Aguarde um momento.");
    QApplication::processEvents(); // Força a janela a desenhar este texto imediatamente!

    std::string pathNodes = "C:/Users/Gabriel/Documents/codigos/_UFPEL/repo_aed/aed2/final/data/nodes.json";
    std::string pathEdges = "C:/Users/Gabriel/Documents/codigos/_UFPEL/repo_aed/aed2/final/data/edges.json";
    std::string pathNomes = "C:/Users/Gabriel/Documents/codigos/_UFPEL/repo_aed/aed2/final/data/label_to_nodes.json";

    //std::string pathNodes = "data/nodes.json";
    //std::string pathEdges = "data/edges.json";
    //std::string pathNomes = "data/label_to_nodes.json";

    cidade->carregarArestas(pathEdges);
    cidade->carregarNos(pathNodes);

    autocomplete->carregarJson(pathNomes);

    ui->txtResultado->setText("Mapa carregado com sucesso! Pode pesquisar.");

    qDebug() << "Carregamento concluido.";
}


// ==========================================
// LÓGICA DA CAIXA DE ORIGEM
// ==========================================

//função para sugerir a cada mudança de texto
void MainWindow::on_txtOrigem_textChanged(const QString &arg1)
{
    ui->listOrigem->clear(); // limpa a lista
    std::string busca = arg1.toStdString();

    qDebug() << "A procurar por:" << arg1;

    // só procura na trie depois de 3 char digitados
    if (busca.length() < 3) return;

    std::vector<std::string> sugestoes = autocomplete->sugerir(busca);

    qDebug() << "Sugestões encontradas na Trie:" << sugestoes.size();

    // add as sugestoes a lista da ui
    for (const auto &s : sugestoes) {
        ui->listOrigem->addItem(QString::fromStdString(s));
    }
}

//reage a um clique na caixa de sugestoes da cx de origem
void MainWindow::on_listOrigem_itemClicked(QListWidgetItem *item)
{
    std::string rua = item->text().toStdString();

    // atualiza a cx de texto com o nome que o usuario clicou
    ui->txtOrigem->setText(QString::fromStdString(rua));

    // busca o ID da rua na trie
    auto ids = autocomplete->buscarID(rua);
    if (!ids.empty()) {
        idOrigem = ids[0]; // guarda o primeiro ID encontrado
        ui->txtResultado->setText("Origem definida.");
    }
}


// ==========================================
// LÓGICA DA CAIXA DE DESTINO
// ==========================================

//função para sugerir a cada mudança da cx de texto
void MainWindow::on_txtDestino_textChanged(const QString &arg1)
{
    ui->listDestino->clear();
    std::string busca = arg1.toStdString();

    if (busca.length() < 3) return;

    std::vector<std::string> sugestoes = autocomplete->sugerir(busca);
    for (const auto &s : sugestoes) {
        ui->listDestino->addItem(QString::fromStdString(s));
    }
}

//reage a um clique na caixa de sugestoes da cx de destino
void MainWindow::on_listDestino_itemClicked(QListWidgetItem *item)
{
    std::string rua = item->text().toStdString();
    ui->txtDestino->setText(QString::fromStdString(rua));

    auto ids = autocomplete->buscarID(rua);
    if (!ids.empty()) {
        idDestino = ids[0];
        ui->txtResultado->setText("Destino definido. Pode calcular.");
    }
}


// ==========================================
// LÓGICA DO BOTÃO CALCULAR (DIJKSTRA)
// ==========================================

void MainWindow::on_btnCalcular_clicked()
{
    // Verifica se o utilizador já selecionou os dois pontos nas listas
    if (idOrigem == -1 || idDestino == -1) {
        ui->txtResultado->setText("Erro: Selecione a origem e o destino nas listas.");
        return;
    }

    ui->txtResultado->setText("A calcular a rota...");
    QApplication::processEvents(); // Força a interface a atualizar o texto

    // Executa o Dijkstra a partir da origem selecionada
    resultadoDijkstra resultado = cidade->executarDijkstra(idOrigem);

    // Obtém o índice interno do vetor associado ao ID do OSM do destino
    int indiceDestino = cidade->obterIndice(idDestino);

    // Verifica se a rota é válida e alcançável (não é infinito)
    if (indiceDestino == -1 || resultado.dist[indiceDestino] >= std::numeric_limits<double>::infinity()) {
        ui->txtResultado->setText("Não existe um caminho válido entre estas ruas.");
        return;
    }

    // Exibe o resultado da distância na etiqueta
    double distanciaMetros = resultado.dist[indiceDestino];
    ui->txtResultado->setText("Distância: " + QString::number(distanciaMetros) + " metros.");
}
