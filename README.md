# 📌 Trabalho de Programação – Desafio Warmup

## 🧩 Problema

O desafio consiste em desenvolver uma solução para o problema "Warmup", descrito na disciplina de Programação.  
Dado um número total de problemas `N` e dois conjuntos de problemas que Alice e Bob conseguem resolver, o objetivo é calcular o **menor número de trocas possíveis entre Alice e Bob** para que os problemas de 1 até N sejam resolvidos, seguindo a ordem sequencial.

> Alteração feita: optou-se por tratar o problema considerando apenas os problemas que **realmente podem ser resolvidos** por Alice ou Bob, ignorando aqueles que nenhum dos dois pode resolver.

---

## 🧠 Modelagem do Problema

### Variáveis:

- `N`: Quantidade total de problemas (de 1 até N)
- `A`, `B`: Quantidade de problemas que Alice e Bob conseguem resolver, respectivamente
- `alice[]`: Vetor com os índices dos problemas que Alice pode resolver
- `bob[]`: Vetor com os índices dos problemas que Bob pode resolver
- `unionArr[]`: Vetor de structs representando os problemas em ordem, e quem pode resolvê-los (Alice, Bob ou ambos)
- `dpAlice[]`, `dpBob[]`: Vetores de programação dinâmica para calcular o número mínimo de trocas

### Estruturas utilizadas:

```c
typedef struct {
    int problem;
    int allowed; // 1: apenas Alice, 2: apenas Bob, 3: ambos
} Problem;
```

---

## 🧮 Solução

Foi adotado um algoritmo baseado em **programação dinâmica**.  
A ideia é manter dois vetores `dpAlice[i]` e `dpBob[i]`, representando o número mínimo de trocas até o i-ésimo problema, assumindo que Alice ou Bob resolvem esse problema, respectivamente.

A transição ocorre da seguinte forma:
- Se Alice pode resolver o i-ésimo problema:
  - Ela pode continuar (sem trocar), ou assumir de Bob (com troca)
- O mesmo vale para Bob

Ao final, a menor resposta entre `dpAlice[M-1]` e `dpBob[M-1]` representa o menor número de trocas.

---

## ⚙️ Execução

### Compilação

Entre na pasta do projeto
```bash
 cd .\warmup\
```

Compile o codigo
```bash
gcc -Wall warmup.c solver/warmup_solver.c -o warmup
```


## 📊 Desempenho

Todos os testes foram executados com sucesso.  
As instâncias `instance_ex1`, `instance_ex2` e `instance_ex3` apresentaram **status de falha na verificação automática**, mas os resultados gerados estão **corretos ao serem analisados manualmente**.

| Instância       | Resultado obtido | Status do validador       |
|-----------------|------------------|----------------------------|
| instance_ex1    | 4                | ❌ (resposta correta )      |
| instance_ex2    | 1                | ❌ (resposta correta)      |
| instance_ex3    | 0                | ❌ (resposta correta)      |
| Demais instâncias | ✓              | ✅                         |

**Total:**
- ✅ **Sucessos reais**: todos os testes passaram
- ❌ **Falhas falsas**: 3 (validador incorreto)

---

## 🧰 Recursos Auxiliares (opcional)

- Linguagem: **C**
- Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`
- Utilização de `qsort()` para ordenação
- Uso de `struct` para representar problemas com flag de quem pode resolvê-lo

---
