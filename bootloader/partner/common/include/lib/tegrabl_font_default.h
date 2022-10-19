/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#define DISP_FONT_WIDTH 8
#define DISP_FONT_HEIGHT 8

static const uint8_t  font_default[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*' '*/
	0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00, /*'!'*/
	0x00, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, /*'"'*/
	0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00, /*'#'*/
	0x0C, 0x3F, 0x68, 0x3E, 0x0B, 0x7E, 0x18, 0x00, /*'$'*/
	0x60, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x06, 0x00, /*'%'*/
	0x38, 0x6C, 0x6C, 0x38, 0x6D, 0x66, 0x3B, 0x00, /*'&'*/
	0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, /*'''*/
	0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, /*'('*/
	0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, /*')'*/
	0x00, 0x18, 0x7E, 0x3C, 0x7E, 0x18, 0x00, 0x00, /*'*'*/
	0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, /*'+'*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, /*','*/
	0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, /*'-'*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, /*'.'*/
	0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, /*'/'*/
	0x00, 0x3C, 0x46, 0x4A, 0x52, 0x62, 0x3C, 0x00, /*'0'*/
	0x00, 0x18, 0x28, 0x08, 0x08, 0x08, 0x3E, 0x00, /*'1'*/
	0x00, 0x3C, 0x42, 0x02, 0x3C, 0x40, 0x7E, 0x00, /*'2'*/
	0x00, 0x3C, 0x42, 0x0C, 0x02, 0x42, 0x3C, 0x00, /*'3'*/
	0x00, 0x08, 0x18, 0x28, 0x48, 0x7E, 0x08, 0x00, /*'4'*/
	0x00, 0x7E, 0x40, 0x7C, 0x02, 0x42, 0x3C, 0x00, /*'5'*/
	0x00, 0x3C, 0x40, 0x7C, 0x42, 0x42, 0x3C, 0x00, /*'6'*/
	0x00, 0x7E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00, /*'7'*/
	0x00, 0x3C, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00, /*'8'*/
	0x00, 0x3C, 0x42, 0x42, 0x3E, 0x02, 0x3C, 0x00, /*'9'*/
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, /*':'*/
	0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, /*';'*/
	0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00, /*'<'*/
	0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00, /*'='*/
	0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x00, /*'>'*/
	0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00, /*'?'*/
	0x3C, 0x66, 0x6E, 0x6A, 0x6E, 0x60, 0x3C, 0x00, /*'@'*/
	0x00, 0x3C, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00, /*'A'*/
	0x00, 0x7C, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00, /*'B'*/
	0x00, 0x3C, 0x42, 0x40, 0x40, 0x42, 0x3C, 0x00, /*'C'*/
	0x00, 0x78, 0x44, 0x42, 0x42, 0x44, 0x78, 0x00, /*'D'*/
	0x00, 0x7E, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00, /*'E'*/
	0x00, 0x7E, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00, /*'F'*/
	0x00, 0x3C, 0x42, 0x40, 0x4E, 0x42, 0x3C, 0x00, /*'G'*/
	0x00, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00, /*'H'*/
	0x00, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, /*'I'*/
	0x00, 0x02, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, /*'J'*/
	0x00, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44, 0x00, /*'K'*/
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, /*'L'*/
	0x00, 0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x00, /*'M'*/
	0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00, /*'N'*/
	0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, /*'O'*/
	0x00, 0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x00, /*'P'*/
	0x00, 0x3C, 0x42, 0x42, 0x52, 0x4A, 0x3C, 0x00, /*'Q'*/
	0x00, 0x7C, 0x42, 0x42, 0x7C, 0x44, 0x42, 0x00, /*'R'*/
	0x00, 0x3C, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00, /*'S'*/
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, /*'T'*/
	0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, /*'U'*/
	0x00, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, /*'V'*/
	0x00, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x24, 0x00, /*'W'*/
	0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00, /*'X'*/
	0x00, 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00, /*'Y'*/
	0x00, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00, /*'Z'*/
	0x7C, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7C, 0x00, /*'['*/
	0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, /*'\'*/
	0x3E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x3E, 0x00, /*']'*/
	0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*'^'*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, /*'_'*/
	0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*'`'*/
	0x00, 0x00, 0x38, 0x04, 0x3C, 0x44, 0x3C, 0x00, /*'a'*/
	0x00, 0x40, 0x40, 0x78, 0x44, 0x44, 0x78, 0x00, /*'b'*/
	0x00, 0x00, 0x1C, 0x20, 0x20, 0x20, 0x1C, 0x00, /*'c'*/
	0x00, 0x04, 0x04, 0x3C, 0x44, 0x44, 0x3C, 0x00, /*'d'*/
	0x00, 0x00, 0x38, 0x44, 0x78, 0x40, 0x3C, 0x00, /*'e'*/
	0x00, 0x18, 0x20, 0x30, 0x20, 0x20, 0x20, 0x00, /*'f'*/
	0x00, 0x00, 0x3C, 0x44, 0x44, 0x3C, 0x04, 0x38, /*'g'*/
	0x00, 0x20, 0x20, 0x3C, 0x22, 0x22, 0x22, 0x00, /*'h'*/
	0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x38, 0x00, /*'i'*/
	0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x48, 0x30, /*'j'*/
	0x00, 0x40, 0x50, 0x60, 0x60, 0x50, 0x48, 0x00, /*'k'*/
	0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x18, 0x00, /*'l'*/
	0x00, 0x00, 0x68, 0x54, 0x54, 0x44, 0x44, 0x00, /*'m'*/
	0x00, 0x00, 0x78, 0x44, 0x44, 0x44, 0x44, 0x00, /*'n'*/
	0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, /*'o'*/
	0x00, 0x00, 0x78, 0x44, 0x44, 0x78, 0x40, 0x40, /*'p'*/
	0x00, 0x00, 0x3C, 0x44, 0x44, 0x3C, 0x04, 0x06, /*'q'*/
	0x00, 0x00, 0x1C, 0x20, 0x20, 0x20, 0x20, 0x00, /*'r'*/
	0x00, 0x00, 0x38, 0x40, 0x38, 0x04, 0x78, 0x00, /*'s'*/
	0x00, 0x10, 0x38, 0x10, 0x10, 0x10, 0x0C, 0x00, /*'t'*/
	0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, /*'u'*/
	0x00, 0x00, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00, /*'v'*/
	0x00, 0x00, 0x44, 0x44, 0x44, 0x54, 0x28, 0x00, /*'w'*/
	0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, /*'x'*/
	0x00, 0x00, 0x44, 0x44, 0x44, 0x3C, 0x04, 0x38, /*'y'*/
	0x00, 0x00, 0x7C, 0x08, 0x10, 0x20, 0x7C, 0x00, /*'z'*/
	0x0C, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0C, 0x00, /*'{'*/
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, /*'|'*/
	0x30, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x30, 0x00, /*'}'*/
	0x31, 0x6B, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, /*'~'*/
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /*'*/
};