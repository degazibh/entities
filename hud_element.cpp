#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "view.h"

#include "iclientmode.h"

#include <KeyValues.h>
#include <vgui/ISurface.h>
#include <vgui/ISystem.h>
#include <vgui_controls/AnimationController.h>

#include <vgui/ILocalize.h>

using namespace vgui;

#include "hudelement.h"
#include "hud_numericdisplay.h"

#include "convar.h"
#include "tier0/memdbgon.h"

class CHudCounter : public CHudElement, public CHudNumericDisplay {
	DECLARE_CLASS_SIMPLE(CHudCounter, CHudNumericDisplay)

public:
	CHudCounter(const char* pElementName);
	virtual void Init(void);
	virtual void Reset(void);

	void MsgFunc_UpdateCounter(bf_read& msg);

private:
	int m_iValue;
};

DECLARE_HUDELEMENT(CHudCounter);

DECLARE_HUD_MESSAGE(CHudCounter, UpdateCounter);

CHudCounter::CHudCounter(const char* pElementName) : CHudElement(pElementName), CHudNumericDisplay(NULL, "HudCounter") {
	SetHiddenBits(HIDEHUD_PLAYERDEAD);
}

void CHudCounter::Init() {
	HOOK_HUD_MESSAGE(CHudCounter, UpdateCounter);
}

void CHudCounter::Reset() {
	m_iValue = 0;
	SetLabelText(L"ITEMS");
	SetDisplayValue(m_iValue);
}

void CHudCounter::MsgFunc_UpdateCounter(bf_read& msg) {
	m_iValue += msg.ReadShort();
	SetDisplayValue(m_iValue);
}
