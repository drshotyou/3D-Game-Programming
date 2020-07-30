//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Alden Rivera/MingWen
\n
My ID: 0416329
\n
My Email: aldenj.riveraf@gmail.com
\n Date: 2017/10/07

This is an assignment of 3D Game Programming
*/



#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
/*!******************************************
\brief Calls our createViewport_## functions
*********************************************/
	virtual void createViewports(void);
/*!***************************************************************************
\brief Calls our createSceme_## functions, loads the Scene Manager and Camera
******************************************************************************/
	virtual void createScene(void);
/*!*******************************************************************
\brief Calls our createCamera_## functions and loads them accordingly
**********************************************************************/
	virtual void createCamera(void);
/*!**********************************************************************
\brief Creates scene managers and stores them in the Scene manager array
*************************************************************************/
	virtual void chooseSceneManager(void);
/*!*******************************************
\brief Manages the penguin animation
**********************************************/
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
    // Add your own stuff.
    //
protected:

/*!********************************************
\brief Create the main viewport of our program
***********************************************/
	void createViewport_00(void);
/*!**************************************************
\brief Creates the secondary viewport of our program
*****************************************************/
	void createViewport_01(void);
	//
/*!*****************************************************************************************************
\brief Creates the camera for our default scene and saves it on the first position of our Camera array
********************************************************************************************************/
	void createCamera_00();
/*!****************************************************************************************************
\brief Creates the camera for our second viewport and stores it on the second spot of our camera array
*******************************************************************************************************/
	void createCamera_01();
/*!***************************************************************************************************************
\brief We create our main scene,add our entities and attach them to their proper nodes and the lighting our scene
******************************************************************************************************************/
	void createScene_00();
/*!***********************************************************************************************************************************
*--Create our second scene which we look at from our secondary viewport, add our entities ,attach them to the node tree and add lights
**************************************************************************************************************************************/
	void createScene_01();
/*!**********************************************************************************************************************************
\brief "Listens" to keys pressed and proceeds to do their function(1->5 change camera angles, N and M interchange viewport positions)
*************************************************************************************************************************************/
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    //
    // Add your own stuff.
    //
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
    // Add your own stuff.
    //
};


#endif // #ifndef __BasicTutorial_00_h_