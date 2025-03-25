#ifndef _OLED_FONT_H_
#define _OLED_FONT_H_

#include <Arduino.h>

/*OLED字模库，宽8像素，高16像素*/
const uint8_t OLED_F8x16[][16]=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//  0
	
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
	
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
	
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,
	0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
	
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,
	0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
	
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,
	0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
	
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,
	0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
	
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
	
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,
	0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
	
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,
	0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
	
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,
	0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
	
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,
	0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
	
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,
	0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
	
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
	
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
	
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,
	0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
	
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,
	0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
	
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,
	0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
	
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,
	0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
	
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,
	0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
	
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
	
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,
	0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
	
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
	
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
	
/*	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
	
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
	
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
	
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,
	0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
	
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,
	0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
	
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,
	0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
	
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,
	0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
	
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
	
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,
	0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
	
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
	
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
	
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
	
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,
	0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
	
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
	
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
	
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,
	0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
	
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,
	0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
	
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
	
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,
	0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
	
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
	
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
	
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,
	0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
	
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
	
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
	
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,
	0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
	
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
	
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
	
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,
	0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
	
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,
	0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
	
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,
	0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
	
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
	
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
	
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,
	0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
	
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
	
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,
	0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
	
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
	
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
	
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,
	0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
	
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
	
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
	
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
	
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,
	0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
	
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
	
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,
	0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
	
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
	
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
	
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
	
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,
	0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
	
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,
	0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
	
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,
	0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
	
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
	
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
	
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,
	0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
	
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
	
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
	
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,
	0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
	
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
	
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
	
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
	
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,
	0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
	
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
	
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,
	0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
	
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94   */  //这些在此例程中没有用到
};


/* 补充字模 温度 湿度 （宽16像素，高16像素） */
const uint8_t font_temperature[][16] = 
{
	0x10,0x60,0x02,0x8C,0x00,0x00,0xFE,0x92,//温（上） 0
	0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
	
	0x04,0x04,0x7E,0x01,0x40,0x7E,0x42,0x42,//温（下） 1
	0x7E,0x42,0x7E,0x42,0x42,0x7E,0x40,0x00, 

	0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,//度（上） 0
	0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,

	0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,//度（下） 1
	0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,
};
const uint8_t font_humidity[][16] = 
{
	0x10,0x60,0x02,0x8C,0x00,0xFE,0x92,0x92,//湿（上） 0
	0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
	
	0x04,0x04,0x7E,0x01,0x44,0x48,0x50,0x7F,//湿（下） 1
	0x40,0x40,0x7F,0x50,0x48,0x44,0x40,0x00, 
	
	0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,//度（上） 0
	0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,

	0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,//度（下） 1
	0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,
};

const uint8_t font_waitToMeasure[][16] = 
{
	0x08,0x04,0x23,0x22,0x26,0x2A,0x22,0xFA,
	0x24,0x23,0x22,0x26,0x2A,0x02,0x02,0x00,
	
	0x01,0x09,0x09,0x09,0x19,0x69,0x09,0x09,
	0x49,0x89,0x7D,0x09,0x09,0x09,0x01,0x00,/*"等",0*/

	0x00,0x10,0x88,0xC4,0x33,0x40,0x48,0x48,
	0x48,0x7F,0x48,0xC8,0x48,0x48,0x40,0x00,
	
	0x02,0x01,0x00,0xFF,0x00,0x02,0x0A,0x32,
	0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x00,/*"待",1*/

	0x10,0x60,0x02,0x8C,0x00,0xFE,0x02,0xF2,
	0x02,0xFE,0x00,0xF8,0x00,0xFF,0x00,0x00,
	
	0x04,0x04,0x7E,0x01,0x80,0x47,0x30,0x0F,
	0x10,0x27,0x00,0x47,0x80,0x7F,0x00,0x00,/*"测",2*/

	0x20,0x20,0x20,0xBE,0xAA,0xAA,0xAA,0xAA,
	0xAA,0xAA,0xAA,0xBE,0x20,0x20,0x20,0x00,
	
	0x00,0x80,0x80,0xAF,0xAA,0xAA,0xAA,0xFF,
	0xAA,0xAA,0xAA,0xAF,0x80,0x80,0x00,0x00,/*"量",3*/
};


