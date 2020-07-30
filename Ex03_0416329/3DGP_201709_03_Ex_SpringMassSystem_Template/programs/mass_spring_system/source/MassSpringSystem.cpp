#include "MassSpringSystem.h"

MASS_SPRING_SYSTEM::MASS_SPRING_SYSTEM(
    int maxParticles,
    int maxSprings)
{
    init(maxParticles, maxSprings);
}

void MASS_SPRING_SYSTEM::init(
    int maxParticles,
    int maxSprings
) {
    m_Gravity = Vector3(0.0, -9.8, 0.0);
    m_FlgCollisionConstraints = false;

    m_MaxParticles = maxParticles;
    m_CurParticles = 0;
    mParticles = new PARTICLE[m_MaxParticles];
    //
    m_MaxSprings = maxSprings;
    m_CurSprings = 0;
    mSprings = new SPRING[m_MaxSprings];
}

int MASS_SPRING_SYSTEM::addParticle(SceneNode *n, Real radius, bool movable)
{
	PARTICLE *p = &mParticles[m_CurParticles];
	p->snode = n;
	p->radius = radius;
	p->movable = movable;
	m_CurParticles++;
    return 0;
    
}

SPRING *MASS_SPRING_SYSTEM::addSpring(
    int n0, int n1)
{
    SPRING *s = &mSprings[m_CurSprings];
	s->n0 = n0;
	s->n1 = n1;
	m_CurSprings++;
    return s;
}

void MASS_SPRING_SYSTEM::setGravity(const Vector3 &g)
{
    m_Gravity = g;
}

//
// reset force
// compute damping force
// compute viscous damping force between particles
// compute spring force
// compute net force
void MASS_SPRING_SYSTEM::computeForce(float time_step)
{
	Real k_viscous =  0.025;
	for(int i=0;i<m_CurParticles;++i)
	{
		mParticles[i].f = Vector3::ZERO;
	}
    for (int i = 0; i < m_CurParticles; ++i ) {
		mParticles[i].f = m_Gravity*mParticles[i].mass;
    }
	for(int i=0;i<m_CurSprings;i++)
	{
		
			int index0 = i;
			int index1 = index0 + 1;
			Vector3 p0,p1;
			p0 = mParticles[mSprings[index0].n0].snode->getPosition();
			p1 = mParticles[mSprings[index1].n1].snode->getPosition();
			Real d = p0.distance(p1);
			Vector3 p0p1 = (p0-p1);
			p0p1.normalise();
			Vector3 F;
			Real L = mSprings[index0].L0;
			F = -(mSprings[index0].k)*(d-L)*p0p1;
			mParticles[mSprings[index0].n0].f +=F;
			mParticles[mSprings[index1].n1].f += -F;
			Vector3 vF;
			Vector3 v0 = mParticles[index0].f;
			Vector3 v1 = mParticles[index1].f;
			vF = -k_viscous*(v0-v1);
			mParticles[index0].f += vF;
			mParticles[index1].f += -vF;
		
	}
	
}

void MASS_SPRING_SYSTEM::computeVelocity(float time_step)
{
	for(int j=0;j<m_CurParticles;++j)
	{
		Vector3 v;
		Vector3 v0 = mParticles[j].velocity;
		v = v0 + (mParticles[j].f/mParticles[j].mass)*time_step;
		mParticles[j].velocity = v;
	}
}

void MASS_SPRING_SYSTEM::computePosition(float time_step)
{
	for(int i = 0; i<8;i++)
	{
		mParticles[i].velocity = Vector3::ZERO;
	}
	for(int j=0;j<m_CurParticles;++j)
	{
		Vector3 p;
		p = mParticles[j].snode->getPosition();
		p = p + mParticles[j].velocity*time_step;
		mParticles[j].snode->setPosition(p);
	}
}

void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint_Floor(float time_step)
{
    float e = 0.05;
	float small_radius=5;
	for(int j=0;j<m_CurParticles;++j)
	{
		Vector3 p;
		Vector3 v;
		p = mParticles[j].snode->getPosition();
		v = mParticles[j].velocity;
		if(p.y < (e+small_radius))
		{
			Vector3 floor = p;
			floor.y=0;
			Vector3 newPos = (floor-p)/(floor-p).length();
			if(newPos.dotProduct(v)>0)
			{
				mParticles[j].velocity = v - newPos.dotProduct(v)*newPos;
			}
		}
		mParticles[j].velocity = v;
		
	}
}

void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint_LargeSphere(float time_step)
{
    float large_radius = 100.0;
    float small_radius = 5.0;
    float e = 0.05;
	for (int i=0;i<m_CurParticles;++i)
	{
		Vector3 curPos = mParticles[i].snode->getPosition();
		Vector3 origin = Vector3::ZERO;
		if((origin-curPos).length()<e+large_radius+small_radius)
		{
			Vector3 newPos = (origin-curPos)/(origin-curPos).length();
			if(newPos.dotProduct(mParticles[i].velocity)>0)
			{
				mParticles[i].velocity = mParticles[i].velocity - newPos.dotProduct(mParticles[i].velocity)*newPos;
			}
		}
	}

}

void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint(float time_step)
{
	float small_radius = 5.0;
	float e = 0.05;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<m_CurParticles;++j)
		{
			for(int k=j+1;k<m_CurParticles;++k)
			{
				Vector3 firstPart= mParticles[j].snode->getPosition();
				Vector3 secondPart= mParticles[k].snode->getPosition();
				if((firstPart-secondPart).length()<(2*small_radius+e))
				{
					Vector3 newPos = (secondPart-firstPart)/(firstPart-secondPart).length();
					if(newPos.dotProduct(mParticles[j].velocity)>0)
					{
						mParticles[j].velocity = mParticles[j].velocity-(newPos.dotProduct(mParticles[j].velocity)*newPos);

					}
					else if(newPos.dotProduct(mParticles[j].velocity)<0) 
					{
						mParticles[k].velocity = mParticles[k].velocity-(newPos.dotProduct(mParticles[k].velocity)*newPos);
					}
				}
			}
		}
	}
    adjustVelocityDueToCollisionConstraint_Floor(time_step);
    adjustVelocityDueToCollisionConstraint_LargeSphere(time_step);

}

void MASS_SPRING_SYSTEM::reset()
{
    resetVelocity();
}

void MASS_SPRING_SYSTEM::resetVelocity()
{
    if (m_CurParticles < 0) return;
    for (int i = 0; i < m_CurParticles; ++i ) {
        PARTICLE *p = &mParticles[i];
        p->velocity = Vector3::ZERO;
    }
}

void MASS_SPRING_SYSTEM::setCollisionConstraint(bool enable)
{
    m_FlgCollisionConstraints = enable;
}

void MASS_SPRING_SYSTEM::update(float time_step) {
    computeForce(time_step);
    computeVelocity(time_step);
    if (m_FlgCollisionConstraints) adjustVelocityDueToCollisionConstraint(time_step);
    computePosition(time_step);
}