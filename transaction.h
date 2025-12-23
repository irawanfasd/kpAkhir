#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "wallet.h"

// status transaksi
typedef enum { TX_PENDING, TX_SUCCESS, TX_FAILED } TxStatus;

// truktur transaksi
typedef struct {
    int txId;
    char* from;
    char* to;
    int amount;
    TxStatus status;
} Transaction;

void sendTransaction(Wallet* from, Wallet* to, Transaction* tx);

#endif
