/*
  Auteur :
  Stéphane MANCINI
  Grenoble INP
*/

/**
 * @file    main_SEOC_CCTR_base.c
 * @brief   Application entry point.
 */
#include "CCTR.h"


void task_LED_R(void *pvParameters);
#define task_LED_R_PRIORITY 0

void task_LED_GB(void *pvParameters);
#define task_LED_GB_PRIORITY 0

/*
 * @brief   Application entry point.
 */
int main(void) {
  /*
    Fonctions d'initialisation des différentes entrées/sorties
    et des protocoles de communication
  */
  BOARD_init_all();
  PRINTF("Hello World CCTR SEOC Test\n\r");
  /* Création d'une tache avec pile statique, priorité statique */
  xTaskCreate(task_LED_R, "Task_LED_R",
              configMINIMAL_STACK_SIZE + 100, NULL,
              task_LED_R_PRIORITY, NULL);
  xTaskCreate(task_LED, "Task_LED_GB",
              configMINIMAL_STACK_SIZE + 100, NULL,
              task_LED_GB_PRIORITY, NULL);
	
  vTaskStartScheduler();
  /* Enter an infinite loop, but should never arrive here */
  for (;;)
    ;
  return 0 ;
}

/*
 * Tache périodique pour faire clignoter la LED R
 */

void task_LED_R(void *pvParameters) {
  const TickType_t xDelay= Ms(100);
  led_cpt=0;

  for (;;)
	{
      LED_RED_TOGGLE();

      vTaskDelay(xDelay);
	}
}

/*
 * Tache périodique pour faire clignoter les LED GB
 */

void task_LED_GB(void *pvParameters) {
  const TickType_t xDelay= Ms(317);
  led_cpt=0;

  for (;;)
	{
      LED_GREEN_TOGGLE();
      LED_BLUE_TOGGLE();

      vTaskDelay(xDelay);
	}
}
