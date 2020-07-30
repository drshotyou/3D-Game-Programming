//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;



BasicTutorial_00::BasicTutorial_00(void)
{
    m_MassSpringSystem = 0;
    m_TimeStep = 0.06;
}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,350,0.0));
	mCamera->lookAt(Ogre::Vector3(0.00001,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

}



void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
}

void BasicTutorial_00::setMassSpringSystem()
{
	m_MassSpringSystem->setGravity(Vector3(0.0, -9.8, 0.0));
	for(int i=0;i<m_NumCircles*m_NumSamples;i++)
	{
		m_MassSpringSystem->addParticle(mSceneNode[i],mSmallSphereRadius,1);
	}
	int index=0;
	for (int j = 0; j < m_NumCircles; ++j) {
		if(j==m_NumCircles-2)
		{
			break;
		}
        for (int i = 0; i < m_NumSamples; ++i) {
			m_MassSpringSystem->addSpring(index,index+m_NumSamples);
			m_MassSpringSystem->addSpring(index,index+2*m_NumSamples);
			index++;
        }
    }
	return;
}

void BasicTutorial_00::setObjPositions(
    int numSamples,
    int numCircles
    )
{
    float r0 = 50.0; // radius of the first circle
    float dr = 12.0; // delta distance
    float h = 100.0; // height
	int current=0;
    for (int j = 0; j < numCircles; ++j) {
        float r = r0 + dr*j;
        for (int i = 0; i < numSamples; ++i) {
            //
            //
            //mSceneNode[index]->setPosition(x, y, z);
			float a = i/(float) numSamples*3.14*2.0;
            int x=r*cos(a);
			int z=r*sin(a);
            mSceneNode[current]->setPosition(x, h, z);
			current++;
        }
    }
}


void BasicTutorial_00::reset()
{
    setObjPositions(m_NumSamples,m_NumCircles);
    //if (m_MassSpringSystem) m_MassSpringSystem->reset();
}

//
// Simple collision handling method
//
// Directly modified the particle positions 
// if they collide with each other
//
void BasicTutorial_00::handleCollision()
{
    int numSpheres = m_NumSamples*m_NumCircles;

    //small spheres
    for (int i = 0; i < numSpheres; ++i) {
        for (int j = i+1; j < numSpheres; ++j) {
            resolveCollision(
            mSceneNode[i],
            mSceneNode[j],
            mSmallSphereRadius,
            mSmallSphereRadius,
            0.15,
            0.15);
        }
    }

    // large sphere and small spheres
    for (int i = 0; i < numSpheres; ++i) {
        resolveCollision(
            mLargeSphereSceneNode,
            mSceneNode[i],
            mLargeSphereRadius,
            mSmallSphereRadius,
            0.0,
            1.0);
    }
    
    //floor
    for (int i = 0; i < numSpheres; ++i) {
        Vector3 p = mSceneNode[i]->getPosition();
        if (p.y < mSmallSphereRadius) {
            p.y = mSmallSphereRadius+0.0001;
            mSceneNode[i]->setPosition(p);
        }
    }
}


