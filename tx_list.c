#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tx_list.h"

/* Tambah transaksi */
void addTransaction(TxNode** head, Transaction tx) {
    TxNode* n = malloc(sizeof(TxNode));
    n->data = tx; n->next = NULL;
    if (!*head) { *head = n; return; }
    TxNode* t = *head;
    while (t->next) t = t->next;
    t->next = n;
}

/* Tampilkan ledger */
void printTransactions(TxNode* head) {
    printf("\n=== TRANSACTION LEDGER ===\n");
    while (head) {
        printf("TX %d | ", head->data.txId);
        printMaskedAddress(head->data.from);
        printf(" -> ");
        printMaskedAddress(head->data.to);
        printf(" | %d | %d\n",
            head->data.amount,
            head->data.status);
        head = head->next;
    }
}

/* Load ledger */
TxNode* loadTransactionList(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;
    TxNode* head = NULL;
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        Transaction tx;
        char* t = strtok(buf, "|"); tx.txId = atoi(t);
        t = strtok(NULL, "|"); tx.from = strdup(t);
        t = strtok(NULL, "|"); tx.to = strdup(t);
        t = strtok(NULL, "|"); tx.amount = atoi(t);
        t = strtok(NULL, "|"); tx.status = atoi(t);
        addTransaction(&head, tx);
    }
    fclose(f);
    return head;
}

/* Save ledger */
void saveTransactionList(const char* filename, TxNode* head) {
    FILE* f = fopen(filename, "w");
    if (!f) return;
    while (head) {
        fprintf(f, "%d|%s|%s|%d|%d\n",
            head->data.txId,
            head->data.from,
            head->data.to,
            head->data.amount,
            head->data.status);
        head = head->next;
    }
    fclose(f);
}

// free ledger
void freeTransactionList(TxNode* head) {
    while (head) {
        TxNode* t = head;
        head = head->next;
        free(t);
    }
}
