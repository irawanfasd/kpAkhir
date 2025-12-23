#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wallet.h"
#include "transaction.h"
#include "tx_list.h"

// clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// input PIN tersembunyi
int inputPIN() {
    char c, pin[5]; int i = 0;
    while ((c = getchar()) != '\n' && i < 4) {
        if (c >= '0' && c <= '9') {
            pin[i++] = c;
            printf("*");
        }
    }
    pin[i] = '\0';
    printf("\n");
    return atoi(pin);
}

// input string
void inputLine(char* buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = 0;
}

int main() {
    Wallet* wallets = NULL;
    int walletCount = loadWallets("wallets.txt", &wallets);
    TxNode* txList = loadTransactionList("transactions.txt");

    int choice;
    while (1) {
        clearScreen();
        printf("=== WEB3 WALLET SIMULATOR ===\n");
        printf("1. Create Wallet\n");
        printf("2. Login Wallet\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            clearScreen();
            char addr[256];
            printf("Address: "); inputLine(addr, 256);
            printf("Saldo awal: ");
            int bal; scanf("%d", &bal); getchar();
            printf("PIN (4 digit): ");
            int pin = inputPIN();

            wallets = realloc(wallets, (walletCount + 1) * sizeof(Wallet));
            wallets[walletCount++] = createWallet(addr, bal, pin);
            saveWallets("wallets.txt", wallets, walletCount);

            printf("Wallet berhasil dibuat.\n"); getchar();
        }

        else if (choice == 2) {
            clearScreen();
            char addr[256];
            printf("Address: "); inputLine(addr, 256);

            int idx = findWalletByAddress(wallets, walletCount, addr);
            if (idx == -1) { printf("Wallet tidak ditemukan.\n"); getchar(); continue; }

            printf("PIN: ");
            int pin = inputPIN();
            if (!verifyPIN(&wallets[idx], pin)) {
                printf("PIN salah.\n"); getchar(); continue;
            }

            /* DASHBOARD */
            int logged = 1;
            while (logged) {
                clearScreen();
                printf("=== WALLET DASHBOARD ===\nAddress: ");
                printMaskedAddress(wallets[idx].address);
                printf("\nBalance: %d\n\n", wallets[idx].balance);

                printf("1. Send Transaction\n");
                printf("2. View Wallet Info\n");
                printf("3. Transaction Statistics\n");
                printf("4. Reset PIN\n");
                printf("5. Logout\n");
                printf("Choice: ");
                scanf("%d", &choice);
                getchar();

                if (choice == 1) {
                    char toAddr[256];
                    printf("Address tujuan: "); inputLine(toAddr, 256);
                    int to = findWalletByAddress(wallets, walletCount, toAddr);
                    if (to == -1) { getchar(); continue; }

                    printf("Jumlah: ");
                    int amt; scanf("%d", &amt); getchar();

                    Transaction tx = { rand()%100000,
                        wallets[idx].address, wallets[to].address,
                        amt, TX_PENDING };

                    sendTransaction(&wallets[idx], &wallets[to], &tx);
                    addTransaction(&txList, tx);
                    saveWallets("wallets.txt", wallets, walletCount);
                    saveTransactionList("transactions.txt", txList);
                    getchar();
                }

                else if (choice == 2) {
                    printf("Address: ");
                    printMaskedAddress(wallets[idx].address);
                    printf("\nBalance: %d\n", wallets[idx].balance);
                    getchar();
                }

                else if (choice == 3) {
                    int in=0,out=0,ti=0,to=0;
                    for (TxNode* c=txList;c;c=c->next){
                        if(!strcmp(c->data.from,wallets[idx].address)){out++;to+=c->data.amount;}
                        if(!strcmp(c->data.to,wallets[idx].address)){in++;ti+=c->data.amount;}
                    }
                    printf("IN:%d (%d) OUT:%d (%d)\n",in,ti,out,to);
                    getchar();
                }

                else if (choice == 4) {
                    printf("PIN baru: ");
                    wallets[idx].pinHash = hashPIN(inputPIN());
                    wallets[idx].pinFailCount = 0;
                    wallets[idx].flags &= ~WALLET_LOCKED;
                    saveWallets("wallets.txt", wallets, walletCount);
                    getchar();
                }

                else if (choice == 5) logged = 0;
            }
        }

        else if (choice == 0) break;
    }

    freeTransactionList(txList);
    for (int i = 0; i < walletCount; i++) freeWallet(&wallets[i]);
    free(wallets);
    return 0;
}