void BasicTutorial_00::createSpace()
{
    String name_en;
    String name_sn;
	
    mSmallSphereRadius = 5.0;

    m_NumSamples = 8;
    m_NumCircles = 15;
    mNumSpheres = m_NumSamples*m_NumCircles;
    for (int i = 0; i < mNumSpheres; ++i ) {
    int index = i;
    float x = (rand()%10000)/10000.0;
    float z = (rand()%10000)/10000.0;
    float spaceSizeX = 400.0;
    float spaceSizeZ = 400.0;

    x = (1-2*x)*spaceSizeX;
    z = (1-2*z)*spaceSizeZ;

        genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" );

    switch(rand()%3) {
    case 0:
        mEntity[index]->setMaterialName("Examples/red");
        break;
    case 1:
        mEntity[index]->setMaterialName("Examples/green");

        break;
    case 2:
        mEntity[index]->setMaterialName("Examples/blue");

        break;
    }

    mSceneNode[index] = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		name_sn, Vector3( x, 0, z ) ); 

    float scale = mSmallSphereRadius*0.01;
    mSceneNode[index]->scale(scale, scale, scale);
    mSceneNode[index]->attachObject(mEntity[index]);
    }
    reset();
    
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	//mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) ); 

	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.3, 0.3, 0.3);		
	light->setSpecularColour(0.5, 0.5, 0.5);	

	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 300, 250)); 
	light->setDiffuseColour(0.25, 0.25, 0.25);		
	light->setSpecularColour(0.35, 0.35, 0.35);	

	//
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
		"ground", 						ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		1500,1500, 	// width, height
		20,20, 		// x- and y-segments
		true, 		// normal
		1, 			// num texture sets
		5,5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
		); 

	Entity *ent = mSceneMgr->createEntity(
		"GroundEntity", "ground"); 
	//ent->setMaterialName("Examples/BeachStones");
	//ent->setMaterialName("Examples/Rockwall");


	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ent); 

    ent = mSceneMgr->createEntity(
		"Background", "ground"); 
	//ent->setMaterialName("Examples/BeachStones");
	ent->setMaterialName("Examples/Rockwall");

    //Radian angle((45/180.0)*3.141592654);
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);

    createSpace();

    m_MassSpringSystem = new MASS_SPRING_SYSTEM(1024, 1024);
    setMassSpringSystem(); 
    
    mLargeSphereEntity  = mSceneMgr
		->createEntity( "large", "sphere.mesh" );
    mLargeSphereEntity->setMaterialName("Examples/yellow");
    mLargeSphereSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    
    mLargeSphereRadius = 100.0;

    mLargeSphereSceneNode->attachObject(mLargeSphereEntity);

    setBackground();
}

void BasicTutorial_00::createScene_01(void) 
{

}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
    //
    mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));

}

void BasicTutorial_00::setBackground()
{
    if (!m_MassSpringSystem) return;

    bool flg = m_MassSpringSystem->getCollisionConstraintState();

    if (!flg) {
        mViewportArr[0]->setBackgroundColour(ColourValue(1.0, 0.0, 0.0));
    } else {
        mViewportArr[0]->setBackgroundColour(ColourValue(0.0, 0.0, 1.0));
    }
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    
    if (arg.key == OIS::KC_C ) {
        
        //How to clear ss?
        ss.str("");
        ss.clear();
        
        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camerea position?
        //-----------------------------
        //This is incorrect.
        //Vector3 pos = mCamera->getPosition();
        //-----------------------------
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));

    }

    if (arg.key == OIS::KC_2 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-824.52,	468.58,	68.45));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.94,	-0.31,	-0.11));

        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }


    if (arg.key == OIS::KC_3 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-22.43,	305.22,	569.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.41,	-0.91));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    //
    if (arg.key == OIS::KC_7 ) {
        m_MassSpringSystem->setGravity(Vector3(0.0, -9.8, 0.0));
    }
    if (arg.key == OIS::KC_8 ) {
        m_MassSpringSystem->setGravity(Vector3(0.0, -30.0, 0.0));
    }
    if (arg.key == OIS::KC_9 ) {
        m_MassSpringSystem->setGravity(Vector3(0.0, 9.8, 0.0));
    }
    if (arg.key == OIS::KC_0 ) {
        m_MassSpringSystem->setGravity(Vector3(0.0, 30.0, 0.0));
    }

    if (arg.key == OIS::KC_P ) {
        m_MassSpringSystem->resetVelocity();
    }

    if (arg.key == OIS::KC_J ) {
        reset();
    }

    if (arg.key == OIS::KC_K ) {
        m_MassSpringSystem->setCollisionConstraint(false);
        setBackground();
    }
    if (arg.key == OIS::KC_L ) {
        m_MassSpringSystem->setCollisionConstraint(true);
        setBackground();
    }
    //
    
    //
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

void BasicTutorial_00::update(Real time_step) 
{
    m_MassSpringSystem->update( time_step );
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    //Real time_step = evt.timeSinceLastFrame;
    Real time_step = m_TimeStep;
    update(time_step);
    handleCollision();
    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
