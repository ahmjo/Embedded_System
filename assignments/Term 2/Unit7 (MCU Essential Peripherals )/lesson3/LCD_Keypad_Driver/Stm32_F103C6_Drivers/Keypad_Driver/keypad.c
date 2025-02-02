#include "keypad.h"

int Key_padRow[] = { R0, R1, R2, R3 };
int Key_padCol[] = { C0, C1, C2, C3 };

void delay_mss(uint32_t time) {
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++);
}

// Initialize Keypad
void Keypad_init() {
    GPIO_PinConfig_t PinCfg;

    // Configure Rows (R0 - R3) Output
    for (int i = 0; i < 4; i++) {
        PinCfg.GPIO_PinNumber = Key_padRow[i];
        PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
        PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
        MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
    }

    // Configure Columns (C0 - C3) Input Pull-up
    for (int i = 0; i < 4; i++) {
        PinCfg.GPIO_PinNumber = Key_padCol[i];
        PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
        MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
    }

    // Set all rows HIGH initially
    for (int i = 0; i < 4; i++) {
        MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padRow[i], GPIO_PIN_SET);
    }
}

char Keypad_getkey() {
    int row, col;

    for (row = 0; row < 4; row++) {
        // Set all rows HIGH
        for (int i = 0; i < 4; i++) {
            MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padRow[i], GPIO_PIN_SET);
        }

        // Set the current row LOW
        MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padRow[row], GPIO_PIN_RESET);

        // Check which column is LOW (button pressed)
        for (col = 0; col < 4; col++) {
            if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padCol[col]) == GPIO_PIN_RESET) {
                delay_mss(20);

                // Wait for key release
                while (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padCol[col]) == GPIO_PIN_RESET);

                char keypad_map[4][4] = {
                    {'7', '8', '9', '/'},
                    {'4', '5', '6', '*'},
                    {'1', '2', '3', '-'},
                    {'?', '0', '=', '+'}
                };

                return keypad_map[row][col];
            }
        }
    }
    return 'A';
}