const uint8_t font_sleep[][16] =
{
	0xFC,0x24,0x24,0xFC,0x00,0x20,0xE4,0x24,
	0x24,0xFE,0x22,0x23,0xE2,0x20,0x00,0x00,
	
	0x3F,0x11,0x11,0x3F,0x00,0x49,0x4F,0x49,
	0x49,0x7F,0x49,0x49,0x4F,0x49,0x01,0x00,/*"睡",0*/

	0x00,0xFC,0x24,0x24,0x24,0xFC,0x00,0xFE,
	0x22,0x22,0xE2,0x22,0x22,0x3E,0x00,0x00,
	
	0x00,0x3F,0x11,0x11,0x11,0x3F,0x00,0xFF,
	0x41,0x21,0x07,0x19,0x21,0x41,0xF1,0x00,/*"眠",1*/
};

const uint8_t font_low[][16] =
{
	0x00,0x80,0x60,0xF8,0x07,0x00,0xFC,0x84,
	0x84,0x84,0xFE,0x82,0x83,0x82,0x80,0x00,
	
	0x01,0x00,0x00,0xFF,0x00,0x00,0xFF,0x40,
	0x20,0x00,0x41,0x8E,0x30,0x40,0xF8,0x00,/*"低",0*/

	0x40,0x40,0x42,0xCC,0x00,0x04,0xF4,0x94,
	0x94,0xFF,0x94,0x94,0xF4,0x04,0x00,0x00,
	
	0x00,0x40,0x20,0x1F,0x20,0x48,0x44,0x42,
	0x41,0x5F,0x41,0x42,0x44,0x48,0x40,0x00,/*"速",1*/
};
const uint8_t font_middle[][16] =
{
	0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,
	0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
	
	0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,
	0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00,/*"中",0*/

	0x40,0x40,0x42,0xCC,0x00,0x04,0xF4,0x94,
	0x94,0xFF,0x94,0x94,0xF4,0x04,0x00,0x00,
	
	0x00,0x40,0x20,0x1F,0x20,0x48,0x44,0x42,
	0x41,0x5F,0x41,0x42,0x44,0x48,0x40,0x00,/*"速",1*/
};
const uint8_t font_high[][16] =
{
	0x04,0x04,0x04,0x04,0xF4,0x94,0x95,0x96,
	0x94,0x94,0xF4,0x04,0x04,0x04,0x04,0x00,

	0x00,0xFE,0x02,0x02,0x7A,0x4A,0x4A,0x4A,
	0x4A,0x4A,0x7A,0x02,0x82,0xFE,0x00,0x00,/*"高",0*/

	0x40,0x40,0x42,0xCC,0x00,0x04,0xF4,0x94,
	0x94,0xFF,0x94,0x94,0xF4,0x04,0x00,0x00,
	
	0x00,0x40,0x20,0x1F,0x20,0x48,0x44,0x42,
	0x41,0x5F,0x41,0x42,0x44,0x48,0x40,0x00,/*"速",1*/
};
const uint8_t font_superstrong[][16] =
{
	0x40,0x48,0x48,0x48,0xFF,0x48,0x48,0x42,
	0xA2,0x9E,0x82,0xA2,0xC2,0xBE,0x00,0x00,
	
	0x80,0x60,0x1F,0x20,0x7F,0x44,0x44,0x40,
	0x4F,0x48,0x48,0x48,0x48,0x4F,0x40,0x00,/*"超",0*/

	0x02,0xE2,0x22,0x22,0x3E,0x00,0x80,0x9E,
	0x92,0x92,0xF2,0x92,0x92,0x9E,0x80,0x00,
	
	0x00,0x43,0x82,0x42,0x3E,0x40,0x47,0x44,
	0x44,0x44,0x7F,0x44,0x44,0x54,0xE7,0x00,/*"强",1*/
};
const uint8_t font_Off[][16] =
{
	0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,
	0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
	
	0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,
	0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,/*"关",0*/

	0x00,0xF8,0x01,0x22,0x20,0x22,0x22,0xA2,
	0xFA,0x22,0x22,0x22,0x02,0xFE,0x00,0x00,
	
	0x00,0xFF,0x00,0x08,0x04,0x02,0x11,0x20,
	0x1F,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,/*"闭",1*/
};

