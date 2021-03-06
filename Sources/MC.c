/*
 * Stepper.c
 *
 *  Created on: Mar 6, 2012
 *      Author: 
 */

#include "MC.h"
#include "IO_Map.h"
/******************************************************************************
* Global variables
******************************************************************************/
MOTOR Motor[MAX_MOTOR_NUM];
uint32_t stepperCounter = 0;

/******************************************************************************
* Local function prototypes
******************************************************************************/

void MC_InitMotorParams();

/******************************************************************************
* Local variables
******************************************************************************/

//Sinusoidal control signal for the stepper motors
const uint16_t phase_data[] = {
	0,	 //  	0
	25,	//  	1
	49,	//  	2
	74,	//  	3
	98,	//  	4
	123,   //  	5
	147,   //  	6
	172,   //  	7
	196,   //  	8
	220,   //  	9
	245,   //  	10
	269,   //  	11
	293,   //  	12
	318,   //  	13
	342,   //  	14
	366,   //  	15
	390,   //  	16
	414,   //  	17
	438,   //  	18
	462,   //  	19
	486,   //  	20
	510,   //  	21
	533,   //  	22
	557,   //  	23
	581,   //  	24
	604,   //  	25
	627,   //  	26
	651,   //  	27
	674,   //  	28
	697,   //  	29
	720,   //  	30
	743,   //  	31
	765,   //  	32
	788,   //  	33
	810,   //  	34
	833,   //  	35
	855,   //  	36
	877,   //  	37
	899,   //  	38
	921,   //  	39
	943,   //  	40
	964,   //  	41
	986,   //  	42
	1007,  //  	43
	1028,  //  	44
	1049,  //  	45
	1070,  //  	46
	1091,  //  	47
	1111,  //  	48
	1131,  //  	49
	1152,  //  	50
	1172,  //  	51
	1191,  //  	52
	1211,  //  	53
	1230,  //  	54
	1250,  //  	55
	1269,  //  	56
	1288,  //  	57
	1306,  //  	58
	1325,  //  	59
	1343,  //  	60
	1361,  //  	61
	1379,  //  	62
	1397,  //  	63
	1414,  //  	64
	1431,  //  	65
	1448,  //  	66
	1465,  //  	67
	1482,  //  	68
	1498,  //  	69
	1514,  //  	70
	1530,  //  	71
	1546,  //  	72
	1561,  //  	73
	1577,  //  	74
	1592,  //  	75
	1606,  //  	76
	1621,  //  	77
	1635,  //  	78
	1649,  //  	79
	1663,  //  	80
	1676,  //  	81
	1690,  //  	82
	1703,  //  	83
	1715,  //  	84
	1728,  //  	85
	1740,  //  	86
	1752,  //  	87
	1764,  //  	88
	1775,  //  	89
	1786,  //  	90
	1797,  //  	91
	1808,  //  	92
	1818,  //  	93
	1828,  //  	94
	1838,  //  	95
	1848,  //  	96
	1857,  //  	97
	1866,  //  	98
	1875,  //  	99
	1883,  //  	100
	1891,  //  	101
	1899,  //  	102
	1907,  //  	103
	1914,  //  	104
	1921,  //  	105
	1928,  //  	106
	1934,  //  	107
	1940,  //  	108
	1946,  //  	109
	1951,  //  	110
	1957,  //  	111
	1962,  //  	112
	1966,  //  	113
	1971,  //  	114
	1975,  //  	115
	1978,  //  	116
	1982,  //  	117
	1985,  //  	118
	1988,  //  	119
	1990,  //  	120
	1993,  //  	121
	1995,  //  	122
	1996,  //  	123
	1998,  //  	124
	1999,  //  	125
	1999,  //  	126
	2000,  //  	127
	2000,  //  	128
	2000,  //  	129
	1999,  //  	130
	1999,  //  	131
	1998,  //  	132
	1996,  //  	133
	1995,  //  	134
	1993,  //  	135
	1990,  //  	136
	1988,  //  	137
	1985,  //  	138
	1982,  //  	139
	1978,  //  	140
	1975,  //  	141
	1971,  //  	142
	1966,  //  	143
	1962,  //  	144
	1957,  //  	145
	1951,  //  	146
	1946,  //  	147
	1940,  //  	148
	1934,  //  	149
	1928,  //  	150
	1921,  //  	151
	1914,  //  	152
	1907,  //  	153
	1899,  //  	154
	1891,  //  	155
	1883,  //  	156
	1875,  //  	157
	1866,  //  	158
	1857,  //  	159
	1848,  //  	160
	1838,  //  	161
	1828,  //  	162
	1818,  //  	163
	1808,  //  	164
	1797,  //  	165
	1786,  //  	166
	1775,  //  	167
	1764,  //  	168
	1752,  //  	169
	1740,  //  	170
	1728,  //  	171
	1715,  //  	172
	1703,  //  	173
	1690,  //  	174
	1676,  //  	175
	1663,  //  	176
	1649,  //  	177
	1635,  //  	178
	1621,  //  	179
	1606,  //  	180
	1592,  //  	181
	1577,  //  	182
	1561,  //  	183
	1546,  //  	184
	1530,  //  	185
	1514,  //  	186
	1498,  //  	187
	1482,  //  	188
	1465,  //  	189
	1448,  //  	190
	1431,  //  	191
	1414,  //  	192
	1397,  //  	193
	1379,  //  	194
	1361,  //  	195
	1343,  //  	196
	1325,  //  	197
	1306,  //  	198
	1288,  //  	199
	1269,  //  	200
	1250,  //  	201
	1230,  //  	202
	1211,  //  	203
	1191,  //  	204
	1172,  //  	205
	1152,  //  	206
	1131,  //  	207
	1111,  //  	208
	1091,  //  	209
	1070,  //  	210
	1049,  //  	211
	1028,  //  	212
	1007,  //  	213
	986,   //  	214
	964,   //  	215
	943,   //  	216
	921,   //  	217
	899,   //  	218
	877,   //  	219
	855,   //  	220
	833,   //  	221
	810,   //  	222
	788,   //  	223
	765,   //  	224
	743,   //  	225
	720,   //  	226
	697,   //  	227
	674,   //  	228
	651,   //  	229
	627,   //  	230
	604,   //  	231
	581,   //  	232
	557,   //  	233
	533,   //  	234
	510,   //  	235
	486,   //  	236
	462,   //  	237
	438,   //  	238
	414,   //  	239
	390,   //  	240
	366,   //  	241
	342,   //  	242
	318,   //  	243
	293,   //  	244
	269,   //  	245
	245,   //  	246
	220,   //  	247
	196,   //  	248
	172,   //  	249
	147,   //  	250
	123,   //  	251
	98,	//  	252
	74,	//  	253
	49,	//  	254
	25,	//  	255
	0,	 //  	256
	32793, //  	257
	32817, //  	258
	32842, //  	259
	32866, //  	260
	32891, //  	261
	32915, //  	262
	32940, //  	263
	32964, //  	264
	32988, //  	265
	33013, //  	266
	33037, //  	267
	33061, //  	268
	33086, //  	269
	33110, //  	270
	33134, //  	271
	33158, //  	272
	33182, //  	273
	33206, //  	274
	33230, //  	275
	33254, //  	276
	33278, //  	277
	33301, //  	278
	33325, //  	279
	33349, //  	280
	33372, //  	281
	33395, //  	282
	33419, //  	283
	33442, //  	284
	33465, //  	285
	33488, //  	286
	33511, //  	287
	33533, //  	288
	33556, //  	289
	33578, //  	290
	33601, //  	291
	33623, //  	292
	33645, //  	293
	33667, //  	294
	33689, //  	295
	33711, //  	296
	33732, //  	297
	33754, //  	298
	33775, //  	299
	33796, //  	300
	33817, //  	301
	33838, //  	302
	33859, //  	303
	33879, //  	304
	33899, //  	305
	33920, //  	306
	33940, //  	307
	33959, //  	308
	33979, //  	309
	33998, //  	310
	34018, //  	311
	34037, //  	312
	34056, //  	313
	34074, //  	314
	34093, //  	315
	34111, //  	316
	34129, //  	317
	34147, //  	318
	34165, //  	319
	34182, //  	320
	34199, //  	321
	34216, //  	322
	34233, //  	323
	34250, //  	324
	34266, //  	325
	34282, //  	326
	34298, //  	327
	34314, //  	328
	34329, //  	329
	34345, //  	330
	34360, //  	331
	34374, //  	332
	34389, //  	333
	34403, //  	334
	34417, //  	335
	34431, //  	336
	34444, //  	337
	34458, //  	338
	34471, //  	339
	34483, //  	340
	34496, //  	341
	34508, //  	342
	34520, //  	343
	34532, //  	344
	34543, //  	345
	34554, //  	346
	34565, //  	347
	34576, //  	348
	34586, //  	349
	34596, //  	350
	34606, //  	351
	34616, //  	352
	34625, //  	353
	34634, //  	354
	34643, //  	355
	34651, //  	356
	34659, //  	357
	34667, //  	358
	34675, //  	359
	34682, //  	360
	34689, //  	361
	34696, //  	362
	34702, //  	363
	34708, //  	364
	34714, //  	365
	34719, //  	366
	34725, //  	367
	34730, //  	368
	34734, //  	369
	34739, //  	370
	34743, //  	371
	34746, //  	372
	34750, //  	373
	34753, //  	374
	34756, //  	375
	34758, //  	376
	34761, //  	377
	34763, //  	378
	34764, //  	379
	34766, //  	380
	34767, //  	381
	34767, //  	382
	34768, //  	383
	34768, //  	384
	34768, //  	385
	34767, //  	386
	34767, //  	387
	34766, //  	388
	34764, //  	389
	34763, //  	390
	34761, //  	391
	34758, //  	392
	34756, //  	393
	34753, //  	394
	34750, //  	395
	34746, //  	396
	34743, //  	397
	34739, //  	398
	34734, //  	399
	34730, //  	400
	34725, //  	401
	34719, //  	402
	34714, //  	403
	34708, //  	404
	34702, //  	405
	34696, //  	406
	34689, //  	407
	34682, //  	408
	34675, //  	409
	34667, //  	410
	34659, //  	411
	34651, //  	412
	34643, //  	413
	34634, //  	414
	34625, //  	415
	34616, //  	416
	34606, //  	417
	34596, //  	418
	34586, //  	419
	34576, //  	420
	34565, //  	421
	34554, //  	422
	34543, //  	423
	34532, //  	424
	34520, //  	425
	34508, //  	426
	34496, //  	427
	34483, //  	428
	34471, //  	429
	34458, //  	430
	34444, //  	431
	34431, //  	432
	34417, //  	433
	34403, //  	434
	34389, //  	435
	34374, //  	436
	34360, //  	437
	34345, //  	438
	34329, //  	439
	34314, //  	440
	34298, //  	441
	34282, //  	442
	34266, //  	443
	34250, //  	444
	34233, //  	445
	34216, //  	446
	34199, //  	447
	34182, //  	448
	34165, //  	449
	34147, //  	450
	34129, //  	451
	34111, //  	452
	34093, //  	453
	34074, //  	454
	34056, //  	455
	34037, //  	456
	34018, //  	457
	33998, //  	458
	33979, //  	459
	33959, //  	460
	33940, //  	461
	33920, //  	462
	33899, //  	463
	33879, //  	464
	33859, //  	465
	33838, //  	466
	33817, //  	467
	33796, //  	468
	33775, //  	469
	33754, //  	470
	33732, //  	471
	33711, //  	472
	33689, //  	473
	33667, //  	474
	33645, //  	475
	33623, //  	476
	33601, //  	477
	33578, //  	478
	33556, //  	479
	33533, //  	480
	33511, //  	481
	33488, //  	482
	33465, //  	483
	33442, //  	484
	33419, //  	485
	33395, //  	486
	33372, //  	487
	33349, //  	488
	33325, //  	489
	33301, //  	490
	33278, //  	491
	33254, //  	492
	33230, //  	493
	33206, //  	494
	33182, //  	495
	33158, //  	496
	33134, //  	497
	33110, //  	498
	33086, //  	499
	33061, //  	500
	33037, //  	501
	33013, //  	502
	32988, //  	503
	32964, //  	504
	32940, //  	505
	32915, //  	506
	32891, //  	507
	32866, //  	508
	32842, //  	509
	32817, //  	510
	32793  //  	511
};

