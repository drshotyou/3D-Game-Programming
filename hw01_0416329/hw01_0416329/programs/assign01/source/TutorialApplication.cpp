////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
////////////////////////////////////////
// Student Name:Alden Rivera
// Student ID:0416329
// Student Email:aldenj.riveraf@gmail.com
//
////////////////////////////////////////
// You can delete everything and start from scratch.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) {}

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
	// add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam1");
	mCamera->setPosition(Vector3(0,350,0.0));
	mCamera->lookAt(Vector3(0.0001,0,0.0));

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
    // add your own stuff
	mCamera = mCameraArr[1];
	Ogre::Viewport* vp1 = mWindow->addViewport(mCamera,1,0.75,0.0,0.25,0.25);
	vp1->setBackgroundColour(ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp1->getActualWidth())/Ogre::Real(vp1->getActualHeight()));

	mViewportArr[1] = vp1;
	vp1->setOverlaysEnabled(false);
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];

    // add your own stuff
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground",
ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					 plane,
					 1500,1500,
					 20,20,
					 true,
					 1,
					 5,5,
					 Vector3::UNIT_Z
					 );
	Entity *groundEnt = mSceneMgr->createEntity("GroundEntity", "ground");
	Entity *penguin1 = mSceneMgr->createEntity("Penguin1","penguin.mesh");
	Entity *penguin2 = mSceneMgr->createEntity("Penguin2","penguin.mesh");
	SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("rootNode");
	node1->attachObject(groundEnt);
	SceneNode *node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node2->attachObject(penguin1);
	node2->setScale(2,3,2);
	node2->setPosition(0,50,0);
	SceneNode *node3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node3->attachObject(penguin2);
	node3->setPosition(150,20,0);
	node3->yaw(Degree(-90));
	int numCubes = 72;
	int L=255;
	for(int i = 0; i <numCubes;i++)
	{
		String name;
		genNameUsingIndex("c",i,name);
		Entity *ent = mSceneMgr->createEntity(name,"cube.mesh");
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		AxisAlignedBox bb = ent->getBoundingBox();
		int cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		int x = 0, y = 0, z = -125;
		SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode -> attachObject(ent);
		float fx = i/(double)(numCubes-1);
		float h = (1+sin(fx*PI*4))*50;
		float circle_radius = 100;
		float x1 = circle_radius*cos(fx*PI*2);
		float z1 = circle_radius*sin(fx*PI*2);
		float unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x1, 50, z1);
	}

	for(int i=0;i<numCubes;i++)
	{
		String name;
		genNameUsingIndex("d",i,name);
		Entity *ent = mSceneMgr->createEntity(name,"cube.mesh");
		ent->setMaterialName("Examples/Chrome");
		AxisAlignedBox bb = ent->getBoundingBox();
		int cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode -> attachObject(ent);
		int z=125;
		float fx = 2*i/(double)(numCubes-1);
		float x = fx*L - L/2.0;
		float h = (1+cos(fx*3.1415*2.0))*20;
		float unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF,h/cubeSize, unitF);
		snode->setPosition(x, 20, z);
	}
	Light *light1 = mSceneMgr->createLight("Light1");
	light1->setType(Light::LT_POINT);
	light1->setPosition(Vector3(150,250,100));
	light1->setDiffuseColour(0.0,1.0,0.0);
	light1->setSpecularColour(0.0,1.0,0.0);

	Light *light2 = mSceneMgr->createLight("Light2");
	light2->setType(Light::LT_POINT);
	light2->setPosition(Vector3(-150,300,250));
	light2->setDiffuseColour(0.5,0.5,.5);
	light2->setSpecularColour(0.5,0.5,0.5);

	penguin1->setCastShadows(true);
	penguin2->setCastShadows(true);




    /*
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);
    */
}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
	mSceneMgr = mSceneMgrArr[1];

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0,0.0,0.0));
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground",
ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					 plane,
					 1500,1500,
					 20,20,
					 true,
					 1,
					 5,5,
					 Vector3::UNIT_Z
					 );
	Entity *groundEnt = mSceneMgr->createEntity("GroundEntity", "ground");
	SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("rootNode");
	node1->attachObject(groundEnt);
	

	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	Entity *cube = mSceneMgr->createEntity("cube","cube.mesh");
	cube->setMaterialName("Examples/green");
	SceneNode *node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node2->attachObject(cube);
	node2->setScale(1.5,2,1);
	node2->setPosition(50,0,0);
	
	
	Light *light1 = mSceneMgr->createLight("Light1");
	light1->setType(Light::LT_POINT);
	light1->setPosition(Vector3(100,150,250));
	light1->setDiffuseColour(0.0,0.0,1.0);
	light1->setSpecularColour(0.0,0.0,1.0);

	cube->setCastShadows(true);

}

void BasicTutorial_00::createViewports(void)
{
    //Do not modify
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
    //Do not modify
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
   
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
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
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
		mCameraMan->getCamera()->setPosition(Vector3(-1463.00,606.45,-513.24));
		mCameraMan->getCamera()->setDirection(Vector3(0.88,-0.47,0.10));
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
		mCameraMan->getCamera()->setPosition(Vector3(-1356.16,634.32,-964.51));
		mCameraMan->getCamera()->setDirection(Vector3(0.71,-0.44,0.55));
        //-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
		mCameraMan->getCamera()->setPosition(Vector3(40.39,155.23,251.20));
		mCameraMan->getCamera()->setDirection(Vector3(-0.02, -0.41, -0.91));
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
		mCameraMan->getCamera()->setPosition(Vector3(19.94,822.63,30.79));
		mCameraMan->getCamera()->setDirection(Vector3(0.00,-0.99,-0.11));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    if (arg.key == OIS::KC_M ) {
        
       Camera *camera1 = mCameraArr[0];
	   Camera *camera2 = mCameraArr[1];
       mWindow->removeViewport(mViewportArr[0]->getZOrder());
	   mWindow->removeViewport(mViewportArr[1]->getZOrder());
	Ogre::Viewport* vp = mWindow->addViewport(camera2);
	vp->setBackgroundColour(Ogre::ColourValue(1.0,1.0,1.0));
	camera2->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
   //delete mViewportArr[0];    // program crashes
    mViewportArr[0] = vp;       // make sure to save the new pointer
	Ogre::Viewport* vp1=mWindow->addViewport(camera1,1,0.75,0,0.25,0.25);
	vp1->setBackgroundColour(Ogre::ColourValue(1.0,0,1.0));
	vp1->setOverlaysEnabled(false);
	camera1->setAspectRatio(Ogre::Real(vp1->getActualWidth())/Ogre::Real(vp1->getActualHeight()));
	mViewportArr[1]=vp1;
    }

    if (arg.key == OIS::KC_N ) {
        // add your own stuff
		Camera *camera1 = mCameraArr[0];
		Camera *camera2 = mCameraArr[1];
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());
		Ogre::Viewport* vp = mWindow->addViewport(camera1);
		vp->setBackgroundColour(Ogre::ColourValue(0,1.0,0));

		camera1->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
		mViewportArr[0]=vp;
		Ogre::Viewport* vp1=mWindow->addViewport(camera2,1,0.75,0,0.25,0.25);
		vp1->setBackgroundColour(Ogre::ColourValue(0,0,1.0));
		vp1->setOverlaysEnabled(false);
		camera2->setAspectRatio(Ogre::Real(vp1->getActualWidth())/Ogre::Real(vp1->getActualHeight()));
		mViewportArr[1]=vp1;
    }

    // Do not delete this line
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
    // add your own stuff
    //
	

    return flg;
}


int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
