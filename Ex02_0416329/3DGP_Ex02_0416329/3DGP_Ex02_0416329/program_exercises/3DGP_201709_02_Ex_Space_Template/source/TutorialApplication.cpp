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

#define mMoveDirection_NONE 0
#define mMoveDirection_DOWN (1 << 0)
#define mMoveDirection_UP   (1 << 1)
#define mMoveDirection_LEFT (1 << 2)
#define mMoveDirection_RIGHT (1<<3)

bool iP=false,kP=false,jP=false,lP=false;
float x=0, y=0;
BasicTutorial_00::BasicTutorial_00(void)
    : 
mMoveDirection(mMoveDirection_NONE)
{}

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

void BasicTutorial_00::resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB)
{
    Vector3 posA = nodeA->getPosition();
    Vector3 posB = nodeB->getPosition();
	Vector3 l = posA - posB;
	
    float R = rA + rB;
    ///////////////////////
    // add your own stuff
    ///////////////////////
	if( R > l.length())
	{
		l.normalise();
		if(wA>wB)
		{	
			posB-=l;	
		}
		if(wA<wB)
		{
			posA+=l;
		}
		if(wA==wB)
		{
			posA+=l;
			posB-=l;
		}
		
	}
		nodeA->setPosition(posA);
		nodeB->setPosition(posB);
}

void BasicTutorial_00::resolveCollisionLargeSphere()
{
    float smallR = 15; // small sphere radius

    float largeR = 1.0/0.15*smallR; // large sphere radius
	for(int i=1;i<=300;++i)
	{
		resolveCollision(mSceneNode[0],mSceneNode[i],largeR,smallR,3,1);
	}
}

// perform collision handling for all pairs
void BasicTutorial_00::resolveCollisionSmallSpheres()
{
    float ri = 15; // sphere radius
    float rj = 15; // sphere radius
    for (int i = 1; i <= mNumSpheres; ++i)
	{
		for (int j = i+1; j <= mNumSpheres; ++j) {
            ///////////////////////
            // add your own stuff
            ///////////////////////
			resolveCollision(mSceneNode[i],mSceneNode[j],ri,rj,1,1);
        }
    }
}

void BasicTutorial_00::resolveCollision()
{
    int num = 10;
    for (int i = 0; i < num;++i) {
        resolveCollisionSmallSpheres();
        resolveCollisionLargeSphere();
    }
}

// reset positions of all small spheres
void BasicTutorial_00::reset()
{
    for (int i = 0; i < mNumSpheres; ++i ) {
        ///////////////////////
        // add your own stuff
        ///////////////////////
		mSceneNode[i]->setPosition(Vector3((rand()%800-400),0,(rand()%800-400)));
    }
	iP=false;
	kP=false;
	jP=false;
	lP=false;
	mSceneNode[0]->setPosition(x,0,y);
}

// create all spheres
// "Examples/red"
// "Examples/green"
// "Examples/blue"
// "Examples/yellow"
void BasicTutorial_00::createSpace()
{
    String name_en;
    String name_sn;
	
    mNumSpheres = 300;

		genNameUsingIndex("R1", 0, name_en);
		genNameUsingIndex("S1", 0, name_sn);
		mEntity[0] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" );
		mSceneNode[0]=mSceneMgr->getRootSceneNode()->createChildSceneNode(name_sn,Vector3(0,0,0));
		mSceneNode[0]->attachObject(mEntity[0]);
		mEntity[0]->setMaterialName("Examples/yellow");
    for (int i = 1; i <= mNumSpheres; ++i ) {
        genNameUsingIndex("R1", i, name_en);
		genNameUsingIndex("S1", i, name_sn);
		mEntity[i] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" );
		mSceneNode[i]=mSceneMgr->getRootSceneNode()->createChildSceneNode(name_sn,Vector3(((rand()%800)  -400),0,((rand()%800)-400)));
		mSceneNode[i]->attachObject(mEntity[i]);
		
         ///////////////////////
        // add your own stuff
        ///////////////////////
		
		
		
		

    switch(rand()%3) {
    case 0:
        mEntity[i]->setMaterialName("Examples/red");
        break;
    case 1:
		mEntity[i]->setMaterialName("Examples/green");
        break;
    case 2:
		mEntity[i]->setMaterialName("Examples/blue");
        break;
    }

    //scale the small spheres
    mSceneNode[i]->scale(0.15, 0.15, 0.15);
    }


    
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

    ///////////////////////
    // add your own stuff
    ///////////////////////
    
    resolveCollision();
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
            ->setPosition(Vector3(19.94,	822.63,	30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00,	-0.99,	-0.11));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    ///////////////////////
    // add your own stuff
    ///////////////////////

    if (arg.key == OIS::KC_B ) {
		reset();
    }

	if (arg.key == OIS::KC_I ) {
		iP=true;
		kP=false;
		jP=false;
		lP=false;
    }
	if (arg.key == OIS::KC_K ) {
		iP=false;
		kP=true;
		jP=false;
		lP=false;
    }
	if (arg.key == OIS::KC_J ) {
		iP=false;
		kP=false;
		jP=true;
		lP=false;
    }
	if (arg.key == OIS::KC_L ) {
		iP=false;
		kP=false;
		jP=false;
		lP=true;
    }

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

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    Vector3 mdir;
    if (mMoveDirection & mMoveDirection_UP ) {
        mdir += Vector3(0.0, 0.0, -1.0);
    }

    ///////////////////////
    // add your own stuff
    ///////////////////////
	if(iP==true)
	{
		y-=1;
		mSceneNode[0]->setPosition(x,0,y);
	}
	if(kP==true)
	{
		y+=1;
		mSceneNode[0]->setPosition(x,0,y);
	}
	if(jP==true)
	{
		x-=1;
		mSceneNode[0]->setPosition(x,0,y);
	}
	if(lP==true)
	{
		x+=1;
		mSceneNode[0]->setPosition(x,0,y);
	}
    resolveCollision();
    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
