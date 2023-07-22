#include "SimpleMDM_OA2.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_OA2::SimpleMDM_OA2( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_OA2" ),
		powered(true)
	{
	}

	SimpleMDM_OA2::~SimpleMDM_OA2()
	{
	}

	void SimpleMDM_OA2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
		dipIOM5[0][0].Connect( pBundle, 0 );// PORT SHLD MECH STOW IND 1
		dipIOM12[1][0].Connect( pBundle, 4 );// PORT SHLD MECH DEPLOY IND 1
		dipIOM7[2][1].Connect( pBundle, 8 );// PORT SHLD MECH STOW IND 2
		dipIOM1[2][1].Connect( pBundle, 12 );// PORT SHLD MECH DEPLOY IND 2

		pBundle = BundleManager()->CreateBundle( "STBD_MPM_IND", 16 );
		dipIOM5[0][1].Connect( pBundle, 0 );// STBD SHLD MECH STOW IND 1
		dipIOM12[1][1].Connect( pBundle, 4 );// STBD SHLD MECH DEPLOY IND 1
		dipIOM7[2][3].Connect( pBundle, 8 );// STBD SHLD MECH STOW IND 2
		dipIOM1[2][3].Connect( pBundle, 12 );// STBD SHLD MECH DEPLOY IND 2

		pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
		dipIOM5[2][0].Connect( pBundle, 0 );// PORT FWD MRL LATCH IND 1
		dipIOM1[2][0].Connect( pBundle, 1 );// PORT FWD MRL RELEASE IND 1
		dipIOM12[2][0].Connect( pBundle, 2 );// PORT FWD MRL LATCH IND 2
		dipIOM7[2][0].Connect( pBundle, 3 );// PORT FWD MRL RELEASE IND 2
		dipIOM10[2][0].Connect( pBundle, 4 );// PORT FWD RETNN R-F-L 1
		dipIOM12[0][0].Connect( pBundle, 5 );// PORT FWD RETNN R-F-L 2
		dipIOM5[2][1].Connect( pBundle, 6 );// STBD FWD MRL LATCH IND 1
		dipIOM1[2][2].Connect( pBundle, 7 );// STBD FWD MRL RELEASE IND 1
		dipIOM12[2][1].Connect( pBundle, 8 );// STBD FWD MRL LATCH IND 2
		dipIOM7[2][2].Connect( pBundle, 9 );// STBD FWD MRL RELEASE IND 2
		dipIOM10[2][1].Connect( pBundle, 10 );// STBD FWD RETNN R-F-L 1
		dipIOM12[0][1].Connect( pBundle, 11 );// STBD FWD RETNN R-F-L 2
		return;
	}

	void SimpleMDM_OA2::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_OA2::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		if (!ReadEna) return;
		if (cw.MIAaddr != GetAddr()) return;

		unsigned short modecontrol = (cw.payload >> 9) & 0xF;
		unsigned short IOMaddr = (cw.payload >> 5) & 0xF;
		unsigned short IOMch = cw.payload & 0x1F;
		unsigned short IOMdata = 0;
		switch (modecontrol)
		{
			case 0b1000:// direct mode output (GPC-to-MDM)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AIS
						break;
					case 0b0001:// IOM 1 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM1 );
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM7 );
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM10 );
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM12 );
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIL
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AIS
						break;
					case 0b0001:// IOM 1 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM1 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM5 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM7 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM10 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM12 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIL
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_OA2::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// TODO power loss -> set outputs to 0
			}
			powered = false;
		}
		else
		{
			powered = true;
		}
		return;
	}
}