const uint8_t font_FanStatus[][16] =
{
	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,

	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",0*/

	0x00,0x00,0xFC,0x24,0x24,0x24,0x25,0x26,
	0x24,0x24,0x24,0x24,0x24,0x3C,0x00,0x00,
	
	0x40,0x30,0x0F,0x21,0x15,0x49,0x81,0x7F,
	0x00,0x21,0x15,0x49,0x81,0x7F,0x00,0x00,/*"扇",1*/

	
	0x00,0x08,0x30,0x00,0xFF,0x20,0x20,0x20,
	0x20,0xFF,0x20,0x20,0x22,0x2C,0x20,0x00,
	
	0x04,0x04,0x02,0x01,0xFF,0x80,0x40,0x30,
	0x0E,0x01,0x06,0x18,0x20,0x40,0x80,0x00,/*"状",2*/

	0x00,0x04,0x84,0x84,0x44,0x24,0x54,0x8F,
	0x14,0x24,0x44,0x84,0x84,0x04,0x00,0x00,
	
	0x41,0x39,0x00,0x00,0x3C,0x40,0x40,0x42,
	0x4C,0x40,0x40,0x70,0x04,0x09,0x31,0x00,/*"态",3*/
};

const uint8_t font_month[][16] =
{
	0x00,0x00,0x00,0xFE,0x22,0x22,0x22,0x22,
	0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
	
    0x80,0x40,0x30,0x0F,0x02,0x02,0x02,0x02,
	0x02,0x02,0x42,0x82,0x7F,0x00,0x00,0x00,/*"月",0*/
};

const uint8_t font_day[][16] =
{
	0x00,0x00,0x00,0xFE,0x82,0x82,0x82,0x82,
	0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,/*"日",0*/
};

const uint8_t font_weather[][16] =
{
	0x40,0x40,0x42,0x42,0x42,0x42,0x42,0xFE,
    0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
    0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,
    0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,/*"天",0*/
    
    0x20,0x10,0x4C,0x47,0x54,0x54,0x54,0x54,
    0x54,0x54,0x54,0xD4,0x04,0x04,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0F,0x30,0x40,0xF0,0x00,/*"气",1*/
};

const uint8_t font_qing[][16] =
{
	0x00,0xFC,0x84,0x84,0xFC,0x00,0x44,0x54,
	0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x00,
	0x00,0x3F,0x10,0x10,0x3F,0x00,0x00,0xFF,
	0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,/*"晴",0*/
};

const uint8_t font_shaoyun[][16] =
{
	0x00,0x00,0x80,0x60,0x18,0x00,0x00,0xFF,
	0x00,0x00,0x08,0x90,0x20,0xC0,0x00,0x00,
	0x00,0x81,0x80,0x80,0x40,0x40,0x20,0x13,
	0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x00,/*"少",0*/

	0x40,0x40,0x42,0x42,0x42,0x42,0xC2,0x42,
	0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
	0x00,0x20,0x70,0x28,0x24,0x23,0x20,0x20,
	0x20,0x24,0x28,0x30,0xE0,0x00,0x00,0x00,/*"云",1*/
};

const uint8_t font_qingjianduoyun[][16] =
{
	0x00,0xFC,0x84,0x84,0xFC,0x00,0x44,0x54,
	0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x00,
	0x00,0x3F,0x10,0x10,0x3F,0x00,0x00,0xFF,
	0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,/*"晴",0*/

	0x00,0xF8,0x01,0x06,0x00,0xF0,0x12,0x12,
	0x12,0xF2,0x02,0x02,0x02,0xFE,0x00,0x00,
	0x00,0xFF,0x00,0x00,0x00,0x1F,0x11,0x11,
	0x11,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00,/*"间",1*/

	0x00,0x00,0x10,0x10,0x98,0xA4,0x47,0x44,
	0xA4,0x54,0x0C,0x04,0x00,0x00,0x00,0x00,
	0x00,0x81,0x89,0x89,0x44,0x44,0x4A,0x31,
	0x21,0x11,0x09,0x05,0x03,0x00,0x00,0x00,/*"多",2*/

	0x40,0x40,0x42,0x42,0x42,0x42,0xC2,0x42,
	0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
	0x00,0x20,0x70,0x28,0x24,0x23,0x20,0x20,
	0x20,0x24,0x28,0x30,0xE0,0x00,0x00,0x00,/*"云",3*/
};

