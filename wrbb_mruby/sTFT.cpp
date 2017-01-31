/*
 * SPI_TFT�֘A
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v2lib-firm/blob/master/MITL
 *
 */
#include <Arduino.h>
#include <string.h>
#include "SPI_TFT.h"
#include "sTFT.h"

#include "mruby.h"
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/compile.h>
#include "../wrbb.h"
#include "sKernel.h"

//**************************************************
// TFT��puts���܂�: TFT_puts
//  TFT_puts(x, y, pch, fg, bg, scale)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_puts(mrb_state *mrb, mrb_value self)
{
mrb_int x, y;
mrb_value vpch;
char *pch;
mrb_int fg, bg, scale;

	mrb_get_args(mrb, "iiSiii", &x, &y, &vpch, &fg, &bg, &scale);
//	pch = mrb_str_to_cstr(mrb, vpch);
	pch = RSTRING_PTR(vpch);
	TFT_puts(x, y, pch, fg, bg, scale);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��drawHLine���܂�: TFT_drawHLine
//  TFT_drawHLine(x, y, w, color)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_drawHLine(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, w;
mrb_int color;

	mrb_get_args(mrb, "iiii", &x, &y, &w, &color);
	TFT_drawHLine(x, y, w, color);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��drawVLine���܂�: TFT_drawVLine
//  TFT_drawVLine(xs, ys, xe, ye, color)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_drawVLine(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, h;
mrb_int color;

	mrb_get_args(mrb, "iiii", &x, &y, &h, &color);
	TFT_drawVLine(x, y, h, color);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��drawLine���܂�: TFT_drawLine
//  TFT_drawLine(xs, ys, xe, ye, color)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_drawLine(mrb_state *mrb, mrb_value self)
{
mrb_int xs, ys, xe, ye;
mrb_int color;

	mrb_get_args(mrb, "iiiii", &xs, &ys, &xe, &ye, &color);
	TFT_drawLine(xs, ys, xe, ye, color);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��drawPixel���܂�: TFT_drawPixel
//  TFT_drawPixel(x, y, color)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_drawPixel(mrb_state *mrb, mrb_value self)
{
mrb_int x, y;
mrb_int color;
	mrb_get_args(mrb, "iii", &x, &y, &color);
	
	TFT_drawPixel(x, y, color);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��FillRect���܂�: TFT_FillRect
//  TFT_FillRect(x, y, w, h, color)
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_fillRect(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, w, h;
mrb_int color;
	mrb_get_args(mrb, "iiiii", &x, &y, &w, &h, &color);
	
	TFT_fillRect(x, y, w, h, color);

	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT��clear���܂�: TFT_clear
//  TFT_clear()
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_clear(mrb_state *mrb, mrb_value self)
{
mrb_int color;
	mrb_get_args(mrb, "i", &color);
	TFT_clear(color);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT����]���܂�: TFT_setRotation
//  TFT_setRotation()
//
// �߂�l�͂Ȃ�
//**************************************************
mrb_value mrb_TFT_setRotation(mrb_state *mrb, mrb_value self)
{
	uint8_t m;
	mrb_get_args(mrb, "i", &m);
	TFT_setRotation(m);
	return mrb_nil_value();	//�߂�l�͖����ł���B 
}
//**************************************************
// TFT���N�����܂�: TFT.init
//  TFT.init()
//
// �߂�l�͈ȉ��̂Ƃ���
//	0: �N�����s
//	1: �N������
//**************************************************
//mrb_value mrb_TFT_init(mrb_state *mrb, mrb_value self)
//{
//	return mrb_fixnum_value(TFT_init());
//}

//**************************************************
// ���C�u�������`���܂�
//**************************************************
int TFT_Init(mrb_state *mrb)
{
	TFT_init();
	
	struct RClass *TFTModule = mrb_define_module(mrb, TFT_CLASS);

	mrb_define_module_function(mrb, TFTModule, "setRotation", mrb_TFT_setRotation, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, TFTModule, "clear", mrb_TFT_clear, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, TFTModule, "fillRect", mrb_TFT_fillRect, MRB_ARGS_REQ(5));
	mrb_define_module_function(mrb, TFTModule, "drawPixel", mrb_TFT_drawPixel, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, TFTModule, "drawLine", mrb_TFT_drawLine, MRB_ARGS_REQ(5));
	mrb_define_module_function(mrb, TFTModule, "drawVLine", mrb_TFT_drawVLine, MRB_ARGS_REQ(4));
	mrb_define_module_function(mrb, TFTModule, "drawHLine", mrb_TFT_drawHLine, MRB_ARGS_REQ(4));	
	mrb_define_module_function(mrb, TFTModule, "puts", mrb_TFT_puts, MRB_ARGS_REQ(6));	

	return 1; 
}
