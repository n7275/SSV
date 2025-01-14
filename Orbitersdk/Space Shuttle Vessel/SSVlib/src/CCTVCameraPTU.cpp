#include "CCTVCameraPTU.h"
#include "MathSSV.h"


constexpr double PTU_HIGHRATE_SPEED = 12.0;// [deg/s]
constexpr double PTU_LOWRATE_SPEED = 1.2;// [deg/s]
constexpr double PLB_CAM_PAN_MIN = -170.0;// [deg]
constexpr double PLB_CAM_PAN_MAX = 170.0;// [deg]
constexpr double PLB_CAM_TILT_MIN = -80.0;// [deg]
constexpr double PLB_CAM_TILT_MAX = 260.0;// [deg]

const VECTOR3 ZoDIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 XoDIR = _V( 0.0, 0.0, 1.0 );
const VECTOR3 PANDIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 TILTDIR = _V( 1.0, 0.0, 0.0 );


CCTVCameraPTU::CCTVCameraPTU( VESSEL4* const v, const VECTOR3& pos ):CCTVCamera( v, pos ),
	CAMERAZO(NULL), CAMERAXO(NULL), CAMERAPAN(NULL), CAMERATILT(NULL), anim_Zo(-1), anim_Xo(-1), anim_Pan(-1), anim_Tilt(-1), panmax(PLB_CAM_PAN_MAX), panmin(PLB_CAM_PAN_MIN),
	tiltmax(PLB_CAM_TILT_MAX), tiltmin(PLB_CAM_TILT_MIN), pantiltlowrate(PTU_LOWRATE_SPEED), pantilthighrate(PTU_HIGHRATE_SPEED), dummyzo{1.0, 0.0, 0.0}, dummyxo{1.0, 0.0, 0.0}
{
	return;
}

CCTVCameraPTU::~CCTVCameraPTU()
{
	if (CAMERAZO) delete CAMERAZO;
	if (CAMERAXO) delete CAMERAXO;

	if (CAMERAPAN) delete CAMERAPAN;
	if (CAMERATILT) delete CAMERATILT;
	return;
}

void CCTVCameraPTU::LoadState( const char* line )
{
	sscanf_s( line, "%lf %lf %lf", &pan, &tilt, &zoom );
	pan = range( panmin, pan, panmax );
	tilt = range( tiltmin, tilt, tiltmax );
	zoom = range( zoommin, zoom, zoommax );
	return;
}

void CCTVCameraPTU::ConnectPowerPTUHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Line )
{
	dipPTUHeater.Connect( Bundle, Line );
	return;
}

void CCTVCameraPTU::SaveState( char* line ) const
{
	sprintf_s( line, 256, "%.6f %.6f %.6f", pan, tilt, zoom );
	return;
}

void CCTVCameraPTU::TimeStep( const double dt )
{
	CCTVCamera::TimeStep( dt );

	if (dipPower && dipPowerOnOff)
	{
		int motion = PanRightCmd - PanLeftCmd;
		if (motion != 0)
		{
			double rt = PanTiltCtrlClk ? pantilthighrate : pantiltlowrate;
			pan = range( panmin, pan + (motion * rt * dt), panmax );
		}

		motion = TiltUpCmd - TiltDownCmd;
		if (motion != 0)
		{
			double rt = PanTiltCtrlClk ? pantilthighrate : pantiltlowrate;
			tilt = range( tiltmin, tilt + (motion * rt * dt), tiltmax );
		}
	}
	PanRightCmd = false;
	PanLeftCmd = false;
	TiltUpCmd = false;
	TiltDownCmd = false;

	Update();
	return;
}

void CCTVCameraPTU::Update( void )
{
	VECTOR3 pan_axis = top0;
	VECTOR3 tilt_axis = -crossp( top0, dir0 );

	MATRIX3 rmat_pan = rotm( pan_axis, pan * RAD );
	VECTOR3 tmptilt_axis = mul( rmat_pan, tilt_axis );
	dir = mul( rmat_pan, dir0 );
	top = mul( rmat_pan, top0 );

	MATRIX3 rmat_tilt = rotm( tmptilt_axis, tilt * RAD );
	dir = mul( rmat_tilt, dir );
	top = mul( rmat_tilt, top );

	v->SetAnimation( anim_Pan, linterp( PLB_CAM_PAN_MIN, 0.0, PLB_CAM_PAN_MAX, 1.0, pan ) );
	v->SetAnimation( anim_Tilt, linterp( PLB_CAM_TILT_MIN, 0.0, PLB_CAM_TILT_MAX, 1.0, tilt ) );
	return;
}

