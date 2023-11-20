/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include "lcd.h"
#include "pomo.h"
#include "speaker.h"
#include "stdbool.h"
#include "button.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#ifndef uint
#define uint unsigned int
#endif
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


int DEFAULT = 0;
int POMO = 1;
int TIME_CHANGE = 2;
int POMO_CHANGE = 3;

bool EDITING_HR = true;
int RANDOM_COUNTER = 0;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */



  // Lcd_PortType ports[] = { D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port };
	Lcd_PortType ports[] = { GPIOC, GPIOB, GPIOA, GPIOA };
	// Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
	Lcd_PinType pins[] = {GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_6};
	Lcd_HandleTypeDef lcd;
	// Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
	lcd = Lcd_create(ports, pins, GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, LCD_4_BIT_MODE);


	// ----------------------------------- values

  // turn on pwm
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  // don't let value = 255 (otherwise is 100% of the duty cycle + we just get 0, 1 // high or low

  // ----------------------------------- values


  	set_speaker_state(false);

	// create clock object
  	  // sec, min, hrr, day, mon, year
  	// int clock[6] = {0, 0, 0, 0, 0, 0};
	int clock[6] = {0, 19, 15, 16, NOV, 2023};

	set_clock_time_arr(clock);
	C_START_TIME = HAL_GetTick();


	Lcd_clear(&lcd);


	//TODO - SPEAKER TESTING
	set_alarm(5, 19, 15);

	int MODE = DEFAULT;

	HAL_Delay(1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	PREV_TIME = CURRENT_TIME;
	CURRENT_TIME = HAL_GetTick();
	DELTA_TIME += CURRENT_TIME - PREV_TIME;
	TEMP_DELTA_TIME = CURRENT_TIME - PREV_TIME;

	HAL_Delay(5);

	// update buttons
	update_buttons();

	// clock update
	second_update_clock(CLOCK);


	// alarm update
	{
		set_speaker_state(false);
		if(ALARM[HRR] == CLOCK[HRR] && ALARM[MIN] == CLOCK[MIN]){
			if(CLOCK[SEC] - ALARM[SEC] < 15){
				// 15s interval satisfied
				set_speaker_state(true);
			}
		}
	}


	// mode specific updates
	if(MODE == DEFAULT){

		// user input stuff now
		/*
		 *  pomo button = set to pomo mode
		 *  	- pomo to exit
		 *  	- timer to start
		 *  	- up to increase min
		 *  	- down to decrease min
		 *  timer button = change time
		 *  	- pomo exit
		 *  	- timer = change hr / min
		 *  	- up = increase
		 *  	- down = decrease
		 *
		 *
		 *  // could add 2 more features but too lazy
		 *
		 *  up button = (if in special mode = go up by 1)
		 *  down button = (if in special mode = go down by 1)
		 *
		 */

		// display information
		display_default(&lcd);
		// check if alarm mis active
		Lcd_cursor(&lcd, 1, 7);
		Lcd_string(&lcd, (SPEAKER_ACTIVE ? "ON" : "DN"));

		if(HOLD_TIME[1] > 3000){
			MODE = TIME_CHANGE;
			Lcd_clear(&lcd);
		}
		if(HOLD_TIME[0] > 3000){
			MODE = POMO_CHANGE;
			HOLD_TIME[0] = 0;
			Lcd_clear(&lcd);
		}




	}else if(MODE == POMO_CHANGE){
		/*
		 *  pomo = exit
		 *  timer = start
		 *  up = increase moin
		 *  down = decrease min
		 *
		 *
		 *
		 *
		 * POMO MODE
		 *
		 *  0123456789
		 * "   POMO MM:SS   "
		 *
		 */

		// exit
		if(HOLD_TIME[0] > 2000){
			HOLD_TIME[0] = 0;
			MODE = DEFAULT;
			RANDOM_COUNTER = 0;
			Lcd_clear(&lcd);
			HAL_Delay(100);
			DELTA_TIME = 0;
		}

		RANDOM_COUNTER+=TEMP_DELTA_TIME;

		// start the pomo
		if(HOLD_TIME[1] > 1000){
			HOLD_TIME[1] = 0;
			MODE = POMO; // exit criteria
			RANDOM_COUNTER = 0;
			HAL_Delay(100);
			Lcd_clear(&lcd);
		}

		// up
		if(HOLD_TIME[2] > 500){
			HOLD_TIME[2] = 0;
			POMO_CLOCK[MIN]++;
		}
		// down
		if(HOLD_TIME[3] > 500){
			HOLD_TIME[3] = 0;
			POMO_CLOCK[MIN]--;
		}
		if(POMO_CLOCK[MIN] < 0) POMO_CLOCK[MIN] = 0;

		// render pomo stuff
		Lcd_cursor(&lcd, 0, 3);
		Lcd_string(&lcd, "POMO");

		if((RANDOM_COUNTER / 1000) % 2 == 0){
			Lcd_cursor(&lcd, 0, 8);
			Lcd_string(&lcd, "__");
		}else{
			Lcd_cursor(&lcd, 0, 8);
			if(POMO_CLOCK[MIN] < 10) {
				Lcd_string(&lcd, "0");
				Lcd_cursor(&lcd, 0, 9);
			}
			Lcd_int(&lcd, POMO_CLOCK[MIN]);
		}
		Lcd_cursor(&lcd, 0, 10);
		Lcd_string(&lcd, ":00");

	}else if(MODE == TIME_CHANGE){
		/*
		 * pomo = exit
		 * timer = change hr/min
		 * up = inc
		 * down = dec
		 *
		 */

		// exit
		if(HOLD_TIME[0] > 2000){
			HOLD_TIME[0] = 0;
			MODE = DEFAULT;
			// reset vars
			RANDOM_COUNTER = 0;
			Lcd_clear(&lcd);
			DELTA_TIME = 0;
			Lcd_clear(&lcd);
			HAL_Delay(100);
		}

		RANDOM_COUNTER += TEMP_DELTA_TIME;
		// if timer sqitch
		if(HOLD_TIME[1] > 2000){
			HOLD_TIME[1] = 0;
			EDITING_HR = !EDITING_HR;
		}

		// if up button
		CLOCK[SEC] = 0;
		if(HOLD_TIME[2] > 500){
			HOLD_TIME[2] = 0;
			HOLD_TIME[2] -= 500;
			// change info
			if(EDITING_HR){
				CLOCK[HRR]++;
			}else{
				CLOCK[MIN]++;
			}
		}
		if(HOLD_TIME[3] > 500){
			HOLD_TIME[3] = 0;
			HOLD_TIME[3] -= 500;
			// chnage
			if(EDITING_HR){
				CLOCK[HRR]--;
			}else{
				CLOCK[MIN]--;
			}
			if(CLOCK[MIN] < 0) CLOCK[MIN] = 0;
		}

		// update stuff
		second_update_clock(CLOCK);
		display_default(&lcd);

		// blink editing blob
		int edit_block = 8;
		if(!EDITING_HR){
			edit_block = 11;
		}
		if((RANDOM_COUNTER / 1000) % 2 == 0){
			Lcd_cursor(&lcd, 0, edit_block);
			Lcd_string(&lcd, "__");
		}


	}else if(MODE == POMO){
		/*
		 *  pomo = exit
		 *  timer = start
		 *  up = increase moin
		 *  down = decrease min
		 *
		 *
		 *
		 *
		 * POMO MODE
		 *
		 *  0123456789
		 * "   POMO MM:SS   "
		 *
		 */
		RANDOM_COUNTER += TEMP_DELTA_TIME;

		pomo_countdown(POMO_CLOCK, &RANDOM_COUNTER);

		if(POMO_ALARM){
			MODE = DEFAULT;
			set_speaker_state(true);
		}


		// display the time
		Lcd_cursor(&lcd, 0, 3);
		Lcd_string(&lcd, "POMO");
		Lcd_cursor(&lcd, 0, 8);
		// output min
		if(POMO_CLOCK[MIN] < 10){
			Lcd_string(&lcd, "0");
			Lcd_cursor(&lcd, 0, 9);
		}
		Lcd_int(&lcd, POMO_CLOCK[MIN]);
		Lcd_cursor(&lcd, 0, 10);
		Lcd_string(&lcd, ":");
		Lcd_cursor(&lcd, 0, 11);
		if(POMO_CLOCK[SEC] < 10){
			Lcd_string(&lcd, "0");
			Lcd_cursor(&lcd, 0, 12);
		}
		Lcd_int(&lcd, POMO_CLOCK[SEC]);

		// exit condition
		if(HOLD_TIME[0] > 3000){
			POMO_CLOCK[MIN] = DEFAULT_POMO_LENGTH;
			POMO_CLOCK[SEC] = 0;
			DELTA_TIME = 0;
			MODE = DEFAULT;
			Lcd_clear(&lcd);
		}


	}

	// pomo stuff
	if(POMO_ALARM) {
		set_speaker_state(true);
		POMO_ALARM_LENGTH += TEMP_DELTA_TIME;
		// length checks
		if(POMO_ALARM_LENGTH > 3000){
			POMO_ALARM = false;
			POMO_ALARM_LENGTH = 0;
			set_speaker_state(false);
		}
	}

//	Lcd_cursor(&lcd, 1, 7);
////	Lcd_int(&lcd, HOLD_TIME[1]);
//	Lcd_string(&lcd, (EDITING_HR ? "YES" : "NO"));
//	Lcd_int(&lcd, TEMP_DELTA_TIME);





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV16;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
