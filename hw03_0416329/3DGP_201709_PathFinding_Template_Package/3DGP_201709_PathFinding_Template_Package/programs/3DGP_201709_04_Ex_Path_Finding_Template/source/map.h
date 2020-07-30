#ifndef __MAP_H__
#define __MAP_H__

#include "BasicTools.h"
#include <vector>

#define MAX_NX 50
#define MAX_NZ 50

using namespace std;

class MapNode {
public:
    MapNode( ) { ix = iz = -1; parent = 0; flgCanMove = true; } 
    int ix, iz;
    Vector3 position;
    bool flgCanMove;
    //
    double f, g, h; // cost value
    //
    MapNode *parent;
    void setParent( MapNode *parent ) { this->parent = parent; }
    bool updateCost( double g, double h ) {
        bool flgBetter = false;
        if ( this->g < 0.0 ) { flgBetter = true; this->g = g; }
        if ( this->h < 0.0 ) { flgBetter = true; this->h = h; }
        if ( flgBetter ) {
            f = g + h;
        } else {
            if ( f > g + h ) {
                flgBetter = true;
                this->g = g;
                this->h = h;
                f = g + h;
            } else {
            }
        }
        return flgBetter;
    }
};

class MAP {
protected:
    Vector3 mDWidth;
    int mNX, mNZ;
    Vector3 mMinSpace;
    Vector3 mMaxSpace;
    SceneNode **mSceneNodes;
    Entity **mEntitys;

    int mMaxNumOfPathPoints;
     std::vector<SceneNode*> mSceneNodes_Path;
    Entity **mEntitys_Path;
    //
    MapNode *mStartNode, *mGoalNode;
    MapNode mMapNodes[MAX_NX][MAX_NZ];
    //
    std::vector<Vector3> mPathPoints;
    //
    std::vector<MapNode*> mOpenList;
    std::vector<MapNode*> mClosedList;

public:
    MAP( );
    
    void setDimension( int nx, int nz );
    void generateMap( SceneManager* mSceneMgr );
    bool performPathFinding( const Vector3 &p, const Vector3 &q ,SceneManager* mSceneMgr);
	void showPath(SceneManager* mSceneMgr,int index);
std::vector<Vector3> getPathPoints( ) const;
protected:
    void reset( );
void computeIndices( const Vector3 &p, int &ix, int &iz ) const;
void setPathPoint( int index, int ix, int iz,SceneManager* mSceneMgr);
//void showPath(SceneManager* mSceneMgr,int index);
Vector3 computePointPosition( int ix, int iz ) const;

void constructPathPoints( int goal_ix, int goal_iz );
void constructPathPoints( MapNode *node );
void performAStarPathFinding( );
void clearAllCosts(SceneManager* mSceneMgr );
double getCostBetweenTwoNodes( const MapNode *p0, const MapNode *p1 ) const; 
MapNode *getNodeFromOpenList( );
void computeNeighbor( MapNode *node, std::vector<MapNode *> &neightbors);
void removeNodeFromOpenList( MapNode *node );
void removeNodeFromClosedList( MapNode *node );
void addNodeToOpenList( MapNode *node );
void setPathPoint( int index, const Vector3 &position );
void setInvisibleAllPathPoints( );

};
#endif