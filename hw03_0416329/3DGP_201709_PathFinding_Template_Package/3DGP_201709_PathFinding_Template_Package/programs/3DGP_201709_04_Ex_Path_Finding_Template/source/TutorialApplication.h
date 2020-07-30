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
#include "map.h"

using namespace Ogre;
#define MOTION_TYPE_NONE 0
#define MOTION_TYPE_IDLE 1
#define MOTION_TYPE_WALK 2

class BasicTutorial_00 : public BaseApplication
{
private:
    
    Vector3 mStartPosition, mGoalPosition;

	SceneNode *mRobotNode;
	Entity *mRobotEntity;

    //
    AnimationState *mAnimationState;
    //
    std::vector<Vector3> mPathPoints;
       int mCurrentPathPointIndex;
    //
	SceneNode *mLightSceneNode;

	void computeGoalPosition( );

Camera *mCameraMap;

MAP *mMap;

virtual void createCamera();
virtual void createViewports();

void volumeSelect( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
void singleClickSelect ( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
virtual bool frameStarted(const FrameEvent &evt);
//
void controlRobotMovingAlongPath( const FrameEvent &evt );

public:
	BasicTutorial_00(void);
	virtual void createScene(void);
};
 
#endif // #ifndef __BasicTutorial_00_h_








// SIGNATURE: XYZ123 //