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

const float PI = 3.141592654;

float ci=0;
Light *light;
Vector3 lightPos,rDest; 
Ray rightClick;
bool pressed=false,rPressed=false,arrived=false;
SceneQueryResult fResult;
RaySceneQueryResult rfResult;

BasicTutorial_00::BasicTutorial_00(void) {
mSound = new SOUND;
	mSound->init();
	mFlgAllReached=false;
	mSound->play();
	mCurrentObject=0;
}

void BasicTutorial_00::createCamera(void)
{
	mSceneMgrArr[0] = mRoot->createSceneManager(ST_GENERIC,"primary");
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCamera");

	mCamera->setPosition(Ogre::Vector3(0,700,800));
	mCamera->lookAt(Ogre::Vector3(0,0,0));

	mCamera->setNearClipDistance(5);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createViewports(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp;
	// Create one viewport, entire window
	vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
void BasicTutorial_00::resolveCollision()
{
	int num = 10;
	for(int i=0;i<num;i++)
	{
		void resolveCollisionSmallRobots();
		void resolveCollisionSmallBigRobots();
		void resolveCollisionSmallSphere();
		void resolveCollisionBigSphere();
	}
}
void BasicTutorial_00::resolveCollisionSmallRobots()
{
	int totalRobots=25;
	float rR=20;
	for(int i=0;i<totalRobots;i++)
	{
		for(int j=i+1;j<totalRobots;j++)
		{
			resolveCollision(mSceneNode[i],mSceneNode[j],rR,rR);
		}
	}
	totalRobots+=25;
	for(int i=25;i<totalRobots;i++)
	{
		for(int j=i+1;j<totalRobots;j++)
		{
			resolveCollision(mSceneNode[i],mSceneNode[j],rR,rR);
		}
	}
}

void BasicTutorial_00::resolveCollisionSmallBigRobots()
{
	int totalRobots=49;
	float sR=20,bR=40;
	for (int i=0;i<totalRobots;i++)
	{
		resolveCollision(mSceneNode[24],mSceneNode[i],bR,sR,2,1);
	}
}
void BasicTutorial_00::resolveCollisionSmallSphere()
{
	int totalRobots=25;
	float sR=20,bR=40;
	for(int i=0;i<totalRobots;i++)
	{
		resolveCollision(mSceneNode[50],mSceneNode[i],bR,sR,2,1);
	}
	totalRobots+=25;
	for(int i=25;i<totalRobots;i++)
	{
		resolveCollision(mSceneNode[50],mSceneNode[i],bR,sR,2,1);
	}
}
void BasicTutorial_00::resolveCollisionBigSphere()
{
	float bR=40,cR=70;
	resolveCollision(mSceneNode[24],mSceneNode[50],bR,cR,1,2);
}
void BasicTutorial_00::resolveCollision(SceneNode *nodeA, SceneNode *nodeB, float rA, float rB)
{
	Vector3 posA = nodeA->getPosition();
    Vector3 posB = nodeB->getPosition();
	Vector3 l = posA - posB;

	float R = rA + rB;
	if(R>l.length())
	{
		l.normalise();
		posA+=l;
		posB-=l;
	}
	nodeA->setPosition(posA);
	nodeB->setPosition(posB);

}
void BasicTutorial_00::resolveCollision(SceneNode *nodeA,SceneNode *nodeB, float rA, float rB,float wA, float wB)
{
	Vector3 posA = nodeA->getPosition();
    Vector3 posB = nodeB->getPosition();
	Vector3 l = posA - posB;

	float R = rA + rB;
	if(R>l.length())
	{
		if(wA>wB)
		{
			posB-=l;
		}
		if(wA<wB)
		{
			posA+=l;
		}
	}
	nodeA->setPosition(posA);
	nodeB->setPosition(posB);

}

void BasicTutorial_00::createScene(void) 
{
	//mouse rectangle
	mSelectionRect = new SelectionRectangle("selectionRect");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mSelectionRect);
	mSelectionRect->setLightMask(0);
	mSelectionRect->setCastShadows(false);
	PlaneBoundedVolumeList volList;
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);

	//plane
	mSceneMgr=mSceneMgrArr[0];
	mSceneMgr->setAmbientLight( ColourValue( 0.9, 0.9, 0.9 ) );
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
	SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("rootNode");
	node1->attachObject(groundEnt);
	groundEnt->setMaterialName("Examples/Rocky");
	ColourValue fadeColour(255,255,255);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	mSceneMgr->setFog(FOG_LINEAR,fadeColour,0,1400,1600);
	mSceneMgr->setSkyBox(true,"Examples/TrippySkyBox");
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	//create Robots
	int numRobots=25;
	float radius1=200;
	float radius2=300;
	for(int i = 0;i<numRobots-1;i++)
	{
		String name;
		genNameUsingIndex("d",i,name);
		mEntity[i] = mSceneMgr->createEntity(name,"robot.mesh");
		AxisAlignedBox bb = mEntity[i]->getBoundingBox();
		int robotSize = bb.getMaximum().x - bb.getMinimum().x;
		int x =0, y=0, z=-125;
		mSceneNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNode[i] -> attachObject(mEntity[i]);
		float fx = i/(double)(numRobots-1);
		float x1 = radius1*cos(fx*PI*2);
		float z1 = radius1*sin(fx*PI*2);
		mSceneNode[i]->setPosition(x1,0,z1);
		mSceneNode[i]->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::UNIT_X);
		mEntity[i]->setCastShadows(true);
	}
	for(int i = 24;i<24+numRobots-1;i++)
	{
		String name2;
		genNameUsingIndex("e",i,name2);
		mEntity[i] = mSceneMgr->createEntity(name2,"robot.mesh");
		AxisAlignedBox bb = mEntity[i]->getBoundingBox();
		int robotSize = bb.getMaximum().x - bb.getMinimum().x;
		int x =0, y=0, z=-125;
		mSceneNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNode[i] -> attachObject(mEntity[i]);
		float fx = i/(double)(numRobots-1);
		float x1 = radius2*cos(fx*PI*2);
		float z1 = radius2*sin(fx*PI*2);
		if(i==24)
		{
			mSceneNode[i]->scale(2,2,2);
		}
		mSceneNode[i]->setPosition(x1,0,z1);
		mSceneNode[i]->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::UNIT_X);
		mEntity[i]->setCastShadows(true);
	}
	mEntity[50] = mSceneMgr->createEntity("sphere","sphere.mesh");
	mSceneNode[50] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mSceneNode[50]->attachObject(mEntity[50]);
	mEntity[50]->setMaterialName("Examples/RustySteel");
	mSceneNode[50]->scale(0.70,0.70,0.70);
	mEntity[50]->setCastShadows(true);
	//particle
	initParticleSystemForExplosion(); 
    Vector3 pos = mSceneNode[24]->getPosition();
	setOffParticleSystem(mParticleNode, "explosion", pos);
	
	//light
	light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setDirection(0,0,0);
	SceneNode * lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("movingLight");
	lightNode->attachObject(light);
	//light->setPosition(Vector3(650,0,0));

}
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	if(pressed == true){
	Ray mRay =mTrayMgr->getCursorRay(mCamera);
	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;
	top = scn.y;
	mSelectionRect->setCorners(left, top, right, bottom);
	mSelectionRect->setVisible(true);
	return BaseApplication::mouseMoved( arg);
	}
	else
	{
			return BaseApplication::mouseMoved( arg);
	}

	return BaseApplication::mouseMoved( arg);

}

