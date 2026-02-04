# 🎵 Sistema de Gestão de Streaming de Música

Este projeto foi desenvolvido no âmbito da Unidade Curricular de **Laboratórios de Informática III (LI3)** na Universidade do Minho (2024/2025). O objetivo principal é o processamento e análise de grandes volumes de dados (datasets) relativos a artistas, álbuns, músicas, utilizadores e históricos de reprodução.

## 👥 Grupo 33
* João Sousa - A106900
* José Rocha - A106887
* Vasco Cota - A106886

---

## 🚀 Funcionalidades Principais

O sistema permite a execução de operações complexas sobre os dados através de dois modos de execução:

### 1. Modo Batch (Execução por Comandos)
Lê um ficheiro de comandos e gera ficheiros de output correspondentes para cada query.
* **Parsing Eficiente:** Tratamento de ficheiros CSV com validação de erros.
* **Gestão de Memória:** Implementação focada em minimizar *memory leaks* e otimizar o uso de estruturas.

### 2. Modo Interativo
Uma interface amigável que permite ao utilizador navegar pelos dados e executar queries em tempo real.
* Interface intuitiva.
* Visualização de resultados formatada no terminal.

---

## 📊 Queries Implementadas

O sistema responde a um conjunto de interrogações específicas (Queries):

* **Q1:** Resumo de uma entidade (utilizador, artista ou álbum).
* **Q2:** Listagem dos top N artistas com maior tempo de discografia.
* **Q3:** Identificação dos géneros musicais mais populares para uma determinada faixa etária.
* **Q4:** (Fase 2) Identificação do artista que mais vezes apareceu no top de álbuns.
* **Q5:** (Fase 2) Recomendação de utilizadores com gostos musicais semelhantes.
* **Q6:** (Fase 2) Estatísticas detalhadas de utilização por período temporal.

---

## 🏗️ Arquitetura e Estrutura

O projeto segue princípios rigorosos de **Modularidade** e **Encapsulamento**:

* **Gestores de Entidades:** Módulos responsáveis pelo armazenamento e manipulação de Artistas, Músicas, Utilizadores e Álbuns.
* **Catálogos:** Estruturas de dados otimizadas para pesquisa rápida.
* **Parser:** Módulo encarregue da leitura, validação e limpeza dos dados brutos.
* **Interface Interativa:** Módulo dedicado à experiência do utilizador.

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C
* **Ferramentas de Análise:** `Valgrind` (gestão de memória) e `GDB` (depuração).
* **Bibliotecas:** GLib (utilizada para estruturas de dados avançadas).
* **Compilação:** `Makefile` para automatização do processo de build.

## ⚙️ Como Compilar e Executar

### Pré-requisitos
Certifica-te de que tens instalada a biblioteca **GLib**:
```bash
sudo apt update
sudo apt install libglib2.0-dev
```

### ⚙️ Compilação e Execução

**Compilação**  
```bash
make
```
**Execução** 
* Modo Batch:
```bash
./programa-principal <caminho_dataset> <ficheiro_comandos>
```
* Modo Interativo:
```bash
./programa-interativo
```



