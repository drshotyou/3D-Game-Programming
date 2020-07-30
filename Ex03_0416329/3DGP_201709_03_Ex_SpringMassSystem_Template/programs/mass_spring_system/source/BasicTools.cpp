#include "BasicTools.h"

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}

void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB)
{
    //Vector3 posA = nodeA->getPosition();
    //Vector3 posB = nodeB->getPosition();
    //float R = rA + rB;

}
