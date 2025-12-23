#ifndef WALLET_H
#define WALLET_H

/* Struktur Wallet */
typedef struct {
    char* address;              // Address wallet
    int balance;                // Saldo
    unsigned char flags;        // Status wallet (bit)
    unsigned short pinHash;     // Hash PIN
    unsigned char pinFailCount; // Counter salah PIN
} Wallet;

// bit status
#define WALLET_ACTIVE   1
#define WALLET_LOCKED   2
#define WALLET_VERIFIED 4

// wallet core
Wallet createWallet(const char* address, int balance, int pin);
void freeWallet(Wallet* w);

// seccurity
unsigned short hashPIN(int pin);
int verifyPIN(Wallet* w, int pin);

// utility
void printMaskedAddress(const char* address);
int findWalletByAddress(Wallet* wallets, int count, const char* address);

// info I/O 
int loadWallets(const char* filename, Wallet** wallets);
void saveWallets(const char* filename, Wallet* wallets, int count);

#endif