//void BasicTutorial_00::singleClickSelect ( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
//{
//}

//void BasicTutorial_00::volumeSelect(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
//{
//}

bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	
	pressed = false;
	mSelectionRect->setVisible(false);

	if (left==right && top==bottom) {
		return BaseApplication::mouseReleased( arg, id );
		
	}
	/* CEGUI
	Ray topLeft = mCamera->getCameraToViewportRay(left, top);
	Ray topRight = mCamera->getCameraToViewportRay(right, top);
	Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
	Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);
	*/
	
	//USING mTrayMgr=============
	Real nleft = left;
	Real nright = right;
	Real ntop = 1+top;
	Real nbottom = 1+bottom;
	//Left = Xmin
	//Right= Xmax
	//Bottom=Ymin
	//Top = Ymax
	
	Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, ntop));
	Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, ntop));
	Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, nbottom));
	Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, nbottom));
	//End Using mTrayMgr=============

	// The plane faces the counter clockwise position.
	PlaneBoundedVolume vol,vol2;
	int np = 100;
	vol.planes.push_back(Plane(topLeft.getPoint(3), topRight.getPoint(3), bottomRight.getPoint(3)));         // front plane
	vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(np), topRight.getPoint(np)));         // top plane
	vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(np), 	topLeft.getPoint(np)));       // left plane
	vol.planes.push_back(Plane(bottomLeft.getOrigin(), bottomRight.getPoint(np), 	bottomLeft.getPoint(np)));   // bottom plane
	vol.planes.push_back(Plane(bottomRight.getOrigin(), topRight.getPoint(np), 	bottomRight.getPoint(np)));     // right plane 

	vol2.planes.push_back(Plane(bottomRight.getPoint(3), topRight.getPoint(3),topLeft.getPoint(3)));         // front plane
	vol2.planes.push_back(Plane(topRight.getPoint(np), topLeft.getPoint(np), topLeft.getOrigin()));         // top plane
	vol2.planes.push_back(Plane(	topLeft.getPoint(np), bottomLeft.getPoint(np),topLeft.getOrigin() ));       // left plane
	vol2.planes.push_back(Plane(	bottomLeft.getPoint(np), bottomRight.getPoint(np), bottomLeft.getOrigin()));   // bottom plane
	vol2.planes.push_back(Plane(	bottomRight.getPoint(np), topRight.getPoint(np),bottomRight.getOrigin()));     // right plane 

	PlaneBoundedVolumeList volList;
	volList.push_back(vol);
	volList.push_back(vol2);
	mVolQuery->setVolumes(volList);

	SceneQueryResult result = mVolQuery->execute();
	fResult=result;
	SceneQueryResultMovableList::iterator itr = result.movables.begin();

	for(int i= 0 ; i<24; i++)
	{
		//String name;
		//genNameUsingIndex("d",i,name);
		SceneNode *snode = mSceneNode[i];
		snode->showBoundingBox(false);
	}
	for(int i=24;i<48;i++)
	{
		//String name2;
		//genNameUsingIndex("e",i,name2);
		SceneNode *snode2 = mSceneNode[i];
		snode2->showBoundingBox(false);
	}

	// Get the results, set the camera height
	// We are interested in the first intersection. It is ok to traverse all the results.
	for (itr = result.movables.begin(); itr != result.movables.end(); ++itr)
	{
		if (*itr)
		{
			mCurrentObject = (*itr)->getParentSceneNode();
			bool flgShow = mCurrentObject->getShowBoundingBox();
			mCurrentObject->showBoundingBox(/*!flgShow*/true);
		}
	}
	

	SceneNode *snode3= mSceneNode[50];
	snode3->showBoundingBox(false);
	//SceneNode plane=mSceneMgr->getSceneNode("ground");
	
	return BaseApplication::mouseReleased( arg, id );
}

bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (id == OIS::MB_Left)
	{
	pressed = true;

	Ray mRay =mTrayMgr->getCursorRay(mCamera);

	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;  // (left, top) = (scn.x, scn.y)
	top = scn.y;

	right = scn.x;
	bottom = scn.y;

	mSelectionRect->setCorners(left, top, right, bottom);

	mRay =mTrayMgr->getCursorRay(mCamera);

	RaySceneQuery *mRaySceneQuery = mSceneMgr->createRayQuery ( Ray() ); 

	mRaySceneQuery->setSortByDistance(true); 

	mRaySceneQuery->setRay(mRay);
	
	
	// Perform the scene query
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	rfResult=result;
	RaySceneQueryResult::iterator itr = result.begin();

	for(int i= 0 ; i<24; i++)
	{
		//String name;
		//genNameUsingIndex("d",i,name);
		SceneNode *snode = mSceneNode[i];
		snode->showBoundingBox(false);
	}
	for(int i=24;i<48;i++)
	{
		//String name2;
		//genNameUsingIndex("e",i,name2);
		SceneNode *snode2 = mSceneNode[i];
		snode2->showBoundingBox(false);
	}
	
	for (itr = result.begin(); itr != result.end(); itr++)
	{
		
		if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[")
		{
			mCurrentObject = itr->movable->getParentSceneNode();
			bool flgShow = mCurrentObject->getShowBoundingBox();
			mCurrentObject->showBoundingBox(!flgShow);
			break;
		} 
		else if (itr->worldFragment) {
			//
		}
	}

	SceneNode *snode3= mSceneNode[50];
	snode3->showBoundingBox(false);
	}
	if (id == OIS::MB_Right) {
		Ray mRay =mTrayMgr->getCursorRay(mCamera);
		rPressed=true;
		rightClick = mRay;
		return BaseApplication::mousePressed( arg, id );
	}
	return BaseApplication::mousePressed( arg, id );
}

bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	SceneNode *node1 = mSceneMgr->getSceneNode("movingLight");
	bool flg=Ogre::FrameListener::frameStarted(evt);
	ci+=2*PI/(360*10);
	if(ci>=2*PI)
	{
		ci=0;
	}
	float cx1 = 450*cos(ci);
	float cz1 = 450*sin(ci);
	//cout <<"ci" << ci << endl;
	//cout <<"cx1" << cx1 << endl;
	//cout <<"cz1" << cz1 << endl;
	lightPos.x=cx1;
	lightPos.y=350;
	lightPos.z=cz1;
	node1->setPosition(lightPos);
	if(rPressed==true)
	{
		//rDest=rightClick;
		
		for (int i=0;i<48;i++)
		{
			if (mSceneNode[i]->getShowBoundingBox()==true && rPressed==true)
			{
				
				Vector3 current,dist;
				
				current=mSceneNode[i]->getPosition();
				Plane p(Vector3(0,1,0),0);
				pair<bool,Real> result = rightClick.intersects(p);
				rDest=rightClick.getPoint(result.second);
				dist=rDest-current;
				dist.normalise();
				current+=dist;
				mSceneNode[i]->setPosition(current);
				if(rDest<current)
				{
					arrived=true;
					rPressed=false;
					mSound->play();
				}
			}
		}
		
	}
	void resolveCollision();
	
    return flg;
}

void BasicTutorial_00::initParticleSystemForExplosion() {
	mParticleNode = static_cast<SceneNode*>(
		mSceneMgr->getRootSceneNode()->createChild());
	ParticleSystem* p = mSceneMgr->createParticleSystem(
		"explosion", "Examples/GreenyNimbus");

	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(false);
	mParticleNode->attachObject(p);
	mParticleNode->setPosition(Vector3::ZERO);
	mParticleNode->setVisible(false);
}

void BasicTutorial_00::setOffParticleSystem(
	Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos) 
{
	fNode->setPosition(pos);
	fNode->setVisible(true);
	MovableObject *s = fNode->getAttachedObject(pname);
	ParticleSystem* p =static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}








