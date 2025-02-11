/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/14   GLS
2020/04/28   GLS
2020/05/09   GLS
2020/05/17   GLS
2020/05/23   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/07/03   GLS
2020/07/16   GLS
2020/07/30   GLS
2020/08/06   GLS
2020/08/13   GLS
2020/08/14   GLS
2020/08/15   GLS
2020/08/16   GLS
2020/08/17   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/08/24   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/09/15   GLS
2020/09/17   GLS
2020/09/20   GLS
2020/09/24   GLS
2020/10/07   GLS
2020/10/17   GLS
2021/02/16   GLS
2021/04/07   GLS
2021/04/15   GLS
2021/06/13   GLS
2021/06/18   GLS
2021/06/19   GLS
2021/06/24   GLS
2021/06/28   GLS
2021/06/30   GLS
2021/07/01   GLS
2021/07/02   GLS
2021/07/27   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/12   GLS
2021/09/20   GLS
2021/09/21   GLS
2021/10/22   GLS
2021/10/23   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/19   GLS
2021/12/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/02/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/08/17   GLS
2022/09/29   GLS
2022/10/29   GLS
2022/10/30   GLS
2022/11/02   GLS
2022/11/03   GLS
2022/12/05   GLS
2022/12/20   GLS
2023/01/13   GLS
2023/02/05   GLS
2023/02/06   GLS
2023/02/12   GLS
2023/02/15   GLS
2023/02/16   GLS
2023/03/26   GLS
2023/04/12   GLS
2023/06/25   GLS
********************************************/
#include "PayloadBay.h"
#include "Atlantis.h"
#include "ExternalLight.h"
#include "Atlantis_vc_defs.h"
#include "ParameterValues.h"
#include "PRLA_defs.h"
#include "../CommonDefs.h"
#include <CCTVCameraPTU.h>
#include "CCTVCameraPTU_LED.h"
#include <CCTVCamera.h>
#include "VideoControlUnit.h"
#include "meshres.h"
#include "meshres_bay13mli.h"
#include "meshres_bay13liner.h"
#include <MathSSV.h>
#include <EngConst.h>
#include "eva_docking/ExtAirlock.h"
#include "eva_docking/TunnelAdapterAssembly.h"
#include "ASE_IUS.h"
#include "CISS.h"
#include "eps/PRSD.h"
#include "SPDS.h"


const static char* MESHNAME_PRLA_PORT_PASSIVE = "SSV\\OV\\PRLA_Port_Passive";
const static char* MESHNAME_PRLA_STBD_PASSIVE = "SSV\\OV\\PRLA_Starboard_Passive";
const static char* MESHNAME_PKA = "SSV\\OV\\PKA";
const static char* MESHNAME_BRIDGEFITTING_LONGERON_PORT[13] = {
	"SSV\\OV\\BridgeFittingLongeronPortBay1",
	"SSV\\OV\\BridgeFittingLongeronPortBay2",
	"SSV\\OV\\BridgeFittingLongeronPortBay3",
	"SSV\\OV\\BridgeFittingLongeronPortBay4",
	"SSV\\OV\\BridgeFittingLongeronPortBay5",
	"SSV\\OV\\BridgeFittingLongeronPortBay6",
	"SSV\\OV\\BridgeFittingLongeronPortBay7",
	"SSV\\OV\\BridgeFittingLongeronPortBay8",
	"SSV\\OV\\BridgeFittingLongeronPortBay9",
	"SSV\\OV\\BridgeFittingLongeronPortBay10",
	"SSV\\OV\\BridgeFittingLongeronPortBay11",
	"SSV\\OV\\BridgeFittingLongeronPortBay12",
	"SSV\\OV\\BridgeFittingLongeronPortBay13"
	};
const static char* MESHNAME_BRIDGEFITTING_LONGERON_STBD[13] = {
	"SSV\\OV\\BridgeFittingLongeronStarboardBay1",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay2",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay3",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay4",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay5",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay6",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay7",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay8",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay9",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay10",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay11",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay12",
	"SSV\\OV\\BridgeFittingLongeronStarboardBay13"
	};
const static char* MESHNAME_BRIDGEFITTING_KEEL[12] = {
	"SSV\\OV\\BridgeFittingKeelBay1",
	"SSV\\OV\\BridgeFittingKeelBay2",
	"SSV\\OV\\BridgeFittingKeelBay3",
	"SSV\\OV\\BridgeFittingKeelBay4",
	"SSV\\OV\\BridgeFittingKeelBay5",
	"SSV\\OV\\BridgeFittingKeelBay6",
	"SSV\\OV\\BridgeFittingKeelBay7",
	"SSV\\OV\\BridgeFittingKeelBay8",
	"SSV\\OV\\BridgeFittingKeelBay9",
	"SSV\\OV\\BridgeFittingKeelBay10",
	"SSV\\OV\\BridgeFittingKeelBay11",
	"SSV\\OV\\BridgeFittingKeelBay12"
	};

const static char* MESHNAME_PLBMLI[13] = {
	"SSV\\OV\\PLBMLIBay1",
	"SSV\\OV\\PLBMLIBay2",
	"SSV\\OV\\PLBMLIBay3",
	"SSV\\OV\\PLBMLIBay4",
	"SSV\\OV\\PLBMLIBay5",
	"SSV\\OV\\PLBMLIBay6",
	"SSV\\OV\\PLBMLIBay7",
	"SSV\\OV\\PLBMLIBay8",
	"SSV\\OV\\PLBMLIBay9",
	"SSV\\OV\\PLBMLIBay10",
	"SSV\\OV\\PLBMLIBay11",
	"SSV\\OV\\PLBMLIBay12",
	"SSV\\OV\\PLBMLIBay13"
	};
const static char* MESHNAME_PLBMLIKEELGAP[11] = {
	"SSV\\OV\\PLBMLIKeelGapBay1",
	"SSV\\OV\\PLBMLIKeelGapBay2",
	"SSV\\OV\\PLBMLIKeelGapBay3",
	"SSV\\OV\\PLBMLIKeelGapBay4",
	"SSV\\OV\\PLBMLIKeelGapBay5",
	"SSV\\OV\\PLBMLIKeelGapBay6",
	"SSV\\OV\\PLBMLIKeelGapBay7",
	"SSV\\OV\\PLBMLIKeelGapBay8",
	"SSV\\OV\\PLBMLIKeelGapBay9",
	"SSV\\OV\\PLBMLIKeelGapBay10",
	"SSV\\OV\\PLBMLIKeelGapBay11"
	};
const static char* MESHNAME_PLBMLIMMUGAP = "SSV\\OV\\PLBMLIMMUGapBay1";
const static char* MESHNAME_PLBMLIKEELMMUGAPS = "SSV\\OV\\PLBMLIKeelMMUGapsBay1";
const static char* MESHNAME_PLBMLIEXTALODSGAP = "SSV\\OV\\PLBMLIExtALODSGapBay2";
const static char* MESHNAME_PLBMLIKEELEXTALODSGAPS = "SSV\\OV\\PLBMLIKeelExtALODSGapsBay2";
const static char* MESHNAME_PLBMLIEDOGAP = "SSV\\OV\\PLBMLIEDOGapBay11";
const static char* MESHNAME_PLBMLIKEELEDOGAPS = "SSV\\OV\\PLBMLIKeelEDOGapsBay11";

const static char* MESHNAME_PLBLINER[13] = {
	"SSV\\OV\\PLBLinerBay1",
	"SSV\\OV\\PLBLinerBay2",
	"SSV\\OV\\PLBLinerBay3",
	"SSV\\OV\\PLBLinerBay4",
	"SSV\\OV\\PLBLinerBay5",
	"SSV\\OV\\PLBLinerBay6",
	"SSV\\OV\\PLBLinerBay7",
	"SSV\\OV\\PLBLinerBay8",
	"SSV\\OV\\PLBLinerBay9",
	"SSV\\OV\\PLBLinerBay10",
	"SSV\\OV\\PLBLinerBay11",
	"SSV\\OV\\PLBLinerBay12",
	"SSV\\OV\\PLBLinerBay13"
	};
const static char* MESHNAME_PLBLINERKEELGAP[11] = {
	"SSV\\OV\\PLBLinerKeelGapBay1",
	"SSV\\OV\\PLBLinerKeelGapBay2",
	"SSV\\OV\\PLBLinerKeelGapBay3",
	"SSV\\OV\\PLBLinerKeelGapBay4",
	"SSV\\OV\\PLBLinerKeelGapBay5",
	"SSV\\OV\\PLBLinerKeelGapBay6",
	"SSV\\OV\\PLBLinerKeelGapBay7",
	"SSV\\OV\\PLBLinerKeelGapBay8",
	"SSV\\OV\\PLBLinerKeelGapBay9",
	"SSV\\OV\\PLBLinerKeelGapBay10",
	"SSV\\OV\\PLBLinerKeelGapBay11"
	};
const static char* MESHNAME_PLBLINERMMUGAPS = "SSV\\OV\\PLBLinerMMUGapBay1";
const static char* MESHNAME_PLBLINERKEELMMUGAPS = "SSV\\OV\\PLBLinerKeelMMUGapsBay1";
const static char* MESHNAME_PLBLINEREXTALODSGAPS = "SSV\\OV\\PLBLinerExtALODSGapBay2";
const static char* MESHNAME_PLBLINERKEELEXTALODSGAPS = "SSV\\OV\\PLBLinerKeelExtALODSGapsBay2";
const static char* MESHNAME_PLBLINERFILTER4GAP = "SSV\\OV\\PLBLinerFilter4GapBay6";
const static char* MESHNAME_PLBLINERKEELFILTER4GAPS = "SSV\\OV\\PLBLinerKeelFilter4GapsBay6";
const static char* MESHNAME_PLBLINEREDOGAPS = "SSV\\OV\\PLBLinerEDOGapBay11";
const static char* MESHNAME_PLBLINERKEELEDOGAPS = "SSV\\OV\\PLBLinerKeelEDOGapsBay11";

const static char* MESHNAME_DFI_WIRETRAY = "SSV\\OV\\DFI_WireTray";
const static char* MESHNAME_EDO_KIT = "SSV\\OV\\EDO_Kit";
const static char* MESHNAME_EXTAL_ODS_KIT = "SSV\\OV\\ExtAL_ODS_Kit";


constexpr int Bay_PLID[13] = {160, 175, 189, 204, 218, 232, 248, 263, 276, 289, 302, 316, 330};// last PLID of bay
constexpr double Bay_Xo[13] = {609.0, 664.5, 721.5, 778.5, 835.0, 891.0, 949.25, 1009.75, 1065.165, 1115.5, 1165.835, 1220.0, 1278.0};// Xo of mid bay attachment

const VECTOR3 PASSIVE_FWD_POS = _V( 0.0, -2.839465, 0.0 );// Yo0.0, Zo+305.025 (fwd of 1191.0)
const VECTOR3 PASSIVE_AFT_POS = _V( 0.0, -2.75374, 0.0 );// Yo0.0, Zo+308.40 (aft of 1191.0)
const VECTOR3 PASSIVE_PORT_POS = _V( -2.3876, -0.0715, 0.0 );// Yo-94.0, Zo+414.0
const VECTOR3 PASSIVE_STBD_POS = _V( 2.3876, -0.0715, 0.0 );// Yo+94.0, Zo+414.0
const VECTOR3 PASSIVE_DIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 PASSIVE_ROT = _V( 0.0, 0.0, 1.0 );

const VECTOR3 BAYBRIDGE_PORT_POS = _V( -2.3876, -0.2239, 0.0 );// Yo-94.0, Zo+408.0
const VECTOR3 BAYBRIDGE_PORT_DIR = _V( 1.0, 0.0, 0.0 );
const VECTOR3 BAYBRIDGE_PORT_ROT = _V( 0.0, 1.0, 0.0 );

const VECTOR3 BAYBRIDGE_STBD_POS = _V( 2.3876, -0.2239, 0.0 );// Yo+94.0, Zo+408.0
const VECTOR3 BAYBRIDGE_STBD_DIR = _V( -1.0, 0.0, 0.0 );
const VECTOR3 BAYBRIDGE_STBD_ROT = _V( 0.0, 1.0, 0.0 );

const VECTOR3 BAYBRIDGE_KEEL_POS = _V( 0.0, -2.8147, 0.0 );// Yo0.0, Zo+306.0
const VECTOR3 BAYBRIDGE_KEEL_DIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 BAYBRIDGE_KEEL_ROT = _V( 0.0, 0.0, 1.0 );


// ============================================================
// Payload Bay Door animation constants
// ============================================================
const double PLBD_MOTOR_RANGE = 134.0 * RAD;// tunes how much the doors open

const VECTOR3 PLBD_PORT_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 PLBD_PORT_P1 = _V( -2.322369, 0.144027, 0.0 );// crank/link rod axis
const VECTOR3 PLBD_PORT_P2 = _V( -2.544433, 0.175146, 0.0 );// link rod/door axis
const VECTOR3 PLBD_PORT_P3 = _V( -2.699512, 0.0809, 0.0 );// door axis
const VECTOR3 PLBD_PORT_P4 = _V( -2.60023, -0.014955, 0.0 );// crank axis
const VECTOR3 PLBD_PORT_P5 = _V( -2.510697, -0.11277, 0.0 );// push rod/crank axis
const VECTOR3 PLBD_PORT_P6 = _V( -2.517796, -0.412041, 0.0 );// torque shaft/push rod axis
const VECTOR3 PLBD_PORT_P7 = _V( -2.46461, -0.311697, 0.0 );// torque shaft axis
const VECTOR3 PLBD_PORT_P8 = _V( -2.530729, -0.017906, 0.0 );// longeron/slidewire link axis
const VECTOR3 PLBD_PORT_P9 = _V( -2.41587, 0.367539, 0.0 );// slidewire link/slidewire bracket axis
const VECTOR3 PLBD_PORT_P10 = _V( -2.519756, 0.2245624, 0.0 );// slidewire bracket/door axis

const VECTOR3 PLBD_STBD_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 PLBD_STBD_P1 = _V( 2.322369, 0.144027, 0.0 );// crank/link rod axis
const VECTOR3 PLBD_STBD_P2 = _V( 2.544433, 0.175146, 0.0 );// link rod/door axis
const VECTOR3 PLBD_STBD_P3 = _V( 2.699512, 0.0809, 0.0 );// door axis
const VECTOR3 PLBD_STBD_P4 = _V( 2.60023, -0.014955, 0.0 );// crank axis
const VECTOR3 PLBD_STBD_P5 = _V( 2.510697, -0.11277, 0.0 );// push rod/crank axis
const VECTOR3 PLBD_STBD_P6 = _V( 2.517796, -0.412041, 0.0 );// torque shaft/push rod axis
const VECTOR3 PLBD_STBD_P7 = _V( 2.46461, -0.311697, 0.0 );// torque shaft axis
const VECTOR3 PLBD_STBD_P8 = _V( 2.530729, -0.017906, 0.0 );// longeron/slidewire link axis
const VECTOR3 PLBD_STBD_P9 = _V( 2.41587, 0.367539, 0.0 );// slidewire link/slidewire bracket axis
const VECTOR3 PLBD_STBD_P10 = _V( 2.519756, 0.2245624, 0.0 );// slidewire bracket/door axis


const VECTOR3 CL_LATCH_AXIS = _V( 0.050577, 2.01893, 0.0 );


const VECTOR3 KUBANDANTENNA_DA_REF = _V( 2.52984, 0.1317, 9.2784 );// [m] (Xo+589.0, Yo+99.6, Zo+422.0)
const VECTOR3 KUBANDANTENNA_DA_DIR = _V( 0.0, 1.0, 0.0 );


// ============================================================
// Radiator animation constants
// ============================================================
const float RADIATOR_DEPLOY = static_cast<float>(35.5 * RAD);

const VECTOR3 RADIATOR_PORT_AXIS = _V( -2.573477, 0.150136, 0.0 );
const VECTOR3 RADIATOR_PORT_DIR = _V( 0.0, 0.0, -1.0 );

const VECTOR3 RADIATOR_STBD_AXIS = _V( 2.573477, 0.150136, 0.0 );
const VECTOR3 RADIATOR_STBD_DIR = _V( 0.0, 0.0, 1.0 );


constexpr double PLBD_OPERATING_SPEED = 1.0 / (126.0 - 1.0);// Opening/closing speed of payload bay doors (single motor) [1/s]
constexpr double PLBD_CENTERLINE_LATCH_OPERATING_SPEED = 1.0 / (40.0 - 1.0);// Opening/closing speed of payload bay door centerline latch gang (single motor) [1/s]
constexpr double PLBD_BULKHEAD_LATCH_OPERATING_SPEED = 1.0 / (60.0 - 1.0);// Opening/closing speed of payload bay door bulkhead latch gang (single motor) [1/s]
// HACK 1-second subtraction above is to account for "command/data transport time" between GPC and motors, to allow operation in single motor

