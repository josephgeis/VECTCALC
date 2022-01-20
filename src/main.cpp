#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <stdio.h>
#include "mvector.h"

#define V_SIZE 7
#define V_DIMENSIONS 3
#define T_SCALE 2
#define T_PADDING 4
#define MAX_INPUT 9

float vectors[V_SIZE][V_DIMENSIONS + 1];
float sum[V_DIMENSIONS + 1];

uint8_t colors[] = {24, 224, 0, 185, 35, 227, 97};
char dimension_letters[] = {'i', 'j', 'k', 'C'};

bool latch2nd = false;
bool latchAlpha = false;

bool isEditing = false;
uint8_t cursorX = 0;
uint8_t cursorY = 0;
uint8_t cursorInput = 0;
char calc_input[MAX_INPUT];

void redrawScreen();
void redrawEditor();

int main(void) {
    // Init vectors
    init_vectors(V_SIZE, V_DIMENSIONS, &vectors[0][0], 0);
    sum[V_DIMENSIONS] = 1;

    // Init graphics
    gfx_Begin();
    gfx_SetTextScale(1, T_SCALE);

    kb_EnableOnLatch();

    redrawScreen();

    uint8_t key;
    bool loop = true;
    while (loop) {
        key = os_GetCSC();
        if (key == sk_Mode) {
            loop = false;
            continue;
        }
        real_t value = os_FloatToReal(0);
        if (isEditing) {
            switch (key) {
                case sk_Enter:
                    isEditing = !isEditing;
                    if (cursorInput > 0) {
                        value = os_StrToReal(calc_input, reinterpret_cast<char **>(calc_input[cursorInput - 1]));
                        vectors[cursorY][cursorX] = os_RealToFloat(&value);
                        add_vectors(V_SIZE, V_DIMENSIONS, &vectors[0][0], &sum[0], sum[V_DIMENSIONS]);
                        while (cursorInput > 0) {
                            calc_input[cursorInput - 1] = 0;
                            cursorInput--;
                        }
                        cursorInput = 0;
                    }
                    redrawScreen();
                    break;
                case sk_Clear:
                    while (cursorInput > 0) {
                        calc_input[cursorInput - 1] = 0;
                        cursorInput--;
                    }
                    cursorInput = 0;
                    redrawEditor();
                    break;
                case sk_Del:
                    if (cursorInput > 0) {
                        calc_input[cursorInput - 1] = 0;
                        cursorInput--;
                    }
                    redrawEditor();
                    break;
                case sk_Add:
                    break;
                case sk_Sub:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '-';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_Mul:
                    break;
                case sk_Div:
                    break;
                case sk_0:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '0';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_1:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '1';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_2:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '2';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_3:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '3';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_4:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '4';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_5:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '5';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_6:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '6';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_7:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '7';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_8:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '8';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_9:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '9';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
                case sk_DecPnt:
                    if (cursorInput < MAX_INPUT) {
                        calc_input[cursorInput] = '.';
                        cursorInput++;
                    }
                    redrawEditor();
                    break;
            }
        } else {
            switch (key) {
                case sk_Mode:
                    loop = false;
                    break;
                case sk_Up:
                    if (isEditing) break;
                    cursorY = cursorY <= 0 ? 0 : cursorY - 1;
                    redrawScreen();
                    break;
                case sk_Down:
                    if (isEditing) break;
                    cursorY = cursorY >= V_SIZE ? V_SIZE : cursorY + 1;
                    redrawScreen();
                    break;
                case sk_Left:
                    if (isEditing) break;
                    cursorX = cursorX <= 0 ? 0 : cursorX - 1;
                    redrawScreen();
                    break;
                case sk_Right:
                    if (isEditing) break;
                    cursorX = cursorX >= V_DIMENSIONS ? V_DIMENSIONS : cursorX + 1;
                    redrawScreen();
                    break;
                case sk_Enter:
                    if (cursorY != V_SIZE || (cursorY == V_SIZE && cursorX == V_DIMENSIONS)) {
                        isEditing = !isEditing;
                        redrawScreen();
                    }
                    break;
            }
        }
    }


    /* End graphics drawing */
    gfx_End();
    os_DelRes();

    return 0;
}

