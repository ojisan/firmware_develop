/*
 * SPI_TFT関連
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
// TFTをputsします: TFT_puts
//  TFT_puts(x, y, pch, fg, bg, scale)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_puts(mrb_state *mrb, mrb_value self)
{
mrb_int x, y;
mrb_value vpch;
char *pch;
mrb_int fg, bg, scale;

	mrb_get_args(mrb, "iiSiii", &x, &y, &vpch, &fg, &bg, &scale);
	pch = mrb_str_to_cstr(mrb, vpch);
//	pch = RSTRING_PTR(vpch);
	TFT_puts(x, y, pch, fg, bg, scale);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをdrawHLineします: TFT_drawHLine
//  TFT_drawHLine(x, y, w, color)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_drawHLine(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, w;
mrb_int color;

	mrb_get_args(mrb, "iiii", &x, &y, &w, &color);
	TFT_drawHLine(x, y, w, color);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをdrawVLineします: TFT_drawVLine
//  TFT_drawVLine(xs, ys, xe, ye, color)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_drawVLine(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, h;
mrb_int color;

	mrb_get_args(mrb, "iiii", &x, &y, &h, &color);
	TFT_drawVLine(x, y, h, color);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをdrawLineします: TFT_drawLine
//  TFT_drawLine(xs, ys, xe, ye, color)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_drawLine(mrb_state *mrb, mrb_value self)
{
mrb_int xs, ys, xe, ye;
mrb_int color;

	mrb_get_args(mrb, "iiiii", &xs, &ys, &xe, &ye, &color);
	TFT_drawLine(xs, ys, xe, ye, color);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをdrawPixelします: TFT_drawPixel
//  TFT_drawPixel(x, y, color)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_drawPixel(mrb_state *mrb, mrb_value self)
{
mrb_int x, y;
mrb_int color;
	mrb_get_args(mrb, "iii", &x, &y, &color);
	
	TFT_drawPixel(x, y, color);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをFillRectします: TFT_FillRect
//  TFT_FillRect(x, y, w, h, color)
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_fillRect(mrb_state *mrb, mrb_value self)
{
mrb_int x, y, w, h;
mrb_int color;
	mrb_get_args(mrb, "iiiii", &x, &y, &w, &h, &color);
	
	TFT_fillRect(x, y, w, h, color);

	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTをclearします: TFT_clear
//  TFT_clear()
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_clear(mrb_state *mrb, mrb_value self)
{
mrb_int color;
	mrb_get_args(mrb, "i", &color);
	TFT_clear(color);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTを回転します: TFT_setRotation
//  TFT_setRotation()
//
// 戻り値はなし
//**************************************************
mrb_value mrb_TFT_setRotation(mrb_state *mrb, mrb_value self)
{
	uint8_t m;
	mrb_get_args(mrb, "i", &m);
	TFT_setRotation(m);
	return mrb_nil_value();	//戻り値は無しですよ。 
}
//**************************************************
// TFTを起動します: TFT.init
//  TFT.init()
//
// 戻り値は以下のとおり
//	0: 起動失敗
//	1: 起動成功
//**************************************************
//mrb_value mrb_TFT_init(mrb_state *mrb, mrb_value self)
//{
//	return mrb_fixnum_value(TFT_init());
//}

//**************************************************
// ライブラリを定義します
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