/******************************************************************************
* Local functions
* @brief    MC_InitMotorParams  Initializes the Motor Controller Parameters
* @param    none
* @return   none
* 
******************************************************************************/

void MC_InitMotorParams()
{
	uint8_t i = 0;

	for (i = 0; i < MAX_MOTOR_NUM; i++)
	{
		Motor[i].ptrA = 0;
		Motor[i].ptrB = 85;
		Motor[i].dir = 0;
		Motor[i].pos = 0;
		Motor[i].stopped = 1;
		Motor[i].desPos = 0;
	}
} //MC_InitMotorParams

/******************************************************************************
* Global functions
* 
* @brief    MC_StepperStopped returns 1 if the motor is stopped, else 0; 
* 			MC_GetMotorPosition returns the motor actual position;
* @param    uint8_t idx 
* @return   uint8_t Motor[idx].stopped; uint16_t Motor[idx].pos
*
******************************************************************************/

uint8_t MC_StepperStopped(uint8_t idx)
{
	return Motor[idx].stopped;
}

void MC_SetMotorPosition(uint8_t idx, uint16_t dp)
{
	Motor[idx].desPos = dp;
}

uint16_t MC_GetMotorPosition(uint8_t idx)
{
	return Motor[idx].pos;
}

void MC_SetMotorSpeed(uint8_t idx, uint8_t s)
{
	Motor[idx].speed = s;
}

