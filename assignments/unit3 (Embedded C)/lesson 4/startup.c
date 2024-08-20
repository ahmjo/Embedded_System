#include "stdint.h"

extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;

extern void main();

void Reset_Handler(){
    uint32_t DATA_SIZE = (unsigned char*)&_E_data - (unsigned char*)&_S_data ;
    unsigned char* P_scr = (unsigned char*)&_E_text ;
    unsigned char* P_dst = (unsigned char*)&_S_data ;
    for(int i=0 ; i< DATA_SIZE ; i++){
        *(unsigned char*) P_dst++=*(unsigned char*) P_scr++;
    }
    
    uint32_t bss_SIZE = (uint32_t*)&_E_bss - (uint32_t*)&_S_bss ;
    P_dst = (unsigned char*)&_S_bss ;
    for(int i=0 ; i< bss_SIZE ; i++){
        *(unsigned char*)P_dst++=(unsigned char)0;
    }

    main();
}

void default_handler(void){
    Reset_Handler();
}

void NMI_Handler() __attribute__((weak, alias("default_handler")));
void H_Fault_handler() __attribute__((weak, alias("default_handler")));

static unsigned long stack_top [256] ; 
void  (* g_p_fn_vectors[]) __attribute__((section(".vectors"))) = {
    (void (*)()) ((unsigned long)stack_top + sizeof(stack_top)),
    &Reset_Handler,
    &NMI_Handler,
    &H_Fault_handler,
};