constexpr double RAD_OPERATING_SPEED = 1.0 / 100.0;// Deployment/stowing speed of radiators (single motor) [1/s]
constexpr double RADLATCH_OPERATING_SPEED = 1.0 / 60.0;// Release/engaging speed of radiator latches (single motor) [1/s]

constexpr double KU_OPERATING_SPEED = 1.0 / 46.0;// Deployment speed of the Ku Band antenna (single motor) [1/s]


// lights
const VECTOR3 PLB_LIGHT_FWD_STBD_POS = _V( 1.4224, -2.32702, 5.37052 );
const VECTOR3 PLB_LIGHT_FWD_STBD_DIR = _V( -0.642788, 0.766044, 0.0 );

const VECTOR3 PLB_LIGHT_FWD_PORT_POS = _V( -1.2192, -2.4591, 5.008 );
const VECTOR3 PLB_LIGHT_FWD_PORT_DIR = _V( 0.642788, 0.766044, 0.0 );

const VECTOR3 PLB_LIGHT_MID_STBD_POS = _V( 1.37922, -2.36004, -0.461479 );
const VECTOR3 PLB_LIGHT_MID_STBD_DIR = _V( -0.642788, 0.766044, 0.0 );

const VECTOR3 PLB_LIGHT_MID_PORT_POS = _V( -1.37922, -2.36004, -0.461479 );
const VECTOR3 PLB_LIGHT_MID_PORT_DIR = _V( 0.642788, 0.766044, 0.0 );

const VECTOR3 PLB_LIGHT_AFT_STBD_POS = _V( 1.4224, -2.33464, -4.55448 );
const VECTOR3 PLB_LIGHT_AFT_STBD_DIR = _V( -0.642788, 0.766044, 0.0 );

const VECTOR3 PLB_LIGHT_AFT_PORT_POS = _V( -1.4224, -2.33464, -4.55448 );
const VECTOR3 PLB_LIGHT_AFT_PORT_DIR = _V( 0.642788, 0.766044, 0.0 );

const VECTOR3 FWD_BLKD_LIGHT_POS = _V( 0.0, 1.654313, 9.459756 );
const VECTOR3 FWD_BLKD_LIGHT_DIR = _V( 0.0, 0.0, -1.0 );

const VECTOR3 DOCKING_LIGHT_POS = _V( 0.0, 1.8843, 9.399651 );
const VECTOR3 DOCKING_LIGHT_DIR = _V( 0.0, 1.0, 0.0 );

constexpr double PLB_LIGHT_RANGE = 20.0;// [m]
const double PLB_LIGHT_UMBRA_ANGLE = 120.0 * RAD;// [rad]
const double PLB_LIGHT_PENUMBRA_ANGLE = PLB_LIGHT_UMBRA_ANGLE + (20.0 * RAD);// [rad]

const double FWD_DOCK_LIGHT_UMBRA_ANGLE = 135.0 * RAD;// [rad]
const double FWD_DOCK_LIGHT_PENUMBRA_ANGLE = FWD_DOCK_LIGHT_UMBRA_ANGLE + (20.0 * RAD);// [rad]

constexpr double PLB_LIGHT_ATT0 = 0.5;// [1]
constexpr double PLB_LIGHT_ATT1 = 0.0;// [1]
constexpr double PLB_LIGHT_ATT2 = 0.05;// [1]


inline constexpr char MESHNAME_PLB_CCTV_CAMERA_506_508[] = "SSV\\OV\\PLB_CCTVCamera_506_508";
inline constexpr char MESHNAME_PLB_CCTV_CAMERA_CTVC_ITVC[] = "SSV\\OV\\PLB_CCTVCamera_CTVC_ITVC";
inline constexpr char MESHNAME_KEEL_CCTV_CAMERA[] = "SSV\\OV\\Keel_CCTVCamera";

const UINT PLB_CCTV_CAMERA_506_508_base_Grp[1] = {4};
constexpr UINT PLB_CCTV_CAMERA_506_508_base_Grp_Sz = 1;
const UINT PLB_CCTV_CAMERA_506_508_PAN_Grp[3] = {1, 2, 3};
constexpr UINT PLB_CCTV_CAMERA_506_508_PAN_Grp_Sz = 3;
const UINT PLB_CCTV_CAMERA_506_508_TILT_Grp[1] = {0};
constexpr UINT PLB_CCTV_CAMERA_506_508_TILT_Grp_Sz = 1;

const UINT PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp[1] = {9};
constexpr UINT PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp_Sz = 1;
const UINT PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp[3] = {1, 2, 8};
constexpr UINT PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp_Sz = 3;
const UINT PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp[6] = {0, 3, 4, 5, 6, 7};
constexpr UINT PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp_Sz = 6;


const VECTOR3 CAM_A_POS = _V( -1.8161, 0.742824, 9.284496 );// Xo+588.76, Yo-71.5, Zo+446.06
const VECTOR3 CAM_B_POS = _V( -2.2098, 0.7413, -8.622504 );// Xo+1293.76, Yo-87.0, Zo+446.0
const VECTOR3 CAM_C_POS = _V( 2.2098, 0.7413, -8.622504 );// Xo+1293.76, Yo+87.0, Zo+446.0
const VECTOR3 CAM_D_POS = _V( 1.8161, 0.742824, 9.284496 );// Xo+588.76, Yo+71.5, Zo+446.06


constexpr VECTOR3 AFT_WINCH_EDO_PALLET_1_OFFSET = {0.0, -0.15, 2.389};// [m]
constexpr VECTOR3 AFT_WINCH_EDO_PALLET_2_OFFSET = {0.0, -0.15, 3.5447};// [m]


// keel camera position data
constexpr double Yo_Generic = -1.40;
constexpr double Yo_226 = -4.0;
constexpr double Yo_280 = -2.80;

constexpr double Zo_Generic = 316.14 - 7.0/*lens offset*/;
constexpr double Zo_226_280 = 317.19 - 7.0/*lens offset*/;


