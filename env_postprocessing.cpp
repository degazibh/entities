#include "cbase.h"

#include "tier0/memdbgon.h"

class CScreenOverlay : public CPointEntity {
public:
	DECLARE_CLASS(CScreenOverlay, CPointEntity);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CNetworkString(ShaderName, 256);

	void Spawn(void);
	void Precache(void);

	int UpdateTransmitState() override
	{
		return SetTransmitState(FL_EDICT_ALWAYS);
	}
};

LINK_ENTITY_TO_CLASS(env_postprocessing, CScreenOverlay);

IMPLEMENT_SERVERCLASS_ST(CScreenOverlay, DT_ScreenOverlay)
SendPropString(SENDINFO(ShaderName))
END_SEND_TABLE()

BEGIN_DATADESC(CScreenOverlay)
	DEFINE_KEYFIELD(ShaderName, FIELD_STRING, "shadername"),
END_DATADESC()

void CScreenOverlay::Precache(void) {
	BaseClass::Precache();
}

void CScreenOverlay::Spawn()
{
	Precache();
	BaseClass::Spawn();
}