/*******************************************************************************
*
* @brief    MC_Init  Initializes the Motor Controller Module
* @param    none
* @return   none
*
********************************************************************************/

void MC_Init()
{
	MC_InitMotorParams();

	MCCTL0_DITH = 1;	//Enable Dithering
	MCCTL0_MCPRE = 0x1; //MC Clock = FBUS/2^(MCPRE)^= FBUS/1 = 32/1 = 32 MHz
	MCPER = 0x07FF;		//Set PWM period

	//MOTOR 0
	MCCC0_MCOM = 0x3; //Dual full-H bridge
	MCCC0_MCAM = 0x3; //PWM center alligned
	MCCC1_MCOM = 0x3; //Dual full-H bridge
	MCCC1_MCAM = 0x3; //PWM center alligned
					  /*
	//MOTOR 1
	MCCC2_MCOM = 0x3;						//Dual full-H bridge
	MCCC2_MCAM = 0x3;						//PWM center alligned
	MCCC3_MCOM = 0x3;						//Dual full-H bridge
	MCCC3_MCAM = 0x3;						//PWM center alligned
	
	//MOTOR 2
	MCCC4_MCOM = 0x3;						//Dual full-H bridge
	MCCC4_MCAM = 0x3;						//PWM center alligned
	MCCC5_MCOM = 0x3;						//Dual full-H bridge
	MCCC5_MCAM = 0x3;						//PWM center alligned
	
	//MOTOR 3
	MCCC6_MCOM = 0x3;						//Dual full-H bridge
	MCCC6_MCAM = 0x3;						//PWM center alligned
	MCCC7_MCOM = 0x3;						//Dual full-H bridge
	MCCC7_MCAM = 0x3;						//PWM center alligned	

	*/
	MCDC0 = phase_data[Motor[0].ptrA];
	MCDC1 = phase_data[Motor[0].ptrB];
	//  MCDC2 = phase_data[Motor[1].ptrA];
	//  MCDC3 = phase_data[Motor[1].ptrB];
	//  MCDC4 = phase_data[Motor[2].ptrA];
	//  MCDC5 = phase_data[Motor[2].ptrB];
	//  MCDC6 = phase_data[Motor[3].ptrA];
	//  MCDC7 = phase_data[Motor[3].ptrB];
	TIM0TIOS_IOS0 = 1;						// TIMCH0 as output compare
	TIM0TIE_C0I = 1;						// TIMCH0 interrupt enable
	TIM0TFLG1_C0F = 1;						// Clear interrupt flag
	
	TIM0TC0 = 1200; 						// Interrupt period
	
	TIM0TSCR2_PR = 0;						// Clock Prescaler FBUS/2^PR		
	TIM0TSCR1_PRNT = 1;						// Precision Timer enable
	TIM0TSCR1_TEN = 1;						// TIM enable
} //MC_Init