const uint8_t font_duoyun[][16] =
{
	0x00,0x00,0x10,0x10,0x98,0xA4,0x47,0x44,
	0xA4,0x54,0x0C,0x04,0x00,0x00,0x00,0x00,
	0x00,0x81,0x89,0x89,0x44,0x44,0x4A,0x31,
	0x21,0x11,0x09,0x05,0x03,0x00,0x00,0x00,/*"多",0*/

	0x40,0x40,0x42,0x42,0x42,0x42,0xC2,0x42,
	0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
	0x00,0x20,0x70,0x28,0x24,0x23,0x20,0x20,
	0x20,0x24,0x28,0x30,0xE0,0x00,0x00,0x00,/*"云",1*/

};

const uint8_t font_yin[][16] =
{
	0x00,0xFE,0x02,0x22,0xDA,0x06,0x00,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
	0x00,0xFF,0x08,0x10,0x88,0x47,0x30,0x0F,
	0x02,0x02,0x02,0x42,0x82,0x7F,0x00,0x00,/*"阴",0*/
};

const uint8_t font_youfeng[][16] =
{
	0x04,0x04,0x04,0x84,0xE4,0x3C,0x27,0x24,
	0x24,0x24,0x24,0xE4,0x04,0x04,0x04,0x00,
	0x04,0x02,0x01,0x00,0xFF,0x09,0x09,0x09,
	0x09,0x49,0x89,0x7F,0x00,0x00,0x00,0x00,/*"有",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_pingjing[][16] =
{
	0x00,0x02,0x02,0x12,0x62,0x02,0x02,0xFE,
	0x02,0x02,0x42,0x32,0x02,0x02,0x00,0x00,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,/*"平",0*/

	0x44,0x54,0x54,0x7F,0x54,0x54,0x44,0x20,
	0x28,0x27,0xE4,0x34,0x2C,0xE0,0x00,0x00,
	0x00,0xFF,0x15,0x55,0x95,0x7F,0x00,0x09,
	0x49,0x89,0x7F,0x09,0x09,0x1F,0x01,0x00,/*"静",1*/
};

const uint8_t font_weifeng[][16] =
{
	0x10,0x88,0xC4,0x33,0x80,0x9E,0x90,0x9F,
	0x90,0x9E,0x20,0xD8,0x17,0xF0,0x10,0x00,
	0x01,0x00,0xFF,0x80,0x40,0x3E,0x02,0x02,
	0x3E,0x10,0x88,0x67,0x18,0x67,0x80,0x00,/*"微",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_hefeng[][16] =
{
	0x20,0x24,0x24,0xA4,0xFE,0x23,0x22,0x20,
	0x00,0xF8,0x08,0x08,0x08,0xF8,0x00,0x00,
	0x10,0x08,0x06,0x01,0xFF,0x01,0x06,0x00,
	0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,/*"和",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_qingfeng[][16] =
{
	0x10,0x60,0x02,0x8C,0x00,0x44,0x54,0x54,
	0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
	0x04,0x04,0x7E,0x01,0x00,0x00,0xFF,0x15,
	0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,/*"清",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_qiangfeng[][16] =
{
	0x02,0xE2,0x22,0x22,0x3E,0x00,0x80,0x9E,
	0x92,0x92,0xF2,0x92,0x92,0x9E,0x80,0x00,
	0x00,0x43,0x82,0x42,0x3E,0x40,0x47,0x44,
	0x44,0x44,0x7F,0x44,0x44,0x54,0xE7,0x00,/*"强",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_jifeng[][16] =
{
	0x10,0x60,0x00,0xFC,0x04,0x84,0x7C,0x24,
	0x25,0xE6,0x24,0x24,0x24,0x24,0x04,0x00,
	0x84,0x42,0x31,0x0F,0x82,0x82,0x42,0x22,
	0x1A,0x07,0x1A,0x22,0x42,0x82,0x82,0x00,/*"疾",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_dafeng[][16] =
{
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
	0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,
	0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,/*"大",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_liefeng[][16] =
{
	0x00,0x42,0x22,0x52,0x9E,0x12,0x92,0x72,
	0x02,0x00,0xFC,0x00,0x00,0xFF,0x00,0x00,
	0x88,0x48,0x34,0x04,0x02,0x11,0x60,0x00,
	0x10,0x60,0x00,0x02,0x14,0xE3,0x00,0x00,/*"烈",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_fengbao[][16] =
{
	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",0*/

	0x00,0x40,0x40,0x5F,0xF5,0x55,0x55,0x55,
	0x55,0x55,0xF5,0x5F,0x40,0x40,0x00,0x00,
	0x09,0x09,0x85,0x45,0x2B,0x51,0x81,0x7D,
	0x01,0x11,0x2B,0x45,0x85,0x09,0x09,0x00,/*"暴",1*/
};

