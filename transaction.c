#include "transaction.h"

// eksekusi transaksi
void sendTransaction(Wallet* from, Wallet* to, Transaction* tx) {
    if (!(from->flags & WALLET_ACTIVE)) { tx->status = TX_FAILED; return; }
    if (from->flags & WALLET_LOCKED)     { tx->status = TX_FAILED; return; }
    if (from->balance < tx->amount)      { tx->status = TX_FAILED; return; }

    from->balance -= tx->amount;
    to->balance   += tx->amount;
    tx->status = TX_SUCCESS;
}
