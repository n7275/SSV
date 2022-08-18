/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Flight Computer Operating System Input/Output definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/30   GLS
2022/05/19   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Flight Computer Operating System Input/Output definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef SIMPLEFCOSIO_H
#define SIMPLEFCOSIO_H


#include "dps_defs.h"


namespace dps
{
	inline constexpr unsigned short EIU1_Address = 17;
	inline constexpr unsigned short EIU2_Address = 23;
	inline constexpr unsigned short EIU3_Address = 24;

	inline constexpr unsigned short HUD1_Address = 6;
	inline constexpr unsigned short HUD2_Address = 9;

	inline constexpr unsigned short MDM_FF1_Address = 25;
	inline constexpr unsigned short MDM_FF2_Address = 26;
	inline constexpr unsigned short MDM_FF3_Address = 27;
	inline constexpr unsigned short MDM_FF4_Address = 28;

	inline constexpr unsigned short MDM_FA1_Address = 19;
	inline constexpr unsigned short MDM_FA2_Address = 20;
	inline constexpr unsigned short MDM_FA3_Address = 21;
	inline constexpr unsigned short MDM_FA4_Address = 22;

	inline constexpr unsigned short MDM_PF1_Address = 29;
	inline constexpr unsigned short MDM_PF2_Address = 30;

	inline constexpr unsigned short MDM_OF1_Address = 10;
	inline constexpr unsigned short MDM_OF2_Address = 11;
	inline constexpr unsigned short MDM_OF3_Address = 12;
	inline constexpr unsigned short MDM_OF4_Address = 13;

	inline constexpr unsigned short MDM_OA1_Address = 14;
	inline constexpr unsigned short MDM_OA2_Address = 15;
	inline constexpr unsigned short MDM_OA3_Address = 16;


	inline constexpr unsigned short ModeControl_MDM_Receive = 0b1000;
	inline constexpr unsigned short ModeControl_MDM_Transmit = 0b1001;

	inline constexpr unsigned short ModuleAddress_IOM0 = 0b0000;
	inline constexpr unsigned short ModuleAddress_IOM1 = 0b0001;
	inline constexpr unsigned short ModuleAddress_IOM2 = 0b0010;
	inline constexpr unsigned short ModuleAddress_IOM3 = 0b0011;
	inline constexpr unsigned short ModuleAddress_IOM4 = 0b0100;
	inline constexpr unsigned short ModuleAddress_IOM5 = 0b0101;
	inline constexpr unsigned short ModuleAddress_IOM6 = 0b0110;
	inline constexpr unsigned short ModuleAddress_IOM7 = 0b0111;
	inline constexpr unsigned short ModuleAddress_IOM8 = 0b1000;
	inline constexpr unsigned short ModuleAddress_IOM9 = 0b1001;
	inline constexpr unsigned short ModuleAddress_IOM10 = 0b1010;
	inline constexpr unsigned short ModuleAddress_IOM11 = 0b1011;
	inline constexpr unsigned short ModuleAddress_IOM12 = 0b1100;
	inline constexpr unsigned short ModuleAddress_IOM13 = 0b1101;
	inline constexpr unsigned short ModuleAddress_IOM14 = 0b1110;
	inline constexpr unsigned short ModuleAddress_IOM15 = 0b1111;

	inline constexpr unsigned int ChannelAddress_0 = 0b00000;
	inline constexpr unsigned int ChannelAddress_1 = 0b00001;
	inline constexpr unsigned int ChannelAddress_2 = 0b00010;
	inline constexpr unsigned int ChannelAddress_3 = 0b00011;
	inline constexpr unsigned int ChannelAddress_4 = 0b00100;

	class SimpleGPCSystem;

	class SimpleFCOS_IO
	{
		protected:
			SimpleGPCSystem* pGPC;

			void InputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr );
			void OutputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr );

		public:
			explicit SimpleFCOS_IO( SimpleGPCSystem* _gpc );
			virtual ~SimpleFCOS_IO();

			/**
			 * Send data requests to subystems.
			 */
			virtual void input( void ) = 0;

			/**
			 * Send commands to subystems.
			 */
			virtual void output( void ) = 0;

			/**
			 * Save data from subsystem.
			 */
			virtual void busRead( SIMPLEBUS_COMMANDDATA_WORD* cdw );
	};
};

#endif// SIMPLEFCOSIO_H