/*******************************************************************************
*
* @brief    Move_Stepper For all the motors (0-3) every time the module motor speed of stepper 
* 			counter becomes 0 and the motor is not stopped the motor moves towards the desired 
* 			direction and counts up or down depending on the direction it is moving, 
* 			then it charges the values on the respective Motor Controller Duty Cycle Register
* @param    uint8_t idx
* @return   none
*
********************************************************************************/

void Move_Stepper()
{
	uint8_t idx = 0;

	stepperCounter++;

	for (idx = 0; idx < MAX_MOTOR_NUM; idx++)
	{

		if (Motor[idx].rtz == 1)
		{

			if ((stepperCounter % Motor[idx].speed) == 0)
			{
				if (Motor[idx].desPos > Motor[idx].pos)
				{
					Motor[idx].dir = 1;
					Motor[idx].stopped = 0;
				}
				else if (Motor[idx].desPos < Motor[idx].pos)
				{
					Motor[idx].dir = 0;
					Motor[idx].stopped = 0;
				}
				else
				{
					Motor[idx].stopped = 1;
				}

				if (!Motor[idx].stopped)
				{

					if (Motor[idx].dir == 0)
					{
						Motor[idx].pos--;

						Motor[idx].ptrA++;
						Motor[idx].ptrB++;

						if (Motor[idx].ptrA == 512)
						{
							Motor[idx].ptrA = 0;
						}
						if (Motor[idx].ptrB == 512)
						{
							Motor[idx].ptrB = 0;
						}
					}
					else
					{
						Motor[idx].pos++;

						Motor[idx].ptrA--;
						Motor[idx].ptrB--;

						if (Motor[idx].ptrA == 0xFFFF)
						{
							Motor[idx].ptrA = 511;
						}
						if (Motor[idx].ptrB == 0xFFFF)
						{
							Motor[idx].ptrB = 511;
						}
					}
				}
			}
		}
	}
	MCDC0 = phase_data[Motor[0].ptrA]; //Motor Controller Duty Cycle Registers
	MCDC1 = phase_data[Motor[0].ptrB];
	// MCDC2 = phase_data[Motor[1].ptrA];
	// MCDC3 = phase_data[Motor[1].ptrB];
	// MCDC4 = phase_data[Motor[2].ptrA];
	// MCDC5 = phase_data[Motor[2].ptrB];
	// MCDC6 = phase_data[Motor[3].ptrA];
	// MCDC7 = phase_data[Motor[3].ptrB];
} //Move_Stepper