void redrawEditor() {
    float *vector;
    vector = cursorY == V_SIZE ? sum : vectors[cursorY];

    if (isEditing) gfx_SetTextFGColor(24);
    else gfx_SetTextFGColor(0);

    char fstr[80];
    if (cursorY == V_SIZE) sprintf(fstr, "Vs");
    else
        sprintf(fstr, "V%i", cursorY + 1);
    sprintf(fstr, "%s(%c)", fstr, dimension_letters[cursorX]);
    if (isEditing) {
        sprintf(fstr, "%s = %*.*s", fstr, cursorInput, cursorInput, calc_input);
    } else
        sprintf(fstr, "%s = %8f", fstr, vector[cursorX]);

    gfx_SetColor(255);
    gfx_FillRectangle(0, LCD_HEIGHT - (8 * T_SCALE + T_PADDING), LCD_WIDTH, (8 * T_SCALE + T_PADDING));
    gfx_PrintStringXY(fstr, 0 + T_PADDING, LCD_HEIGHT - (8 * T_SCALE + T_PADDING));
}

void redrawScreen() {
    gfx_FillScreen(0xFF);
    gfx_SetColor(255);


    // Draw vectors
    for (int i = 0; i < V_SIZE; ++i) {
        char fstr[80];
        if (i == cursorY) {
            gfx_SetTextBGColor(colors[i % 7]);
            gfx_SetTextFGColor(255);
        } else {
            gfx_SetTextFGColor(colors[i % 7]);
            gfx_SetTextBGColor(255);
        }


        sprintf(fstr, "V%i = <", i + 1);
        for (int j = 0; j < V_DIMENSIONS; ++j) {
            sprintf(fstr, "%s%s%.2f", fstr, (j != 0 ? ", " : ""), vectors[i][j]);
        }
        sprintf(fstr, "%s> * %.2f", fstr, vectors[i][V_DIMENSIONS]);

        gfx_SetColor(255);
//        gfx_FillRectangle(0, (LCD_HEIGHT + (8 * T_SCALE * (i)) + T_PADDING), LCD_WIDTH, LCD_HEIGHT + (8 * T_SCALE) + T_PADDING);

        gfx_PrintStringXY(fstr,
                          0 + T_PADDING,
                          LCD_HEIGHT + (8 * T_SCALE * (i + 1)) + T_PADDING);

    }

    {
        char fstr[80];
        if (cursorY == V_SIZE) {
            gfx_SetTextBGColor(colors[0]);
            gfx_SetTextFGColor(255);
        } else {
            gfx_SetTextFGColor(colors[0]);
            gfx_SetTextBGColor(255);
        }


        sprintf(fstr, "Vs = <");
        for (int j = 0; j < V_DIMENSIONS; ++j) {
            sprintf(fstr, "%s%s%.2f", fstr, (j != 0 ? ", " : ""), sum[j]);
        }
        sprintf(fstr, "%s> * %.2f", fstr, sum[V_DIMENSIONS]);

        gfx_SetColor(255);
//        gfx_FillRectangle(0, (LCD_HEIGHT + (8 * T_SCALE * (V_SIZE + 1)) + T_PADDING), LCD_WIDTH, (8 * T_SCALE) + T_PADDING);

        gfx_PrintStringXY(fstr,
                          0 + T_PADDING,
                          LCD_HEIGHT + (8 * T_SCALE * (V_SIZE + 1)) + T_PADDING);
    }

    // Draw field select
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);

    gfx_SetTextXY(0 + T_PADDING, gfx_GetTextY() + (8 * T_SCALE * 2));
    for (int i = 0; i <= V_DIMENSIONS; ++i) {
        char fstr[4];
        if (i == cursorX) {
            gfx_SetTextBGColor(0);
            gfx_SetTextFGColor(255);
        } else {
            gfx_SetTextFGColor(0);
            gfx_SetTextBGColor(255);
        }

        sprintf(fstr, " %c ", dimension_letters[i]);
        gfx_PrintString(fstr);

        gfx_SetTextBGColor(255);
        gfx_SetTextFGColor(0);
        gfx_PrintString(" ");
    }

    redrawEditor();
}
