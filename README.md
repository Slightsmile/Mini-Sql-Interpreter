# Mini SQL Interpreter for CSV Files

## 📌 Overview
This project implements a **lightweight SQL-like interpreter** for querying CSV files using **Flex** (Lexical Analysis) and **Bison** (Syntax Analysis). It demonstrates **compiler construction principles** applied to real-world data filtering without requiring a full database system.

---

## ✨ Features

- SQL-like query syntax
```
SELECT column1, column2 FROM filename.csv WHERE column condition value;
```
- Supports:
  - Multiple column selection
  - WHERE clause with numeric and string conditions
  - Lightweight and fast (no DBMS needed)
  - Works with any CSV file

---

## 🛠 Tools & Technologies
- **Flex** – Lexical Analyzer
- **Bison** – Parser Generator
- **C Language**
- **GCC**
- **Linux**

---

## 📂 Project Structure
```
mini-sql-interpreter/
├── lexer.l # Token definitions (Flex)
├── parser.y # Grammar rules (Bison)
├── csv_utils.c # CSV processing logic
├── csv_utils.h # Function declarations
├── main.c # Entry point
├── Makefile # Build script
├── people.csv # Sample data
└── README.md # Documentation
```

---

## 🚀 Getting Started - Linux

### 1. Install Flex Bison
```
sudo apt-get install flex bison
```
### 2. Clone the repository:
```
git clone https://github.com/Slightsmile/Mini-Sql-Interpreter.git
cd mini-sql-interpreter
```

### 3. Build the project:
```
make
```
### 4. Run the interpreter:
```
./mini_sql
```
### 5. Example Queries:
```
SELECT name, age FROM people.csv WHERE age > 30;
SELECT name, city FROM people.csv WHERE city = "Dhaka";
```

---

## 📷 Example Output

<img width="503" height="204" alt="Screenshot from 2025-08-06 12-51-43" src="https://github.com/user-attachments/assets/4070a85c-5c2a-4eb8-8638-72533080aaf7" />
<img width="407" height="119" alt="Screenshot from 2025-08-06 12-52-38" src="https://github.com/user-attachments/assets/84bcc8a6-0d71-419a-94b0-6fe1d2c29ded" />
<img width="546" height="136" alt="Screenshot from 2025-08-06 12-53-32" src="https://github.com/user-attachments/assets/f303d5a4-12da-47f8-b928-56769407f3fe" />

---

## ⚠️ Error Handling
- Invalid query → Error: syntax error
- Missing file → Cannot open CSV file

---

## 📜 License
This project is open source and available under the MIT License.
Feel free to use and modify it for personal use.

> Developed as a part of the Compiler Desgin Lab Project at Daffodil International University.
