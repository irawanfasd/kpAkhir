# Web3 Wallet Simulator (C Language)

Web3 Wallet Simulator adalah aplikasi **Command Line Interface (CLI)** yang dibuat menggunakan bahasa **C**, dengan tujuan mensimulasikan cara kerja **wallet Web3** seperti Ethereum wallet secara sederhana namun terstruktur.

Project ini mengimplementasikan konsep:
- Wallet berbasis address
- Autentikasi menggunakan PIN
- Ledger transaksi (blockchain-like)
- Keamanan dasar (PIN hashing, limit login)
- Struktur aplikasi berbasis **login & dashboard**

---

## Tujuan Project

Project ini dibuat untuk:
- Menerapkan konsep **struktur data (struct, linked list)**
- Mempraktikkan **modular programming (header & source file)**
- Memahami simulasi **Web3 Wallet & Transaction**
- Menerapkan **keamanan dasar aplikasi** dalam bahasa C
- Membuat aplikasi CLI yang terstruktur seperti aplikasi nyata

---

## Konsep Web3 yang Diimplementasikan

| Konsep Web3 | Implementasi |
|------------|--------------|
| Wallet Address | String address unik |
| Private Credential | PIN wallet (hash) |
| Ledger | Linked List transaksi |
| Transaction | Transfer antar wallet |
| Security | PIN masking & lock wallet |
| Privacy | Masking address (0x12****) |
| Account-Based App | Login & dashboard wallet |

---

## Struktur Program

```

.
├── main.c            # Program utama (menu, login, dashboard)
├── wallet.h          # Definisi struktur wallet
├── wallet.c          # Manajemen wallet & keamanan
├── transaction.h     # Struktur transaksi
├── transaction.c     # Logika transaksi
├── tx_list.h         # Linked list ledger transaksi
├── tx_list.c         # Implementasi ledger
├── wallets.txt       # Data wallet (auto-generated)
└── transactions.txt  # Data transaksi (auto-generated)

```

---

## Alur Aplikasi

### Menu Utama
```

1. Create Wallet
2. Login Wallet
3. Exit

```

### Login Wallet
User login menggunakan:
- Address
- PIN (ditampilkan sebagai `****`)

Jika PIN salah 3x → wallet otomatis **LOCKED**

---

### Wallet Dashboard
Setelah login berhasil:
```

1. Send Transaction
2. View Wallet Info
3. Transaction Statistics
4. Reset PIN
5. Logout

````

emua fitur di dashboard **berlaku hanya untuk wallet yang sedang login**

---

## Fitur Keamanan

- PIN di-hash sebelum disimpan
- Input PIN dimasking (`****`)
- Maksimal 3x salah PIN
- Wallet otomatis terkunci
- Data sensitif tidak ditampilkan ke layar

---

## Ledger & Statistik

- Semua transaksi disimpan dalam **Linked List**
- Ledger dapat ditampilkan
- Statistik per wallet:
  - Jumlah transaksi masuk
  - Jumlah transaksi keluar
  - Total nilai transaksi

---

## Penyimpanan Data

Aplikasi menggunakan file teks sebagai simulasi storage:
- `wallets.txt` → data wallet
- `transactions.txt` → data transaksi

Data otomatis di-load saat program dijalankan dan di-save saat perubahan terjadi.

---

## Cara Compile & Run

### Compile:
```bash
gcc main.c wallet.c transaction.c tx_list.c -o projekkp
````

### Run:

```bash
./projekkp
```

---

## Contoh Output

```
=== WALLET DASHBOARD ===
Address : 0x12****
Balance : 20000
```

```
TX 10231 | 0x12**** -> 0x98**** | 500 | SUCCESS
```

---

## Catatan Pengembangan

Project ini merupakan **simulasi edukatif**, bukan wallet sungguhan.
Tidak menggunakan kriptografi asli blockchain.

---

## Pengembangan Lanjutan (Opsional)

* Multi-admin & recovery
* Export ledger ke CSV
* Signature-based authentication
* Integrasi database
* UI berbasis terminal lebih interaktif

---

## Author

**Nama:** Irawan Prasetyo
**Project:** Web3 Wallet Simulator
**Bahasa:** C
**Topik:** Sistem Terdistribusi / Web3 / Struktur Data

---

## License

Project ini dibuat untuk keperluan **Responsi KP2**.

```

---

## **screenshot output CLI**
<img width="601" height="229" alt="image" src="https://github.com/user-attachments/assets/291f814e-1ac8-473d-bb5b-9b17693879e3" />


```
feat: implement login-based wallet dashboard
---
C, Web3, CLI, Blockchain, Wallet, Data-Structure
---


