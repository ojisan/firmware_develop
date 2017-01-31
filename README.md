# firmware_develop
GR-CITRUS firmware_develop special version with base on revision 2.28(2017/1/4)f3(256KB)
Add some files to original lib files as belows to use SPI TFT module(2.2inch QVGA with ILI9341).
* Add new TFT folder in gr_common folder.
* make additional 3files SPI_TFT.cpp, SPI_TFT.h font.h in TFT folder.
* make additional 2files sTFT.cpp, sTFT.h in wrbb_mruby folder.
* modify ｓSys.cpp file in wrbb_mruby folder to use TFT.
* modify makefile to make in firmware_develop folder as belows.
  ・Add ./gr_common/lib/TFT/SPI_TFT.cpp, ./wrbb_mruby/sTFT.cpp to SRCFILES
  ・Add ./gr_common/lib/TFT/SPI_TFT.o, ./wrbb_mruby/sTFT.o to  OBJFILES
  ・Add -I./gr_common/lib/TFT to CCINC
  ・Add ./gr_common/lib/TFT/SPI_TFT.h and ./gr_common/lib/TFT/font.h, ./wrbb_mruby/sTFT.h to HEADERFILES
