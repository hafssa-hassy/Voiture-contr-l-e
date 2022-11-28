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

void task_LED(void *pvParameters);
void read_speed(void *pvParameters);
void update_motor(void *pvParameters);
void update_steering(void* pvParameters);
void task_Trajectory(void *pvParameters);
void task_Camera(void *pvParameters);
void task_Camera_Display(void *pvParameters);
void task_Debug(void* pvParameters);

/*
 * @brief   Application entry point.
 */
int main(void) {
  /*
    Fonctions d'initialisation des différentes entrées/sorties
    et des protocoles de communication
  */
  BOARD_init_all();

  PRINTF("\n\r========== Hello World CCTR SEOC ==========\n\r");
  PRINTF("============ Projet du groupe 8 ===========\n\r");

  // Tâche des LEDs (ne fait pas grand chose)
  xTaskCreate(task_LED, "Task_LED", configMINIMAL_STACK_SIZE + 100, NULL, 4, NULL);

  // Tâche principale
  xTaskCreate(task_Trajectory, "Trajectory", configMINIMAL_STACK_SIZE +100, NULL, 2, NULL);

  // Affichages (désactivés) :
  #if 0
  xTaskCreate(task_Camera_Display, "Camera display", configMINIMAL_STACK_SIZE +100, NULL, 6, NULL);
  xTaskCreate(task_Debug, "Debug", configMINIMAL_STACK_SIZE +100, NULL, 5, NULL);
  #endif

  // Prise d'image (double intégration) :
  xTaskCreate(task_Camera, "Camera", configMINIMAL_STACK_SIZE +100, NULL, 0, NULL);

  // Démarrage
  vTaskStartScheduler();
  for (;;);
  return 0 ;
}

/**
 * Tache périodique pour faire clignoter la LED
 */
void task_LED(void *pvParameters) {
	TickType_t previousWake = xTaskGetTickCount();

	LED_GREEN_TOGGLE();
	LED_BLUE_TOGGLE();
	LED_RED_TOGGLE();
	for (;;)
	{
		// Ne fait plus rien, parce la LED est éblouissante
		vTaskDelayUntil(&previousWake, Ms(2000));
	}
}