PayloadBay::PayloadBay( AtlantisSubsystemDirector* _director, const mission::MissionPayloads& payloads, const mission::PLB_Cameras& plbcameras, const std::string& orbiter, bool KuBandAntenna, bool FwdBulkDockLights, bool Liner, bool DFIWireTray, bool VentDoors4and7, bool EDOKit, bool ExtALODSKit )
	:AtlantisSubsystem( _director, "PayloadBay" ), hasAntenna(KuBandAntenna), hasFwdBulkDockLights(FwdBulkDockLights),
	hasLiner(Liner), hasAftHandrails(true), hasEDOKit(EDOKit), hasBay13covers(true), hasT4panelcovers(true), hasDumpLinecovers(true), hasDFIWireTray(DFIWireTray),
	hasVentDoors4and7(VentDoors4and7), hasExtALODSKit(ExtALODSKit), EDOpallet(0), payloads(payloads), plbcameras(plbcameras), mesh_plbcamera{MESH_UNDEFINED, MESH_UNDEFINED, MESH_UNDEFINED, MESH_UNDEFINED},
	mesh_keelcamera(MESH_UNDEFINED), cameras{NULL, NULL, NULL, NULL}, keelcamera(NULL)
{
	hasOriginalHandrails = (orbiter == "Columbia") || (orbiter == "Challenger");
	hasMMUFSSInterfacePanel = (orbiter != "Columbia");

	// Payload bay doors
	posplbd_port = 0.0;
	posplbd_stbd = 0.0;
	posplbd_latch_cl_1_4 = 0.0;
	posplbd_latch_cl_5_8 = 0.0;
	posplbd_latch_cl_9_12 = 0.0;
	posplbd_latch_cl_13_16 = 0.0;
	posplbd_latch_blkd_port_fwd = 0.0;
	posplbd_latch_blkd_port_aft = 0.0;
	posplbd_latch_blkd_stbd_fwd = 0.0;
	posplbd_latch_blkd_stbd_aft = 0.0;

	// Radiators
	posradiator_port = 0.0;
	posradiator_stbd = 0.0;
	posradiator_latch_port_1_6 = 0.0;
	posradiator_latch_port_7_12 = 0.0;
	posradiator_latch_stbd_1_6 = 0.0;
	posradiator_latch_stbd_7_12 = 0.0;

	// Ku-band antenna
	poskuband = 0.0;
	DAparent = NULL;
	anim_da = MESH_UNDEFINED;

	for (int i = 0; i < 5; i++)
	{
		ahPassive[i] = NULL;
		Passive_pos[i] = PASSIVE_AFT_POS;// default
	}

	for (int i = 0; i < 8; i++)
	{
		ahBayBridge[i] = NULL;
		BayBridge_pos[i] = BAYBRIDGE_PORT_POS;// default
		BayBridge_dir[i] = BAYBRIDGE_PORT_DIR;// default
		BayBridge_rot[i] = BAYBRIDGE_PORT_ROT;// default
	}

	mesh_PLB_bay13 = MESH_UNDEFINED;

	for (int i = 0; i < 11; i++)
	{
		hasKeelBridge[i] = false;
	}

	// lights
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_FWD_STBD_POS, PLB_LIGHT_FWD_STBD_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_FWD_PORT_POS, PLB_LIGHT_FWD_PORT_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_MID_STBD_POS, PLB_LIGHT_MID_STBD_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_MID_PORT_POS, PLB_LIGHT_MID_PORT_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_AFT_STBD_POS, PLB_LIGHT_AFT_STBD_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	lights.push_back( new ExternalLight( STS(), PLB_LIGHT_AFT_PORT_POS, PLB_LIGHT_AFT_PORT_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, PLB_LIGHT_UMBRA_ANGLE, PLB_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
	if (hasFwdBulkDockLights)
	{
		lights.push_back( new ExternalLight( STS(), FWD_BLKD_LIGHT_POS, FWD_BLKD_LIGHT_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, FWD_DOCK_LIGHT_UMBRA_ANGLE, FWD_DOCK_LIGHT_PENUMBRA_ANGLE, HG_VAPOR ) );
		lights.push_back( new ExternalLight( STS(), DOCKING_LIGHT_POS, DOCKING_LIGHT_DIR, 0.0f, 0.0f, PLB_LIGHT_RANGE, PLB_LIGHT_ATT0, PLB_LIGHT_ATT1, PLB_LIGHT_ATT2, FWD_DOCK_LIGHT_UMBRA_ANGLE, FWD_DOCK_LIGHT_PENUMBRA_ANGLE, INCANDESCENT ) );
	}

	CreateCCTV();
	return;
}

PayloadBay::~PayloadBay( void )
{
	for (auto& x : lights) delete x;

	if (cameras[0]) delete cameras[0];
	if (cameras[1]) delete cameras[1];
	if (cameras[2]) delete cameras[2];
	if (cameras[3]) delete cameras[3];
	if (keelcamera) delete keelcamera;
	return;
}

bool PayloadBay::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "DOOR_PORT", 9 ))
	{
		sscanf_s( (char*)(line + 9), "%lf", &posplbd_port );
		posplbd_port = range( 0.0, posplbd_port, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_STBD", 9 ))
	{
		sscanf_s( (char*)(line + 9), "%lf", &posplbd_stbd );
		posplbd_stbd = range( 0.0, posplbd_stbd, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_CL_1_4", 17 ))
	{
		sscanf_s( (char*)(line + 17), "%lf", &posplbd_latch_cl_1_4 );
		posplbd_latch_cl_1_4 = range( 0.0, posplbd_latch_cl_1_4, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_CL_5_8", 17 ))
	{
		sscanf_s( (char*)(line + 17), "%lf", &posplbd_latch_cl_5_8 );
		posplbd_latch_cl_5_8 = range( 0.0, posplbd_latch_cl_5_8, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_CL_9_12", 18 ))
	{
		sscanf_s( (char*)(line + 18), "%lf", &posplbd_latch_cl_9_12 );
		posplbd_latch_cl_9_12 = range( 0.0, posplbd_latch_cl_9_12, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_CL_13_16", 19 ))
	{
		sscanf_s( (char*)(line + 19), "%lf", &posplbd_latch_cl_13_16 );
		posplbd_latch_cl_13_16 = range( 0.0, posplbd_latch_cl_13_16, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_BLKD_PORT_FWD", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posplbd_latch_blkd_port_fwd );
		posplbd_latch_blkd_port_fwd = range( 0.0, posplbd_latch_blkd_port_fwd, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_BLKD_PORT_AFT", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posplbd_latch_blkd_port_aft );
		posplbd_latch_blkd_port_aft = range( 0.0, posplbd_latch_blkd_port_aft, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_BLKD_STBD_FWD", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posplbd_latch_blkd_stbd_fwd );
		posplbd_latch_blkd_stbd_fwd = range( 0.0, posplbd_latch_blkd_stbd_fwd, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "DOOR_LATCH_BLKD_STBD_AFT", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posplbd_latch_blkd_stbd_aft );
		posplbd_latch_blkd_stbd_aft = range( 0.0, posplbd_latch_blkd_stbd_aft, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_PORT", 13 ))
	{
		sscanf_s( (char*)(line + 13), "%lf", &posradiator_port );
		posradiator_port = range( 0.0, posradiator_port, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_STBD", 13 ))
	{
		sscanf_s( (char*)(line + 13), "%lf", &posradiator_stbd );
		posradiator_stbd = range( 0.0, posradiator_stbd, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_LATCH_PORT_1_6", 23 ))
	{
		sscanf_s( (char*)(line + 23), "%lf", &posradiator_latch_port_1_6 );
		posradiator_latch_port_1_6 = range( 0.0, posradiator_latch_port_1_6, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_LATCH_PORT_7_12", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posradiator_latch_port_7_12 );
		posradiator_latch_port_7_12 = range( 0.0, posradiator_latch_port_7_12, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_LATCH_STBD_1_6", 23 ))
	{
		sscanf_s( (char*)(line + 23), "%lf", &posradiator_latch_stbd_1_6 );
		posradiator_latch_stbd_1_6 = range( 0.0, posradiator_latch_stbd_1_6, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RADIATOR_LATCH_STBD_7_12", 24 ))
	{
		sscanf_s( (char*)(line + 24), "%lf", &posradiator_latch_stbd_7_12 );
		posradiator_latch_stbd_7_12 = range( 0.0, posradiator_latch_stbd_7_12, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "CAM_A", 5 ))
	{
		if (cameras[0]) cameras[0]->LoadState( line + 5 );
	}
	else if (!_strnicmp( line, "CAM_B", 5 ))
	{
		if (cameras[1]) cameras[1]->LoadState( line + 5 );
	}
	else if (!_strnicmp( line, "CAM_C", 5 ))
	{
		if (cameras[2]) cameras[2]->LoadState( line + 5 );
	}
	else if (!_strnicmp( line, "CAM_D", 5 ))
	{
		if (cameras[3]) cameras[3]->LoadState( line + 5 );
	}
	else if (!_strnicmp( line, "KU_BAND", 7 ))
	{
		sscanf_s( (char*)(line + 7), "%lf", &poskuband );
		poskuband = range( 0.0, poskuband, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "KEEL_CAM", 8 ))
	{
		if (keelcamera) keelcamera->LoadState( line + 8 );
	}
	return false;
}

void PayloadBay::OnSaveState( FILEHANDLE scn ) const
{
	char cbuf[256];

	oapiWriteScenario_float( scn, "DOOR_PORT", posplbd_port );
	oapiWriteScenario_float( scn, "DOOR_STBD", posplbd_stbd );
	oapiWriteScenario_float( scn, "DOOR_LATCH_CL_1_4", posplbd_latch_cl_1_4 );
	oapiWriteScenario_float( scn, "DOOR_LATCH_CL_5_8", posplbd_latch_cl_5_8 );
	oapiWriteScenario_float( scn, "DOOR_LATCH_CL_9_12", posplbd_latch_cl_9_12 );
	oapiWriteScenario_float( scn, "DOOR_LATCH_CL_13_16", posplbd_latch_cl_13_16 );
	oapiWriteScenario_float( scn, "DOOR_LATCH_BLKD_PORT_FWD", posplbd_latch_blkd_port_fwd );
	oapiWriteScenario_float( scn, "DOOR_LATCH_BLKD_PORT_AFT", posplbd_latch_blkd_port_aft );
	oapiWriteScenario_float( scn, "DOOR_LATCH_BLKD_STBD_FWD", posplbd_latch_blkd_stbd_fwd );
	oapiWriteScenario_float( scn, "DOOR_LATCH_BLKD_STBD_AFT", posplbd_latch_blkd_stbd_aft );

	oapiWriteScenario_float( scn, "RADIATOR_PORT", posradiator_port );
	oapiWriteScenario_float( scn, "RADIATOR_STBD", posradiator_stbd );
	oapiWriteScenario_float( scn, "RADIATOR_LATCH_PORT_1_6", posradiator_latch_port_1_6 );
	oapiWriteScenario_float( scn, "RADIATOR_LATCH_PORT_7_12", posradiator_latch_port_7_12 );
	oapiWriteScenario_float( scn, "RADIATOR_LATCH_STBD_1_6", posradiator_latch_stbd_1_6 );
	oapiWriteScenario_float( scn, "RADIATOR_LATCH_STBD_7_12", posradiator_latch_stbd_7_12 );

	if (cameras[0])
	{
		cameras[0]->SaveState( cbuf );
		oapiWriteScenario_string( scn, "CAM_A", cbuf );
	}
	if (cameras[1])
	{
		cameras[1]->SaveState( cbuf );
		oapiWriteScenario_string( scn, "CAM_B", cbuf );
	}
	if (cameras[2])
	{
		cameras[2]->SaveState( cbuf );
		oapiWriteScenario_string( scn, "CAM_C", cbuf );
	}
	if (cameras[3])
	{
		cameras[3]->SaveState( cbuf );
		oapiWriteScenario_string( scn, "CAM_D", cbuf );
	}

	if (hasAntenna == true) oapiWriteScenario_float( scn, "KU_BAND", poskuband );

	if (keelcamera)
	{
		keelcamera->SaveState( cbuf );
		oapiWriteScenario_string( scn, "KEEL_CAM", cbuf );
	}
	return;
}

void PayloadBay::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MMC_POWER", 16 );
	MNA_MMC1.Connect( pBundle, 0 );
	MNB_MMC1.Connect( pBundle, 1 );
	MNB_MMC2.Connect( pBundle, 2 );
	MNC_MMC2.Connect( pBundle, 3 );
	MNA_MMC3.Connect( pBundle, 4 );
	MNB_MMC3.Connect( pBundle, 5 );
	MNB_MMC4.Connect( pBundle, 6 );
	MNC_MMC4.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "PLBD_PORT_PDU", 16 );
	PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_FWD_RDY_LATCH_1.Connect( pBundle, 2 );
	PORT_FWD_RDY_LATCH_2.Connect( pBundle, 3 );
	PORT_FWD_RDY_LATCH_3.Connect( pBundle, 4 );
	PORT_AFT_RDY_LATCH_1.Connect( pBundle, 5 );
	PORT_AFT_RDY_LATCH_2.Connect( pBundle, 6 );
	PORT_AFT_RDY_LATCH_3.Connect( pBundle, 7 );
	PORT_DOOR_CLOSE_1.Connect( pBundle, 8 );
	PORT_DOOR_CLOSE_2.Connect( pBundle, 9 );
	PORT_DOOR_OPEN_1.Connect( pBundle, 10 );
	PORT_DOOR_OPEN_2.Connect( pBundle, 11 );
	PORT_FWD_88.Connect( pBundle, 12 );
	PORT_AFT_88.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "PLBD_STBD_PDU", 16 );
	STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR.Connect( pBundle, 0 );
	STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.Connect( pBundle, 1 );
	STBD_FWD_RDY_LATCH_1.Connect( pBundle, 2 );
	STBD_FWD_RDY_LATCH_2.Connect( pBundle, 3 );
	STBD_FWD_RDY_LATCH_3.Connect( pBundle, 4 );
	STBD_AFT_RDY_LATCH_1.Connect( pBundle, 5 );
	STBD_AFT_RDY_LATCH_2.Connect( pBundle, 6 );
	STBD_AFT_RDY_LATCH_3.Connect( pBundle, 7 );
	STBD_DOOR_CLOSE_1.Connect( pBundle, 8 );
	STBD_DOOR_CLOSE_2.Connect( pBundle, 9 );
	STBD_DOOR_OPEN_1.Connect( pBundle, 10 );
	STBD_DOOR_OPEN_2.Connect( pBundle, 11 );
	STBD_FWD_88.Connect( pBundle, 12 );
	STBD_AFT_88.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "PLBD_CL_1", 16 );
	CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.Connect( pBundle, 0 );
	LAT_1_4_LAT_1.Connect( pBundle, 1 );
	LAT_1_4_REL_1.Connect( pBundle, 2 );
	CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.Connect( pBundle, 3 );
	LAT_5_8_LAT_1.Connect( pBundle, 4 );
	LAT_5_8_REL_1.Connect( pBundle, 5 );
	CENTERLINE_ACTUATOR_9_12_MOTOR_1_PWR.Connect( pBundle, 6 );
	LAT_9_12_LAT_1.Connect( pBundle, 7 );
	LAT_9_12_REL_1.Connect( pBundle, 8 );
	CENTERLINE_ACTUATOR_13_16_MOTOR_1_PWR.Connect( pBundle, 9 );
	LAT_13_16_LAT_1.Connect( pBundle, 10 );
	LAT_13_16_REL_1.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_CL_2", 16 );
	CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.Connect( pBundle, 0 );
	LAT_1_4_LAT_2.Connect( pBundle, 1 );
	LAT_1_4_REL_2.Connect( pBundle, 2 );
	CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.Connect( pBundle, 3 );
	LAT_5_8_LAT_2.Connect( pBundle, 4 );
	LAT_5_8_REL_2.Connect( pBundle, 5 );
	CENTERLINE_ACTUATOR_9_12_MOTOR_2_PWR.Connect( pBundle, 6 );
	LAT_9_12_LAT_2.Connect( pBundle, 7 );
	LAT_9_12_REL_2.Connect( pBundle, 8 );
	CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.Connect( pBundle, 9 );
	LAT_13_16_LAT_2.Connect( pBundle, 10 );
	LAT_13_16_REL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_1", 16 );
	BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_1_PWR.Connect( pBundle, 0 );
	STBD_FWD_BLKHD_LAT_1.Connect( pBundle, 1 );
	STBD_FWD_BLKHD_REL_1.Connect( pBundle, 2 );
	BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_1_PWR.Connect( pBundle, 3 );
	STBD_AFT_BLKHD_LAT_1.Connect( pBundle, 4 );
	STBD_AFT_BLKHD_REL_1.Connect( pBundle, 5 );
	BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_1_PWR.Connect( pBundle, 6 );
	PORT_FWD_BLKHD_LAT_1.Connect( pBundle, 7 );
	PORT_FWD_BLKHD_REL_1.Connect( pBundle, 8 );
	BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.Connect( pBundle, 9 );
	PORT_AFT_BLKHD_LAT_1.Connect( pBundle, 10 );
	PORT_AFT_BLKHD_REL_1.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_2", 16 );
	BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_2_PWR.Connect( pBundle, 0 );
	STBD_FWD_BLKHD_LAT_2.Connect( pBundle, 1 );
	STBD_FWD_BLKHD_REL_2.Connect( pBundle, 2 );
	BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.Connect( pBundle, 3 );
	STBD_AFT_BLKHD_LAT_2.Connect( pBundle, 4 );
	STBD_AFT_BLKHD_REL_2.Connect( pBundle, 5 );
	BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_2_PWR.Connect( pBundle, 6 );
	PORT_FWD_BLKHD_LAT_2.Connect( pBundle, 7 );
	PORT_FWD_BLKHD_REL_2.Connect( pBundle, 8 );
	BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.Connect( pBundle, 9 );
	PORT_AFT_BLKHD_LAT_2.Connect( pBundle, 10 );
	PORT_AFT_BLKHD_REL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_1", 16 );
	PORT_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_RAD_LATCH_1_6_REL_1.Connect( pBundle, 1 );
	PORT_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 2 );
	STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_LATCH_1_6_REL_1.Connect( pBundle, 4 );
	STARBOARD_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 5 );
	PORT_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 6 );
	PORT_RAD_LATCH_7_12_REL_1.Connect( pBundle, 7 );
	PORT_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 8 );
	STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_LATCH_7_12_REL_1.Connect( pBundle, 10 );
	STARBOARD_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_2", 16 );
	PORT_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 0 );
	PORT_RAD_LATCH_1_6_REL_2.Connect( pBundle, 1 );
	PORT_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 2 );
	STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_LATCH_1_6_REL_2.Connect( pBundle, 4 );
	STARBOARD_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 5 );
	PORT_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 6 );
	PORT_RAD_LATCH_7_12_REL_2.Connect( pBundle, 7 );
	PORT_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 8 );
	STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_LATCH_7_12_REL_2.Connect( pBundle, 10 );
	STARBOARD_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RadiatorMotorInd", 16 );
	PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 1 );
	PORT_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 2 );
	STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 4 );
	STARBOARD_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 5 );
	PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 6 );
	PORT_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 7 );
	PORT_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 8 );
	STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 10 );
	STARBOARD_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 11 );

	if (hasAntenna == true)
	{
		pBundle = BundleManager()->CreateBundle( "KuBandAntennaMotorInd", 16 );
		KU_RNDZ_RADAR_MOTOR_1_PWR.Connect( pBundle, 0 );
		KU_RNDZ_RADAR_STO_IND_1.Connect( pBundle, 1 );
		KU_RNDZ_RADAR_DPY_IND_1.Connect( pBundle, 2 );
		KU_RNDZ_RADAR_MOTOR_2_PWR.Connect( pBundle, 3 );
		KU_RNDZ_RADAR_STO_IND_2.Connect( pBundle, 4 );
		KU_RNDZ_RADAR_DPY_IND_2.Connect( pBundle, 5 );
		KU_RNDZ_RADAR_STO_IND.Connect( pBundle, 6 );
		KU_RNDZ_RADAR_DPY_IND.Connect( pBundle, 7 );
	}

	pBundle = BundleManager()->CreateBundle( "PLB_LIGHTS", 16 );
	for (int i = 0; i < 6; i++)
	{
		lights[i]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, i );
	}
	lights[0]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_FWD_STBD );
	lights[1]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_FWD_PORT );
	lights[2]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_MID_STBD );
	lights[3]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_MID_PORT );
	lights[4]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_AFT_STBD );
	lights[5]->DefineMeshGroup( STS()->OVmesh(), GRP_PLB_LIGHT_AFT_PORT );
	if (hasFwdBulkDockLights)
	{
		lights[6]->DefineState( 1, 0.5f, 0.25f, 1.0f, pBundle, 6 );
		lights[7]->DefineState( 1, 0.5f, 0.0f, 0.6f, pBundle, 7 );
		lights[7]->DefineState( 2, 0.5f, 0.0f, 1.0f, pBundle, 8 );

		lights[6]->DefineMeshGroup( STS()->OVmesh(), GRP_FWD_BULKHEAD_LIGHT );
		lights[7]->DefineMeshGroup( STS()->OVmesh(), GRP_DOCKING_LIGHT );
	}

	HandleSubsystemsVisuals();

	DefineAnimations();

	SetPayloadBayDoorPosition( 0, posplbd_port );
	SetPayloadBayDoorPosition( 1, posplbd_stbd );
	SetPayloadBayDoorLatchPosition( 0, posplbd_latch_cl_1_4 );
	SetPayloadBayDoorLatchPosition( 1, posplbd_latch_cl_5_8 );
	SetPayloadBayDoorLatchPosition( 2, posplbd_latch_cl_9_12 );
	SetPayloadBayDoorLatchPosition( 3, posplbd_latch_cl_13_16 );

	SetIndications();

	SetAnimations();

	LoadPayload();

	LoadPLBBlankets();

	if (hasDFIWireTray == true) LoadDFIWireTray();
	if (hasEDOKit == true) LoadEDOKit();
	if (hasExtALODSKit == true) LoadExtALODSKit();

	{
		VideoControlUnit* pVCU = static_cast<VideoControlUnit*>(director->GetSubsystemByName( "VideoControlUnit" ));
		DiscreteBundle* pBundle_power = STS()->BundleManager()->CreateBundle( "CAMERA_POWER", 16 );
		DiscreteBundle* pBundle_VCU = BundleManager()->CreateBundle( "VCU_output", 16 );

		if (cameras[0])
		{
			double rot = 0.0;
			if (plbcameras.Custom[0]) rot = plbcameras.Rot[0];
			cameras[0]->DefineAnimations( mesh_plbcamera[0], rot, 0.0,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp_Sz,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp_Sz,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp,
				(plbcameras.Type[0] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp_Sz );

			pVCU->AddCamera( cameras[0], IN_FWD_BAY );

			cameras[0]->ConnectPowerCameraPTU( pBundle_power, 0 );
			cameras[0]->ConnectPowerHeater( pBundle_power, 1 );
			cameras[0]->ConnectPowerPTUHeater( pBundle_power, 2 );

			cameras[0]->ConnectPowerOnOff( pBundle_VCU, 5 );

			CCTVCameraPTU_LED* led = dynamic_cast<CCTVCameraPTU_LED*>(cameras[0]);
			if (led)
			{
				led->DefineMeshGroup( mesh_plbcamera[0], 6 );
				led->ConnectLEDPower( pBundle_power, 2 );
			}
		}
		if (cameras[1])
		{
			double rot = 180.0;
			if (plbcameras.Custom[1]) rot = plbcameras.Rot[1];
			cameras[1]->DefineAnimations( mesh_plbcamera[1], rot, 0.0,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp_Sz,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp_Sz,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp,
				(plbcameras.Type[1] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp_Sz );

			pVCU->AddCamera( cameras[1], IN_KEEL_EVA );

			cameras[1]->ConnectPowerCameraPTU( pBundle_power, 3 );
			cameras[1]->ConnectPowerHeater( pBundle_power, 4 );
			cameras[1]->ConnectPowerPTUHeater( pBundle_power, 5 );

			cameras[1]->ConnectPowerOnOff( pBundle_VCU, 6 );

			CCTVCameraPTU_LED* led = dynamic_cast<CCTVCameraPTU_LED*>(cameras[1]);
			if (led)
			{
				led->DefineMeshGroup( mesh_plbcamera[1], 6 );
				led->ConnectLEDPower( pBundle_power, 5 );
			}
		}
		if (cameras[2])
		{
			double rot = 180.0;
			if (plbcameras.Custom[2]) rot = plbcameras.Rot[2];
			cameras[2]->DefineAnimations( mesh_plbcamera[2], rot, 0.0,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp_Sz,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp_Sz,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp,
				(plbcameras.Type[2] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp_Sz );

			pVCU->AddCamera( cameras[2], IN_AFT_BAY );

			cameras[2]->ConnectPowerCameraPTU( pBundle_power, 6 );
			cameras[2]->ConnectPowerHeater( pBundle_power, 7 );
			cameras[2]->ConnectPowerPTUHeater( pBundle_power, 8 );

			cameras[2]->ConnectPowerOnOff( pBundle_VCU, 7 );

			CCTVCameraPTU_LED* led = dynamic_cast<CCTVCameraPTU_LED*>(cameras[2]);
			if (led)
			{
				led->DefineMeshGroup( mesh_plbcamera[2], 6 );
				led->ConnectLEDPower( pBundle_power, 8 );
			}
		}
		if (cameras[3])
		{
			double rot = 0.0;
			if (plbcameras.Custom[3]) rot = plbcameras.Rot[3];
			cameras[3]->DefineAnimations( mesh_plbcamera[3], rot, 0.0,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_base_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_base_Grp_Sz,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_PAN_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_PAN_Grp_Sz,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp,
				(plbcameras.Type[3] == 0) ? PLB_CCTV_CAMERA_506_508_TILT_Grp_Sz : PLB_CCTV_CAMERA_CTVC_ITVC_TILT_Grp_Sz );

			pVCU->AddCamera( cameras[3], IN_STBD_RMS );

			cameras[3]->ConnectPowerCameraPTU( pBundle_power, 9 );
			cameras[3]->ConnectPowerHeater( pBundle_power, 10 );
			cameras[3]->ConnectPowerPTUHeater( pBundle_power, 11 );

			cameras[3]->ConnectPowerOnOff( pBundle_VCU, 8 );

			CCTVCameraPTU_LED* led = dynamic_cast<CCTVCameraPTU_LED*>(cameras[3]);
			if (led)
			{
				led->DefineMeshGroup( mesh_plbcamera[3], 6 );
				led->ConnectLEDPower( pBundle_power, 11 );
			}
		}
		if (keelcamera)
		{
			keelcamera->DefineAnimations( 180.0, 90.0 );

			pVCU->AddCamera( keelcamera, IN_PL1 );

			pBundle = STS()->BundleManager()->CreateBundle( "PLB_INTERNAL", 16 );
			keelcamera->ConnectPowerCameraPTU( pBundle, 0 );
			//keelcamera->ConnectPowerHeater( pBundle, 1 );
			keelcamera->ConnectPowerOnOff( pBundle, 2 );
			DiscOutPort camerapower[3];// HACK no control panel yet, so have camera always powered on
			camerapower[0].Connect( pBundle, 0 );
			camerapower[0].SetLine();
			/*camerapower[1].Connect( pBundle, 1 );
			camerapower[1].SetLine();*/
			camerapower[2].Connect( pBundle, 2 );
			camerapower[2].SetLine();
		}
	}
	return;
}

void PayloadBay::DefineAnimations( void )
{
	static UINT PLBD_PORT_Grp[12] = {GRP_PLBD_EXTERIOR_LEFT, GRP_PLBD_INTERIOR_LEFT, GRP_PLBD_STRUCTURE_LEFT, GRP_PLBD_CL_LATCHES_LEFT, GRP_PLBD_CL_SEAL_LEFT, GRP_RADIATOR_3_LEFT, GRP_RADIATOR_4_LEFT, GRP_HANDRAILS_PLBD_LEFT, GRP_RADIATOR_4_INLET_HOSE_LEFT, GRP_RADIATOR_4_OUTLET_3_INLET_HOSE_LEFT, GRP_RADIATOR_3_OUTLET_HOSE_LEFT, GRP_PLBD_MONKEY_FUR_LEFT};
	MGROUP_ROTATE* PLBD_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_PORT_Grp, 12, PLBD_PORT_P3, -PLBD_PORT_AXIS, (float)(360 * RAD) );
	anim_door_port = STS()->CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( anim_door_port, 0.0, 1.0, PLBD_PORT );
	SaveAnimation( PLBD_PORT );

	static UINT PLB_RAD_PORT_Grp[5] = {GRP_RADIATOR_1_LEFT, GRP_RADIATOR_2_LEFT, GRP_RADIATOR_2_INLET_HOSE_LEFT, GRP_RADIATOR_2_OUTLET_1_INLET_HOSE_LEFT, GRP_RADIATOR_1_OUTLET_HOSE_LEFT};
	MGROUP_ROTATE* PLB_RAD_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLB_RAD_PORT_Grp, 5, RADIATOR_PORT_AXIS, RADIATOR_PORT_DIR, RADIATOR_DEPLOY );
	anim_rad_port = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_rad_port, 0.0, 1.0, PLB_RAD_PORT, parent );
	SaveAnimation( PLB_RAD_PORT );

	static UINT PLBD_PULLROD_PORT_Grp[1] = {GRP_PLBD_LINK_LEFT};
	MGROUP_ROTATE* PLBD_PULLROD_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_PULLROD_PORT_Grp, 1, PLBD_PORT_P2, PLBD_PORT_AXIS, (float)(360 * RAD) );
	anim_door_port_pullrod = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_port_pullrod, 0.0, 1.0, PLBD_PULLROD_PORT, parent );
	SaveAnimation( PLBD_PULLROD_PORT );

	static UINT PLBD_CLAMP_PORT_Grp[1] = {GRP_PLBD_CRANK_LEFT};
	MGROUP_ROTATE* PLBD_CLAMP_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_CLAMP_PORT_Grp, 1, PLBD_PORT_P4, PLBD_PORT_AXIS, (float)(360 * RAD) );
	anim_door_port_clamp = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_door_port_clamp, 0.0, 1.0, PLBD_CLAMP_PORT );
	SaveAnimation( PLBD_CLAMP_PORT );

	static UINT PLBD_PUSHROD_PORT_Grp[1] = {GRP_PLBD_ACTUATOR_PUSH_PULL_ROD_LEFT};
	MGROUP_ROTATE* PLBD_PUSH_ROD_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_PUSHROD_PORT_Grp, 1, PLBD_PORT_P5, PLBD_PORT_AXIS, static_cast<float>(360 * RAD) );
	anim_door_port_pushrod = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_port_pushrod, 0.0, 1.0, PLBD_PUSH_ROD_PORT, parent );
	SaveAnimation( PLBD_PUSH_ROD_PORT );

	static UINT PLBD_SLIDEWIRELINK_PORT_Grp[1] = {GRP_SLIDEWIRE_LINKS_LEFT};
	MGROUP_ROTATE* PLBD_SLIDEWIRELINK_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_SLIDEWIRELINK_PORT_Grp, 1, PLBD_PORT_P8, PLBD_PORT_AXIS, static_cast<float>(360 * RAD) );
	anim_door_port_slidewirelink = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_door_port_slidewirelink, 0.0, 1.0, PLBD_SLIDEWIRELINK_PORT );
	SaveAnimation( PLBD_SLIDEWIRELINK_PORT );

	static UINT PLBD_SLIDEWIREBRACKET_PORT_Grp[2] = {GRP_SLIDEWIRE_BRACKETS_LEFT, GRP_SLIDEWIRE_CUSHION_LEFT};
	MGROUP_ROTATE* PLBD_SLIDEWIREBRACKET_PORT = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_SLIDEWIREBRACKET_PORT_Grp, 2, PLBD_PORT_P9, PLBD_PORT_AXIS, static_cast<float>(360 * RAD) );
	anim_door_port_slidewirebracket = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_port_slidewirebracket, 0.0, 1.0, PLBD_SLIDEWIREBRACKET_PORT, parent );
	SaveAnimation( PLBD_SLIDEWIREBRACKET_PORT );


	static UINT PLBD_STBD_Grp[12] = {GRP_PLBD_EXTERIOR_RIGHT, GRP_PLBD_INTERIOR_RIGHT, GRP_PLBD_STRUCTURE_RIGHT, GRP_PLBD_CL_LATCHES_RIGHT, GRP_PLBD_CL_SEAL_RIGHT, GRP_RADIATOR_3_RIGHT, GRP_RADIATOR_4_RIGHT, GRP_HANDRAILS_PLBD_RIGHT, GRP_RADIATOR_4_INLET_HOSE_RIGHT, GRP_RADIATOR_4_OUTLET_3_INLET_HOSE_RIGHT, GRP_RADIATOR_3_OUTLET_HOSE_RIGHT, GRP_PLBD_MONKEY_FUR_RIGHT};
	MGROUP_ROTATE* PLBD_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_STBD_Grp, 12, PLBD_STBD_P3, -PLBD_STBD_AXIS, (float)(360 * RAD) );
	anim_door_stbd = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_door_stbd, 0.0, 1.0, PLBD_STBD );
	SaveAnimation( PLBD_STBD );

	static UINT PLB_RAD_STBD_Grp[5] = {GRP_RADIATOR_1_RIGHT, GRP_RADIATOR_2_RIGHT, GRP_RADIATOR_2_INLET_HOSE_RIGHT, GRP_RADIATOR_2_OUTLET_1_INLET_HOSE_RIGHT, GRP_RADIATOR_1_OUTLET_HOSE_RIGHT};
	MGROUP_ROTATE* PLB_RAD_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLB_RAD_STBD_Grp, 5, RADIATOR_STBD_AXIS, RADIATOR_STBD_DIR, RADIATOR_DEPLOY );
	anim_rad_stbd = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_rad_stbd, 0.0, 1.0, PLB_RAD_STBD, parent );
	SaveAnimation( PLB_RAD_STBD );

	static UINT CLatch1_4Grp[1] = {GRP_PLBD_CL_LATCHES_1_4};
	MGROUP_ROTATE* CLatch1_4 = new MGROUP_ROTATE( STS()->OVmesh(), CLatch1_4Grp, 1, CL_LATCH_AXIS, _V( 0.0, 0.0, 1.0 ), static_cast<float>(110.0 * RAD) );
	anim_clatch[0] = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_clatch[0], 0.0, 1.0, CLatch1_4, parent );
	SaveAnimation( CLatch1_4 );

	static UINT CLatch5_8Grp[1] = {GRP_PLBD_CL_LATCHES_5_8};
	MGROUP_ROTATE* CLatch5_8 = new MGROUP_ROTATE( STS()->OVmesh(), CLatch5_8Grp, 1, CL_LATCH_AXIS, _V( 0.0, 0.0, 1.0 ), static_cast<float>(110.0 * RAD) );
	anim_clatch[1] = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_clatch[1], 0.0, 1.0, CLatch5_8, parent );
	SaveAnimation( CLatch5_8 );

	static UINT CLatch9_12Grp[1] = {GRP_PLBD_CL_LATCHES_9_12};
	MGROUP_ROTATE* CLatch9_12 = new MGROUP_ROTATE( STS()->OVmesh(), CLatch9_12Grp, 1, CL_LATCH_AXIS, _V( 0.0, 0.0, 1.0 ), static_cast<float>(100.0 * RAD) );
	anim_clatch[2] = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_clatch[2], 0.0, 1.0, CLatch9_12, parent );
	SaveAnimation( CLatch9_12 );

	static UINT CLatch13_16Grp[1] = {GRP_PLBD_CL_LATCHES_13_16};
	MGROUP_ROTATE* CLatch13_16 = new MGROUP_ROTATE( STS()->OVmesh(), CLatch13_16Grp, 1, CL_LATCH_AXIS, _V( 0.0, 0.0, 1.0 ), static_cast<float>(110.0 * RAD) );
	anim_clatch[3] = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_clatch[3], 0.0, 1.0, CLatch13_16, parent );
	SaveAnimation( CLatch13_16 );

	static UINT PLBD_PULLROD_STBD_Grp[1] = {GRP_PLBD_LINK_RIGHT};
	MGROUP_ROTATE* PLBD_PULLROD_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_PULLROD_STBD_Grp, 1, PLBD_STBD_P2, PLBD_STBD_AXIS, (float)(360 * RAD));
	anim_door_stbd_pullrod = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_stbd_pullrod, 0.0, 1.0, PLBD_PULLROD_STBD, parent );
	SaveAnimation( PLBD_PULLROD_STBD );

	static UINT PLBD_CLAMP_STBD_Grp[1] = {GRP_PLBD_CRANK_RIGHT};
	MGROUP_ROTATE* PLBD_CLAMP_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_CLAMP_STBD_Grp, 1, PLBD_STBD_P4, PLBD_STBD_AXIS, (float)(360 * RAD));
	anim_door_stbd_clamp = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_door_stbd_clamp, 0.0, 1.0, PLBD_CLAMP_STBD );
	SaveAnimation( PLBD_CLAMP_STBD );

	static UINT PLBD_PUSHROD_STBD_Grp[1] = {GRP_PLBD_ACTUATOR_PUSH_PULL_ROD_RIGHT};
	MGROUP_ROTATE* PLBD_PUSH_ROD_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_PUSHROD_STBD_Grp, 1, PLBD_STBD_P5, PLBD_STBD_AXIS, static_cast<float>(360 * RAD));
	anim_door_stbd_pushrod = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_stbd_pushrod, 0.0, 1.0, PLBD_PUSH_ROD_STBD, parent );
	SaveAnimation( PLBD_PUSH_ROD_STBD );

	static UINT PLBD_SLIDEWIRELINK_STBD_Grp[1] = {GRP_SLIDEWIRE_LINKS_RIGHT};
	MGROUP_ROTATE* PLBD_SLIDEWIRELINK_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_SLIDEWIRELINK_STBD_Grp, 1, PLBD_STBD_P8, PLBD_STBD_AXIS, static_cast<float>(360 * RAD) );
	anim_door_stbd_slidewirelink = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_door_stbd_slidewirelink, 0.0, 1.0, PLBD_SLIDEWIRELINK_STBD );
	SaveAnimation( PLBD_SLIDEWIRELINK_STBD );

	static UINT PLBD_SLIDEWIREBRACKET_STBD_Grp[2] = {GRP_SLIDEWIRE_BRACKETS_RIGHT, GRP_SLIDEWIRE_CUSHION_RIGHT};
	MGROUP_ROTATE* PLBD_SLIDEWIREBRACKET_STBD = new MGROUP_ROTATE( STS()->OVmesh(), PLBD_SLIDEWIREBRACKET_STBD_Grp, 2, PLBD_STBD_P9, PLBD_STBD_AXIS, static_cast<float>(360 * RAD) );
	anim_door_stbd_slidewirebracket = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_door_stbd_slidewirebracket, 0.0, 1.0, PLBD_SLIDEWIREBRACKET_STBD, parent );
	SaveAnimation( PLBD_SLIDEWIREBRACKET_STBD );

	MGROUP_ROTATE* DA = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, KUBANDANTENNA_DA_REF, KUBANDANTENNA_DA_DIR, (float)(-143.747339 * RAD) );
	anim_da = STS()->CreateAnimation( 0.0 );
	DAparent = STS()->AddAnimationComponent( anim_da, 0.0, 1.0, DA );
	SaveAnimation( DA );

	if (EDOpallet != 0)
	{
		static UINT AFT_WINCH_Grp[1] = {GRP_AFT_WINCH};
		MGROUP_TRANSLATE* AFT_WINCH_EDO = new MGROUP_TRANSLATE( STS()->OVmesh(), AFT_WINCH_Grp, 1, (EDOpallet == 1) ? AFT_WINCH_EDO_PALLET_1_OFFSET : AFT_WINCH_EDO_PALLET_2_OFFSET );
		anim_aftwinch_edo = STS()->CreateAnimation( 0.0 );
		parent = STS()->AddAnimationComponent( anim_aftwinch_edo, 0.0, 1.0, AFT_WINCH_EDO );
		STS()->SetAnimation( anim_aftwinch_edo, 1.0 );
		SaveAnimation( AFT_WINCH_EDO );
	}
	return;
}

