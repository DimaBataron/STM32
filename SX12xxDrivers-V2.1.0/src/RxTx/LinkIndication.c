/*
 * LinkIndication.c
 *
 *  Created on: Feb 28, 2024
 *      Author: dima
 *      ���������� �������� �����
 */
#include "LinkIndication.h"
#include "math.h"
// ���������� ������ �� ������ ��������� �� ����� SSD1306
//
//#ifndef STARTTEST_H_
//void ReceptionIndicationSSD1306(){
//	disp1color_FillScreenbuff(0); //������� �������
//	  disp1color_printf(0, 0, FONTID_6X8M, "�������� ������");
//	  disp1color_printf(98,0,FONTID_6X8M,"%d",ReceivedPackets);
//
//	  disp1color_printf(0, 9, FONTID_6X8M, "������ CRC");
//	  disp1color_printf(98,9,FONTID_6X8M,"%d",PayLoadCRCError);
//
//	  disp1color_printf(0, 18, FONTID_6X8M, "�������. ������");
//	  disp1color_printf(98,18,FONTID_6X8M,"%d",CorruptData);
//
//	  disp1color_printf(0, 27, FONTID_6X8M, "SNR");
//	  disp1color_printf(98,27,FONTID_6X8M,"%d",RxPacketSnr);
//
//	  disp1color_printf(0, 36, FONTID_6X8M, "RSSI");
//	  disp1color_printf(98,36,FONTID_6X8M,"%d",(int)round(RxPacketRssi));
//	  disp1color_UpdateFromBuff();
//}
//#endif