const uint8_t font_kuangbaofeng[][16] =
{
	0x40,0x22,0x14,0x08,0xF4,0x02,0x00,0x04,
	0x04,0x04,0xFC,0x04,0x04,0x04,0x00,0x00,
	0x08,0x44,0x82,0x41,0x3F,0x00,0x40,0x41,
	0x41,0x41,0x7F,0x41,0x41,0x41,0x40,0x00,/*"狂",0*/

	0x00,0x40,0x40,0x5F,0xF5,0x55,0x55,0x55,
	0x55,0x55,0xF5,0x5F,0x40,0x40,0x00,0x00,
	0x09,0x09,0x85,0x45,0x2B,0x51,0x81,0x7D,
	0x01,0x11,0x2B,0x45,0x85,0x09,0x09,0x00,/*"暴",1*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",2*/
};

const uint8_t font_jufeng[][16] =
{
	0x00,0xFE,0x42,0x82,0x62,0xFE,0x00,0x00,
	0xFE,0xAA,0xAA,0xAA,0xFE,0x00,0x00,0x00,
	0x80,0x7F,0x04,0x03,0x04,0x1F,0x20,0x42,
	0x53,0x4A,0x42,0x4A,0x53,0x42,0x60,0x00,/*"飓",0*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",1*/
};

const uint8_t font_redaifengbao[][16] =
{
	0x08,0x08,0x88,0xFF,0x48,0x48,0x00,0x08,
	0x48,0xFF,0x08,0x08,0xF8,0x00,0x00,0x00,
	0x81,0x65,0x08,0x07,0x20,0xC0,0x08,0x04,
	0x23,0xC0,0x03,0x00,0x23,0xC4,0x0F,0x00,/*"热",0*/

	0x00,0xC4,0x44,0x44,0x5F,0x44,0x44,0xDF,
	0x44,0x44,0x5F,0x44,0x44,0x44,0xC0,0x00,
	0x01,0x00,0x00,0x3E,0x02,0x02,0x02,0xFF,
	0x02,0x12,0x22,0x1E,0x00,0x01,0x00,0x00,/*"带",1*/

	0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,
	0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
	0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,
	0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,/*"风",2*/
	
	0x00,0x40,0x40,0x5F,0xF5,0x55,0x55,0x55,
	0x55,0x55,0xF5,0x5F,0x40,0x40,0x00,0x00,
	0x09,0x09,0x85,0x45,0x2B,0x51,0x81,0x7D,
	0x01,0x11,0x2B,0x45,0x85,0x09,0x09,0x00,/*"暴",3*/
};

const uint8_t font_mai[][16] =
{
	0x50,0x4C,0xA5,0x35,0xD5,0x95,0x45,0xDF,
	0x45,0x55,0xD5,0x55,0x45,0xD4,0x0C,0x00,
	0x42,0x4A,0x29,0xA5,0x92,0x7C,0x00,0x57,
	0x55,0x55,0x7F,0x55,0x55,0x57,0x40,0x00,/*"霾",0*/
};

const uint8_t font_xiaoyu[][16] =
{
	0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0xFF,
	0x00,0x00,0x00,0x20,0x40,0x80,0x00,0x00,
	0x08,0x04,0x03,0x00,0x00,0x40,0x80,0x7F,
	0x00,0x00,0x00,0x00,0x00,0x01,0x0E,0x00,/*"小",0*/

	0x02,0xE2,0x22,0x22,0x22,0x22,0x22,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00,
	0x00,0xFF,0x00,0x00,0x09,0x12,0x00,0x7F,
	0x00,0x09,0x12,0x40,0x80,0x7F,0x00,0x00,/*"雨",1*/
};