void PayloadBay::CreateAttachments( void )
{
	for (int i = 0; i < 5; i++)
	{
		if (!ahPassive[i]) ahPassive[i] = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + Passive_pos[i], PASSIVE_DIR, PASSIVE_ROT, "SSV_XS" );
		else STS()->SetAttachmentParams( ahPassive[i], STS()->GetOrbiterCoGOffset() + Passive_pos[i], PASSIVE_DIR, PASSIVE_ROT );
	}

	for (int i = 0; i < 8; i++)
	{
		if (!ahBayBridge[i]) ahBayBridge[i] = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + BayBridge_pos[i], BayBridge_dir[i], BayBridge_rot[i], "SSV_BB" );
		else STS()->SetAttachmentParams( ahBayBridge[i], STS()->GetOrbiterCoGOffset() + BayBridge_pos[i], BayBridge_dir[i], BayBridge_rot[i] );
	}
	return;
}

void PayloadBay::OnPostStep( double simt, double simdt, double mjd )
{
	// payload bay doors
	posplbd_latch_cl_1_4 = range( 0.0, posplbd_latch_cl_1_4 + (simdt * PLBD_CENTERLINE_LATCH_OPERATING_SPEED * (CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.GetVoltage() + CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_cl_5_8 = range( 0.0, posplbd_latch_cl_5_8 + (simdt * PLBD_CENTERLINE_LATCH_OPERATING_SPEED * (CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.GetVoltage() + CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_cl_9_12 = range( 0.0, posplbd_latch_cl_9_12 + (simdt * PLBD_CENTERLINE_LATCH_OPERATING_SPEED * (CENTERLINE_ACTUATOR_9_12_MOTOR_1_PWR.GetVoltage() + CENTERLINE_ACTUATOR_9_12_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_cl_13_16 = range( 0.0, posplbd_latch_cl_13_16 + (simdt * PLBD_CENTERLINE_LATCH_OPERATING_SPEED * (CENTERLINE_ACTUATOR_13_16_MOTOR_1_PWR.GetVoltage() + CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.GetVoltage())), 1.0 );
	SetPayloadBayDoorLatchPosition( 0, posplbd_latch_cl_1_4 );
	SetPayloadBayDoorLatchPosition( 1, posplbd_latch_cl_5_8 );
	SetPayloadBayDoorLatchPosition( 2, posplbd_latch_cl_9_12 );
	SetPayloadBayDoorLatchPosition( 3, posplbd_latch_cl_13_16 );

	posplbd_latch_blkd_port_fwd = range( 0.0, posplbd_latch_blkd_port_fwd + (simdt * PLBD_BULKHEAD_LATCH_OPERATING_SPEED * (BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_1_PWR.GetVoltage() + BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_blkd_port_aft = range( 0.0, posplbd_latch_blkd_port_aft + (simdt * PLBD_BULKHEAD_LATCH_OPERATING_SPEED * (BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.GetVoltage() + BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_blkd_stbd_fwd = range( 0.0, posplbd_latch_blkd_stbd_fwd + (simdt * PLBD_BULKHEAD_LATCH_OPERATING_SPEED * (BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_1_PWR.GetVoltage() + BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posplbd_latch_blkd_stbd_aft = range( 0.0, posplbd_latch_blkd_stbd_aft + (simdt * PLBD_BULKHEAD_LATCH_OPERATING_SPEED * (BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_1_PWR.GetVoltage() + BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.GetVoltage())), 1.0 );

	if ((posplbd_port != 0.0) || ((posplbd_latch_blkd_port_fwd > 0.5) && (posplbd_latch_blkd_port_aft > 0.5) && (posplbd_latch_cl_1_4 > 0.5) && (posplbd_latch_cl_5_8 > 0.5) && (posplbd_latch_cl_9_12 > 0.5) && (posplbd_latch_cl_13_16 > 0.5)))// only run if free or latches open enough
	{
		double range_min = 0.0;
		double range_max = 1.0;

		// limit range if latches are in the way
		if ((posplbd_latch_blkd_port_fwd < 0.5) || (posplbd_latch_blkd_port_aft < 0.5)) range_min = 0.025;// just outside RFL

		// limit range if stbd door is in the way
		if (posplbd_port < 0.025)
		{
			if (posplbd_stbd < 0.008) range_max = posplbd_port;
		}
		else
		{
			if (posplbd_stbd < 0.008) range_min = max(range_min,0.025);
		}

		posplbd_port = range( range_min, posplbd_port + (simdt * PLBD_OPERATING_SPEED * (PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR.GetVoltage() + PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.GetVoltage())), range_max );
		SetPayloadBayDoorPosition( 0, posplbd_port );
	}
	if ((posplbd_stbd != 0.0) || ((posplbd_latch_blkd_stbd_fwd > 0.5) && (posplbd_latch_blkd_stbd_aft > 0.5) && (posplbd_latch_cl_1_4 > 0.5) && (posplbd_latch_cl_5_8 > 0.5) && (posplbd_latch_cl_9_12 > 0.5) && (posplbd_latch_cl_13_16 > 0.5)))// only run if free or latches open enough
	{
		double range_min = 0.0;

		// limit range if latches are in the way
		if ((posplbd_latch_blkd_stbd_fwd < 0.5) || (posplbd_latch_blkd_stbd_aft < 0.5)) range_min = 0.025;// just outside RFL
		if ((posplbd_latch_cl_1_4 < 0.5) || (posplbd_latch_cl_5_8 < 0.5) || (posplbd_latch_cl_9_12 < 0.5) || (posplbd_latch_cl_13_16 < 0.5)) range_min = max(range_min,0.0135);// just outside RFL

		posplbd_stbd = range( range_min, posplbd_stbd + (simdt * PLBD_OPERATING_SPEED * (STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR.GetVoltage() + STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.GetVoltage())), 1.0 );
		SetPayloadBayDoorPosition( 1, posplbd_stbd );
	}


	// radiators
	posradiator_latch_port_1_6 = range( 0.0, posradiator_latch_port_1_6 + (simdt * RADLATCH_OPERATING_SPEED * (PORT_RAD_LATCH_1_6_MOTOR_1_PWR.GetVoltage() + PORT_RAD_LATCH_1_6_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posradiator_latch_port_7_12 = range( 0.0, posradiator_latch_port_7_12 + (simdt * RADLATCH_OPERATING_SPEED * (PORT_RAD_LATCH_7_12_MOTOR_1_PWR.GetVoltage() + PORT_RAD_LATCH_7_12_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posradiator_latch_stbd_1_6 = range( 0.0, posradiator_latch_stbd_1_6 + (simdt * RADLATCH_OPERATING_SPEED * (STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.GetVoltage() + STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posradiator_latch_stbd_7_12 = range( 0.0, posradiator_latch_stbd_7_12 + (simdt * RADLATCH_OPERATING_SPEED * (STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.GetVoltage() + STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.GetVoltage())), 1.0 );

	if ((posradiator_port != 0.0) || ((posradiator_latch_port_1_6 > 0.5) && (posradiator_latch_port_7_12 > 0.5)))// only run if free or latches open enough
	{
		double range_min = 0.0;

		// limit range if latches are in the way
		if ((posradiator_latch_port_1_6 < 0.5) || (posradiator_latch_port_7_12 < 0.5)) range_min = 0.02;

		posradiator_port = range( range_min, posradiator_port + (simdt * RAD_OPERATING_SPEED * (PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.GetVoltage() + PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.GetVoltage())), 1.0 );
	}

	if ((posradiator_stbd != 0.0) || ((posradiator_latch_stbd_1_6 > 0.5) && (posradiator_latch_stbd_7_12 > 0.5)))// only run if free or latches open enough
	{
		double range_min = 0.0;

		// limit range if latches are in the way
		if ((posradiator_latch_stbd_1_6 < 0.5) || (posradiator_latch_stbd_7_12 < 0.5)) range_min = 0.02;

		posradiator_stbd = range( range_min, posradiator_stbd + (simdt * RAD_OPERATING_SPEED * (STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.GetVoltage() + STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.GetVoltage())), 1.0 );
	}

	// cameras
	if (cameras[0]) cameras[0]->TimeStep( simdt );
	if (cameras[1]) cameras[1]->TimeStep( simdt );
	if (cameras[2]) cameras[2]->TimeStep( simdt );
	if (cameras[3]) cameras[3]->TimeStep( simdt );
	if (keelcamera) keelcamera->TimeStep( simdt );

	// ku antenna boom
	if (hasAntenna) poskuband = range( 0.0, poskuband + (simdt * KU_OPERATING_SPEED * (KU_RNDZ_RADAR_MOTOR_1_PWR.GetVoltage() + KU_RNDZ_RADAR_MOTOR_2_PWR.GetVoltage())), 1.0 );

	// indications
	SetIndications();

	// set animations
	SetAnimations();

	RunLights( simdt );
	return;
}

void PayloadBay::SetIndications( void )
{
	// doors
	if (posplbd_port == 0.0)// HACK CL indications should be set at <2�
	{
		if (MNB_MMC4) PORT_DOOR_CLOSE_1.SetLine();
		else PORT_DOOR_CLOSE_1.ResetLine();
		if (MNA_MMC1) PORT_DOOR_CLOSE_2.SetLine();
		else PORT_DOOR_CLOSE_2.ResetLine();
		PORT_DOOR_OPEN_1.ResetLine();
		PORT_DOOR_OPEN_2.ResetLine();
	}
	else if (posplbd_port == 1.0)
	{
		PORT_DOOR_CLOSE_1.ResetLine();
		PORT_DOOR_CLOSE_2.ResetLine();
		if (MNC_MMC4) PORT_DOOR_OPEN_1.SetLine();
		else PORT_DOOR_OPEN_1.ResetLine();
		if (MNB_MMC2) PORT_DOOR_OPEN_2.SetLine();
		else PORT_DOOR_OPEN_2.ResetLine();
	}
	else
	{
		PORT_DOOR_CLOSE_1.ResetLine();
		PORT_DOOR_CLOSE_2.ResetLine();
		PORT_DOOR_OPEN_1.ResetLine();
		PORT_DOOR_OPEN_2.ResetLine();
	}
	if (posplbd_port <= (4.0 / 175.5))// 4�
	{
		if (MNA_MMC1) PORT_FWD_RDY_LATCH_1.SetLine();
		else PORT_FWD_RDY_LATCH_1.ResetLine();
		if (MNB_MMC4) PORT_FWD_RDY_LATCH_2.SetLine();
		else PORT_FWD_RDY_LATCH_2.ResetLine();
		if (MNC_MMC2) PORT_FWD_RDY_LATCH_3.SetLine();
		else PORT_FWD_RDY_LATCH_3.ResetLine();
		if (MNA_MMC3) PORT_AFT_RDY_LATCH_1.SetLine();
		else PORT_AFT_RDY_LATCH_1.ResetLine();
		if (MNB_MMC2) PORT_AFT_RDY_LATCH_2.SetLine();
		else PORT_AFT_RDY_LATCH_2.ResetLine();
		if (MNC_MMC2) PORT_AFT_RDY_LATCH_3.SetLine();
		else PORT_AFT_RDY_LATCH_3.ResetLine();
		PORT_FWD_88.ResetLine();
		PORT_AFT_88.ResetLine();
	}
	else if (posplbd_port > (88.0 / 175.5))// 88�
	{
		PORT_FWD_RDY_LATCH_1.ResetLine();
		PORT_FWD_RDY_LATCH_2.ResetLine();
		PORT_FWD_RDY_LATCH_3.ResetLine();
		PORT_AFT_RDY_LATCH_1.ResetLine();
		PORT_AFT_RDY_LATCH_2.ResetLine();
		PORT_AFT_RDY_LATCH_3.ResetLine();
		if (MNC_MMC4) PORT_FWD_88.SetLine();
		else PORT_FWD_88.ResetLine();
		if (MNB_MMC2) PORT_AFT_88.SetLine();
		else PORT_AFT_88.ResetLine();
	}
	else
	{
		PORT_FWD_RDY_LATCH_1.ResetLine();
		PORT_FWD_RDY_LATCH_2.ResetLine();
		PORT_FWD_RDY_LATCH_3.ResetLine();
		PORT_AFT_RDY_LATCH_1.ResetLine();
		PORT_AFT_RDY_LATCH_2.ResetLine();
		PORT_AFT_RDY_LATCH_3.ResetLine();
		PORT_FWD_88.ResetLine();
		PORT_AFT_88.ResetLine();
	}

	if (posplbd_stbd == 0.0)// HACK CL indications should be set at <2�
	{
		if (MNB_MMC2) STBD_DOOR_CLOSE_1.SetLine();
		else STBD_DOOR_CLOSE_1.ResetLine();
		if (MNC_MMC4) STBD_DOOR_CLOSE_2.SetLine();
		else STBD_DOOR_CLOSE_2.ResetLine();
		STBD_DOOR_OPEN_1.ResetLine();
		STBD_DOOR_OPEN_2.ResetLine();
	}
	else if (posplbd_stbd == 1.0)
	{
		STBD_DOOR_CLOSE_1.ResetLine();
		STBD_DOOR_CLOSE_2.ResetLine();
		if (MNA_MMC1) STBD_DOOR_OPEN_1.SetLine();
		else STBD_DOOR_OPEN_1.ResetLine();
		if (MNB_MMC4) STBD_DOOR_OPEN_2.SetLine();
		else STBD_DOOR_OPEN_2.ResetLine();
	}
	else
	{
		STBD_DOOR_CLOSE_1.ResetLine();
		STBD_DOOR_CLOSE_2.ResetLine();
		STBD_DOOR_OPEN_1.ResetLine();
		STBD_DOOR_OPEN_2.ResetLine();
	}
	if (posplbd_stbd <= (4.0 / 175.5))// 4�
	{
		if (MNA_MMC1) STBD_FWD_RDY_LATCH_1.SetLine();
		else STBD_FWD_RDY_LATCH_1.ResetLine();
		if (MNB_MMC4) STBD_FWD_RDY_LATCH_2.SetLine();
		else STBD_FWD_RDY_LATCH_2.ResetLine();
		if (MNC_MMC4) STBD_FWD_RDY_LATCH_3.SetLine();
		else STBD_FWD_RDY_LATCH_3.ResetLine();
		if (MNA_MMC3) STBD_AFT_RDY_LATCH_1.SetLine();
		else STBD_AFT_RDY_LATCH_1.ResetLine();
		if (MNB_MMC2) STBD_AFT_RDY_LATCH_2.SetLine();
		else STBD_AFT_RDY_LATCH_2.ResetLine();
		if (MNC_MMC4) STBD_AFT_RDY_LATCH_3.SetLine();
		else STBD_AFT_RDY_LATCH_3.ResetLine();
		STBD_FWD_88.ResetLine();
		STBD_AFT_88.ResetLine();
	}
	else if (posplbd_stbd > (88.0 / 175.5))// 88�
	{
		STBD_FWD_RDY_LATCH_1.ResetLine();
		STBD_FWD_RDY_LATCH_2.ResetLine();
		STBD_FWD_RDY_LATCH_3.ResetLine();
		STBD_AFT_RDY_LATCH_1.ResetLine();
		STBD_AFT_RDY_LATCH_2.ResetLine();
		STBD_AFT_RDY_LATCH_3.ResetLine();
		if (MNA_MMC1) STBD_FWD_88.SetLine();
		else STBD_FWD_88.ResetLine();
		if (MNB_MMC4) STBD_AFT_88.SetLine();
		else STBD_AFT_88.ResetLine();
	}
	else
	{
		STBD_FWD_RDY_LATCH_1.ResetLine();
		STBD_FWD_RDY_LATCH_2.ResetLine();
		STBD_FWD_RDY_LATCH_3.ResetLine();
		STBD_AFT_RDY_LATCH_1.ResetLine();
		STBD_AFT_RDY_LATCH_2.ResetLine();
		STBD_AFT_RDY_LATCH_3.ResetLine();
		STBD_FWD_88.ResetLine();
		STBD_AFT_88.ResetLine();
	}

	if (posplbd_latch_cl_1_4 == 0.0)
	{
		if (MNA_MMC3) LAT_1_4_LAT_1.SetLine();
		else LAT_1_4_LAT_1.ResetLine();
		if (MNC_MMC2) LAT_1_4_LAT_2.SetLine();
		else LAT_1_4_LAT_2.ResetLine();
		LAT_1_4_REL_1.ResetLine();
		LAT_1_4_REL_2.ResetLine();
	}
	else if (posplbd_latch_cl_1_4 == 1.0)
	{
		LAT_1_4_LAT_1.ResetLine();
		LAT_1_4_LAT_2.ResetLine();
		if (MNA_MMC3) LAT_1_4_REL_1.SetLine();
		else LAT_1_4_REL_1.ResetLine();
		if (MNC_MMC2) LAT_1_4_REL_2.SetLine();
		else LAT_1_4_REL_2.ResetLine();
	}
	else
	{
		LAT_1_4_LAT_1.ResetLine();
		LAT_1_4_LAT_2.ResetLine();
		LAT_1_4_REL_1.ResetLine();
		LAT_1_4_REL_2.ResetLine();
	}

	if (posplbd_latch_cl_5_8 == 0.0)
	{
		if (MNA_MMC3) LAT_5_8_LAT_1.SetLine();
		else LAT_5_8_LAT_1.ResetLine();
		if (MNC_MMC2) LAT_5_8_LAT_2.SetLine();
		else LAT_5_8_LAT_2.ResetLine();
		LAT_5_8_REL_1.ResetLine();
		LAT_5_8_REL_2.ResetLine();
	}
	else if (posplbd_latch_cl_5_8 == 1.0)
	{
		LAT_5_8_LAT_1.ResetLine();
		LAT_5_8_LAT_2.ResetLine();
		if (MNA_MMC3) LAT_5_8_REL_1.SetLine();
		else LAT_5_8_REL_1.ResetLine();
		if (MNC_MMC2) LAT_5_8_REL_2.SetLine();
		else LAT_5_8_REL_2.ResetLine();
	}
	else
	{
		LAT_5_8_LAT_1.ResetLine();
		LAT_5_8_LAT_2.ResetLine();
		LAT_5_8_REL_1.ResetLine();
		LAT_5_8_REL_2.ResetLine();
	}

	if (posplbd_latch_cl_9_12 == 0.0)
	{
		if (MNA_MMC1) LAT_9_12_LAT_1.SetLine();
		else LAT_9_12_LAT_1.ResetLine();
		if (MNC_MMC4) LAT_9_12_LAT_2.SetLine();
		else LAT_9_12_LAT_2.ResetLine();
		LAT_9_12_REL_1.ResetLine();
		LAT_9_12_REL_2.ResetLine();
	}
	else if (posplbd_latch_cl_9_12 == 1.0)
	{
		LAT_9_12_LAT_1.ResetLine();
		LAT_9_12_LAT_2.ResetLine();
		if (MNA_MMC1) LAT_9_12_REL_1.SetLine();
		else LAT_9_12_REL_1.ResetLine();
		if (MNC_MMC4) LAT_9_12_REL_2.SetLine();
		else LAT_9_12_REL_2.ResetLine();
	}
	else
	{
		LAT_9_12_LAT_1.ResetLine();
		LAT_9_12_LAT_2.ResetLine();
		LAT_9_12_REL_1.ResetLine();
		LAT_9_12_REL_2.ResetLine();
	}

	if (posplbd_latch_cl_13_16 == 0.0)
	{
		if (MNC_MMC4) LAT_13_16_LAT_1.SetLine();
		else LAT_13_16_LAT_1.ResetLine();
		if (MNB_MMC2) LAT_13_16_LAT_2.SetLine();
		else LAT_13_16_LAT_2.ResetLine();
		LAT_13_16_REL_1.ResetLine();
		LAT_13_16_REL_2.ResetLine();
	}
	else if (posplbd_latch_cl_13_16 == 1.0)
	{
		LAT_13_16_LAT_1.ResetLine();
		LAT_13_16_LAT_2.ResetLine();
		if (MNC_MMC4) LAT_13_16_REL_1.SetLine();
		else LAT_13_16_REL_1.ResetLine();
		if (MNB_MMC2) LAT_13_16_REL_2.SetLine();
		else LAT_13_16_REL_2.ResetLine();
	}
	else
	{
		LAT_13_16_LAT_1.ResetLine();
		LAT_13_16_LAT_2.ResetLine();
		LAT_13_16_REL_1.ResetLine();
		LAT_13_16_REL_2.ResetLine();
	}

	if (posplbd_latch_blkd_port_fwd == 0.0)
	{
		if (MNA_MMC1) PORT_FWD_BLKHD_LAT_1.SetLine();
		else PORT_FWD_BLKHD_LAT_1.ResetLine();
		if (MNB_MMC4) PORT_FWD_BLKHD_LAT_2.SetLine();
		else PORT_FWD_BLKHD_LAT_2.ResetLine();
		PORT_FWD_BLKHD_REL_1.ResetLine();
		PORT_FWD_BLKHD_REL_2.ResetLine();
	}
	else if (posplbd_latch_blkd_port_fwd == 1.0)
	{
		PORT_FWD_BLKHD_LAT_1.ResetLine();
		PORT_FWD_BLKHD_LAT_2.ResetLine();
		if (MNA_MMC1) PORT_FWD_BLKHD_REL_1.SetLine();
		else PORT_FWD_BLKHD_REL_1.ResetLine();
		if (MNB_MMC4) PORT_FWD_BLKHD_REL_2.SetLine();
		else PORT_FWD_BLKHD_REL_2.ResetLine();
	}
	else
	{
		PORT_FWD_BLKHD_LAT_1.ResetLine();
		PORT_FWD_BLKHD_LAT_2.ResetLine();
		PORT_FWD_BLKHD_REL_1.ResetLine();
		PORT_FWD_BLKHD_REL_2.ResetLine();
	}

	if (posplbd_latch_blkd_port_aft == 0.0)
	{
		if (MNA_MMC3) PORT_AFT_BLKHD_LAT_1.SetLine();
		else PORT_AFT_BLKHD_LAT_1.ResetLine();
		if (MNC_MMC2) PORT_AFT_BLKHD_LAT_2.SetLine();
		else PORT_AFT_BLKHD_LAT_2.ResetLine();
		PORT_AFT_BLKHD_REL_1.ResetLine();
		PORT_AFT_BLKHD_REL_2.ResetLine();
	}
	else if (posplbd_latch_blkd_port_aft == 1.0)
	{
		PORT_AFT_BLKHD_LAT_1.ResetLine();
		PORT_AFT_BLKHD_LAT_2.ResetLine();
		if (MNA_MMC3) PORT_AFT_BLKHD_REL_1.SetLine();
		else PORT_AFT_BLKHD_REL_1.ResetLine();
		if (MNC_MMC2) PORT_AFT_BLKHD_REL_2.SetLine();
		else PORT_AFT_BLKHD_REL_2.ResetLine();
	}
	else
	{
		PORT_AFT_BLKHD_LAT_1.ResetLine();
		PORT_AFT_BLKHD_LAT_2.ResetLine();
		PORT_AFT_BLKHD_REL_1.ResetLine();
		PORT_AFT_BLKHD_REL_2.ResetLine();
	}

	if (posplbd_latch_blkd_stbd_fwd == 0.0)
	{
		if (MNA_MMC1) STBD_FWD_BLKHD_LAT_1.SetLine();
		else STBD_FWD_BLKHD_LAT_1.ResetLine();
		if (MNB_MMC4) STBD_FWD_BLKHD_LAT_2.SetLine();
		else STBD_FWD_BLKHD_LAT_2.ResetLine();
		STBD_FWD_BLKHD_REL_1.ResetLine();
		STBD_FWD_BLKHD_REL_2.ResetLine();
	}
	else if (posplbd_latch_blkd_stbd_fwd == 1.0)
	{
		STBD_FWD_BLKHD_LAT_1.ResetLine();
		STBD_FWD_BLKHD_LAT_2.ResetLine();
		if (MNA_MMC1) STBD_FWD_BLKHD_REL_1.SetLine();
		else STBD_FWD_BLKHD_REL_1.ResetLine();
		if (MNB_MMC4) STBD_FWD_BLKHD_REL_2.SetLine();
		else STBD_FWD_BLKHD_REL_2.ResetLine();
	}
	else
	{
		STBD_FWD_BLKHD_LAT_1.ResetLine();
		STBD_FWD_BLKHD_LAT_2.ResetLine();
		STBD_FWD_BLKHD_REL_1.ResetLine();
		STBD_FWD_BLKHD_REL_2.ResetLine();
	}

	if (posplbd_latch_blkd_stbd_aft == 0.0)
	{
		if (MNC_MMC4) STBD_AFT_BLKHD_LAT_1.SetLine();
		else STBD_AFT_BLKHD_LAT_1.ResetLine();
		if (MNB_MMC2) STBD_AFT_BLKHD_LAT_2.SetLine();
		else STBD_AFT_BLKHD_LAT_2.ResetLine();
		STBD_AFT_BLKHD_REL_1.ResetLine();
		STBD_AFT_BLKHD_REL_2.ResetLine();
	}
	else if (posplbd_latch_blkd_stbd_aft == 1.0)
	{
		STBD_AFT_BLKHD_LAT_1.ResetLine();
		STBD_AFT_BLKHD_LAT_2.ResetLine();
		if (MNC_MMC4) STBD_AFT_BLKHD_REL_1.SetLine();
		else STBD_AFT_BLKHD_REL_1.ResetLine();
		if (MNB_MMC2) STBD_AFT_BLKHD_REL_2.SetLine();
		else STBD_AFT_BLKHD_REL_2.ResetLine();
	}
	else
	{
		STBD_AFT_BLKHD_LAT_1.ResetLine();
		STBD_AFT_BLKHD_LAT_2.ResetLine();
		STBD_AFT_BLKHD_REL_1.ResetLine();
		STBD_AFT_BLKHD_REL_2.ResetLine();
	}

	// radiators
	if (posradiator_latch_port_1_6 == 0.0)
	{
		PORT_RAD_LATCH_1_6_REL_1.ResetLine();
		PORT_RAD_LATCH_1_6_REL_2.ResetLine();
		PORT_RAD_LATCH_1_6_LAT_1.SetLine();
		PORT_RAD_LATCH_1_6_LAT_2.SetLine();
	}
	else if (posradiator_latch_port_1_6 == 1.0)
	{
		PORT_RAD_LATCH_1_6_REL_1.SetLine();
		PORT_RAD_LATCH_1_6_REL_2.SetLine();
		PORT_RAD_LATCH_1_6_LAT_1.ResetLine();
		PORT_RAD_LATCH_1_6_LAT_2.ResetLine();
	}
	else
	{
		PORT_RAD_LATCH_1_6_REL_1.ResetLine();
		PORT_RAD_LATCH_1_6_REL_2.ResetLine();
		PORT_RAD_LATCH_1_6_LAT_1.ResetLine();
		PORT_RAD_LATCH_1_6_LAT_2.ResetLine();
	}

	if (posradiator_latch_port_7_12 == 0.0)
	{
		PORT_RAD_LATCH_7_12_REL_1.ResetLine();
		PORT_RAD_LATCH_7_12_REL_2.ResetLine();
		PORT_RAD_LATCH_7_12_LAT_1.SetLine();
		PORT_RAD_LATCH_7_12_LAT_2.SetLine();
	}
	else if (posradiator_latch_port_7_12 == 1.0)
	{
		PORT_RAD_LATCH_7_12_REL_1.SetLine();
		PORT_RAD_LATCH_7_12_REL_2.SetLine();
		PORT_RAD_LATCH_7_12_LAT_1.ResetLine();
		PORT_RAD_LATCH_7_12_LAT_2.ResetLine();
	}
	else
	{
		PORT_RAD_LATCH_7_12_REL_1.ResetLine();
		PORT_RAD_LATCH_7_12_REL_2.ResetLine();
		PORT_RAD_LATCH_7_12_LAT_1.ResetLine();
		PORT_RAD_LATCH_7_12_LAT_2.ResetLine();
	}

	if (posradiator_latch_stbd_1_6 == 0.0)
	{
		STARBOARD_RAD_LATCH_1_6_REL_1.ResetLine();
		STARBOARD_RAD_LATCH_1_6_REL_2.ResetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_1.SetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_2.SetLine();
	}
	else if (posradiator_latch_stbd_1_6 == 1.0)
	{
		STARBOARD_RAD_LATCH_1_6_REL_1.SetLine();
		STARBOARD_RAD_LATCH_1_6_REL_2.SetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_1.ResetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_2.ResetLine();
	}
	else
	{
		STARBOARD_RAD_LATCH_1_6_REL_1.ResetLine();
		STARBOARD_RAD_LATCH_1_6_REL_2.ResetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_1.ResetLine();
		STARBOARD_RAD_LATCH_1_6_LAT_2.ResetLine();
	}

	if (posradiator_latch_stbd_7_12 == 0.0)
	{
		STARBOARD_RAD_LATCH_7_12_REL_1.ResetLine();
		STARBOARD_RAD_LATCH_7_12_REL_2.ResetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_1.SetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_2.SetLine();
	}
	else if (posradiator_latch_stbd_7_12 == 1.0)
	{
		STARBOARD_RAD_LATCH_7_12_REL_1.SetLine();
		STARBOARD_RAD_LATCH_7_12_REL_2.SetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_1.ResetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_2.ResetLine();
	}
	else
	{
		STARBOARD_RAD_LATCH_7_12_REL_1.ResetLine();
		STARBOARD_RAD_LATCH_7_12_REL_2.ResetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_1.ResetLine();
		STARBOARD_RAD_LATCH_7_12_LAT_2.ResetLine();
	}


	if (posradiator_port == 0.0)
	{
		PORT_RAD_DEPLOYMENT_DPY_1.ResetLine();
		PORT_RAD_DEPLOYMENT_DPY_2.ResetLine();
		PORT_RAD_DEPLOYMENT_STO_1.SetLine();
		PORT_RAD_DEPLOYMENT_STO_2.SetLine();
	}
	else if (posradiator_port == 1.0)
	{
		PORT_RAD_DEPLOYMENT_DPY_1.SetLine();
		PORT_RAD_DEPLOYMENT_DPY_2.SetLine();
		PORT_RAD_DEPLOYMENT_STO_1.ResetLine();
		PORT_RAD_DEPLOYMENT_STO_2.ResetLine();
	}
	else
	{
		PORT_RAD_DEPLOYMENT_DPY_1.ResetLine();
		PORT_RAD_DEPLOYMENT_DPY_2.ResetLine();
		PORT_RAD_DEPLOYMENT_STO_1.ResetLine();
		PORT_RAD_DEPLOYMENT_STO_2.ResetLine();
	}

	if (posradiator_stbd == 0.0)
	{
		STARBOARD_RAD_DEPLOYMENT_DPY_1.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_DPY_2.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_1.SetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_2.SetLine();
	}
	else if (posradiator_stbd == 1.0)
	{
		STARBOARD_RAD_DEPLOYMENT_DPY_1.SetLine();
		STARBOARD_RAD_DEPLOYMENT_DPY_2.SetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_1.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_2.ResetLine();
	}
	else
	{
		STARBOARD_RAD_DEPLOYMENT_DPY_1.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_DPY_2.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_1.ResetLine();
		STARBOARD_RAD_DEPLOYMENT_STO_2.ResetLine();
	}

	// antenna
	if (hasAntenna)
	{
		if (poskuband == 0.0)
		{
			KU_RNDZ_RADAR_STO_IND_1.SetLine();
			KU_RNDZ_RADAR_STO_IND_2.SetLine();
			KU_RNDZ_RADAR_DPY_IND_1.ResetLine();
			KU_RNDZ_RADAR_DPY_IND_2.ResetLine();

			KU_RNDZ_RADAR_STO_IND.SetLine();
			KU_RNDZ_RADAR_DPY_IND.ResetLine();
		}
		else if (poskuband == 1.0)
		{
			KU_RNDZ_RADAR_STO_IND_1.ResetLine();
			KU_RNDZ_RADAR_STO_IND_2.ResetLine();
			KU_RNDZ_RADAR_DPY_IND_1.SetLine();
			KU_RNDZ_RADAR_DPY_IND_2.SetLine();

			KU_RNDZ_RADAR_STO_IND.ResetLine();
			KU_RNDZ_RADAR_DPY_IND.SetLine();
		}
		else
		{
			KU_RNDZ_RADAR_STO_IND_1.ResetLine();
			KU_RNDZ_RADAR_STO_IND_2.ResetLine();
			KU_RNDZ_RADAR_DPY_IND_1.ResetLine();
			KU_RNDZ_RADAR_DPY_IND_2.ResetLine();

			KU_RNDZ_RADAR_STO_IND.ResetLine();
			KU_RNDZ_RADAR_DPY_IND.ResetLine();
		}
	}
	return;
}

void PayloadBay::SetAnimations( void )
{
	if (hasAntenna) STS()->SetAnimation( anim_da, poskuband );

	STS()->SetAnimation( anim_rad_port, posradiator_port );
	STS()->SetAnimation( anim_rad_stbd, posradiator_stbd );
	return;
}

void PayloadBay::SetPayloadBayDoorPosition( int side, double pos )
{
	if (side == 0)// port
	{
		// motor/push rod/crank part
		static const double r5 = length( PLBD_PORT_P4 - PLBD_PORT_P5 );
		static const double r6 = length( PLBD_PORT_P5 - PLBD_PORT_P6 );
		static const double r7 = length( PLBD_PORT_P4 - PLBD_PORT_P7 );
		static const double r8 = length( PLBD_PORT_P7 - PLBD_PORT_P6 );

		static const double theta5o = PI2 - angle( PLBD_PORT_P5 - PLBD_PORT_P4, _V( -1.0, 0.0, 0.0 ) );
		static const double theta6o = PI2 - angle( PLBD_PORT_P6 - PLBD_PORT_P5, _V( -1.0, 0.0, 0.0 ) );
		static const double theta7 = PI2 - angle( PLBD_PORT_P7 - PLBD_PORT_P4, _V( -1.0, 0.0, 0.0 ) );
		static const double theta8o = PI2 - angle( PLBD_PORT_P6 - PLBD_PORT_P7, _V( -1.0, 0.0, 0.0 ) );

		double theta8 = theta8o + (pos * PLBD_MOTOR_RANGE);
		if (theta8 > PI2) theta8 -= PI2;

		double xa = r7 * cos( theta7 ) + r8 * cos( theta8 );
		double ya = r7 * sin( theta7 ) + r8 * sin( theta8 );

		double theta6 = PI2 + atan2( ya, xa ) + acos( ((xa * xa) + (ya * ya) + (r6 * r6) - (r5 * r5)) / (2 * r6 * sqrt( (xa * xa) + (ya * ya) )) );

		double theta5 = PI2 + atan2( ya - r6 * sin( theta6 ), xa - r6 * cos( theta6 ) );
		if (theta5 > PI2) theta5 -= PI2;

		// clamp/pull rod/door part
		static const double r1 = length( PLBD_PORT_P2 - PLBD_PORT_P1 );
		static const double r2 = length( PLBD_PORT_P3 - PLBD_PORT_P2 );
		static const double r3 = length( PLBD_PORT_P3 - PLBD_PORT_P4 );
		static const double r4 = length( PLBD_PORT_P4 - PLBD_PORT_P1 );

		static const double theta1o = PI2 - angle( PLBD_PORT_P1 - PLBD_PORT_P2, _V( -1.0, 0.0, 0.0 ) );
		static const double theta2o = angle( PLBD_PORT_P2 - PLBD_PORT_P3, _V( -1.0, 0.0, 0.0 ) );
		static const double theta3 = PI2 - angle( PLBD_PORT_P4 - PLBD_PORT_P3, _V( -1.0, 0.0, 0.0 ) );
		static const double theta4o = angle( PLBD_PORT_P1 - PLBD_PORT_P4, _V( -1.0, 0.0, 0.0 ) );

		double theta4 = theta4o - (theta5o - theta5);

		xa = r3 * cos( theta3 ) + r4 * cos( theta4 );
		ya = r3 * sin( theta3 ) + r4 * sin( theta4 );

		double theta2 = PI2 + atan2( ya, xa ) - acos( ((xa * xa) + (ya * ya) + (r2 * r2) - (r1 * r1)) / (2 * r2 * sqrt( (xa * xa) + (ya * ya) )) );
		if (theta2 > PI2) theta2 -= PI2;

		double theta1 = PI2 + atan2( ya - r2 * sin( theta2 ), xa - r2 * cos( theta2 ) );
		if (theta1 > PI2) theta1 -= PI2;


		STS()->SetAnimation( anim_door_port_pushrod, (theta6 - theta6o - (theta4 - theta4o)) / PI2 );

		double tmp = (theta4 - theta4o) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_port_clamp, tmp );

		tmp = (theta1 - theta1o + (theta2o - theta2)) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_port_pullrod, tmp );

		tmp = (theta2o - theta2) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_port, tmp );

		// slidewire part
		static const double r9 = length( PLBD_PORT_P9 - PLBD_PORT_P8 );
		static const double r10 = length( PLBD_PORT_P10 - PLBD_PORT_P9 );
		static const double r11 = length( PLBD_PORT_P10 - PLBD_PORT_P3 );
		static const double r12 = length( PLBD_PORT_P3 - PLBD_PORT_P8 );

		static const double theta9o = angle( PLBD_PORT_P8 - PLBD_PORT_P9, _V( -1.0, 0.0, 0.0 ) );
		static const double theta10o = PI2 - angle( PLBD_PORT_P9 - PLBD_PORT_P10, _V( -1.0, 0.0, 0.0 ) );
		static const double theta11o = angle( PLBD_PORT_P3 - PLBD_PORT_P10, _V( -1.0, 0.0, 0.0 ) );
		static const double theta12 = angle( PLBD_PORT_P8 - PLBD_PORT_P3, _V( -1.0, 0.0, 0.0 ) );

		double theta11 = theta11o + (theta2o - theta2);

		xa = r11 * cos( theta11 ) + r12 * cos( theta12 );
		ya = r11 * sin( theta11 ) + r12 * sin( theta12 );

		double theta10 = PI2 + atan2( ya, xa ) + acos( ((xa * xa) + (ya * ya) + (r10 * r10) - (r9 * r9)) / (2.0 * r10 * sqrt( (xa * xa) + (ya * ya) )) );
		if (theta10 > PI2) theta10 -= PI2;

		double theta9 = PI2 + atan2( ya - r10 * sin( theta10 ), xa - r10 * cos( theta10 ) );
		if (theta9 > PI2) theta9 -= PI2;

		tmp = (theta9o - theta9) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_port_slidewirelink, tmp );

		tmp = ((theta10o - theta10) - (theta9o - theta9)) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_port_slidewirebracket, tmp );
	}
	else// starboard
	{
		// motor/push rod/crank part
		static const double r5 = length( PLBD_STBD_P4 - PLBD_STBD_P5 );
		static const double r6 = length( PLBD_STBD_P5 - PLBD_STBD_P6 );
		static const double r7 = length( PLBD_STBD_P4 - PLBD_STBD_P7 );
		static const double r8 = length( PLBD_STBD_P7 - PLBD_STBD_P6 );

		static const double theta5o = PI2 - angle( PLBD_STBD_P5 - PLBD_STBD_P4, _V( 1.0, 0.0, 0.0 ) );
		static const double theta6o = PI2 - angle( PLBD_STBD_P6 - PLBD_STBD_P5, _V( 1.0, 0.0, 0.0 ) );
		static const double theta7 = PI2 - angle( PLBD_STBD_P7 - PLBD_STBD_P4, _V( 1.0, 0.0, 0.0 ) );
		static const double theta8o = PI2 - angle( PLBD_STBD_P6 - PLBD_STBD_P7, _V( 1.0, 0.0, 0.0 ) );

		double theta8 = theta8o + (pos * PLBD_MOTOR_RANGE);
		if (theta8 > PI2) theta8 -= PI2;

		double xa = r7 * cos( theta7 ) + r8 * cos( theta8 );
		double ya = r7 * sin( theta7 ) + r8 * sin( theta8 );

		double theta6 = PI2 + atan2( ya, xa ) + acos( ((xa * xa) + (ya * ya) + (r6 * r6) - (r5 * r5)) / (2 * r6 * sqrt( (xa * xa) + (ya * ya) )) );

		double theta5 = PI2 + atan2( ya - r6 * sin( theta6 ), xa - r6 * cos( theta6 ) );
		if (theta5 > PI2) theta5 -= PI2;

		// clamp/pull rod/door part
		static const double r1 = length( PLBD_STBD_P2 - PLBD_STBD_P1 );
		static const double r2 = length( PLBD_STBD_P3 - PLBD_STBD_P2 );
		static const double r3 = length( PLBD_STBD_P3 - PLBD_STBD_P4 );
		static const double r4 = length( PLBD_STBD_P4 - PLBD_STBD_P1 );

		static const double theta1o = PI2 - angle( PLBD_STBD_P1 - PLBD_STBD_P2, _V( 1.0, 0.0, 0.0 ) );
		static const double theta2o = angle( PLBD_STBD_P2 - PLBD_STBD_P3, _V( 1.0, 0.0, 0.0 ) );
		static const double theta3 = PI2 - angle( PLBD_STBD_P4 - PLBD_STBD_P3, _V( 1.0, 0.0, 0.0 ) );
		static const double theta4o = angle( PLBD_STBD_P1 - PLBD_STBD_P4, _V( 1.0, 0.0, 0.0 ) );

		double theta4 = theta4o - (theta5o - theta5);

		xa = r3 * cos( theta3 ) + r4 * cos( theta4 );
		ya = r3 * sin( theta3 ) + r4 * sin( theta4 );

		double theta2 = PI2 + atan2( ya, xa ) - acos( ((xa * xa) + (ya * ya) + (r2 * r2) - (r1 * r1)) / (2 * r2 * sqrt( (xa * xa) + (ya * ya) )) );
		if (theta2 > PI2) theta2 -= PI2;

		double theta1 = PI2 + atan2( ya - r2 * sin( theta2 ), xa - r2 * cos( theta2 ) );
		if (theta1 > PI2) theta1 -= PI2;


		STS()->SetAnimation( anim_door_stbd_pushrod, (theta6 - theta6o - (theta4 - theta4o)) / PI2 );

		double tmp = (theta4 - theta4o) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_stbd_clamp, tmp );

		tmp = (theta1 - theta1o + (theta2o - theta2)) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_stbd_pullrod, tmp );

		tmp = (theta2o - theta2) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_stbd, tmp );

		// slidewire part
		static const double r9 = length( PLBD_STBD_P9 - PLBD_STBD_P8 );
		static const double r10 = length( PLBD_STBD_P10 - PLBD_STBD_P9 );
		static const double r11 = length( PLBD_STBD_P10 - PLBD_STBD_P3 );
		static const double r12 = length( PLBD_STBD_P3 - PLBD_STBD_P8 );

		static const double theta9o = angle( PLBD_STBD_P8 - PLBD_STBD_P9, _V( 1.0, 0.0, 0.0 ) );
		static const double theta10o = PI2 - angle( PLBD_STBD_P9 - PLBD_STBD_P10, _V( 1.0, 0.0, 0.0 ) );
		static const double theta11o = angle( PLBD_STBD_P3 - PLBD_STBD_P10, _V( 1.0, 0.0, 0.0 ) );
		static const double theta12 = angle( PLBD_STBD_P8 - PLBD_STBD_P3, _V( 1.0, 0.0, 0.0 ) );

		double theta11 = theta11o + (theta2o - theta2);

		xa = r11 * cos( theta11 ) + r12 * cos( theta12 );
		ya = r11 * sin( theta11 ) + r12 * sin( theta12 );

		double theta10 = PI2 + atan2( ya, xa ) + acos( ((xa * xa) + (ya * ya) + (r10 * r10) - (r9 * r9)) / (2.0 * r10 * sqrt( (xa * xa) + (ya * ya) )) );
		if (theta10 > PI2) theta10 -= PI2;

		double theta9 = PI2 + atan2( ya - r10 * sin( theta10 ), xa - r10 * cos( theta10 ) );
		if (theta9 > PI2) theta9 -= PI2;

		tmp = (theta9o - theta9) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_stbd_slidewirelink, tmp );

		tmp = ((theta10o - theta10) - (theta9o - theta9)) / PI2;
		if (tmp < 0.0) tmp += 1.0;
		STS()->SetAnimation( anim_door_stbd_slidewirebracket, tmp );
	}
	return;
}

void PayloadBay::SetPayloadBayDoorLatchPosition( unsigned int gang, double pos )
{
	assert( (gang <= 3) && "Atlantis::SetPayloadBayDoorLatchPosition.gang" );
	STS()->SetAnimation( anim_clatch[gang], pos );
	return;
}

void PayloadBay::RunLights( double simdt )
{
	for (const auto& x : lights) x->TimeStep( simdt );
	return;
}

void PayloadBay::ShiftCG( const VECTOR3& shift )
{
	for (const auto& x : lights) x->ShiftLightPosition( shift );
	return;
}

void PayloadBay::LoadPayload( void )
{
	UINT mesh_idx;

	// passive CL
	for (int i = 0; i < 5; i++)
	{
		if (payloads.passive[i].IsUsed)
		{
			// port longeron
			for (int j = 0; j < 4; j++)
			{
				if (payloads.passive[i].PLID[j] != 0)
				{
					// find PRLA Xo position
					double Xo = PLID_Xo[payloads.passive[i].PLID[j] - PLID_Xo_base];
					if (Xo > 0.0)
					{
						// convert to z position
						VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

						// add mesh instance
						mesh_idx = STS()->AddMesh( payloads.passive[i].Reversed[j] ? MESHNAME_PRLA_STBD_PASSIVE : MESHNAME_PRLA_PORT_PASSIVE, &pos );
						STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

						// add animation (for positioning)
						if (payloads.passive[i].Reversed[j])
						{
							static UINT PRLA_Grp[2] = {0, 1};
							MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, PRLA_Grp, 2, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
							UINT animPRLA = STS()->CreateAnimation( 0.0 );
							STS()->SetAnimation( animPRLA, 1.0 );
							STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
							SaveAnimation( PRLA );
						}

						// load corresponding longeron bridge
						LoadLongeronPortBridgeByPLID( payloads.passive[i].PLID[j] );

						// set attachment location
						if (payloads.passive[i].IsAttachment[j])
							Passive_pos[i] = PASSIVE_PORT_POS + pos;
					}
					else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Passive: %d %d", payloads.passive[i].PLID[j], i, j );
				}
			}

			// starboard longeron
			for (int j = 4; j < 8; j++)
			{
				if (payloads.passive[i].PLID[j] != 0)
				{
					// find PRLA Xo position
					double Xo = PLID_Xo[payloads.passive[i].PLID[j] - PLID_Xo_base];
					if (Xo > 0.0)
					{
						// convert to z position
						VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

						// add mesh instance
						mesh_idx = STS()->AddMesh( payloads.passive[i].Reversed[j] ? MESHNAME_PRLA_PORT_PASSIVE : MESHNAME_PRLA_STBD_PASSIVE, &pos );
						STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

						// add animation (for positioning)
						if (payloads.passive[i].Reversed[j])
						{
							static UINT PRLA_Grp[2] = {0, 1};
							MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, PRLA_Grp, 2, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
							UINT animPRLA = STS()->CreateAnimation( 0.0 );
							STS()->SetAnimation( animPRLA, 1.0 );
							STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
							SaveAnimation( PRLA );
						}

						// load corresponding longeron bridge
						LoadLongeronStbdBridgeByPLID( payloads.passive[i].PLID[j] );

						// set attachment location
						if (payloads.passive[i].IsAttachment[j])
							Passive_pos[i] = PASSIVE_STBD_POS + pos;
					}
					else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Passive: %d %d", payloads.passive[i].PLID[j], i, j );
				}
			}

			// keel
			for (int j = 8; j < 12; j++)
			{
				if (payloads.passive[i].PLID[j] != 0)
				{
					// find PRLA Xo position
					double Xo = PLID_Xo[payloads.passive[i].PLID[j] - PLID_Xo_base];
					if (Xo > 0.0)
					{
						// convert to z position
						VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

						// handle bay 12 vertical offset
						VECTOR3 posmesh = _V( 0.0, (Xo < 1191.0) ? 0.0 : (PASSIVE_AFT_POS.y - PASSIVE_FWD_POS.y), pos.z );

						// add mesh instance
						mesh_idx = STS()->AddMesh( MESHNAME_PKA, &posmesh );
						STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

						// load corresponding keel bridge
						LoadKeelBridgeByPLID( payloads.passive[i].PLID[j] );

						// set attachment location
						if (payloads.passive[i].IsAttachment[j])
							Passive_pos[i] = ((Xo < 1191.0) ? PASSIVE_FWD_POS : PASSIVE_AFT_POS) + pos;
					}
					else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in Passive: %d %d", payloads.passive[i].PLID[j], i, j );
				}
			}
		}
	}

	// set positions for passive port attachments
	for (int i = 0; i < 8; i++)
	{
		if (payloads.baybridge[i].IsUsed)
		{
			if (payloads.baybridge[i].bridge == 0)// port
			{
				BayBridge_pos[i] = BAYBRIDGE_PORT_POS;
				BayBridge_dir[i] = BAYBRIDGE_PORT_DIR;
				BayBridge_rot[i] = BAYBRIDGE_PORT_ROT;
			}
			else if (payloads.baybridge[i].bridge == 1)// stbd
			{
				BayBridge_pos[i] = BAYBRIDGE_STBD_POS;
				BayBridge_dir[i] = BAYBRIDGE_STBD_DIR;
				BayBridge_rot[i] = BAYBRIDGE_STBD_ROT;
			}
			else /*if (payloads.baybridge[i].bridge == 2)*/// keel
			{
				BayBridge_pos[i] = BAYBRIDGE_KEEL_POS;
				BayBridge_dir[i] = BAYBRIDGE_KEEL_DIR;
				BayBridge_rot[i] = BAYBRIDGE_KEEL_ROT;
			}
			BayBridge_pos[i] += _V( 0.0, 0.0, 24.239 - (Bay_Xo[payloads.baybridge[i].bay - 1] * IN2M) );// add bay offset
		}
	}

	CreateAttachments();// need to call this again to update positions
	return;
}

void PayloadBay::AddPRLA( unsigned short PLID, bool Reversed )
{
	UINT mesh_idx[2];

	if (PLID != 0)
	{
		// find PRLA Xo position
		double Xo = PLID_Xo[PLID - PLID_Xo_base];
		if (Xo > 0.0)
		{
			// convert to z position
			VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

			// add mesh instances
			mesh_idx[0] = STS()->AddMesh( MESHNAME_PRLA_PORT_PASSIVE, &pos );
			mesh_idx[1] = STS()->AddMesh( MESHNAME_PRLA_STBD_PASSIVE, &pos );
			STS()->SetMeshVisibilityMode( mesh_idx[0], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
			STS()->SetMeshVisibilityMode( mesh_idx[1], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

			// add animation (for positioning)
			if (Reversed)
			{
				static UINT PRLA_Grp[2] = {0, 1};
				MGROUP_ROTATE* PRLA0 = new MGROUP_ROTATE( mesh_idx[0], PRLA_Grp, 2, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
				MGROUP_ROTATE* PRLA1 = new MGROUP_ROTATE( mesh_idx[1], PRLA_Grp, 2, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
				UINT animPRLA = STS()->CreateAnimation( 0.0 );
				STS()->SetAnimation( animPRLA, 1.0 );
				STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA0 );
				STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA1 );
				SaveAnimation( PRLA0 );
				SaveAnimation( PRLA1 );
			}

			// load corresponding longeron bridges
			LoadLongeronPortBridgeByPLID( PLID );
			LoadLongeronStbdBridgeByPLID( PLID );
		}
	}
	return;
}

void PayloadBay::AddPKA( unsigned short PLID )
{
	UINT mesh_idx;

	if (PLID != 0)
	{
		// find PRLA Xo position
		double Xo = PLID_Xo[PLID - PLID_Xo_base];
		if (Xo > 0.0)
		{
			// convert to z position
			VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

			// handle bay 12 vertical offset
			pos.y = (Xo < 1191.0) ? 0.0 : (PASSIVE_AFT_POS.y - PASSIVE_FWD_POS.y);

			// add mesh instances
			mesh_idx = STS()->AddMesh( MESHNAME_PKA, &pos );
			STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

			// load corresponding keel bridge
			LoadKeelBridgeByPLID( PLID );
		}
	}
	return;
}

void PayloadBay::HandleSubsystemsVisuals( void )
{
	// ExtAL
	eva_docking::ExtAirlock* pExtAL = dynamic_cast<eva_docking::ExtAirlock*>(director->GetSubsystemByName( "ODS" ));
	if (!pExtAL) pExtAL = dynamic_cast<eva_docking::ExtAirlock*>(director->GetSubsystemByName( "ExternalAirlock" ));
	if (pExtAL)
	{
		unsigned short PLID_longeron1 = 0;
		unsigned short PLID_longeron2 = 0;
		unsigned short PLID_keel = 0;
		bool Reversed_longeron1 = false;
		bool Reversed_longeron2 = false;

		pExtAL->GetPLBInfo( PLID_longeron1, PLID_longeron2, PLID_keel, Reversed_longeron1, Reversed_longeron2 );

		AddPRLA( PLID_longeron1, Reversed_longeron1 );
		AddPRLA( PLID_longeron2, Reversed_longeron2 );
		AddPKA( PLID_keel );
	}

	// TAA
	eva_docking::TunnelAdapterAssembly* pTAA = dynamic_cast<eva_docking::TunnelAdapterAssembly*>(director->GetSubsystemByName( "TunnelAdapterAssembly" ));
	if (pTAA)
	{
		unsigned short PLID_longeron1 = 0;
		unsigned short PLID_longeron2 = 0;
		unsigned short PLID_keel = 0;
		bool Reversed_longeron1 = false;
		bool Reversed_longeron2 = false;

		pTAA->GetPLBInfo( PLID_longeron1, PLID_longeron2, PLID_keel, Reversed_longeron1, Reversed_longeron2 );

		AddPRLA( PLID_longeron1, Reversed_longeron1 );
		AddPRLA( PLID_longeron2, Reversed_longeron2 );
		AddPKA( PLID_keel );
	}

	// PDRS
	eps::PRSD* pPRSD = dynamic_cast<eps::PRSD*>(director->GetSubsystemByName( "PRSD" ));
	if (pPRSD)
	{
		unsigned short PLID = 0;
		bool Reversed = false;

		pPRSD->GetPLBInfo( PLID, Reversed, EDOpallet );

		AddPRLA( PLID, Reversed );
		AddPKA( PLID );
	}

	// ASE IUS
	ASE_IUS* pASE_IUS = dynamic_cast<ASE_IUS*>(director->GetSubsystemByName( "ASE_IUS" ));
	if (pASE_IUS)
	{
		unsigned short PLID_longeron1 = 0;
		unsigned short PLID_longeron2 = 0;
		unsigned short PLID_longeron3 = 0;
		unsigned short PLID_keel = 0;
		bool aftlocation = false;
		bool Reversed_longeron1 = false;
		bool Reversed_longeron2 = false;
		bool Reversed_longeron3 = false;

		pASE_IUS->GetPLBInfo( PLID_longeron1, PLID_longeron2, PLID_longeron3, PLID_keel, aftlocation, Reversed_longeron1, Reversed_longeron2, Reversed_longeron3 );

		AddPRLA( PLID_longeron1, Reversed_longeron1 );
		AddPRLA( PLID_longeron2, Reversed_longeron2 );
		AddPRLA( PLID_longeron3, Reversed_longeron3 );
		AddPKA( PLID_keel );

		hasAftHandrails = !aftlocation;
	}

	// CISS
	CISS* pCISS = dynamic_cast<CISS*>(director->GetSubsystemByName( "CISS" ));
	if (pCISS)
	{
		unsigned short PLID_longeron1 = 0;
		unsigned short PLID_longeron2 = 0;
		unsigned short PLID_keel = 0;
		unsigned short bay = 0;
		bool Reversed_longeron1 = false;
		bool Reversed_longeron2 = false;

		pCISS->GetPLBInfo( PLID_longeron1, PLID_longeron2, PLID_keel, bay, Reversed_longeron1, Reversed_longeron2 );

		AddPRLA( PLID_longeron1, Reversed_longeron1 );
		AddPRLA( PLID_longeron2, Reversed_longeron2 );
		AddPKA( PLID_keel );

		LoadLongeronPortBridge( bay );
		LoadLongeronStbdBridge( bay );
		LoadKeelBridge( bay );

		hasAftHandrails = false;
		hasBay13covers = false;
		hasT4panelcovers = false;
		hasDumpLinecovers = false;
	}

	// ActiveLatchGroup 1-5
	for (unsigned short id = 0; id < 5; id++)
	{
		if (payloads.active[id].IsUsed)
		{
			// port longeron
			for (int j = 0; j < 4; j++)
			{
				LoadLongeronPortBridgeByPLID( payloads.active[id].PLID[j] );
			}

			// starboard longeron
			for (int j = 4; j < 8; j++)
			{
				LoadLongeronStbdBridgeByPLID( payloads.active[id].PLID[j] );
			}

			// keel
			for (int j = 8; j < 12; j++)
			{
				LoadKeelBridgeByPLID( payloads.active[id].PLID[j] );
			}
		}
	}

	// SPDS
	SPDS* pSPDS = dynamic_cast<SPDS*>(director->GetSubsystemByName( "SPDS" ));
	if (pSPDS)
	{
		unsigned short PLID_longeron_port1 = 0;
		unsigned short PLID_longeron_port2 = 0;
		unsigned short PLID_longeron_stbd1 = 0;
		unsigned short PLID_longeron_stbd2 = 0;
		unsigned short PLID_keel = 0;

		pSPDS->GetPLBInfo( PLID_longeron_port1, PLID_longeron_port2, PLID_longeron_stbd1, PLID_longeron_stbd2, PLID_keel );

		LoadLongeronPortBridgeByPLID( PLID_longeron_port1 );
		LoadLongeronPortBridgeByPLID( PLID_longeron_port2 );
		LoadLongeronStbdBridgeByPLID( PLID_longeron_stbd1 );
		LoadLongeronStbdBridgeByPLID( PLID_longeron_stbd2 );
		LoadKeelBridgeByPLID( PLID_keel );
	}
	return;
}

void PayloadBay::LoadLongeronPortBridgeByPLID( unsigned short PLID )
{
	if (PLID == 0) return;

	for (int k = 0; k < 13; k++)
	{
		if (PLID < Bay_PLID[k])
		{
			LoadLongeronPortBridge( k + 1 );
			break;
		}
	}
	return;
}

void PayloadBay::LoadLongeronStbdBridgeByPLID( unsigned short PLID )
{
	if (PLID == 0) return;

	for (int k = 0; k < 13; k++)
	{
		if (PLID < Bay_PLID[k])
		{
			LoadLongeronStbdBridge( k + 1 );
			break;
		}
	}
	return;
}

void PayloadBay::LoadKeelBridgeByPLID( unsigned short PLID )
{
	if (PLID == 0) return;

	for (int k = 0; k < 12; k++)
	{
		if (PLID < Bay_PLID[k])
		{
			LoadKeelBridge( k + 1 );
			break;
		}
	}
	return;
}

void PayloadBay::LoadLongeronPortBridge( unsigned short bay )
{
	if ((bay < 1) || (bay > 13)) throw std::exception( "LoadLongeronPortBridge::bay" );

	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_BRIDGEFITTING_LONGERON_PORT[bay - 1] ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void PayloadBay::LoadLongeronStbdBridge( unsigned short bay )
{
	if ((bay < 1) || (bay > 13)) throw std::exception( "LoadLongeronStbdBridge::bay" );

	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_BRIDGEFITTING_LONGERON_STBD[bay - 1] ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void PayloadBay::LoadKeelBridge( unsigned short bay )
{
	if ((bay < 1) || (bay > 12)) throw std::exception( "LoadKeelBridge::bay" );

	if (bay < 12) hasKeelBridge[bay - 1] = true;

	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_BRIDGEFITTING_KEEL[bay - 1] ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void PayloadBay::VisualCreated( VISHANDLE vis )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	// hide aft bulkhead handrails as needed
	if (!hasAftHandrails)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding aft bulkhead handrails" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_HANDRAILS_REMOVABLE_103SUBS, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_HANDRAILS_REMOVABLE_ORIGINAL, &grpSpec );
	}
	else if (hasOriginalHandrails)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding OV-103 and subs aft bulkhead handrails" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_HANDRAILS_REMOVABLE_103SUBS, &grpSpec );
	}
	else
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding original aft bulkhead handrails" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_HANDRAILS_REMOVABLE_ORIGINAL, &grpSpec );
	}

	// hide dump line covers as needed
	if (!hasDumpLinecovers)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding dump and vent line covers" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_DUMP_LINE_COVER_PORT, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_DUMP_LINE_COVER_STARBOARD, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_CISS_GH2_VENT_COVER, &grpSpec );
	}

	// hide T-4 external panel covers as needed
	if (!hasT4panelcovers)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding T-4 and RBUS hinge covers" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_T4_UMBILICAL_PANEL_COVER_PORT, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_T4_UMBILICAL_PANEL_COVER_STARBOARD, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_RBUS_UMBILICAL_PLATE_HINGE_COVERS, &grpSpec );
	}

	// hide T-4 cavity bay 13 covers as needed
	DEVMESHHANDLE hDevBay13Mesh = STS()->GetDevMesh( vis, mesh_PLB_bay13 );
	if (!hasBay13covers)
	{
		if (hasLiner)
		{
			oapiWriteLog( "(SSV_OV) [INFO] Hiding T-4 cavity liner cover" );
			oapiEditMeshGroup( hDevBay13Mesh, GRP_PLB_TCS_LINER_PORT_T4_CAVITY_BAY13LINER, &grpSpec );
			oapiEditMeshGroup( hDevBay13Mesh, GRP_PLB_TCS_LINER_STBD_T4_CAVITY_BAY13LINER, &grpSpec );
		}
		else
		{
			oapiWriteLog( "(SSV_OV) [INFO] Hiding T-4 cavity MLI cover" );
			oapiEditMeshGroup( hDevBay13Mesh, GRP_PLB_MLI_TCS_PORT_T4_CAVITY_BAY13MLI, &grpSpec );
			oapiEditMeshGroup( hDevBay13Mesh, GRP_PLB_MLI_TCS_STBD_T4_CAVITY_BAY13MLI, &grpSpec );
		}
	}

	// hide MMU/FSS interface panel as needed
	if (!hasMMUFSSInterfacePanel)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding FSS panels" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_MMU_FSS_INTERFACE_PANELS, &grpSpec );
	}

	// hide fwd bulkhead and docking lights as needed
	if (!hasFwdBulkDockLights)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding Fwd bulkhead and docking lights" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_DOCKING_LIGHT, &grpSpec );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_FWD_BULKHEAD_LIGHT, &grpSpec );
	}

	// hide vent door 4 filter as needed
	if (!hasVentDoors4and7)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding vent door 4 filter" );
		oapiEditMeshGroup( STS()->GetOVDevMesh(), GRP_PLB_VENT_DOOR_FILTER_SCREENS_VENT_DOOR_4, &grpSpec );
	}

	// update UV in lights
	for (const auto& x : lights) x->VisualCreated();

	// update UV in camera lights
	for (int i = 0; i < 4; i++)
	{
		if (!cameras[i]) continue;

		CCTVCameraPTU_LED* led = dynamic_cast<CCTVCameraPTU_LED*>(cameras[i]);
		if (led) led->VisualCreated();
		else
		{
			// if CTVC/ITVC and not using illuminator, hide those parts
			if (plbcameras.Type[i] == 1)
			{
				oapiEditMeshGroup( STS()->GetDevMesh( STS()->Get_vis(), mesh_plbcamera[i] ), 3, &grpSpec );
				oapiEditMeshGroup( STS()->GetDevMesh( STS()->Get_vis(), mesh_plbcamera[i] ), 4, &grpSpec );
				oapiEditMeshGroup( STS()->GetDevMesh( STS()->Get_vis(), mesh_plbcamera[i] ), 5, &grpSpec );
				oapiEditMeshGroup( STS()->GetDevMesh( STS()->Get_vis(), mesh_plbcamera[i] ), 6, &grpSpec );
				oapiEditMeshGroup( STS()->GetDevMesh( STS()->Get_vis(), mesh_plbcamera[i] ), 7, &grpSpec );
			}
		}
	}
	return;
}

void PayloadBay::LoadPLBBlankets( void )
{
	// bay 1
	STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? (hasKeelBridge[0] ? (hasMMUFSSInterfacePanel ? MESHNAME_PLBLINERKEELMMUGAPS : MESHNAME_PLBLINERKEELGAP[0]) : (hasMMUFSSInterfacePanel ? MESHNAME_PLBLINERMMUGAPS : MESHNAME_PLBLINER[0])) : (hasKeelBridge[0] ? (hasMMUFSSInterfacePanel ? MESHNAME_PLBMLIKEELMMUGAPS : MESHNAME_PLBMLIKEELGAP[0]) : (hasMMUFSSInterfacePanel ? MESHNAME_PLBMLIMMUGAP : MESHNAME_PLBMLI[0])) ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// bay 2
	STS()->SetMeshVisibilityMode( STS()->AddMesh(
		hasLiner ?
			(hasKeelBridge[1] ?
				(hasExtALODSKit ?
					MESHNAME_PLBLINERKEELEXTALODSGAPS :
					MESHNAME_PLBLINERKEELGAP[1]) :
				(hasExtALODSKit ?
					MESHNAME_PLBLINEREXTALODSGAPS :
					MESHNAME_PLBLINER[1])) :
			(hasKeelBridge[1] ?
				(hasExtALODSKit ?
					MESHNAME_PLBMLIKEELEXTALODSGAPS :
					MESHNAME_PLBMLIKEELGAP[1]) :
				(hasExtALODSKit ?
					MESHNAME_PLBMLIEXTALODSGAP :
					MESHNAME_PLBMLI[1]))
		), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// bay 3-5
	for (int i = 2; i < 5; i++)
	{
		STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? (hasKeelBridge[i] ? MESHNAME_PLBLINERKEELGAP[i] : MESHNAME_PLBLINER[i]) : (hasKeelBridge[i] ? MESHNAME_PLBMLIKEELGAP[i] : MESHNAME_PLBMLI[i]) ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}

	// bay 6
	STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? (hasKeelBridge[5] ? (hasVentDoors4and7 ? MESHNAME_PLBLINERKEELFILTER4GAPS : MESHNAME_PLBLINERKEELGAP[5]) : (hasVentDoors4and7 ? MESHNAME_PLBLINERFILTER4GAP : MESHNAME_PLBLINER[5])) : (hasKeelBridge[5] ? MESHNAME_PLBMLIKEELGAP[5] : MESHNAME_PLBMLI[5]) ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// bay 7-10
	for (int i = 6; i < 10; i++)
	{
		STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? (hasKeelBridge[i] ? MESHNAME_PLBLINERKEELGAP[i] : MESHNAME_PLBLINER[i]) : (hasKeelBridge[i] ? MESHNAME_PLBMLIKEELGAP[i] : MESHNAME_PLBMLI[i]) ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}

	// bay 11
	STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? (hasKeelBridge[10] ? (hasEDOKit ? MESHNAME_PLBLINERKEELEDOGAPS : MESHNAME_PLBLINERKEELGAP[10]) : (hasEDOKit ? MESHNAME_PLBLINEREDOGAPS : MESHNAME_PLBLINER[10])) : (hasKeelBridge[10] ? (hasEDOKit ? MESHNAME_PLBMLIKEELEDOGAPS : MESHNAME_PLBMLIKEELGAP[10]) : (hasEDOKit ? MESHNAME_PLBMLIEDOGAP : MESHNAME_PLBMLI[10])) ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// bay 12
	STS()->SetMeshVisibilityMode( STS()->AddMesh( hasLiner ? MESHNAME_PLBLINER[11] : MESHNAME_PLBMLI[11] ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// bay 13
	mesh_PLB_bay13 = STS()->AddMesh( hasLiner ? MESHNAME_PLBLINER[12] : MESHNAME_PLBMLI[12] );
	STS()->SetMeshVisibilityMode( mesh_PLB_bay13, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void PayloadBay::LoadDFIWireTray( void )
{
	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_DFI_WIRETRAY ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	oapiWriteLog( "(SSV_OV) [INFO] DFI Wire Tray mesh added" );
	return;
}

void PayloadBay::LoadEDOKit( void )
{
	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_EDO_KIT ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	oapiWriteLog( "(SSV_OV) [INFO] EDO kit mesh added" );
	return;
}

void PayloadBay::LoadExtALODSKit( void )
{
	STS()->SetMeshVisibilityMode( STS()->AddMesh( MESHNAME_EXTAL_ODS_KIT ), MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	oapiWriteLog( "(SSV_OV) [INFO] External Airlock / ODS kit mesh added" );
	return;
}

void PayloadBay::CreateCCTV( void )
{
	CreatePLBCam( CAM_A_POS, 0 );
	CreatePLBCam( CAM_B_POS, 1 );
	CreatePLBCam( CAM_C_POS, 2 );
	CreatePLBCam( CAM_D_POS, 3 );

	// keel
	if (plbcameras.Keel[0] != 0)
	{
		// find Xo position
		double Xo = PLID_Xo[plbcameras.Keel[0] - PLID_Xo_base];
		if (Xo > 0.0)
		{
			// convert to z position
			VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

			// Yo and Zo
			switch (plbcameras.Keel[0])
			{
				case 226:
					pos.x = Yo_226 * IN2M;
					pos.y = (Zo_226_280 * IN2M) - 10.5871;
					break;
				case 280:
					pos.x = Yo_280 * IN2M;
					pos.y = (Zo_226_280 * IN2M) - 10.5871;
					break;
				default:
					pos.x = Yo_Generic * IN2M;
					pos.y = (Zo_Generic * IN2M) - 10.5871;
					break;
			}
			// shift for lens distance to center
			pos.y -= 0.18931;

			mesh_keelcamera = STS()->AddMesh( oapiLoadMeshGlobal( MESHNAME_KEEL_CCTV_CAMERA ), &pos );
			STS()->SetMeshVisibilityMode( mesh_keelcamera, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

			keelcamera = new CCTVCamera( STS(), pos );

			// add keel bridge
			LoadKeelBridgeByPLID( plbcameras.Keel[0] );
		}
	}
	return;
}

void PayloadBay::CreatePLBCam( const VECTOR3& pos, const unsigned int idx )
{
	if (plbcameras.Installed[idx])
	{
		VECTOR3 _pos;
		if (plbcameras.Custom[idx])
		{
			_pos.x = plbcameras.Yo[idx] * IN2M;
			_pos.y = (plbcameras.Zo[idx] * IN2M) - 10.5871;
			_pos.z = 24.239 - (plbcameras.Xo[idx] * IN2M);
		}
		else _pos = pos;

		if (plbcameras.Type[idx] == 0)// -506/-508
		{
			mesh_plbcamera[idx] = STS()->AddMesh( oapiLoadMeshGlobal( MESHNAME_PLB_CCTV_CAMERA_506_508 ), &_pos );
			cameras[idx] = new CCTVCameraPTU( STS(), _pos );
		}
		else// if (plbcameras.Type[idx] == 1)// CTVC/ITVC
		{
			mesh_plbcamera[idx] = STS()->AddMesh( oapiLoadMeshGlobal( MESHNAME_PLB_CCTV_CAMERA_CTVC_ITVC ), &_pos );
			if (plbcameras.Illuminator[idx]) cameras[idx] = new CCTVCameraPTU_LED( STS(), _pos );
			else cameras[idx] = new CCTVCameraPTU( STS(), _pos );
		}

		STS()->SetMeshVisibilityMode( mesh_plbcamera[idx], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}
	return;
}
