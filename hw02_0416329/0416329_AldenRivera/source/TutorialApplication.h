//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Select and move characters
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "selection_rectangle.h"
#include "sound.h"

using namespace Ogre;
#define MOTION_TYPE_NONE 0
#define MOTION_TYPE_IDLE 1
#define MOTION_TYPE_WALK 2

class BasicTutorial_00 : public BaseApplication
{
private:
	SceneNode *mCurrentObject;
	PlaneBoundedVolumeListSceneQuery *mVolQuery;
	Real left, top, right, bottom;
	SelectionRectangle *mSelectionRect;
	bool mFlgAllReached;
	/*!**************************
	\brief Initializes particle systems
	*****************************/
	void initParticleSystemForExplosion();
	/*!**************************
	\brief Sets of particles around node
	*****************************/
	void setOffParticleSystem(Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos);
SOUND *mSound;
SceneNode *mParticleNode;
/*!**************************
\brief Creates Camera
*****************************/
virtual void createCamera();
/*!**************************
\brief CreateViewports
*****************************/
virtual void createViewports();
/*!**************************
\brief moveMoved
*****************************/
virtual bool mouseMoved( const OIS::MouseEvent &arg );
/*!**************************
\brief mousePressed
*****************************/
virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
/*!**************************
\brief mouseReleased
*****************************/
virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
/*!**************************
\brief frameStarted
*****************************/
virtual bool frameStarted(const FrameEvent &evt);


public:
	BasicTutorial_00(void);
	virtual void createScene(void);
protected:
	SceneNode *mSceneNode[1024];
    Entity *mEntity[1024];
	Ogre::Viewport * mViewportArr[8];
	Ogre::Camera * mCameraArr[8];
	Ogre::SceneManager * mSceneMgrArr[8];
	void resolveCollision();
	void resolveCollisionSmallRobots();
	void resolveCollisionSmallBigRobots();
	void resolveCollisionSmallSphere();
	void resolveCollisionBigSphere();
	void resolveCollision(SceneNode *nodeA, SceneNode *nodeB, float rA, float rB);
	void resolveCollision(SceneNode *nodeA, SceneNode *nodeB, float rA, float rB,float wA, float wB);

};
 
#endif // #ifndef __BasicTutorial_00_h_