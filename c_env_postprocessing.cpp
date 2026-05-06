#include "cbase.h"
#include "view_scene.h"
#include "viewrender.h"
#include "viewdebug.h"

#include "tier0/memdbgon.h"

class C_ScreenOverlay : public C_BaseEntity {
public:
    DECLARE_CLASS(C_ScreenOverlay, C_BaseEntity);
    DECLARE_CLIENTCLASS();

    char ShaderName[256];

    void Spawn(void);
    void Precache(void);

    virtual void OnDataChanged(DataUpdateType_t updateType) {
        BaseClass::OnDataChanged(updateType);
    }
};

IMPLEMENT_CLIENTCLASS_DT(C_ScreenOverlay, DT_ScreenOverlay, CScreenOverlay)
RecvPropString(RECVINFO(ShaderName)),
END_RECV_TABLE()

void C_ScreenOverlay::Precache(void) {
    BaseClass::Precache();
}

void C_ScreenOverlay::Spawn(void) {
    Precache();

    IMaterial* pMaterial = materials->FindMaterial(TOSTRING(ShaderName), TEXTURE_GROUP_OTHER, true);
    view->SetScreenOverlayMaterial(pMaterial);
}
