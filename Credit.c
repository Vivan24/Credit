#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to input credit card number
    long card = get_long("\nEnter credit card number here: ");

    // Initializes variables
    long eod = 100;
    long eod_total = 0;
    long eod_value = 0;

    // Finds every other digit (E.O.D.) of card number and multiplies by two. Product is added to sum
    for (eod = 100; card % (eod / 100) <= (card / 100); eod = eod * 100) {
        eod_value = (card % eod - card % (eod / 10)) / (eod / 10); // Finds E.O.D of card number

        if (eod_value > 4) {
            eod_total = eod_total + ((eod_value * 2 % 100 - (eod_value * 2 % 10)) / 10 + (eod_value * 2 % 10));
        } else {
            eod_total = eod_total + eod_value * 2;
        }
    }

    // Gets remainging digits (which weren't multiplied) and adds to sum
    for (eod = 10; card % (eod / 10) < card; eod = eod * 100) {
        eod_value = (card % eod - card % (eod / 10)) / (eod / 10);
        eod_total = eod_total + eod_value;
    }

    // If checksum is valid, then procceeds with identifying card type
    if (eod_total % 10 != 0) {
        printf("INVALID\n");
    } else {

        // Determines length of card
        long card_len = 0;
        long i = 0;
        for (i = 10; card % (i / 10) != card; i = i * 10) {
            card_len = card_len  + 1;
        }

        // Checks if card is American Express
        long d_15 = (card % 1000000000000000 - card % 10000000000000) / 10000000000000;
        if ((d_15 == 34 || d_15 == 37) && card_len == 15) {
            printf("AMEX\n");
        } else {
            // Checks if card is Mastercard
            long d_16 = (card % 10000000000000000 - card % 100000000000000) / 100000000000000;
            if ((d_16 == 51 || d_16 == 52 || d_16 == 53 || d_16 == 54 || d_16 == 55) && card_len == 16) {
                printf("MASTERCARD\n");
            } else {
                // Checks if card is Visa
                long d_13 = (card % 10000000000000 - card % 1000000000000) / 1000000000000;
                long d_16_1 = (card % 10000000000000000 - card % 1000000000000000) / 1000000000000000;
                if ((d_13 == 4 || d_16_1 == 4) && (card_len == 13 || card_len == 16)) {
                    printf("VISA\n");
                } else {
                    // Otherwise, card is invalid
                    printf("INVALID\n");
                }
            }
        }
    }
}