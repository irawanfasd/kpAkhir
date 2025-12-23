#ifndef TX_LIST_H
#define TX_LIST_H

#include "transaction.h"

// node ledger
typedef struct TxNode {
    Transaction data;
    struct TxNode* next;
} TxNode;

void addTransaction(TxNode** head, Transaction tx);
void printTransactions(TxNode* head);
TxNode* loadTransactionList(const char* filename);
void saveTransactionList(const char* filename, TxNode* head);
void freeTransactionList(TxNode* head);

#endif
