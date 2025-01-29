#include "comparator.h"
#include "targets.h"
#include "common.h"

uint8_t medium_speed_set;
COMP_TypeDef* active_COMP = MAIN_COMP;

uint8_t getCompOutputLevel() { return LL_COMP_ReadOutputLevel(MAIN_COMP);}


void maskPhaseInterrupts(){
	EXTI->IMR1 &= ~(EXTI_LINE);
	LL_EXTI_ClearFlag_0_31(EXTI_LINE);
}

void enableCompInterrupts(){
    EXTI->IMR1 |= EXTI_LINE;
}

void changeCompInput() {
	if((average_interval < 400) && medium_speed_set){
	LL_COMP_SetPowerMode(active_COMP, LL_COMP_POWERMODE_HIGHSPEED);
	medium_speed_set = 0;
	}
	if((average_interval > 600) && !medium_speed_set){
	LL_COMP_SetPowerMode(active_COMP, LL_COMP_POWERMODE_MEDIUMSPEED);
	medium_speed_set = 1;
	}
	
	if (step == 1 || step == 4) {   // c floating
		LL_COMP_ConfigInputs(MAIN_COMP, PHASE_C_COMP , COMMON_COMP);
  	}
	if (step == 2 || step == 5) {     // a floating
	LL_COMP_ConfigInputs(MAIN_COMP, PHASE_A_COMP, COMMON_COMP);
	}
	if (step == 3 || step == 6) {      // b floating
    LL_COMP_ConfigInputs(MAIN_COMP, PHASE_B_COMP, COMMON_COMP);
	}
	if (rising){
		  LL_EXTI_DisableRisingTrig_0_31(EXTI_LINE);
		  LL_EXTI_EnableFallingTrig_0_31(EXTI_LINE);
	}else{                          // falling bemf
		  LL_EXTI_EnableRisingTrig_0_31(EXTI_LINE);
		  LL_EXTI_DisableFallingTrig_0_31(EXTI_LINE);
	}
}

