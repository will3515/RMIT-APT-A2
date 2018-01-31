/**
 * File: vm_coin.c
 * Author: William Cohen
 * Student no.: s3660470
 * Course: Advanced Programming Techniques
 * Year: 2017
 **/
#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

void initCoinsArray(Coin * cashReg) {
    /* ... */
    int i;
    for (i = 0; i < NUM_DENOMS; i++) {
        cashReg[i].denom = i;
        cashReg[i].count = 0;
    }
}

void insertCoins(Coin * cashReg, int * coins) {
    int i;
    for (i = 0; i < NUM_DENOMS; i++) {
        cashReg[i].count += coins[i];
    } 
}

void removeCoins(Coin * cashReg, int * coins) {
    int i;
    for (i = 0; i < NUM_DENOMS; i++) {
        cashReg[i].count -= coins[i];
    } 
}

void coinsToString(char * string, int * coins) {
    int i;
    char multi[MULTIPLICITY_BUFFER_SIZE];
    strcpy(string, " ");
    for (i = 0; i < NUM_DENOMS; i++) {
        if (coins[i] == 0) continue;
        if (coins[i] > 1) {
            sprintf(multi, "%dx", coins[i]);
            strcat(string, multi);
        }
        switch (i) {
            case FIVE_CENTS:
                strcat(string, "5c ");
                break;
            case TEN_CENTS:
                strcat(string, "10c ");
                break;
            case TWENTY_CENTS:
                strcat(string, "20c ");
                break;
            case FIFTY_CENTS:
                strcat(string, "50c ");
                break;
            case ONE_DOLLAR:
                strcat(string, "$1 ");
                break;
            case TWO_DOLLARS:
                strcat(string, "$2 ");
                break;
            case FIVE_DOLLARS:
                strcat(string, "$5 ");
                break;
            case TEN_DOLLARS:
                strcat(string, "$10 ");
                break;
        }
    }
}


Denomination getCoinDenom(Coin * cashReg, int amount) {
    switch (amount) {
        case 1000:
            return TEN_DOLLARS;
        case 500:
            return FIVE_DOLLARS;
        case 200:
            return TWO_DOLLARS;
        case 100:
            return ONE_DOLLAR;
        case 50:
            return FIFTY_CENTS;
        case 20:
            return TWENTY_CENTS;
        case 10:
            return TEN_CENTS;
        case 5:
            return FIVE_CENTS;
    }
    return -1;
}

unsigned getCoinValue(Denomination denom) {
    switch (denom) {
        case FIVE_CENTS:
            return 5;
        case TEN_CENTS:
            return 10;
        case TWENTY_CENTS:
            return 20;
        case FIFTY_CENTS:
            return 50;
        case ONE_DOLLAR:
            return 100;
        case TWO_DOLLARS:
            return 200;
        case FIVE_DOLLARS:
            return 500;
        case TEN_DOLLARS:
            return 1000;
    }
    return 0;
}

void printCoins(Coin * cashReg) {
    printf("%-12s | Count\n", "Denomination");
    printf("-------------+--------\n");
    printf("%-12s | %u\n", "5 cents", cashReg[FIVE_CENTS].count);
    printf("%-12s | %u\n", "10 cents", cashReg[TEN_CENTS].count);
    printf("%-12s | %u\n", "20 cents", cashReg[TWENTY_CENTS].count);
    printf("%-12s | %u\n", "50 cents", cashReg[FIFTY_CENTS].count);
    printf("%-12s | %u\n", "1 dollar", cashReg[ONE_DOLLAR].count);
    printf("%-12s | %u\n", "2 dollar", cashReg[TWO_DOLLARS].count);
    printf("%-12s | %u\n", "5 dollar", cashReg[FIVE_DOLLARS].count);
    printf("%-12s | %u\n", "10 dollar", cashReg[TEN_DOLLARS].count);
    printf("\n\n");
}

Boolean calculateChange(Coin * cashReg, int * change, int amount) {
    int i;
    unsigned value;

    /* Everything's already calculated. Return */
    if (amount == 0) return TRUE;

    /* Run through each denomination, make deductions to whats owed */
    for (i = TEN_DOLLARS; i >= 0; i--) {
        if (cashReg[i].count != 0) {
            if ((value = getCoinValue(i)) <= amount) {
                /* Increment change vector at that denomination */
                change[i]++;
                /* Decrement amount of change in the register */
                cashReg[i].count--;
                /* Recursively continue the calculation */
                return (calculateChange(cashReg, change, amount - value));
            }
        }
    }

    /* If we got here, something went wrong. */
    return FALSE;
}

