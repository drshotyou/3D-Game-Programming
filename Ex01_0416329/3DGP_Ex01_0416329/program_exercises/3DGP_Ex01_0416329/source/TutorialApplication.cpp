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
bool nineP=false, zeroP=false, sevenP=false,eightP=false;
Real y=70;
int d=0;
BasicTutorial_00::BasicTutorial_00(void)
    : 
mFlg_Root(false), mFlg_Root_Dir(true)

, mFlg_Arm(false), mFlg_Arm_Dir(true)
      
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


void BasicTutorial_00::createHierarchyStructure()
{
    String name_en;
    String name_sn;
	

    int index = 0;

    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" ); ;
    mSceneNode[index] = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		name_sn, Vector3( 0, 0, 0 ) ); 

    mSceneNode[index]->attachObject(mEntity[index]);
    //
    //
    ++index;
    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "column.mesh" ); ;
    mSceneNode[index] = mSceneNode[index-1]
		->createChildSceneNode( 
		name_sn, Vector3( 0, 100, 0 ) ); 
    mSceneNode[index]->scale(1.0, 0.5, 1.0);
    mSceneNode[index]->translate(Vector3(0.0, 0.0, 0.0),
        Node::TS_PARENT);
    mSceneNode[index]->attachObject(mEntity[index]);
    //
    ++index;
    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" ); ;
    mSceneNode[index] = mSceneNode[index-1]
		->createChildSceneNode( 
		name_sn, Vector3( 0, 275, 0 ) ); 
    mSceneNode[index]->scale(0.35, 0.35/0.5, 0.35);
    mSceneNode[index]->attachObject(mEntity[index]);
    //
    ++index;
    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "cube.mesh" ); ;
    mSceneNode[index] = mSceneNode[index-1]
		->createChildSceneNode( 
		name_sn, Vector3( 0, 250, 0 ) ); 
    mSceneNode[index]->scale(1.0/0.35, 1.0/0.35, 1.0/0.35);
    mSceneNode[index]->attachObject(mEntity[index]);
    //
    ++index;
    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "penguin.mesh" );
	mSceneNode[index] = mSceneNode[index-1]->createChildSceneNode(name_sn,Vector3(0,75,0));
    mSceneNode[index]->scale(1.0, 1.0, 1.0);
	mSceneNode[index]->attachObject(mEntity[index]);
    
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.0, 1.0, 0.0);		
	light->setSpecularColour(0.0, 1.0, 0.0);	

	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 300, 250)); 
	light->setDiffuseColour(0.5, 0.5, 0.5);		
	light->setSpecularColour(0.5, 0.5, 0.5);	

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

    createHierarchyStructure();

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
    /////////////////////////////
    //add your own stuff
    /////////////////////////////
    BaseApplication::keyPressed(arg);
	if(arg.key == OIS::KC_9){
		if(nineP==false && zeroP==false) 
		{
			nineP=true;
		}
		else if (nineP==true && zeroP==false)
		{
			nineP=false;
		}
		else if(zeroP==true)
		{
			zeroP=false;
			nineP=true;
		}
	}
	if(arg.key == OIS::KC_0){
		if(zeroP==false && nineP==false)
		{
			zeroP=true;
		}
		else if(zeroP==true && nineP==false)
		{
			zeroP=false;
		}
		else if(nineP=true)
		{
			nineP=false;
			zeroP=true;
		}
	}
	if(arg.key == OIS::KC_7){
		if(sevenP==false && eightP==false)
		{
			sevenP=true;
		}
		else if (sevenP==true && eightP==false)
		{
			sevenP=false;
		}
		else if (eightP==true)
		{
			eightP=false;
			sevenP=true;
		}
		
	}
	if(arg.key == OIS::KC_8){
		if(eightP==false && sevenP==false)
		{
			eightP=true;
		}
		else if(eightP==true && sevenP==false)
		{
			eightP=false;
		}
		else if(sevenP==true)
		{
			sevenP=false;
			eightP=true;
		}

	}

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
    /////////////////////////////
    //add your own stuff
    /////////////////////////////
    //
	Ogre::Real one=-0.1,two=0.1;
	
	if(nineP==1){
		mSceneNode[0]->yaw(Degree(one));
	}
	if(zeroP==1)
	{
		mSceneNode[0]->yaw(Degree(two));
	}
	if(sevenP==1){
		mSceneNode[1]->pitch(Degree(one));
	}
	if(eightP==1){
		mSceneNode[1]->pitch(Degree(two));
	}
	if(d==0)
	{
		if(y>200)
		{
			d=1;
		}
		y+=0.1;
		mSceneNode[4]->setPosition(0,y,0);
	}
	if(d==1)
	{
		if(y<70)
		{
			d=0;
		}
		y-=0.1;
		mSceneNode[4]->setPosition(0,y,0);
	}

	
		
	
	

	

    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
