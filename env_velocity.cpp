// I cant actually say is it works properly

#include "cbase.h"

class CVelocityEntity : public CPointEntity {
public:
    DECLARE_CLASS(CVelocityEntity, CPointEntity);
    DECLARE_DATADESC();

    CVelocityEntity() {
        // values by default
        m_bIsActive = true;
    }

    // smth here

    void Precache(void);
    void Spawn(void);

    void Velocity(inputdata_t& inputdata);
private:
    bool m_bIsActive;
    Vector m_vecDir;
};

LINK_ENTITY_TO_CLASS(env_velocity, CVelocityEntity);

    BEGIN_DATADESC(CVelocityEntity)

        DEFINE_KEYFIELD(m_bIsActive, FIELD_BOOLEAN, "activity"),
        DEFINE_KEYFIELD(m_vecDir, FIELD_VECTOR, "dir"),
        DEFINE_INPUTFUNC(FIELD_VOID, "ApplyVelocity", Velocity),

    END_DATADESC()

void CVelocityEntity::Precache(void) {
    BaseClass::Precache();
}

void CVelocityEntity::Spawn(void) {
    Precache();
}

void CVelocityEntity::Velocity(inputdata_t& inputdata) {
    if (inputdata.pActivator->IsAlive()) {
        inputdata.pActivator->ApplyAbsVelocityImpulse(m_vecDir);
    }
    else return;
}