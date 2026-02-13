# INTEGRANTES DO GRUPO

Nome: Edmar Jacinto Domingos Francisco.
Nome: Gabriel Kruger Brum.

## Como Rodar no Qt Creator

Entre no Qt Creator -> Open Project... -> Selecione o arquivo CMakeLists.txt
No Qt Creator: Configure Project, Escolhe : o kit **Desktop Qt 6.x.x MinGW 64-bit**.
Depois disso: Next → Next → Finish.

Agora faz em ordem: Build → Clean All, Build → Run CMake , Build → Build Project ,Run.

## Estruturas de Dados (resumindo tudo o que fizemos no trabalho)

### 🔹 `noGrafo`
Representa um nó do grafo (vértice do mapa).
- `lat` → latitude  
- `lon` → longitude  

Usado para armazenar coordenadas geográficas dos pontos do mapa.

---

### 🔹 `arestaGrafo`
Representa uma aresta (ligação entre dois nós).
- `destino` → índice do nó de destino  
- `peso` → custo da aresta (distância do segmento da via)

---

### 🔹 `resultadoDijkstra`
Estrutura de saída do algoritmo de Dijkstra.
- `dist` → vetor com as menores distâncias da origem até cada nó  
- `pai` → vetor de predecessores para reconstrução do caminho mínimo  

---

### 🔹 `Grafo` (classe principal)
Estrutura central do sistema, responsável por:
- Armazenamento do grafo por **lista de adjacência**
- Mapeamento usando Hash Map (std::unordered_map) entre **ID OSM (long long)** e **índices internos (int)**
- Execução do algoritmo de **Dijkstra**
- Reconstrução de caminhos mínimos
- Leitura de dados a partir de arquivos **JSON**

#### Principais estruturas internas:
- `adjList` → lista de adjacência (`vector<vector<arestaGrafo>>`)  
- `nodeList` → lista de nós com coordenadas  
- `id_para_indice` → mapa `ID OSM → índice interno`  
- `indice_para_id` → mapa inverso `índice interno → ID OSM`  

---

## Estruturas da Trie (Autocomplete de Ruas)

### 🔹 `NoTrie`
Representa um nó da Trie.
- `filhos[256]` → ponteiros para caracteres ASCII estendidos  
- `ids_nodo` → lista de IDs OSM associados ao nome da rua  
- `ehFim` → indica final de uma palavra válida  

---

### 🔹 `Trie`
Estrutura responsável por busca textual e autocomplete.
Funções principais:
- Inserção de nomes de ruas
- Busca de ruas por nome completo
- Busca por prefixo
- Sistema de **autocomplete**
- Leitura de dados via **JSON**

Usada para: localizar ruas pelo nome e obter os IDs associados no grafo

## Dependência obrigatória

Não há dependências obrigatória para rodar o projeto, o único código externo utilizado é a biblioteca nlohmann/json, mas ela ja esta inclusa nos arquivos do programa