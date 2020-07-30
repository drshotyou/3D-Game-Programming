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
#include "TutorialApplication.h"
#include "BasicTools.h"


using namespace Ogre;
using namespace std;
BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::createCamera(void)
{
	mCameraMap = mSceneMgr->createCamera("MapCamera");

	/*
	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	*/


	mCameraMap->setPosition(Ogre::Vector3(0,700,0));
	mCameraMap->lookAt(Ogre::Vector3(0,0,0.001));

	mCameraMap->setNearClipDistance(5);
	mCameraMap->yaw(Degree(180));

	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCamera");

	/*
	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	*/


	mCamera->setPosition(Ogre::Vector3(0,750,500));
	mCamera->lookAt(Ogre::Vector3(0,0,0));

	mCamera->setNearClipDistance(5);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createViewports(void)
{
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(
		mCameraMap, 1, 0.0, 0, 0.25, 0.25);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
	vp->setOverlaysEnabled(false);
	vp->setSkiesEnabled(false);
	// Alter the camera aspect ratio to match the viewport
	mCameraMap->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// Create one viewport, entire window
	vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    //vp->setOverlaysEnabled(false);
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void BasicTutorial_00::createScene(void) 
{
    mCurrentPathPointIndex = 0;
	ColourValue fadeColour(0.9, 0.9, 0.9); 
	//mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0, 1400, 1600);
	mSceneMgr->setSkyBox(
		true, 
		"Examples/SpaceSkyBox"); 

    mSceneMgr->setAmbientLight( ColourValue( 0.9, 0.9, 0.9 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 

	//
	Light *light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(0, 150, 250)); 
	light->setDiffuseColour(1.0, 1.0, 1.0);		//red
	light->setSpecularColour(0.5, 0.5, 0.5);	//red

	mLightSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mLightSceneNode->attachObject(light);
	int i;

	//Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing SCENE ***");

	//

    //
    mRobotNode = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();
    mRobotEntity = mSceneMgr->createEntity(
		"robot", "robot.mesh"); 
    mRobotNode->attachObject( mRobotEntity );
    //
    mRobotNode->scale(1.0, 1.0, 1.0 );
    
    //mAnimationState = mRobotEntity->getAnimationState("Idle");
	//	mAnimationState->setEnabled(true);
	//	mAnimationState->setLoop(true);

    //
    mMap = new MAP;
    mMap->generateMap( mSceneMgr );
    //

}
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
/*
	if (mFlgSelectNow == true) {
		Ray mRay =mTrayMgr->getCursorRay(mCamera);

		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
		left = scn.x;
		top = scn.y;
		mSelectionRect->setCorners(left, top, right, bottom);
		mSelectionRect->setVisible(true);
	}
    */
	return BaseApplication::mouseMoved( arg);

}

void BasicTutorial_00::singleClickSelect ( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	Ray mRay =mTrayMgr->getCursorRay(mCamera);

}

//
// Compute the intersection point between 
// the mouse ray and the plane.
// Save the intersection point to mGoalPosition
//
// Algorithm:
// 1. Get the mouse ray using mTrayMgr->getCursorRay(mCamera)
// 2. Set up the plane p: Plane p(Vector3(0, 1, 0), 0)
// 3. Compute the intersection point: 
//    std::pair<bool,Real> result = ray.intersects(p);
//	  Vector3 point = ray.getOrigin()+result.second*ray.getDirection();
// 4. mGoalPosition = point
//
void BasicTutorial_00::computeGoalPosition( )
{
    //mGoalPosition = point;
}

bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	/*
	if (left==right && top==bottom) {
	return BaseApplication::mouseReleased( arg, id );

	}
	*/
	/* CEGUI
	Ray topLeft = mCamera->getCameraToViewportRay(left, top);
	Ray topRight = mCamera->getCameraToViewportRay(right, top);
	Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
	Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);
	*/
	if (id == OIS::MB_Right) {
		//computeTargetPosition(1);
		//return true;
		return BaseApplication::mouseReleased( arg, id );
	}
	return BaseApplication::mouseReleased( arg, id );

}

//
// If MouseButtonID id == OIS::MB_Left do
//   computeGoalPosition( )
//   perform path finding
//   Save the path points: mPathPoints = mMap->getPathPoints();
//
bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (id == OIS::MB_Left) {
		
        
		return BaseApplication::mouseReleased( arg, id );
	}


	return BaseApplication::mousePressed( arg, id );
}

//
// Control the robot to move along the path
// Update the look-at direction of the robot
// Set the animation state of the robot properly
//
void BasicTutorial_00::controlRobotMovingAlongPath( const FrameEvent &evt )
{
    if ( mPathPoints.size() == 0 ) return;

}

bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
    controlRobotMovingAlongPath( evt );
	return BaseApplication::frameStarted(evt);
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
