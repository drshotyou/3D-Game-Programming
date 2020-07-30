#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

using namespace Ogre;
extern void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name);

extern void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB);

extern void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB
    );
#endif