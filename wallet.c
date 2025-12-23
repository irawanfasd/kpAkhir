#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wallet.h"

// hash sederhana pin
unsigned short hashPIN(int pin) {
    return (unsigned short)((pin * 31) ^ 0xAAAA);
}

// membuat wallet
Wallet createWallet(const char* address, int balance, int pin) {
    Wallet w;
    w.address = strdup(address);
    w.balance = balance;
    w.flags = WALLET_ACTIVE | WALLET_VERIFIED | WALLET_LOCKED;
    w.pinHash = hashPIN(pin);
    w.pinFailCount = 0;
    return w;
}

/* Verifikasi PIN + limit 3x */
int verifyPIN(Wallet* w, int pin) {
    if (w->pinHash == hashPIN(pin)) {
        w->flags &= ~WALLET_LOCKED;
        w->pinFailCount = 0;
        return 1;
    }
    w->pinFailCount++;
    if (w->pinFailCount >= 3)
        w->flags |= WALLET_LOCKED;
    return 0;
}

/* Masking address */
void printMaskedAddress(const char* address) {
    for (int i = 0; i < 4 && address[i]; i++)
        printf("%c", address[i]);
    printf("****");
}

/* Cari wallet by address */
int findWalletByAddress(Wallet* wallets, int count, const char* address) {
    for (int i = 0; i < count; i++)
        if (strcmp(wallets[i].address, address) == 0)
            return i;
    return -1;
}

/* Load wallet */
int loadWallets(const char* filename, Wallet** wallets) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;

    int count = 0;
    char buf[256];
    *wallets = NULL;

    while (fgets(buf, sizeof(buf), f)) {
        *wallets = realloc(*wallets, (count + 1) * sizeof(Wallet));
        char* t = strtok(buf, "|");
        (*wallets)[count].address = strdup(t);

        t = strtok(NULL, "|"); (*wallets)[count].balance = atoi(t);
        t = strtok(NULL, "|"); (*wallets)[count].flags = atoi(t);
        t = strtok(NULL, "|"); (*wallets)[count].pinHash = atoi(t);
        t = strtok(NULL, "|"); (*wallets)[count].pinFailCount = atoi(t);
        count++;
    }
    fclose(f);
    return count;
}

/* Save wallet */
void saveWallets(const char* filename, Wallet* wallets, int count) {
    FILE* f = fopen(filename, "w");
    if (!f) return;
    for (int i = 0; i < count; i++)
        fprintf(f, "%s|%d|%d|%d|%d\n",
            wallets[i].address,
            wallets[i].balance,
            wallets[i].flags,
            wallets[i].pinHash,
            wallets[i].pinFailCount);
    fclose(f);
}

/* Free wallet */
void freeWallet(Wallet* w) {
    free(w->address);
}
