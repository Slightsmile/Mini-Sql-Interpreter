#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "csv_utils.h"

static int find_column_index(char *headers[], int count, const char *col) {
    for (int i = 0; i < count; i++) {
        if (strcmp(headers[i], col) == 0)
            return i;
    }
    return -1;
}

static bool check_condition(const char *value, const char *op, const char *condVal) {
    // Numeric comparison if condVal is a number
    bool isNumeric = true;
    for (int i = 0; condVal[i]; i++) {
        if (!isdigit(condVal[i])) { isNumeric = false; break; }
    }

    if (isNumeric) {
        int val = atoi(value);
        int num = atoi(condVal);
        if (strcmp(op, ">") == 0) return val > num;
        if (strcmp(op, "<") == 0) return val < num;
        if (strcmp(op, "=") == 0) return val == num;
    } else {
        if (strcmp(op, "=") == 0) return strcmp(value, condVal) == 0;
    }
    return false;
}

void execute_query(char *columns, char *table, char *condition) {
    FILE *fp = fopen(table, "r");
    if (!fp) {
        perror("Cannot open CSV file");
        return;
    }

    char line[1024];
    char *headers[100];
    int colCount = 0;

    // Read header
    fgets(line, sizeof(line), fp);
    char *token = strtok(line, ",\n");
    while (token) {
        headers[colCount++] = strdup(token);
        token = strtok(NULL, ",\n");
    }

    // Parse selected columns
    char *selectedCols[50];
    int selCount = 0;
    token = strtok(columns, ",");
    while (token) {
        selectedCols[selCount++] = strdup(token);
        token = strtok(NULL, ",");
    }

    // Print header of selected columns
    for (int i = 0; i < selCount; i++) {
        printf("%s", selectedCols[i]);
        if (i < selCount - 1) printf(",");
    }
    printf("\n");

    // Parse condition if exists
    char condCol[50] = "", op[3] = "", condVal[100] = "";
    bool hasCondition = false;
    if (condition) {
        if (sscanf(condition, "%49[^><=]%2[><=]%99s", condCol, op, condVal) == 3) {
            hasCondition = true;
        }
    }

    // Process rows
    while (fgets(line, sizeof(line), fp)) {
        char *rowVals[100];
        int i = 0;
        token = strtok(line, ",\n");
        while (token && i < colCount) {
            rowVals[i++] = token;
            token = strtok(NULL, ",\n");
        }

        // Apply WHERE condition
        if (hasCondition) {
            int condIndex = find_column_index(headers, colCount, condCol);
            if (condIndex == -1 || condIndex >= i) continue;
            if (!check_condition(rowVals[condIndex], op, condVal)) continue;
        }

        // Print selected columns only
        for (int j = 0; j < selCount; j++) {
            int idx = find_column_index(headers, colCount, selectedCols[j]);
            if (idx != -1 && idx < i) printf("%s", rowVals[idx]);
            if (j < selCount - 1) printf(",");
        }
        printf("\n");
    }

    fclose(fp);
}
