#ifndef __MASS_SPRING_SYSTEM_H__
#define __MASS_SPRING_SYSTEM_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

using namespace Ogre;

class PARTICLE {
public:
    PARTICLE() {
        snode = 0;
        velocity = Vector3::ZERO;
        mass = 1.0;
        movable = true;
        radius = 1.0;
        
    }
    SceneNode *snode;
    Vector3 velocity;
    Real radius;
    float mass;
    bool movable;
    //
    Vector3 f; // force
};
class SPRING {
public:
    SPRING() {
        k = 500.0;
        L0 = 1.0;
        n0 = n1 = 0;
    }
    int n0, n1;
    float L0;
    
    Real k; //stiffness
	
};

class MASS_SPRING_SYSTEM {
protected:
    void init(int maxParticles, int maxSprings);
    void computeForce(float time_step);
    void computeVelocity(float time_step);
    void computePosition(float time_step);
public:
    MASS_SPRING_SYSTEM(
        int maxParticles = 1024,
        int maxSprings = 1024);
    int addParticle(SceneNode *n, Real radius, bool movable);
    SPRING *addSpring(int n0, int n1);

    void update(float time_step);
	
    void reset();
    void resetVelocity();
    void setCollisionConstraint(bool enable);
    bool getCollisionConstraintState() const { return m_FlgCollisionConstraints; }
    void setGravity(const Vector3 &g);
    //
    void adjustVelocityDueToCollisionConstraint_Floor(float time_step);
    void adjustVelocityDueToCollisionConstraint_LargeSphere(float time_step);
    void adjustVelocityDueToCollisionConstraint(float time_step);
protected:
    int m_MaxParticles;
    int m_CurParticles;
    PARTICLE *mParticles;
    //
    int m_MaxSprings;
    int m_CurSprings;
    SPRING *mSprings;
    //
    Vector3 m_Gravity;
    bool m_FlgCollisionConstraints;
    
};

#endif