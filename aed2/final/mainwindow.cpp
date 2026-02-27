#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>
#include <QMessageBox>
#include <QTimer>
#include <QWheelEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet(
        // Caixa de texto: Fundo branco, letra preta
        "QLineEdit { border: 1px solid #ccc; border-radius: 5px; padding: 5px; font-size: 14px; background-color: white; color: black; }"

        // Lista de sugestões: Fundo escuro elegante, letra branca
        "QListWidget { border: 1px solid #444; border-radius: 5px; background-color: #2b2b2b; color: white; }"
        "QListWidget::item { padding: 5px; }"

        // Item selecionado (Hover): Fundo azul, letra branca
        "QListWidget::item:hover { background-color: #007bff; color: white; }"

        // Botão
        "QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #0056b3; }"
        );

    ui->txtOrigem->setPlaceholderText("Pesquise a rua de origem...");
    ui->txtDestino->setPlaceholderText("Pesquise a rua de destino...");

    ui->listOrigem->hide();
    ui->listDestino->hide();

    cidade = new Grafo();
    autocomplete = new Trie();

    cena = new QGraphicsScene(this);
    ui->mapView->setScene(cena);

    ui->mapView->viewport()->installEventFilter(this);


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

    std::string pathNodes = "data/nodes.json";
    std::string pathEdges = "data/edges.json";
    std::string pathNomes = "data/label_to_nodes.json";

    cidade->carregarArestas(pathEdges);
    cidade->carregarNos(pathNodes);
    autocomplete->carregarJson(pathNomes);

    qDebug() << "A desenhar o mapa...";
    desenharMapaBase();

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
    std::string busca = arg1.toLower().toStdString();

    qDebug() << "A procurar por:" << arg1;

    // só procura na trie depois de 3 char digitados
    if (busca.length() < 3){
        ui->listOrigem->hide();
        return;
    }

    std::vector<std::string> sugestoes = autocomplete->sugerir(busca);

    qDebug() << "Sugestões encontradas na Trie:" << sugestoes.size();

    // add as sugestoes a lista da ui
    if (sugestoes.empty()) {
        ui->listOrigem->hide();
    } else {
        ui->listOrigem->setMinimumHeight(120);
        ui->listOrigem->show();
        for (const auto &s : sugestoes) {
            ui->listOrigem->addItem(QString::fromStdString(s));
        }
    }
}

//reage a um clique na caixa de sugestoes da cx de origem
void MainWindow::on_listOrigem_itemClicked(QListWidgetItem *item)
{
    std::string rua = item->text().toStdString();

    // atualiza a cx de texto com o nome que o usuario clicou
    ui->txtOrigem->setText(QString::fromStdString(rua));

    ui->listOrigem->hide();

    // busca o ID da rua na trie
    auto ids = autocomplete->buscarID(rua);
    if (!ids.empty()) {
        idOrigem = ids[0]; // guarda o primeiro ID encontrado
        ui->txtResultado->setText("Origem definida.");
        desenharMarcador(idOrigem, true);
    }
}


// ==========================================
// LÓGICA DA CAIXA DE DESTINO
// ==========================================

//função para sugerir a cada mudança da cx de texto
void MainWindow::on_txtDestino_textChanged(const QString &arg1)
{
    ui->listDestino->clear();
    std::string busca = arg1.toLower().toStdString();

    if (busca.length() < 3){
        ui->listDestino->hide();
        return;
    }

    std::vector<std::string> sugestoes = autocomplete->sugerir(busca);

    if (sugestoes.empty()) {
        ui->listDestino->hide();
    } else {
        ui->listDestino->setMinimumHeight(120);
        ui->listDestino->show();
        for (const auto &s : sugestoes) {
            ui->listDestino->addItem(QString::fromStdString(s));
        }
    }
}