const uint8_t font_zhongyu[][16] =
{
	0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,
	0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
	0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,
	0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00,/*"中",0*/

	0x02,0xE2,0x22,0x22,0x22,0x22,0x22,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00,
	0x00,0xFF,0x00,0x00,0x09,0x12,0x00,0x7F,
	0x00,0x09,0x12,0x40,0x80,0x7F,0x00,0x00,/*"雨",1*/
};

const uint8_t font_dayu[][16] =
{
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
	0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,
	0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,/*"大",0*/

	0x02,0xE2,0x22,0x22,0x22,0x22,0x22,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00,
	0x00,0xFF,0x00,0x00,0x09,0x12,0x00,0x7F,
	0x00,0x09,0x12,0x40,0x80,0x7F,0x00,0x00,/*"雨",1*/
};

const uint8_t font_baoyu[][16] =
{
	0x00,0x40,0x40,0x5F,0xF5,0x55,0x55,0x55,
	0x55,0x55,0xF5,0x5F,0x40,0x40,0x00,0x00,
	0x09,0x09,0x85,0x45,0x2B,0x51,0x81,0x7D,
	0x01,0x11,0x2B,0x45,0x85,0x09,0x09,0x00,/*"暴",0*/

	0x02,0xE2,0x22,0x22,0x22,0x22,0x22,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00,
	0x00,0xFF,0x00,0x00,0x09,0x12,0x00,0x7F,
	0x00,0x09,0x12,0x40,0x80,0x7F,0x00,0x00,/*"雨",1*/
};

const uint8_t font_yu[][16] =
{
	0x02,0xE2,0x22,0x22,0x22,0x22,0x22,0xFE,
	0x22,0x22,0x22,0x22,0x22,0xE2,0x02,0x00,
	0x00,0xFF,0x00,0x00,0x09,0x12,0x00,0x7F,
	0x00,0x09,0x12,0x40,0x80,0x7F,0x00,0x00,/*"雨",0*/
};

const uint8_t font_xue[][16] =
{
	0x10,0x0C,0x05,0x55,0x55,0x55,0x05,0x7F,
	0x05,0x55,0x55,0x55,0x05,0x14,0x0C,0x00,
	0x00,0x00,0x41,0x49,0x49,0x49,0x49,0x49,
	0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,/*"雪",0*/
};

const uint8_t font_fuchen[][16] =
{
	0x10,0x60,0x02,0x0C,0xC0,0x00,0x94,0xA4,
	0x84,0x94,0xA2,0x82,0xA3,0x1A,0x00,0x00,
	0x04,0x04,0x7C,0x03,0x00,0x04,0x04,0x04,
	0x44,0x84,0x7E,0x05,0x04,0x04,0x04,0x00,/*"浮",0*/

	0x00,0x40,0x20,0x10,0x0C,0x00,0x00,0x7F,
	0x00,0x00,0x04,0x08,0x10,0x60,0x00,0x00,
	0x40,0x40,0x44,0x44,0x44,0x44,0x44,0x7F,
	0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,/*"尘",1*/
};

const uint8_t font_wu[][16] =
{
	0x10,0x0C,0x05,0x55,0x55,0xD5,0x05,0x7F,
	0x05,0x55,0x55,0x55,0x05,0x14,0x0C,0x00,
	0x10,0x10,0x10,0x8A,0xA9,0x6B,0x35,0x25,
	0x25,0xAB,0xE9,0x08,0x10,0x10,0x10,0x00,/*"雾",0*/
};

const uint8_t font_weizhi[][16] =
{
	0x80,0x80,0x88,0x88,0x88,0x88,0x88,0xFF,
	0x88,0x88,0x88,0x88,0x88,0x80,0x80,0x00,
	0x20,0x20,0x10,0x08,0x04,0x02,0x01,0xFF,
	0x01,0x02,0x04,0x08,0x10,0x20,0x20,0x00,/*"未",0*/

	0x20,0x18,0x0F,0x08,0xF8,0x08,0x08,0x00,
	0x00,0xFC,0x04,0x04,0x04,0xFC,0x00,0x00,
	0x81,0x41,0x31,0x0D,0x03,0x0D,0x71,0x01,
	0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,/*"知",1*/
};

#endif