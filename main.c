#include "project.h"
#include <stdio.h>

#define LOW (0)
#define HIGH (1)
#define NUM_ACTIONS_IN_SEQUENCE (6)

void delay();
void report_incorrect();
void report_correct();
int check();
int next_seq(int *seq, int size, int max_number);

int main(void)
{
    CyGlobalIntEnable;
    
    UART_Start();
    
    Pin_OK_Write(HIGH);
    Pin_ERR_Write(HIGH);

    for(;;)
    {
start_outer_loop:;
        uint8_t cur_d = 0;
        int cur_c = 1;
        D_Reg_Write(0b00000000);
        C_Reg_Write(0b0);
        delay();
        C_Reg_Write(0b1);
        delay();
        if (!check()) {
            report_incorrect();
        }
        int seq_of_actions[NUM_ACTIONS_IN_SEQUENCE] = {0};
        do {
            for (int num_action = 0; num_action < NUM_ACTIONS_IN_SEQUENCE; num_action++) {
                int action_code = seq_of_actions[num_action];
                if (action_code == 8) {
                    cur_c = !cur_c;
                } else {
                    cur_d = cur_d ^ (0b1 << action_code);
                }
                D_Reg_Write(cur_d);
                C_Reg_Write(cur_c);
                delay();
                
                
                if (!check()) {
                    report_incorrect();
                    goto start_outer_loop;
                }
            }
        } while (next_seq(seq_of_actions, NUM_ACTIONS_IN_SEQUENCE, 8));
        report_correct();
    }
}

void delay() 
{
    CyDelayCycles(1);
}

void report_incorrect()
{
    Pin_ERR_Write(LOW);
    CyDelay(5000);
    Pin_ERR_Write(HIGH);
}

void report_correct()
{
    Pin_OK_Write(LOW);
    CyDelay(5000);
    Pin_OK_Write(HIGH);
}

int check()
{
    return (Eq_Reg_Read() & 0b1) == 0b1;
}

int next_seq(int *seq, int size, int max_number) {
    if (size == 0) {
        return 0;
    }
    if (!next_seq(seq + 1, size - 1, max_number)) {
        if (seq[0] == max_number) {
            seq[0] = 0;
            return 0;
        } else {
            seq[0]++;
            return 1;
        }
    }
    return 1;
}