//reage a um clique na caixa de sugestoes da cx de destino
void MainWindow::on_listDestino_itemClicked(QListWidgetItem *item)
{
    std::string rua = item->text().toStdString();
    ui->txtDestino->setText(QString::fromStdString(rua));

    ui->listDestino->hide();

    auto ids = autocomplete->buscarID(rua);
    if (!ids.empty()) {
        idDestino = ids[0];
        ui->txtResultado->setText("Destino definido. Pode calcular.");
        desenharMarcador(idDestino, false);
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
    QString textoDistancia;

    if (distanciaMetros >= 1000.0) {
        textoDistancia = QString::number(distanciaMetros / 1000.0, 'f', 2) + " km";
    } else {
        textoDistancia = QString::number(std::round(distanciaMetros)) + " metros";
    }

    ui->txtResultado->setText("Distância: " + textoDistancia);

    // DESENHAR A ROTA
    std::vector<noGrafo> caminho = cidade->reconstruirCaminho(idOrigem, idDestino, resultado.pai);

    QPen canetaRota(Qt::red);
    canetaRota.setCosmetic(true); // A linha tem espessura em pixels, não "engrossa" com o zoom
    canetaRota.setWidth(4);       // Linha com 4 pixels de largura para se destacar muito bem

    double escala = 100000.0;

    // Liga os pontos de trás para a frente com linhas vermelhas
    for (size_t i = 0; i < caminho.size() - 1; ++i) {
        double x1 = caminho[i].lon * escala;
        double y1 = -caminho[i].lat * escala;
        double x2 = caminho[i+1].lon * escala;
        double y2 = -caminho[i+1].lat * escala;

        QGraphicsLineItem *linha = cena->addLine(x1, y1, x2, y2, canetaRota);
        linha->setZValue(1); // Fica por cima do mapa cinza, mas por baixo das bolinhas (Z=2)
        linhasRotaAtiva.push_back(linha);
    }

    if (!linhasRotaAtiva.empty()) {
        QRectF areaDaRota = linhasRotaAtiva[0]->boundingRect();

        // Une as áreas de todas as linhas da rota para descobrir o tamanho total
        for (QGraphicsLineItem* linha : linhasRotaAtiva) {
            areaDaRota = areaDaRota.united(linha->boundingRect());
        }

        // Dá uma margem de "respiro" de 10% à volta da rota para não colar nas bordas
        double margemX = areaDaRota.width() * 0.1;
        double margemY = areaDaRota.height() * 0.1;
        areaDaRota.adjust(-margemX, -margemY, margemX, margemY);

        // Anima/Foca a câmara nessa área
        ui->mapView->fitInView(areaDaRota, Qt::KeepAspectRatio);
    }
}



// ==========================================
// FUNÇÂO DE DESENHAR O MAPA
// ==========================================
void MainWindow::desenharMapaBase()
{
    cena->clear(); // Limpa a tela

    // Define uma caneta cinzenta e fina para o mapa de fundo
    QPen canetaFundo(QColor(200, 200, 200));
    canetaFundo.setWidth(0); // 0 significa que a linha terá sempre 1 pixel de espessura, mesmo com zoom

    // Fator de ampliação (escala) para converter as coordenadas GPS em pixels
    double escala = 100000.0;

    // Vai buscar todas as ruas ao grafo
    auto linhas = cidade->obterTodasAsArestasParaDesenho();

    for (const auto& linha : linhas) {
        // Multiplica para afastar os pontos e inverte o Y (lat) pois no Qt o Y cresce para baixo
        double x1 = linha.first.lon * escala;
        double y1 = -linha.first.lat * escala;
        double x2 = linha.second.lon * escala;
        double y2 = -linha.second.lat * escala;

        // Adiciona a linha à cena
        cena->addLine(x1, y1, x2, y2, canetaFundo);
    }

    // 1. Permite que o utilizador arraste o mapa clicando e puxando com o rato
    ui->mapView->setDragMode(QGraphicsView::ScrollHandDrag);

    // 2. Atrasa o cálculo do zoom em 100 milissegundos para garantir que a janela já abriu
    QTimer::singleShot(100, this, [this]() {
        // Agora sim, com a janela aberta, ele ajusta perfeitamente
        ui->mapView->fitInView(cena->itemsBoundingRect(), Qt::KeepAspectRatio);
    });
}

//função que cuida o scroll do mouse para dar zoom no mapa
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // Verifica se o evento aconteceu dentro do mapView e se foi um rodar do rato
    if (watched == ui->mapView->viewport() && event->type() == QEvent::Wheel) {

        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        // Se a roda foi para a frente (valor positivo), fazemos Zoom In (15% maior)
        if (wheelEvent->angleDelta().y() > 0) {
            ui->mapView->scale(1.15, 1.15);
        }
        // Se a roda foi para trás, fazemos Zoom Out (15% menor)
        else {
            ui->mapView->scale(0.85, 0.85);
        }

        return true; // Avisa o Qt que já tratámos deste evento
    }

    // Para todos os outros eventos (cliques, teclado), deixa o Qt seguir o padrão normal
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::desenharMarcador(long long id, bool isOrigem) {
    noGrafo coord = cidade->obterCoordenada(id);
    if (coord.lat == 0 && coord.lon == 0) return; // Segurança

    double escala = 100000.0;
    double x = coord.lon * escala;
    double y = -coord.lat * escala;

    QColor cor = isOrigem ? Qt::green : Qt::blue;

    // Cria um círculo de 12x12 pixels centrado na origem (-6, -6)
    QGraphicsEllipseItem* ponto = cena->addEllipse(-6, -6, 12, 12, QPen(Qt::black), QBrush(cor));
    ponto->setPos(x, y); // Coloca nas coordenadas do GPS

    // O TRUQUE MÁGICO: Este círculo ignora o Zoom! Fica sempre com 12px no ecrã.
    ponto->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    ponto->setZValue(2); // Garante que o ponto fica por cima de todas as ruas

    if (isOrigem) {
        if (marcadorOrigem) cena->removeItem(marcadorOrigem);
        marcadorOrigem = ponto;
        limparRota(); // Se mudou a origem, limpa a rota anterior
    } else {
        if (marcadorDestino) cena->removeItem(marcadorDestino);
        marcadorDestino = ponto;
        limparRota(); // Se mudou o destino, limpa a rota anterior
    }
}

void MainWindow::limparRota() {
    // Apaga as linhas vermelhas velhas da tela e da memória
    for (auto linha : linhasRotaAtiva) {
        cena->removeItem(linha);
        delete linha;
    }
    linhasRotaAtiva.clear();
}
