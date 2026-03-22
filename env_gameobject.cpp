// bobos
// We finnaly can grab it!

#include "cbase.h"
#include "Sprite.h"

// #include "tier0/memdbgon.h" // Remove?

class CSprite;

class CGameObject : public CPointEntity {
public:
	DECLARE_CLASS(CGameObject, CPointEntity);
	DECLARE_DATADESC();

	CGameObject() {
		// values by default

		m_bActive = false;
		m_TextureName = NULL_STRING;
		m_SoundName = NULL_STRING;
		m_flScale = 1.0f;
		m_iBrightness = 255;
		m_iPoints = 0;
	}

	CSprite* m_pEyeFlash;
	COutputEvent m_OnTouchedEntity;

	void Spawn(void);
	void Precache(void);

	void MoveThink(void);

	void Touch(CBaseEntity* pOther);
	void AddPoint(CBasePlayer* pPlayer);

private:
	bool m_bActive;
	float m_flScale;
	int m_iBrightness;
	int m_iObjectType;
	int m_iPoints;
	string_t m_TextureName;
	string_t m_SoundName;
};

LINK_ENTITY_TO_CLASS(env_object, CGameObject);

BEGIN_DATADESC(CGameObject)

DEFINE_FIELD(m_bActive, FIELD_BOOLEAN),

DEFINE_KEYFIELD(m_TextureName, FIELD_STRING, "texturename"),
DEFINE_KEYFIELD(m_SoundName, FIELD_STRING, "obj_sound"),
DEFINE_KEYFIELD(m_flScale, FIELD_FLOAT, "obj_scale"),
DEFINE_KEYFIELD(m_iBrightness, FIELD_INTEGER, "brightness"),
DEFINE_KEYFIELD(m_iObjectType, FIELD_INTEGER, "obj_type"),
DEFINE_KEYFIELD(m_iPoints, FIELD_INTEGER, "add_points"),

DEFINE_OUTPUT(m_OnTouchedEntity, "OnTouchedEntity"),

DEFINE_ENTITYFUNC(Touch),

END_DATADESC()

void CGameObject::Precache(void) {
	BaseClass::Precache();

	if (m_TextureName == NULL_STRING) {
		Warning("GameObject with no texture name! Defaulting to sprites/white.vmt\n");
		m_TextureName = MAKE_STRING("sprites/white.vmt");
	}

	PrecacheModel(STRING(m_TextureName));
	PrecacheSound(STRING(m_SoundName));
}

void CGameObject::Touch(CBaseEntity* pOther)
{
	CBasePlayer* pPlayer = ToBasePlayer(pOther);

	if (m_iObjectType == 0)
		return;

	if (pOther->IsPlayer()) {
		EmitSound(STRING(m_SoundName));

		m_OnTouchedEntity.FireOutput(pOther, this);
		AddPoint(pPlayer);

		SetTouch(nullptr);
		UTIL_Remove(this);
		UTIL_Remove(m_pEyeFlash); // i forgor
	}
}

void CGameObject::Spawn(void) {
	Precache();

	// collision group
	SetMoveType(MOVETYPE_NONE);
	SetSolid(SOLID_BBOX);
	UTIL_SetSize(this, Vector(-8, -8, -8), Vector(8, 8, 8));

	// TODO: fix collision with obstacles
	SetTouch(&CGameObject::Touch);

	// draw group
	m_pEyeFlash = CSprite::SpriteCreate(STRING(m_TextureName), GetLocalOrigin(), FALSE);
	m_pEyeFlash->SetTransparency(kRenderTransTexture, 255, 255, 255, 0, kRenderFxNoDissipation);
	m_pEyeFlash->SetBrightness(m_iBrightness);
	m_pEyeFlash->SetScale(m_flScale);
}

void CGameObject::AddPoint(CBasePlayer* pPlayer) {

	CSingleUserRecipientFilter filter(pPlayer);
	filter.MakeReliable();

	UserMessageBegin(filter, "UpdateCounter");
	WRITE_SHORT(m_iPoints);
	MessageEnd();
}
