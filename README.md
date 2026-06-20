# C23 Kilo From Scratch

Um editor de texto para terminal desenvolvido do zero e modernizado para o padrão **C23**.

---

## 📌 Sobre o Projeto

O **C23_Kilo_From_Scratch** é um projeto de engenharia de software com propósito puramente educacional, focado no desenvolvimento de sistemas em baixo nível. Ele baseia-se no clássico editor de texto minimalista `kilo` (criado por Salvatore Sanfilippo, o *antirez*) e no aclamado guia *"Build Your Own Text Editor"*.

A grande virada de chave deste repositório não é apenas replicar o código original, mas conduzir uma **refatoração arquitetural profunda** para aplicar as melhores práticas modernas da linguagem e explorar as novas especificações e recursos introduzidos pelo padrão **C23**.

Este espaço funciona como um laboratório prático ("sandbox") para entender os fundamentos por trás de softwares de edição de texto, forçando o desenvolvedor a pensar criticamente sobre cada decisão de design, alocação de memória e tratamento de dados, em vez de simplesmente realizar um "copiar e colar".

---

## 🎯 Objetivos de Aprendizado e Engenharia

Construir este projeto do zero visa solidificar conceitos essenciais de ciência da computação e programação de sistemas:

1. **Manipulação de Terminal em Baixo Nível (POSIX):** Entender a transição do modo canônico para o modo bruto (*raw mode*), gerenciando flags do terminal através da API `termios.h`, capturando entradas de teclado em tempo real e lidando com sinais do sistema (como interrupções de fluxo).
2. **Arquitetura de Gerenciamento de Tela:** Aprender a desenhar interfaces e renderizar caracteres dinamicamente através de buffers de escrita estruturados, utilizando sequências de escape ANSI/VT100 diretamente no fluxo de saída standard (`stdout`).
3. **Estruturas de Dados para Editores de Texto:** Desenhar soluções eficientes para representação de buffers de texto mutáveis em memória, controlando índices de linhas, mapeamento de caracteres especiais (como tabulações) e coordenadas de cursor de forma performática.
4. **Pensamento de Engenheiro Moderno (C23):** Adaptar rotinas legadas para o dialeto mais recente da linguagem C, avaliando melhorias em verificação de tipos, novas palavras-chave, inicialização segura de memória e conformidade com compiladores modernos.

---

## 🔍 Visão Geral do Escopo

O desenvolvimento está estruturado de forma incremental para garantir clareza conceitual a cada etapa:

- [x] **Fase 1: Entrada Bruta (*Raw Input*):** Configuração do terminal para capturar teclas byte-a-byte, desativando ecôos automáticos e interrupções padrão do sistema para controle total da aplicação.
- [ ] **Fase 2: Saída Avançada e Bufferização:** Implementação de um sistema de atualização de tela otimizado para evitar *flickering* (piscadas na tela), agrupando comandos de escape e caracteres textuais em um buffer dinâmico de escrita única.
- [ ] **Fase 3: Visualização de Arquivos (*Text Viewer*):** Leitura de arquivos do disco rígido e mapeamento para uma estrutura de linhas sequenciais na memória principal do programa.
- [ ] **Fase 4: Edição Atômica de Texto:** Criação de algoritmos seguros para inserção e remoção de caracteres em qualquer posição espacial do documento, seguidos pela persistência fiel de volta ao sistema de arquivos.
- [ ] **Fase 5: Localização e Busca Incremental:** Desenvolvimento de um motor de busca de substrings que navega em tempo real pelo buffer conforme as teclas são pressionadas, atualizando a posição visual do cursor instantaneamente.
- [ ] **Fase 6: Análise Léxica e Destaque de Sintaxe (*Syntax Highlighting*):** Construção de um *parser* simples para categorização de tokens (números, strings, palavras-chave da linguagem, comentários) e colorização dinâmica de código no terminal.

---

## 📄 Créditos e Direitos Autorais

* **Código Base Original:** O editor `kilo` foi idealizado e implementado originalmente por **Salvatore Sanfilippo (antirez)** sob a licença BSD de 2 cláusulas.
* **Material de Apoio Didático:** A trilha lógica e conceitual baseia-se no projeto didático criado por Jeremy Ruten.
* **Modernização e Adaptações:** Todo o trabalho de transposição para **C23**, documentação arquitetural e expansão conceitual foi realizado de forma independente com viés de estudo e engenharia de software.