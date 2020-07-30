//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: AA BB CC
\n
My ID: 0123456789
\n
My Email: aaa@cs.nctu.edu.tw
\n Date: 2017/09/24

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "MassSpringSystem.h"

using namespace Ogre;

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
    //
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    void createSpace();
    void reset();
    void update(Real time_step);
    //
    void setMassSpringSystem();
    void setObjPositions(
    int numSamples,
    int numCircles);
    void handleCollision();
    //
    void setBackground();

protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
    Real mSmallSphereRadius;
    //
    int mNumSpheres;
    SceneNode *mSceneNode[1024];
    Entity *mEntity[1024];

    Real mLargeSphereRadius;

    SceneNode *mLargeSphereSceneNode;
    Entity *mLargeSphereEntity;
    //
    int m_NumSamples;
    int m_NumCircles;
    //
    Real m_TimeStep;
    MASS_SPRING_SYSTEM *m_MassSpringSystem;
};

#endif // #ifndef __BasicTutorial_00_h_