void CCTVCameraPTU::DefineAnimations( const UINT mesh_idx, const double rotZo, const double rotXo, const UINT* base_grp, const UINT base_grp_sz, const UINT* pan_grp, const UINT pan_grp_sz, const UINT* tilt_grp, const UINT tilt_grp_sz )
{
	assert( (mesh_idx != -1) && "CCTVCameraPTU::DefineAnimations.mesh_idx" );

	ANIMATIONCOMPONENT_HANDLE parent = NULL;
	VECTOR3 tmpXoDIR = XoDIR;

	// base orientation
	if (rotZo != 0.0)
	{
		CAMERAZO = new MGROUP_ROTATE( LOCALVERTEXLIST, MAKEGROUPARRAY(&dummyzo), 1, _V( 0.0, 0.0, 0.0 ), ZoDIR, static_cast<float>(rotZo * RAD) );
		anim_Zo = v->CreateAnimation( 0.0 );
		parent = v->AddAnimationComponent( anim_Zo, 0.0, 1.0, CAMERAZO );
		v->SetAnimation( anim_Zo, 1.0 );

		// update base direction and top
		MATRIX3 rmat = rotm( ZoDIR, rotZo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
		tmpXoDIR = mul( rmat, tmpXoDIR );
	}

	//if (rotXo != 0.0)
	{
		CAMERAXO = new MGROUP_ROTATE( mesh_idx, const_cast<UINT*>(base_grp), base_grp_sz, _V( 0.0, 0.0, 0.0 ), XoDIR, static_cast<float>(rotXo * RAD) );
		anim_Xo = v->CreateAnimation( 0.0 );
		parent = v->AddAnimationComponent( anim_Xo, 0.0, 1.0, CAMERAXO, parent );
		v->SetAnimation( anim_Xo, 1.0 );

		// update base direction and top
		MATRIX3 rmat = rotm( tmpXoDIR, rotXo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
	}

	// PTU
	CAMERAPAN = new MGROUP_ROTATE( mesh_idx, const_cast<UINT*>(pan_grp), pan_grp_sz, _V( 0.0, 0.0, 0.0 ), PANDIR, static_cast<float>((PLB_CAM_PAN_MAX - PLB_CAM_PAN_MIN) * RAD) );
	anim_Pan = v->CreateAnimation( 0.5 );
	parent = v->AddAnimationComponent( anim_Pan, 0.0, 1.0, CAMERAPAN, parent );

	CAMERATILT = new MGROUP_ROTATE( mesh_idx, const_cast<UINT*>(tilt_grp), tilt_grp_sz, _V( 0.0, 0.0, 0.0 ), TILTDIR, static_cast<float>((PLB_CAM_TILT_MAX - PLB_CAM_TILT_MIN) * RAD) );
	anim_Tilt = v->CreateAnimation( PLB_CAM_TILT_MIN / (PLB_CAM_TILT_MIN - PLB_CAM_TILT_MAX) );
	v->AddAnimationComponent( anim_Tilt, 0.0, 1.0, CAMERATILT, parent );

	Update();
	return;
}

void CCTVCameraPTU::DefineAnimations( const double rotZo, const double rotXo, const UINT anim_pan, const UINT anim_tilt )
{
	VECTOR3 tmpXoDIR = XoDIR;

	// base orientation
	if (rotZo != 0.0)
	{
		// update base direction and top
		MATRIX3 rmat = rotm( ZoDIR, rotZo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
		tmpXoDIR = mul( rmat, tmpXoDIR );
	}

	if (rotXo != 0.0)
	{
		MATRIX3 rmat = rotm( tmpXoDIR, rotXo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
	}

	anim_Pan = anim_pan;
	anim_Tilt = anim_tilt;

	Update();
	return;
}
